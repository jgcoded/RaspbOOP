#include "robotconnectdialog.h"
#include "ui_robotconnectdialog.h"
#include <QMessageBox>

RobotConnectDialog::RobotConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RobotConnectDialog),
    mIOService(),
    mResolver(mIOService),
    mSocket(mIOService, udp::endpoint(udp::v4(), 9037)),
    mMulticastSocket(mIOService)
{
    ui->setupUi(this);
    mSocket.set_option(udp::socket::reuse_address(true));
    AutoDiscover();
    mIOService.run();
}

void RobotConnectDialog::AutoDiscover(std::string interface,
                                      std::string group,
                                      int port)
{
    if(mMulticastSocket.is_open())
    {
        ui->multicastList->clear();
        mIOService.stop();
        mMulticastSocket.set_option(
                    boost::asio::ip::multicast::leave_group(mMulticastGroup));
        mMulticastSocket.close();
    }

    mMulticastGroup = boost::asio::ip::address::from_string(group);
    boost::asio::ip::address localIp =
            boost::asio::ip::address::from_string(interface);
    mMulticastEndpoint = udp::endpoint(mMulticastGroup, port);

    mMulticastSocket.open(mMulticastEndpoint.protocol());


    mMulticastSocket.set_option(udp::socket::reuse_address(true));


    mMulticastSocket.bind(udp::endpoint(localIp, port));


    mMulticastSocket.set_option(boost::asio::ip::multicast::join_group(mMulticastGroup.to_v4(), localIp.to_v4()));


    mMulticastSocket.set_option(boost::asio::ip::multicast::hops(5));


    mMulticastSocket.set_option(boost::asio::ip::multicast::enable_loopback(true));


    mMulticastSocket.set_option(boost::asio::socket_base::broadcast(true));


    boost::asio::socket_base::receive_buffer_size receiveSize(MAX_DATA);
    mMulticastSocket.set_option(receiveSize);
    boost::asio::socket_base::send_buffer_size sendSize(MAX_DATA);
    mMulticastSocket.set_option(sendSize);


    mMulticastSocket.async_receive_from(
            boost::asio::buffer(mMulticastData, MAX_DATA),
            mMulticastEndpoint,
            boost::bind(&RobotConnectDialog::HandleMulticastReceive,
              this,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));

    if(mIOService.stopped())
    {
        mIOService.reset();
        mIOService.run();
    }
}

void RobotConnectDialog::HandleMulticastReceive(const boost::system::error_code& error,
                                                                        size_t bytes_recvd)
{
    if (!error)
    {
        std::string data(mMulticastData);
        size_t endPos = data.find("END");
        data = data.substr(0, endPos);
        ui->multicastList->addItem(QString::fromStdString(data));
    }
}

void RobotConnectDialog::AttemptConnect(std::string ip, std::string port)
{
    try
    {
        udp::endpoint endpoint = *mResolver.resolve({udp::v4(), ip, port});

        // We expect the server to echo our greeting
        const unsigned char greeting[] = { 0x56 };
        std::memset(mConnectData, 0, MAX_DATA);
        mSocket.send_to(boost::asio::buffer(greeting), endpoint);

        mSocket.receive_from(boost::asio::buffer(mConnectData, MAX_DATA),
                                   mSocketSender);

        if(mConnectData[0] == greeting[0])
        {
            this->ipAddress = ip;
            this->mPort = port;
            this->done(QDialog::Accepted);
        }

    } catch (std::exception&) {

    }
}

void RobotConnectDialog::ip_connect()
{
    std::string ip = ui->ipAddressText->text().toStdString();
    std::string port = ui->portText->text().toStdString();
    AttemptConnect(ip, port);
}

void RobotConnectDialog::multicast_find()
{
    std::string ip = ui->multicastIPText->text().toStdString();
    int port = ui->multicastPortText->text().toInt();
    AutoDiscover("0.0.0.0", ip, port);
}

void RobotConnectDialog::multicast_connect()
{
    std::string address =
            ui->multicastList->currentItem()->text().toStdString();

    size_t portPos = address.find(":") + 1;
    std::string port = address.substr(portPos);
    std::string ip = address.substr(0, portPos - 1);
    AttemptConnect(ip, port);
}

RobotConnectDialog::~RobotConnectDialog()
{
    mMulticastSocket.set_option(
                boost::asio::ip::multicast::leave_group(mMulticastGroup));
    mMulticastSocket.close();
    mSocket.close();
    mIOService.stop();
    delete ui;
}
