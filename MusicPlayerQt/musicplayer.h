#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QMediaPlayer>
#include <QFileDialog>
#include <QMediaMetaData>
#include <string>

class MusicPlayer
{
public:
    MusicPlayer();
    void playFile();
    void stopFile();
    void openFile(const std::string& fileName);
    void closeFile();
    bool isPlaying();
    QString getSongTitle();
    QString getSongAlbum();
    int getSongDurationInSecond();

private:
    QMediaPlayer player;
    std::string fileName;
};

#endif // MUSICPLAYER_H
