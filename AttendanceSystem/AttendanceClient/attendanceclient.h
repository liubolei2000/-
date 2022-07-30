#ifndef ATTENDANCECLIENT_H
#define ATTENDANCECLIENT_H

#include <QMainWindow>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <opencv.hpp>
#include<seeta/FaceTracker.h>

using namespace cv;
using namespace  seeta;

const QString ser_addr="43.138.136.251";

QT_BEGIN_NAMESPACE
namespace Ui { class AttendanceClient; }
QT_END_NAMESPACE

class AttendanceClient : public QMainWindow
{
    Q_OBJECT

public:
    AttendanceClient(QWidget *parent = nullptr);
    ~AttendanceClient();
private:
    void getInfoByFace();
    void getHeadPicture(QString picname);
    void showInfo(QStringList infoList);
private slots:
    void on_t1();
    void on_showTime();
    void on_delayClose();
    void on_readyRead();
    void on_finished();
    void on_gethead_finished();
private:
    Ui::AttendanceClient *ui;
    QTimer t1,t2,t3;
    FaceTracker * fTracker;
    VideoCapture *Cap;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QByteArray alldata;
    bool flag=false,flag2=false;

};
#endif // ATTENDANCECLIENT_H
