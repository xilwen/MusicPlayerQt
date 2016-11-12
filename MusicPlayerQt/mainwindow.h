#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QLayout>
#include <thread>
#include <string>
#include <deque>
#include "musicplayer.h"
#include "timer.h"
#include "lyricplayer.h"

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow() = delete;
    MainWindow(QObject* uiObject);
    ~MainWindow();
    Q_INVOKABLE void on_OpenFileButton_clicked();
    Q_INVOKABLE void on_PlayControlButton_clicked();

public slots:
    void updateLyric(const std::deque<std::string>& newLyricStage);
    void updateTimeLabel(const QString& output);
    void updateProgressBar(const int& seconds);

signals:
    void timerTickedwithQString(const QString& output);
    void timerTicked(const int& seconds);

private:
    QObject *ui, *songTitleLabel, *songAlbumLabel, *openFileButton,
    *playControlButton, *lyricLabel0, *lyricLabel1, *lyricLabel2, *progressBar1, *timerLabel;
    MusicPlayer player;
    Timer timer;
    LyricPlayer* lyric;
    std::string fileName;
    void popErrorMsgbox(QString msg);
    void playMusic();
    void timeLabelUpdater();
    void openFile();
    void stopMusic();
    void clearLabels();

    void initUIObjects();
};

#endif // MAINWINDOW_H
