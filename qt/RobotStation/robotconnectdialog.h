#ifndef ROBOTCONNECTDIALOG_H
#define ROBOTCONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class RobotConnectDialog;
}

class RobotConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RobotConnectDialog(QWidget *parent = 0);

    QString getIPAddress() { return ipAddress; }
    int getPort() { return port; }

    ~RobotConnectDialog();

private slots:
    void ip_connect();
    void multicast_connect();

private:
    QString ipAddress;
    int port;
    Ui::RobotConnectDialog *ui;
};

#endif // ROBOTCONNECTDIALOG_H
