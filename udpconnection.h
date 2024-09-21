#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

class UdpConnection : public QObject
{
    Q_OBJECT
public:
    explicit UdpConnection(QTcpSocket *newClient, QHostAddress &newIp, quint16 newUdpPort, QObject *parent = nullptr);
public:
    const QHostAddress &getIp() const;
    void setIp(const QHostAddress &newIp);
    quint16 getUdpPort() const;
    void setUdpPort(quint16 newUdpPort);
    QTcpSocket *getClient() const;
private:
    QTcpSocket *client = nullptr;
    QHostAddress ip;
    quint16 udpPort;
};

#endif // UDPCONNECTION_H
