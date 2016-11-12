#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{

}

void MusicPlayer::openFile(const std::string& fileName)
{
    stopFile();
    this->fileName = fileName;
    player.setMedia(QUrl::fromLocalFile(QString(fileName.c_str())));
    if (player.error() != QMediaPlayer::NoError)
        throw std::runtime_error("QMediaPlayer 回傳錯誤" +
                                 std::to_string(player.error()) + "\n有沒有可能電腦的解碼器沒有裝好呢?");
}

void MusicPlayer::playFile()
{
    if (player.error() != QMediaPlayer::NoError)
        throw std::runtime_error("QMediaPlayer 回傳錯誤" + std::to_string(player.error())+ "\n有沒有可能電腦的解碼器沒有裝好呢?");
    player.play();
}

void MusicPlayer::stopFile()
{
    player.stop();
}

bool MusicPlayer::isPlaying()
{
    if(player.state() == QMediaPlayer::StoppedState)
        return false;
    else
        return true;
}

QString MusicPlayer::getSongTitle()
{
    return player.metaData(QMediaMetaData::Title).toString();
}

QString MusicPlayer::getSongAlbum()
{
    return player.metaData(QMediaMetaData::AlbumTitle).toString();
}

int MusicPlayer::getSongDurationInSecond()
{
    return (player.metaData(QMediaMetaData::Duration).toInt() / 1000);
}
