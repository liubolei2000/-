#ifndef CAMERAWIN_H
#define CAMERAWIN_H

#include <QWidget>
#include <opencv.hpp>
#include <seeta/FaceDetector.h>
#include <QTimer>
using namespace  cv;
using namespace  seeta;
using namespace  seeta::v2;
namespace Ui {
class CameraWin;
}

class CameraWin : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWin(QWidget *parent = nullptr);
    ~CameraWin();
signals:
    void send_cheese();
private slots:
    void on_t1();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CameraWin *ui;
    FaceDetector *fDetector;
    VideoCapture Cap;
    QTimer t1;
    bool flag = false;
};

#endif // CAMERAWIN_H
