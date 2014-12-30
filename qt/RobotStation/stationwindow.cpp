#include "stationwindow.h"
#include "ui_stationwindow.h"
#include "robotconnectdialog.h"
#include <QMessageBox>
using rbp::Command;

StationWindow::StationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StationWindow),
    mIOService(),
    mResolver(mIOService),
    mRemoteEndpoint(),
    mSocket(mIOService, udp::endpoint(udp::v4(), 9036))
{
    ui->setupUi(this);
    mSocket.set_option(udp::socket::reuse_address(true));
}

void StationWindow::connect()
{

    if(QObject::sender() == ui->connectButton
            && ui->connectButton->text() == "Disconnect")
    {
        disconnect();
        return;
    }

    ui->connectButton->setEnabled(false);

    RobotConnectDialog rcd;

    rcd.show();

    if(rcd.exec() == QDialog::Accepted)
    {
        ui->connectButton->setText("Disconnect");

        std::stringstream ss;
        ss << rcd.getIPAddress() << ":" << rcd.getPort();
        ui->ipLabel->setText(QString::fromStdString(ss.str()));

        mRemoteEndpoint = *mResolver.resolve({udp::v4(),
                                             rcd.getIPAddress(),
                                             rcd.getPort()});
        ui->actionButton->setEnabled(true);
        ui->forwardButton->setEnabled(true);
        ui->stopButton->setEnabled(true);
    }

    ui->connectButton->setEnabled(true);
}

void StationWindow::forwardCommand()
{
    Command forwardCommand(0, 1);
    mSocket.send_to(boost::asio::buffer(forwardCommand.EncodeCommandToData()),
                    mRemoteEndpoint);
}

void StationWindow::stopCommand()
{
    Command stopCommand(0, 2);
    mSocket.send_to(boost::asio::buffer(stopCommand.EncodeCommandToData()),
                    mRemoteEndpoint);
}

void StationWindow::actionCommand()
{
    Command actionCommand(0, 3);
    mSocket.send_to(boost::asio::buffer(actionCommand.EncodeCommandToData()),
                    mRemoteEndpoint);
}

void StationWindow::disconnect()
{
    ui->connectButton->setText("Connect to Robot");
    ui->ipLabel->setText("");
    ui->actionButton->setEnabled(false);
    ui->forwardButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
}


StationWindow::~StationWindow()
{
    mSocket.close();
    delete ui;
}
