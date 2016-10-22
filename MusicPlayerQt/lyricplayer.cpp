#include "lyricplayer.h"

LyricPlayer::LyricPlayer(Timer& _timer): timer(_timer)
{

}

void LyricPlayer::LoadFile(const std::string& in)
{
    lyricBase.clear();

    filename = in;
    filename.resize(in.size() - 3);
    filename += "lrc";

    QFile inFile(filename.c_str());

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qInfo() << "Cannot open LRC file.";
        available = false;
    }
    else
    {
        LyricParser(inFile);
        inFile.close();
        available = true;
    }
}

void LyricPlayer::LyricParser(QFile& inFile)
{
    QTextStream in(&inFile);
    char tmpChar0, tmpChar1, tmpChar2, tmpChar3;
    int tmpInt0, tmpInt1, tmpInt2;

    std::string tmpString;
    while(in.atEnd() == false)
    {
        in >> tmpChar0 >> tmpInt0 >> tmpChar1 >> tmpInt1 >> tmpChar2 >> tmpInt2 >> tmpChar3;
        tmpString = in.readLine().toStdString();
        lyricBase.push_back({tmpInt0 * 60 + tmpInt1, tmpString});
    }
}

void LyricPlayer::PlayLyric(QLabel* upper, QLabel* mid, QLabel* med)
{
    playing = true;
    unsigned int NextLrcPtr = 2, sec = 0;
    std::deque<std::string> stage;
    stage.resize(3);
    stage[1] = lyricBase[0].text;
    stage[2] = (static_cast<int>(lyricBase.size()) > 1)? lyricBase[1].text : "";
    updateScrn(upper, mid, med, stage);
    stop = false;

    while(NextLrcPtr < lyricBase.size() && stop == false)
    {
        if(sec >= static_cast<unsigned int>(lyricBase.at(NextLrcPtr - 1).second))
        {
            stage.pop_front();
            stage.push_back(lyricBase.at(NextLrcPtr).text);
            updateScrn(upper, mid, med, stage);
            ++NextLrcPtr;
        }
        while(sec == timer.getSecond())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if(sec < timer.getSecond())
            {
                break;
            }
        }
        sec = timer.getSecond();
    }
    playing = false;
}

void LyricPlayer::updateScrn(QLabel* upper, QLabel* mid, QLabel* med, std::deque<std::string>& stage)
{
    upper->setText(stage[0].c_str());
    mid->setText(stage[1].c_str());
    med->setText(stage[2].c_str());
    upper->update();
    mid->update();
    med->update();
}

void LyricPlayer::Stop()
{
    stop = true;
}

bool LyricPlayer::isPlaying()
{
    return playing;
}

bool LyricPlayer::isAvailable()
{
    return available;
}

