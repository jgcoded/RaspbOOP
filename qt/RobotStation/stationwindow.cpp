#include "stationwindow.h"
#include "ui_stationwindow.h"
#include "robotconnectdialog.h"

using rbp::Command;

StationWindow::StationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StationWindow)
{
    ui->setupUi(this);
}

void StationWindow::connect()
{

    if(QObject::sender() == ui->connectButton && ui->connectButton->text() == "Disconnect")
    {
        disconnect();
        return;
    }

    RobotConnectDialog rcd;

    rcd.show();

    if(rcd.exec() == QDialog::Accepted)
    {
        ui->connectButton->setText("Disconnect");
    }

}

void StationWindow::forwardCommand()
{
    Command forwardCommand(0, 1, std::vector<float>());
}

void StationWindow::stopCommand()
{
    Command stopCommand(0, 2, std::vector<float>());
}

void StationWindow::actionCommand()
{
    Command actionCommand(0, 3, std::vector<float>());
}

void StationWindow::disconnect()
{
    ui->connectButton->setText("Connect to Robot");
}


StationWindow::~StationWindow()
{
    delete ui;
}
