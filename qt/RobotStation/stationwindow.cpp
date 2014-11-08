#include "stationwindow.h"
#include "ui_stationwindow.h"
#include "robotconnectdialog.h"

StationWindow::StationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StationWindow)
{
    ui->setupUi(this);
}

void StationWindow::connect()
{

    if(QObject::sender() == ui->pushButton && ui->pushButton->text() == "Disconnect")
    {
        disconnect();
        return;
    }

    RobotConnectDialog rcd;

    rcd.show();

    if(rcd.exec() == QDialog::Accepted)
    {
        ui->pushButton->setText("Disconnect");
    }

}

void StationWindow::disconnect()
{
    ui->pushButton->setText("Connect to Robot");
}


StationWindow::~StationWindow()
{
    delete ui;
}
