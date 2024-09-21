#ifndef SETPORT_H
#define SETPORT_H

#include <QDialog>

namespace Ui {
class SetPort;
}

class SetPort : public QDialog
{
    Q_OBJECT

public:
    explicit SetPort(QWidget *parent = nullptr);
    ~SetPort();

signals:
    void setPort(int port);
    void connectToLocalHost(int port, QString username);

private slots:
    void on_buttonBox_accepted();
    void on_TextChanged(const QString &text);
private:
    Ui::SetPort *ui;
};

#endif // SETPORT_H
