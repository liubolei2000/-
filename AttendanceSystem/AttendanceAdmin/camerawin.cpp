#include "camerawin.h"
#include "ui_camerawin.h"

CameraWin::CameraWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWin)
{
    ui->setupUi(this);
    connect(&t1,&QTimer::timeout,this,&CameraWin::on_t1);
    seeta::ModelSetting setting("C:/SeetaFace/bin/model/fd_2_00.dat",seeta::ModelSetting::CPU,0);
    fDetector =new FaceDetector(setting);
    ui->label->hide();
    ui->label_2->hide();
}

CameraWin::~CameraWin()
{
    delete ui;
}

void CameraWin::on_t1()
{
    Mat image;
    Cap>>image;
    if(image.data==nullptr)return;
    bool okflag=false;
    Mat minImage = image(cv::Rect(80,0,480,480));
    Mat saveImage;
    cv::cvtColor(minImage,saveImage,cv::COLOR_BGR2RGB);
    Mat inputImage;
    cv::Size dsize;
    dsize.width=240;
    dsize.height=240;
    cv::resize(saveImage,inputImage,dsize);
    seeta::ImageData seetaImage;
    seetaImage.data=saveImage.data;
    seetaImage.width=saveImage.cols;
    seetaImage.height=saveImage.rows;
    seetaImage.channels=saveImage.channels();
    QImage img(inputImage.data,inputImage.cols,inputImage.rows,QImage::Format_RGB888);
    QPixmap mmp =  QPixmap::fromImage(img);
    ui->label->setPixmap(mmp);
    SeetaFaceInfoArray faceArr =fDetector->detect(seetaImage);

    cv::Rect faceRect;
    if(faceArr.size>0){
        SeetaRect pos = faceArr.data->pos;
        faceRect=cv::Rect(pos.x,pos.y,pos.width,pos.height);
        ui->label_2->show();
        if(faceArr.data->score>0.99){
            okflag=true;
            ui->label_2->setStyleSheet("border-image: url(:/image/ok.png);background-color: rgba(255, 255, 255,0);");
        }else{
            flag=false;
            okflag=false;
            ui->label_2->setStyleSheet("border-image: url(:/image/no.png);background-color: rgba(255, 255, 255,0);");
        }
    }else{
        flag=false;
        okflag=false;
        ui->label_2->hide();
    }
    if(okflag&&flag){
        Mat faceIma,sIma;
        cv::cvtColor(saveImage,faceIma,cv::COLOR_BGR2RGB);
        cv::imwrite("./t.jpg",faceIma);
        sIma=faceIma(faceRect);
        cv::imwrite("./h.jpg",sIma);
        flag=false;
        send_cheese();
    }
}

void CameraWin::on_pushButton_clicked()
{
    //qDebug()<<ui->pushButton->text();
    if(ui->pushButton->text()=="关闭摄像头"){
        ui->label->hide();
        ui->label_2->hide();
        Cap.release();
        t1.stop();
        ui->pushButton->setText("打开摄像头");
    }else{
        ui->label->show();
        Cap.open(0);
        t1.start(50);
        ui->pushButton->setText("关闭摄像头");
    }
}

void CameraWin::on_pushButton_2_clicked()
{
    flag=true;
}
