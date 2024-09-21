#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioSink>
#include <QAudioSource>
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QVideoWidget>
#include <QPushButton>
#include <QDebug>
#include <QThread>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QListWidget>

#include "openurl.h"
#include "setport.h"
#include "server.h"
#include "udpserver.h"
#include "client.h"
#include "udpclient.h"
#include "connecttoserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    void sendTimestampThreaded();
    void sendTimestamp();
    void readFile(const QString &filePath);
    void readDirectoryFilesRecursively(const QString &directoryPath, QVector<QString> &files);
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;
signals:
    void themeChanged(QString theme);
    void signalOpenPath(const QString &filePath);
    void playListItemSetUrl(QString url);  //双击播放列表发射信号
    void setlocalFile(QString filePath);
private slots:
    void on_actionOpen_URL_triggered();
    void setVideoSource(QString url);
    void on_actionStart_Server_triggered();
    void on_actionConnect_to_Server_triggered();
    void fullScreen();
    void playPressed();
    void pausePressed();
    void stopPressed();
    void setUserName(QString userName);
    void on_chatInput_returnPressed();
    void on_sendButton_clicked();
    void newChatMsg(QString msg);
    void connectToLocalHost(int port, QString username);
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void seek(int mseconds);
    void remotePlay(qint64 position);
    void remotePause(qint64 position);
    void remoteStop();
    void remoteSeek(qint64 position);
    void remoteSync(qint64 position);
    void remoteSetVideoSource(QString src);
    void userConnected(QString usrName);
    void userDisconnected(QString usrName);
    void on_volumeSlider_valueChanged(int value);
    void readFromMicrophone();
    void initClientConnections();
    void voiceReceived(QByteArray data);
    void on_muteButton_stateChanged(int arg1);
    // void handleBuffering(QMediaPlayer::MediaStatus status);
    void hostLocalFile(QString file);
    void on_actionObit_triggered();
    void on_actionMyWatch_triggered();
    void on_actionFilmovio_triggered();
    void on_actionCombinear_triggered();
    void on_actionPerstfic_triggered();
    void on_actionVisualScript_triggered();
    void on_actionWstartpage_triggered();
    void remoteSetLocalVideoSource(QString src);
    void setServerURL(QUrl url);
    void on_action_Open_Directory_triggered();
    void on_actOpenLocalFile_triggered();

private:
    Ui::MainWindow *ui;
private:
    QMediaPlayer *player = nullptr;
    QAudioOutput *audioOutput = nullptr;
    QAudioSink *udpAudioSink = nullptr;
    QAudioSource *udpAudioSource = nullptr;
    QIODevice *udpAudioSinkDevice = nullptr;
    QIODevice *udpAudioSourceDevice = nullptr;

    Server *server = nullptr;
    Client *client = nullptr;
    UdpServer *udpServer = nullptr; //接收语音数据
    UdpClient *udpClient = nullptr; //发送语音数据

    bool micMuted = false;
    // bool buffering = false;
    QString serverURL = "";
    QSet<QString> setFilePath;
    QListWidget *playList = nullptr;
private:
    void slotOpenPath(const QString &filePath);
};
#endif // MAINWINDOW_H
