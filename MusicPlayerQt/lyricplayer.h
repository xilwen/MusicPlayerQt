#ifndef LYRICPLAYER_H
#define LYRICPLAYER_H

#include <string>
#include <deque>
#include <cctype>
#include <QObject>
#include <QFile>
#include <QDebug>
#include "timer.h"

class LyricPlayer : public QObject
{
    Q_OBJECT
public:
    LyricPlayer() = delete;
    LyricPlayer(Timer& _timer);
    void LoadFile(const std::string& in);
    void PlayLyric();
    bool isPlaying();
    bool isAvailable();
    void Stop();

signals:
    void lyricChanged(const std::deque<std::string>& newLyricStage);

private:
    struct DynaLyric
    {
        int second;
        std::string text;
    };

    std::string filename;
    std::deque<DynaLyric> lyricBase;

    bool stop = false;
    bool playing = false;
    bool available = false;
    Timer& timer;

    void LyricParser(QFile& in);
};

#endif // LYRICPLAYER_H
