#ifndef STATIONWINDOW_H
#define STATIONWINDOW_H

#include <QMainWindow>
#include "raspboop/data/Command.h"

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
    void disconnect();
    Ui::StationWindow *ui;
};

#endif // STATIONWINDOW_H
