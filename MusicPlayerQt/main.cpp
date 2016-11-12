#include "mainwindow.h"
#include <QObject>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlProperty>
#include "mainwindow.h"
#include "musicplayer.h"
#include "timer.h"
#include "lyricplayer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    QObject* object = QQmlComponent(&engine, QUrl(QLatin1String("qrc:/main.qml"))).create();
    MainWindow mainWindow(object);
    engine.rootContext()->setContextProperty("mainWindow", &mainWindow);

    return app.exec();
}
