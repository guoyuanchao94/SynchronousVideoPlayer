#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    qInfo() << "Server::构造服务端";
}

Server::~Server()
{
    qInfo() << "Server::服务端析构,端口号: " << port << " closed.";
    //清理套接字
    for (auto client : clients)
    {
        client->close();
        client->deleteLater();
        client = nullptr;
    }
    tcpServer->close();
    tcpServer->deleteLater();
    tcpServer = nullptr;
}

void Server::initServer(int port)
{
    qDebug() << "Server::初始化服务端,监听端口" << port;
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
    this->port = port;
    listen();   //开始监听端口
}

void Server::newConnection()
{
    qInfo() << "Server::新连接到达";
    while (tcpServer->hasPendingConnections())
    {
        appendNewConnection(tcpServer->nextPendingConnection());
    }
}

void Server::appendNewConnection(QTcpSocket *client)
{
    qInfo() << "Server::添加新连接: " << client;
    clients.append(client); //保存连接到的客户端
    qDebug() <<"连接到的客户端的数目: " << clients.count();
    connect(client, &QTcpSocket::disconnected, this, &Server::clientDisconnected);  //绑定客户端端口事件
    connect(client, &QTcpSocket::readyRead, this, &Server::readFromClient); // 绑定接收端读取数据的响应函数
    //listClients();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (isSourceSet)    //如果设置了播放源,将播放源发送给其他客户端
    {
        QString type = "src";
        //client是和连接到的客户端通信的套接字,不是客户端本身
        client->write(type.toUtf8() + source.toUtf8() + QString("\n").toUtf8());
        client->flush();
    }
    //send client list to client
    QString clientList = "";
    for (auto myClient : clients)
    {
        //不把服务端的客户端添加进来
        if (myClient->objectName() != "")
        {
            clientList.append(myClient->objectName() + "&&");  //添加客户端带有&&,作为定界符
        }
    }
    clientList.chop(2);//移除最后的定界符
    qDebug() << "Server::打印客户端列表" << clientList;
    if (clientList != QString(""))
    {
        //发送客户端列表,等下客户端受到消息再去分割
        client->write(QString("usrlst").toUtf8() + clientList.toUtf8() + QString("\n").toUtf8());
        client->flush();
    }
}

//发送给所有的客户端
void Server::writeToClients(QString msg, QString type)
{
    qInfo() << "Server::发送给所有的客户端, type: " << type << ",msg: " << msg;
    for (const auto &client: clients)
    {
        QByteArray buffer = type.toUtf8() + msg.toUtf8() + "\n";
        client->write(buffer);  //这里是和连接到服务器的客户端通信,是他们知道有哪些客户端连接
        client->flush();
    }
}

//发送给所有的client除了currrentClient
void Server::writeToClients(QString msg, QString type, QTcpSocket *currentClient)
{
    qInfo() << "Server::发送给除了当前客户端以外的客户端, type: " << type << ", msg: " << msg;
    for (auto client: clients)
    {
        if (client != currentClient)
        {
            QByteArray buffer = type.toUtf8() + msg.toUtf8() + "\n";
            client->write(buffer);
            client->flush();
        }
    }
}

//从clients队列删除断开的client
void Server::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());  //获取发送者
    if(client == nullptr)
    {
        qDebug() << "Server::无法确定发送者";
        return;
    }
    qInfo() << "Server::客户端断开连接,移除客户端: " << client << "IP地址:" << client->peerAddress() << " = " << clients.removeOne(client);
    //让其他客户端也知道这个消息,除了这个断开连接的客户端
    writeToClients("dis" + client->objectName(), "usr", client);
    emit removeUdpClient(client);   //同时也移除UDP客户端
    clients.squeeze();  //移除不存储项的内存
    client->deleteLater();
    client = nullptr;
}

//响应客户端的处理
void Server::readFromClient()
{
    qInfo() << "Server::读取客户端数据";
    //获取发送者
    QTcpSocket *client = reinterpret_cast<QTcpSocket *>(sender());
    while (client->canReadLine())
    {
        QByteArray buffer = client->readLine();
        qDebug() <<"Server::读取到的数据: " << buffer;

        QString header = buffer.mid(0, 3);
        QString content = buffer.mid(3).trimmed();  //去除首尾空格
        qInfo() << "Server::读取客户端数据,header: <<" << header << ", content: " << content;
        if (header == "snc")
        {
            qInfo() << "Server::服务端同步消息来自于" << client->objectName() << " : " << content;
            writeToClients(content, "snc"); //同步给其他的客户端
        }   
        else if (header == "msg")
        {
            //qInfo() << "Message from " << client->objectName() << " : " << content;
            writeToClients(client->objectName() + ": " + content, "msg");
        }   
        else if (header == "usr")
        {
            client->setObjectName(content);
            writeToClients("con" + client->objectName(), "usr");    //连接消息
        }
        else if (header == "src")
        {
            source = content;
            isSourceSet = true;
            QString srcType = content.mid(0, 3);//已经去除了src头部,srcType = net or lcl
            content = content.mid(3);   //去除net or lcl
            qDebug() << "你好" << content;
            if (srcType == "net")
            {
                writeToClients(content, "srcnet");
            }
            if (srcType == "lcl")
            {
               writeToClients(content, "srclcl");
            }
            //writeToClients("New source: " + content, "msg");
            qInfo() << "Server::新播放源: " << content;
        }
        else if (header == "prt")
        {
            qInfo() << "UDPIP地址:" << client->peerAddress() << "udp端口: " << content << "TCP端口: " << client->peerPort() << "客户端名字: " << client->objectName();
            emit addUdpClient(client, client->peerAddress(), content.toUShort());
        }
    }
}

void Server::listen()
{
    tcpServer->listen(QHostAddress::Any, port);
    qInfo() << "Server::开始监听端口号: " << port;
}

void Server::listClients()
{
    //列出所有client
    for(auto client : clients)
    {
        qInfo() << client;
    }
}
