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

    std::string getIPAddress() { return ipAddress; }
    std::string getPort() { return mPort; }

    ~RobotConnectDialog();

private slots:
    void ip_connect();
    void multicast_connect();
    void multicast_find();

private:

    void AutoDiscover(std::string interface = "0.0.0.0",
                                          std::string group = "239.255.101.33",
                                          int port = 30001);

    void HandleMulticastReceive(const boost::system::error_code& error,
      size_t bytes_recvd);

    void AttemptConnect(std::string ip, std::string port);

#define MAX_DATA 100

    std::string ipAddress;
    std::string mPort;
    Ui::RobotConnectDialog *ui;
    boost::asio::io_service mIOService;
    udp::resolver mResolver;
    udp::socket mSocket;
    udp::endpoint mSocketSender;
    udp::socket mMulticastSocket;
    boost::asio::ip::address mMulticastGroup;
    udp::endpoint mMulticastEndpoint;
    char mMulticastData[MAX_DATA];
    char mConnectData[MAX_DATA];

};

#endif // ROBOTCONNECTDIALOG_H
