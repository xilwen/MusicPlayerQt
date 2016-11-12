import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    visible: true
    minimumWidth: 600
    minimumHeight: 235
    title: qsTr("MusicPlayerQt")
    Material.theme: Material.Dark
    Material.accent: Material.BlueGrey
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    Label {
        id: songTitleLabel
        objectName: "songTitleLabel"
        x: 19
        y: 12
        width: 450
        height: 32
        text: qsTr("songTitleLabel")
        font.pointSize: 20
        font.family: "Microsoft JhengHei UI"

    }

    Label {
        id: songAlbumLabel
        objectName:"songAlbumLabel"
        x: 19
        y: 48
        width: 450
        height: 19
        text: qsTr("songAlbumLabel")
        font.pointSize: 12
        font.family: "Microsoft JhengHei UI"
    }

    Button {
        id: openFileButton
        objectName: "openFileButton"
        x: 482
        y: 12
        width: 100
        height: 50
        text: qsTr("開啟")
        font.family: "Microsoft JhengHei UI"
        onClicked: {
            mainWindow.on_OpenFileButton_clicked()
        }
    }

    Button {
        id: playControlButton
        objectName: "playControlButton"
        x: 19
        y: 169
        width: 100
        text: qsTr("播放/停止")
        font.family: "Microsoft JhengHei UI"
        onClicked:  mainWindow.on_PlayControlButton_clicked()
    }

    Label {
        id: lyricLabel0
        objectName: "lyricLabel0"
        x: 19
        y: 87
        width: 500
        text: qsTr("lyricLabel0")
        font.family: "Microsoft JhengHei UI"
    }

    Label {
        id: lyricLabel1
        objectName: "lyricLabel1"
        x: 19
        y: 112
        width: 500
        text: qsTr("lyricLabel1")
        font.family: "Microsoft JhengHei UI"
    }

    Label {
        id: lyricLabel2
        objectName: "lyricLabel2"
        x: 19
        y: 136
        width: 500
        text: qsTr("lyricLabel2")
        font.family: "Microsoft JhengHei UI"
    }

    ProgressBar {
        id: progressBar1
        objectName: "progressBar1"
        x: 149
        y: 187
        width: 350
        height: 5
        indeterminate: true
        value: 0.5
    }

    Label {
        id: timerLabel
        objectName: "timerLabel"
        x: 517
        y: 182
        text: qsTr("00:00")
        font.family: "Microsoft JhengHei UI"
    }

}

