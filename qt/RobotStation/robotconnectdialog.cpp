#include "robotconnectdialog.h"
#include "ui_robotconnectdialog.h"

RobotConnectDialog::RobotConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RobotConnectDialog)
{
    ui->setupUi(this);
}

void RobotConnectDialog::ip_connect()
{
    this->done(QDialog::Accepted);
}

void RobotConnectDialog::multicast_connect()
{
    this->done(QDialog::Accepted);
}

RobotConnectDialog::~RobotConnectDialog()
{
    delete ui;
}
