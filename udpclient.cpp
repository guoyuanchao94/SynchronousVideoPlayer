#include "udpclient.h"

UdpClient::UdpClient(QObject *parent) : QObject(parent)
{
    qInfo() << "UdpClient::UdpClient";
}

UdpClient::~UdpClient()
{
    qInfo() << "UdpClient::~UdpClient";
    socket->close();
    delete socket;
    socket = nullptr;
}

void UdpClient::udpConnectToLocalServer(int port)
{
    qInfo() << "UdpClient::Udp连接到本地服务器,端口号: " << port;
    socket = new QUdpSocket(this);
    // qInfo() << socket->bind(QHostAddress::LocalHost);
    socket->connectToHost(QHostAddress("127.0.0.1"), port);
    QByteArray data;
    data.append("UDP");
    socket->write(data);
    emit connected();
    emit setUdpPort(socket->localPort());
    qDebug() << "UdpClient::本地端口号是 " << socket->localPort();
    connect(socket, &QUdpSocket::readyRead, this, &UdpClient::udpReadFromServer);
}

void UdpClient::udpConnectToServer(QUrl url, int port)
{
    qInfo() << "UdpClient::Udp连接到服务器,url: " << url <<  ",port: " << port;
    socket = new QUdpSocket(this);
    //qInfo() << socket->bind(QHostAddress::Any);
    if (url.toString() == "127.0.0.1")
    {
        socket->connectToHost(QHostAddress("127.0.0.1"), port);
    }
    else
    {
        //也可能是服务端的IP地址
        socket->connectToHost(QHostAddress(url.toString()), port);
    }
    QByteArray data;
    data.append("UDP");
    socket->write(data);
    emit connected();
    emit setUdpPort(socket->localPort());   //发射当前udpsocket分配的端口号
    connect(socket, &QUdpSocket::readyRead, this, &UdpClient::udpReadFromServer);
}

void UdpClient::udpReadFromServer()
{
    while (socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        emit voiceReceived(datagram.data());
    }
}

void UdpClient::udpWriteToServer(QByteArray data)
{
    if (socket)
    {
        socket->write(data);
    }
}
