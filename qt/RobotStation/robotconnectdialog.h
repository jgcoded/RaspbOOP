#ifndef ROBOTCONNECTDIALOG_H
#define ROBOTCONNECTDIALOG_H

#include <QDialog>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio::ip;
using boost::asio::ip::udp;

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
    void multicast_find();

private:

    void AutoDiscover(std::string multicastIP = "239.255.101.32",
                                          std::string interfaceIP = "0.0.0.0",
                                          int multicastPort = 30001);

    void HandleMulticastReceive(const boost::system::error_code& error,
      size_t bytes_recvd);

#define MAX_DATA 100

    QString ipAddress;
    int port;
    Ui::RobotConnectDialog *ui;
    boost::asio::io_service mIOService;
    udp::resolver mResolver;
    udp::socket mSocket;
    udp::endpoint mSocketSender;
    udp::socket mMulticastSocket;
    udp::endpoint mMulticastSender;
    char mMulticastData[MAX_DATA];
    char mConnectData[MAX_DATA];

};

#endif // ROBOTCONNECTDIALOG_H
