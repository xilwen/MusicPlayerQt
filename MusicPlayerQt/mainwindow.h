#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QLayout>
#include <thread>
#include <string>
#include "musicplayer.h"
#include "timer.h"
#include "lyricplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenFileButton_clicked();

    void on_PlayControlButton_clicked();

private:
    Ui::MainWindow *ui;
    MusicPlayer player;
    Timer timer;
    LyricPlayer* lyric;
    std::string fileName;
    void LoadDarkStylesheet();
    void popErrorMsgbox(QString msg);
    void playMusic();
    void timeLabelUpdater();
    void openFile();
    void stopMusic();
    void clearLabels();
};

#endif // MAINWINDOW_H
