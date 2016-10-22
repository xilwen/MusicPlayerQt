#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    lyric = new LyricPlayer(timer);
    LoadDarkStylesheet();
    window()->setFixedSize( window()->sizeHint() );
    ui->setupUi(this);
    clearLabels();
}

MainWindow::~MainWindow()
{
    delete lyric;
    delete ui;
}

void MainWindow::LoadDarkStylesheet()
{
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        qInfo() <<"Unable to set stylesheet, file not found\n";
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
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
        ui->PlayControlButton->clicked(); //workaround for Qt not detecting metadata
        ui->PlayControlButton->setFocus();
    }
}


void MainWindow::on_PlayControlButton_clicked()
{
    if(fileName.size() == 0)
    {
        ui->OpenFileButton->clicked();
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
    ui->PlayControlButton->setText("播放");
    player.stopFile();
    timer.stop();
}

void MainWindow::playMusic()
{
    stopMusic();
    clearLabels();
    ui->PlayControlButton->setText("停止");
    try
    {
        player.playFile();
    }
    catch(std::runtime_error e)
    {
        popErrorMsgbox(e.what());
    }

    ui->SongTitleLabel->setText(player.getSongTitle());
    ui->SongAlbumLabel->setText(player.getSongAlbum());

    timer.reset();

    std::thread timeUpdater(&MainWindow::timeLabelUpdater, this);
    timeUpdater.detach();
    if(lyric->isAvailable() == true)
    {
        std::thread lyricUpdater(&LyricPlayer::PlayLyric, lyric, ui->LyricLabel0, ui->LyricLabel1, ui->LyricLabel2);
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
        ui->TimerLabel->setText(out);
        ui->TimerLabel->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    stopMusic();
    timer.stop();
}

void MainWindow::openFile()
{
    fileName = QFileDialog::getOpenFileName(nullptr,"開啟音樂檔案", QDir::currentPath(),"MP3 (*.mp3)").toStdString();
    if(fileName.size() > 0)
    {
        player.openFile(fileName);
        lyric->LoadFile(fileName);
    }
}

void MainWindow::clearLabels()
{
    ui->SongTitleLabel->setFont(QFont("Microsoft JhengHei UI", 20, QFont::Bold));
    ui->SongTitleLabel->setText("");
    ui->SongAlbumLabel->setFont(QFont("Microsoft JhengHei UI", 12, QFont::Normal));
    ui->SongAlbumLabel->setText("");
    ui->TimerLabel->setFont(QFont("Microsoft JhengHei UI", 20, QFont::Normal));
    ui->TimerLabel->setText("");
    ui->LyricLabel0->setText("");
    ui->LyricLabel1->setText("");
    ui->LyricLabel2->setText("");
}


