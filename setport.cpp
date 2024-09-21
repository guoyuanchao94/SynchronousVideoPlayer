#include "setport.h"
#include "ui_setport.h"
#include <QMessageBox>
#include <QPushButton>
SetPort::SetPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPort)
{
    ui->setupUi(this);
    connect(ui->portInput,&QLineEdit::textChanged,this,&SetPort::on_TextChanged);
    connect(ui->userNameInput,&QLineEdit::textChanged,this,&SetPort::on_TextChanged);
}

SetPort::~SetPort()
{
    delete ui;
}

void SetPort::on_buttonBox_accepted()
{
    int port = ui->portInput->text().toInt();
    if(ui->portInput->text().isEmpty())   //防止ui->portInput->text()是空
    {
        port = 1234;
    }
    qDebug() << "SetPort::发射设置端口信号";
    emit setPort(port); //先发射这个信号去开启监听服务,后续连接到服务器再去执行
    QString userName = ui->userNameInput->text();
    if(ui->userNameInput->text().isEmpty())
    {
        userName = "server";
    }
    emit connectToLocalHost(port, userName);
    qInfo() << "SetPort::on_buttonBox_accepted, port: " << port << ",userNmae: " << userName;
}

void SetPort::on_TextChanged(const QString &text)
{
    Q_UNUSED(text)
    QString port = ui->portInput->text().trimmed();
    QString userName = ui->userNameInput->text().trimmed();
    bool enable = !port.isEmpty() && !userName.isEmpty();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enable);
}
