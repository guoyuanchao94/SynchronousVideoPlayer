#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include <QDialog>
#include <QUrl>

namespace Ui {
class ConnectToServer;
}

class ConnectToServer : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectToServer(QWidget *parent = nullptr);
    ~ConnectToServer();
signals:
    void connectToServer(QUrl url, int port);
    void connectToUdpServer(QUrl url, int port);
    void setUserName(QString username);
    void setServerURL(QUrl url);
private slots:
    void on_buttonBox_accepted();
    void on_TextChanged(const QString &text);
private:
    Ui::ConnectToServer *ui;
};

#endif // CONNECTTOSERVER_H
