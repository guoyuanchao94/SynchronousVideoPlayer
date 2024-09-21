#include "connecttoserver.h"
#include "ui_connecttoserver.h"
#include <QPushButton>

ConnectToServer::ConnectToServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToServer)
{
    ui->setupUi(this);
    connect(ui->ipInput,&QLineEdit::textChanged,this,&ConnectToServer::on_TextChanged);
    connect(ui->portInput,&QLineEdit::textChanged,this,&ConnectToServer::on_TextChanged);
    connect(ui->userNameInput,&QLineEdit::textChanged,this,&ConnectToServer::on_TextChanged);
}

ConnectToServer::~ConnectToServer()
{
    qInfo() << "ConnectToServer::~ConnectToServer";
    delete ui;
}

void ConnectToServer::on_buttonBox_accepted()
{
    qInfo() << "ConnectToServer::连接到服务器";
    QUrl url = ui->ipInput->text();
    int port = ui->portInput->text().toInt();
    if(ui->ipInput->text().isEmpty())
    {
        url = "127.0.0.1";  //存疑
    }
    if(ui->portInput->text().isEmpty())
    {
        port = 1234;
    }
    qInfo() << "ConnectToServer::on_buttonBox_accepted, Connecting to " << url << ":" << port;
    QString userName = ui->userNameInput->text();
    if(ui->userNameInput->text().isEmpty())
    {
        userName = "client";
    }
    emit connectToServer(url, port);
    emit connectToUdpServer(url, port); //连接到UDP服务端
    emit setUserName(userName); //设置客户端名字,便于区分
    emit setServerURL(url);
}

void ConnectToServer::on_TextChanged(const QString &text)
{
    Q_UNUSED(text)
    QString ip= ui->ipInput->text().trimmed();
    QString port = ui->portInput->text().trimmed();
    QString userName = ui->userNameInput->text().trimmed();
    bool enable = !ip.isEmpty() && !port.isEmpty() && !userName.isEmpty();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enable);
}
