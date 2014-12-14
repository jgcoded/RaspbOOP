#include "robotconnectdialog.h"
#include "ui_robotconnectdialog.h"
#include <QMessageBox>

RobotConnectDialog::RobotConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RobotConnectDialog),
    mIOService(),
    mResolver(mIOService),
    mSocket(mIOService, udp::endpoint(udp::v4(), 9035)),
    mMulticastSocket(mIOService)
{
    ui->setupUi(this);
    mIOService.run();
    //AutoDiscover();
}

void RobotConnectDialog::AutoDiscover(std::string multicastIP,
                                      std::string interfaceIP,
                                      int multicastPort)
{

    address multicastAddress =
            boost::asio::ip::address::from_string(multicastIP);

    address interfaceAddress =
            address::from_string(interfaceIP);

    udp::endpoint multicast_endpoint(
                multicastAddress, multicastPort);

    udp::endpoint listen_endpoint(
            udp::v4() , multicastPort);

    mMulticastSocket.open(listen_endpoint.protocol());
    mMulticastSocket.set_option(udp::socket::reuse_address(true));
    mMulticastSocket.bind(multicast_endpoint);

        // Join the multicast group.
    mMulticastSocket.set_option(udp::socket::reuse_address(true));
    mMulticastSocket.set_option(boost::asio::ip::multicast::enable_loopback(true));
    mMulticastSocket.set_option(
        multicast::join_group(multicastAddress.to_v4(), interfaceAddress.to_v4()));

    mMulticastSocket.async_receive_from(
            boost::asio::buffer(mMulticastData, MAX_DATA),
            mMulticastSender,
            boost::bind(&RobotConnectDialog::HandleMulticastReceive, this,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
}

void RobotConnectDialog::HandleMulticastReceive(const boost::system::error_code& error,
                                                                        size_t bytes_recvd)
{
    if (!error)
    {
        std::string data(mMulticastData);
        ui->multicastList->addItem(QString::fromStdString(data));
    }
}

void RobotConnectDialog::ip_connect()
{
    std::string ip = ui->ipAddressText->text().toStdString();
    std::string port = ui->portText->text().toStdString();

    try
    {
        udp::endpoint endpoint = *mResolver.resolve({udp::v4(), ip, port});

        // We expect the server to echo our greeting
        const unsigned char greeting[] = { 0x56 };

        mSocket.send_to(boost::asio::buffer(greeting), endpoint);

        // The server usually responds quickly so no need for async receive
        mSocket.receive_from(boost::asio::buffer(mConnectData, MAX_DATA), mSocketSender);

        if(mConnectData[0] == greeting[0])
            this->done(QDialog::Accepted);

    } catch (std::exception& e) {
        std::stringstream ss;
        ss << "Could not connect to " << ip << ": " << e.what();
        QMessageBox::warning(this,
                             QString("Connect failed"),
                             QString::fromStdString(ss.str()));
    }
}

void RobotConnectDialog::multicast_find()
{

}

void RobotConnectDialog::multicast_connect()
{
    this->done(QDialog::Accepted);
}

RobotConnectDialog::~RobotConnectDialog()
{
    delete ui;
}
