#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QUrl>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
public:
    void waitForConnection();   //等待连接到服务器
    void writeToServer(QString msg, QString type);  //发送消息给服务器,带有消息类型
    void connectToLocalServer(int port);    //连接到本地服务器
    void disconnect();  //断开连接
    QString getPeerIpAddress() const;
signals:
    void newChatMsg(QString msg);
    void remotePlay(qint64 position);
    void remotePause(qint64 position);
    void remoteStop();
    void remoteSeek(qint64 position);
    void remoteSync(qint64 position);
    void remoteSetVideoSource(QString src); //设置播放源
    void remoteSetLocalVideoSource(QString src);
    void userConnected(QString usrName);    //判断哪一个客户端连接到服务端
    void userDisconnected(QString usrName);
public slots:
    void setUdpPort(quint16 udpPort);
    void connectToServer(QUrl url, int port);
private slots:
    void readFromServer();
private:
    QTcpSocket *socket = nullptr;
};

#endif // CLIENT_H
