#ifndef LYRICPLAYER_H
#define LYRICPLAYER_H

#include <string>
#include <deque>
#include <cctype>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include "timer.h"

class LyricPlayer
{
public:
    LyricPlayer() = delete;
    LyricPlayer(Timer& _timer);
    void LoadFile(const std::string& in);
    void PlayLyric(QLabel* upper, QLabel* mid, QLabel* med);
    bool isPlaying();
    void Stop();
private:
    struct DynaLyric
    {
        int second;
        std::string text;
    };

    std::string filename;
    std::deque<DynaLyric> lyricBase;

    bool stop;
    bool playing;
    Timer& timer;

    void LyricParser(QFile& in);
    void updateScrn(QLabel* upper, QLabel* mid, QLabel* med, std::deque<std::string>& stage);

};

#endif // LYRICPLAYER_H
