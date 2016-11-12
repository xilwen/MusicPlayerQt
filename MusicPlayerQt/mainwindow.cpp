#include "mainwindow.h"


MainWindow::MainWindow(QObject* uiObject) : ui(uiObject)
{
    initUIObjects();
    lyric = new LyricPlayer(timer);
    clearLabels();
    qRegisterMetaType<std::deque<std::string> >("std::deque<std::string>");
    connect(lyric, &LyricPlayer::lyricChanged, this,
            &MainWindow::updateLyric);
    connect(this, &MainWindow::timerTickedwithQString, this, &MainWindow::updateTimeLabel);
    connect(this, &MainWindow::timerTicked, this, &MainWindow::updateProgressBar);
}

void MainWindow::initUIObjects()
{
    songTitleLabel = ui->findChild<QObject*>("songTitleLabel");
    songAlbumLabel = ui->findChild<QObject*>("songAlbumLabel");
    openFileButton = ui->findChild<QObject*>("openFileButton");
    playControlButton = ui->findChild<QObject*>("playControlButton");
    lyricLabel0 = ui->findChild<QObject*>("lyricLabel0");
    lyricLabel1 = ui->findChild<QObject*>("lyricLabel1");
    lyricLabel2 = ui->findChild<QObject*>("lyricLabel2");
    progressBar1 = ui->findChild<QObject*>("progressBar1");
    timerLabel = ui->findChild<QObject*>("timerLabel");
}


MainWindow::~MainWindow()
{
    delete lyric;
}

void MainWindow::popErrorMsgbox(QString msg)
{
    QMessageBox errorMsg;
    errorMsg.setText(msg);
    errorMsg.exec();
}

void MainWindow::on_OpenFileButton_clicked()
{
    stopMusic();
    try
    {
        openFile();
        if(fileName.size() > 0)
            player.playFile();
    }
    catch(std::runtime_error e)
    {
        popErrorMsgbox(e.what());
    }
    if(fileName.size() > 0)
    {
       stopMusic();
    }
}

void MainWindow::on_PlayControlButton_clicked()
{
    if(fileName.size() == 0)
    {
        openFile();
        return;
    }
    if(player.isPlaying() == true)
    {
        stopMusic();
    }
    else
    {
        playMusic();
    }
}

void MainWindow::stopMusic()
{
    lyric->Stop();
    while(lyric->isPlaying() == true)
    {
        //wait for lyric player to stop its thread
    }
    if(fileName.size() > 0)
        lyric->LoadFile(fileName);
    playControlButton->setProperty("text", "播放");
    player.stopFile();
    timer.stop();
    progressBar1->setProperty("indeterminate", true);

}

void MainWindow::playMusic()
{
    stopMusic();
    clearLabels();
    progressBar1->setProperty("indeterminate", false);
    playControlButton->setProperty("text", "停止");
    try
    {
        player.playFile();
    }
    catch(std::runtime_error e)
    {
        popErrorMsgbox(e.what());
    }

    songTitleLabel->setProperty("text", player.getSongTitle());
    songAlbumLabel->setProperty("text", player.getSongTitle());

    timer.reset();

    std::thread timeUpdater(&MainWindow::timeLabelUpdater, this);
    timeUpdater.detach();
    if(lyric->isAvailable() == true)
    {
        std::thread lyricUpdater(&LyricPlayer::PlayLyric, lyric);
        lyricUpdater.detach();
    }
}

void MainWindow::timeLabelUpdater()
{
    timer.start();
    unsigned int min, sec, raw;
    std::string outMin, outSec;
    QString out;
    while(player.isPlaying() == true)
    {
        raw = timer.getSecond();
        min = raw / 60;
        sec = raw % 60;
        outMin = (((min < 10)? "0" : "") + std::to_string(min));
        outSec = (((sec < 10)? "0" : "") + std::to_string(sec));
        out = std::string(outMin + ":" + outSec).c_str();
        timerTickedwithQString(out);
        timerTicked(raw);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    stopMusic();
    timer.stop();
}

void MainWindow::openFile()
{
    fileName = QFileDialog::getOpenFileName(NULL,"開啟音樂檔案", QDir::currentPath(),"MP3 (*.mp3)").toStdString();
    if(fileName.size() > 0)
    {
        player.openFile(fileName);
        lyric->LoadFile(fileName);
    }
}

void MainWindow::clearLabels()
{
    songTitleLabel->setProperty("text", "");
    songAlbumLabel->setProperty("text", "");
    timerLabel->setProperty("text", "");
    lyricLabel0->setProperty("text", "");
    lyricLabel1->setProperty("text", "");
    lyricLabel2->setProperty("text", "");
}

void MainWindow::updateLyric(const std::deque<std::string>& newLyricStage)
{
    lyricLabel0->setProperty("text", newLyricStage[0].c_str());
    lyricLabel1->setProperty("text", newLyricStage[1].c_str());
    lyricLabel2->setProperty("text", newLyricStage[2].c_str());
}

void MainWindow::updateTimeLabel(const QString& output)
{
    timerLabel->setProperty("text", output);
}

void MainWindow::updateProgressBar(const int& seconds)
{
    progressBar1->setProperty("value", static_cast<double>(seconds) / static_cast<double>(player.getSongDurationInSecond()));
}




