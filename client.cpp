#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    qInfo() << "Client::构造客户端";
}

Client::~Client()
{
    qInfo() << "Client::析构客户端";
    if(socket)
    {
        socket->close();
        delete socket;
        socket = nullptr;
    }
}

void Client::connectToServer(QUrl url, int port)
{
    qInfo() << "Client::客户端连接到服务器" << url << ":"<< port;
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(url.toString()), port);
    waitForConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Client::readFromServer);
    connect(socket,&QTcpSocket::disconnected,this,[=]()
    {
        qDebug() << "Client::客户端断开连接";
        socket->deleteLater();
        socket = nullptr;
    });
}

void Client::connectToLocalServer(int port)
{
    qDebug() <<"Client::客户端连接到本地服务器,端口号: " << port;
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(QHostAddress::LocalHost), port);
    waitForConnection();
    qDebug() <<"Client::本地客户端连接";
    connect(socket, &QTcpSocket::readyRead, this, &Client::readFromServer);
    connect(socket,&QTcpSocket::disconnected,this,[=]()
    {
        qDebug() << "Client::客户端断开连接";
        socket->deleteLater();
        socket = nullptr;
    });
}

void Client::waitForConnection()
{
    qInfo() << "Client::客户端等待连接";
    if (socket->waitForConnected(-1))
    {
        qDebug("Client::客户端连接成功");
    }
    else
    {
        qDebug()<<"Client::客户端连接失败,失败原因: "<<socket->errorString();
    }
}

//同步消息,聊天消息,用户消息,播放源消息
void Client::writeToServer(QString msg, QString type) //type can be "msg","snc","usr","url"
{
    qInfo() << "Client::发送消息给服务器,msg: " << msg << ",type: " << type;
    QByteArray buffer = type.toUtf8() + msg.toUtf8() + "\n";    //canReadLine,先发送类型
    socket->write(buffer);
    socket->flush();    //立即发送数据
}

void Client::disconnect()
{
    qDebug() << "Client::客户端即将断开连接";
    socket->disconnect();
    socket->disconnectFromHost();
}

QString Client::getPeerIpAddress() const
{
    return socket->peerAddress().toString();
}

void Client::readFromServer()
{
    while (socket->canReadLine())
    {
        QByteArray buffer = socket->readLine();
        qDebug() << "Client::读取缓冲区的内容: " << buffer;
        QString header = buffer.mid(0, 3);
        QString content = buffer.mid(3).trimmed();
        qInfo() << "Client::从服务端读取数据,header: " << header << ", content: " << content;
        if (header == "snc")
        {
            qInfo() << "Client::来自服务端的同步消息: " << content;
            QString syncType = content.mid(0, 4);
            qint64 position = content.mid(4).toLongLong();
            if (syncType == "play")
            {
                emit remotePlay(position);
            }
            else if (syncType == "paus")
            {
                emit remotePause(position);
            }
            else if (syncType == "stop")
            {
                emit remoteStop();
            }
            else if (syncType == "seek")
            {
                emit remoteSeek(position);
            }
            //服务端每一秒的同步消息
            else if (syncType == "sync")
            {
                emit remoteSync(position);
            }
        }
        else if (header == "msg")
        {
            qInfo() << "Client::来自服务端的消息(message): " << content;
            emit newChatMsg(content);
        }
        else if (header == "src")
        {
            QString srcType = content.mid(0, 3);
            content = content.mid(3);
            if (srcType == "net")
            {
                emit remoteSetVideoSource(content);
            }
            if (srcType == "lcl")
            {
                qDebug() << "Client::视频源是本地文件: "<<content;
                emit remoteSetLocalVideoSource(content);
            }
            emit newChatMsg("设置播放源: " + content);   //发送到聊天列表
        }
        else if (header == "usr")
        {
            QString usrType = content.mid(0, 3);
            QString usrName = content.mid(3);
            if (usrType == "con")
            {
                emit userConnected(usrName);
                emit newChatMsg(QString(usrName + " connected."));
            }
            else if (usrType == "dis")
            {
                emit userDisconnected(usrName);
                emit newChatMsg(QString(usrName + " disconnected."));
            }
            else if (usrType == "lst")
            {
                //服务端发送过来的时候,每一个客户端都用&&分割,这里就分割掉&&,获取每一个客户端
                QStringList userList = usrName.split("&&");
                for (auto &user : userList)
                {
                    //用户连接
                    emit userConnected(user);
                }
            }
        }
    }
}

//设置UDP端口
void Client::setUdpPort(quint16 udpPort)
{
    qInfo() << "Client::设置UDP端口: " << udpPort;
    writeToServer(QString::number(udpPort), "prt");
}
