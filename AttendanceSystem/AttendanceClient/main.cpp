#include "attendanceclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AttendanceClient w;
    w.show();
    return a.exec();
}
