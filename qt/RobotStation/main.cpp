#include "stationwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StationWindow w;
    w.show();

    return a.exec();
}
