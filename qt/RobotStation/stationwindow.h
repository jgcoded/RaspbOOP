#ifndef STATIONWINDOW_H
#define STATIONWINDOW_H

#include <QMainWindow>
#include <boost/asio.hpp>
#include "raspboop/data/Command.h"

using namespace boost::asio::ip;

namespace Ui {
class StationWindow;
}

class StationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StationWindow(QWidget *parent = 0);
    ~StationWindow();

private slots:
    void connect();
    void forwardCommand();
    void actionCommand();
    void stopCommand();

private:
    boost::asio::io_service mIOService;
    udp::resolver mResolver;
    udp::endpoint mRemoteEndpoint;
    udp::socket mSocket;
    void disconnect();
    Ui::StationWindow *ui;
};

#endif // STATIONWINDOW_H
