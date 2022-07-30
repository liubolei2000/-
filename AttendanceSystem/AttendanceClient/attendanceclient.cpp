#include "attendanceclient.h"
#include "ui_attendanceclient.h"

#include <QFile>

AttendanceClient::AttendanceClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceClient)
{
    ui->setupUi(this);
    Cap=new VideoCapture(0);
    connect(&t1,&QTimer::timeout,this,&AttendanceClient::on_t1);
    connect(&t2,&QTimer::timeout,this,&AttendanceClient::on_showTime);
    connect(&t3,&QTimer::timeout,this,&AttendanceClient::on_delayClose);
    t1.start(50);
    t2.start(1000);
    ui->looplab->hide();
    ui->infoBox->hide();
    seeta::ModelSetting setting("C:/SeetaFace/bin/model/fd_2_00.dat",seeta::ModelSetting::CPU,0);
    fTracker =new seeta::v2::FaceTracker(setting);
}

AttendanceClient::~AttendanceClient()
{
    delete ui;
    delete  Cap;
    delete  reply;
}

void AttendanceClient::on_t1()
{

    Mat image;
    Cap->read(image);
    if(image.data==nullptr)return;
    Mat minImage = image(cv::Rect(50,0,540,480));
    Mat saveImage;
    cv::cvtColor(minImage,saveImage,cv::COLOR_BGR2RGB);
    seeta::ImageData seetaImage;
    seetaImage.data=saveImage.data;
    seetaImage.width=saveImage.cols;
    seetaImage.height=saveImage.rows;
    seetaImage.channels=saveImage.channels();
    QImage img(saveImage.data,saveImage.cols,saveImage.rows,QImage::Format_RGB888);
    QPixmap mmp =  QPixmap::fromImage(img);
    ui->label->setPixmap(mmp);
    cv::Rect facePos;
    SeetaTrackingFaceInfoArray faceArr = fTracker->track(seetaImage);
    static int fpid=-1;;

    if(faceArr.size>0&&faceArr.data->score>0.9){
        ui->looplab->show();

        for(int i =0;i<faceArr.size;i++){
            SeetaRect rect = faceArr.data[i].pos;
            facePos= cv::Rect(rect.x, rect.y, rect.width, rect.height);
            int maxsize = rect.width>rect.height?rect.width:rect.height;
            ui->looplab->setGeometry(rect.x-18,rect.y-12,maxsize,maxsize);
        }
       // qDebug()<<fpid<<faceArr.data->PID;
        if(faceArr.data->PID!=fpid){
           // qDebug()<<faceArr.data->PID;
            fpid=faceArr.data->PID;
            Mat savepic = saveImage(facePos);
            cv::cvtColor(savepic,savepic,cv::COLOR_BGR2RGB);
            cv::imwrite("./t.jpg",savepic);
            getInfoByFace();
        }
    }else{
        fpid=-1;
        ui->looplab->hide();
        ui->looplab->clear();
    }
}

void AttendanceClient::on_showTime()
{
    QTime timeNow = QTime::currentTime();
    ui->timelab->setText(timeNow.toString("hh:mm:ss"));
}

void AttendanceClient::on_delayClose()
{
    ui->namelab->clear();
    ui->zhiweilab->clear();
    ui->bumenlab->clear();
    ui->numlab->clear();
    ui->infoBox->hide();
    ui->headimg->setStyleSheet("border:none;border-radius:50px;border-image: url(:/image/head.png);");
}

void AttendanceClient::getInfoByFace()
{
    if(flag)return;
    QFile *file = new QFile("./t.jpg");
    file->open(QIODevice::ReadOnly);
    QNetworkRequest req(QUrl(QString("http://%1/cgi-bin/getface").arg(ser_addr)));
    //qDebug()<<req.url();
    req.setHeader(QNetworkRequest::ContentTypeHeader, "t.jpg");
    reply=manager.post(req,file);
    alldata.clear();
    connect(reply, &QNetworkReply::readyRead, this, &AttendanceClient::on_readyRead);
    connect(reply, &QNetworkReply::finished, this, &AttendanceClient::on_finished);
    flag=true;
}

void AttendanceClient::showInfo(QStringList infoList)
{
    ui->looplab->setText(infoList[1]);
    ui->namelab->setText(infoList[1]);
    ui->zhiweilab->setText(infoList[2]);
    ui->bumenlab->setText(infoList[3]);
    ui->numlab->setText(infoList[4]);
    ui->infoBox->show();
    if(infoList[5].toUInt()){
        ui->qiandaolab->setText("您已经签到啦");
    }else{
        ui->qiandaolab->setText("签到成功");
    }
    t3.start(3000);
}

void AttendanceClient::on_readyRead()
{
    alldata.append(reply->readAll());
}

void AttendanceClient::on_finished()
{
    disconnect(reply, &QNetworkReply::readyRead, this, &AttendanceClient::on_readyRead);
    disconnect(reply, &QNetworkReply::finished, this, &AttendanceClient::on_finished);
    QString recvdata = QString(alldata);
    if(recvdata.contains('&')){
        QStringList li = recvdata.split("&");
        if(li.size()==7){
            showInfo(li);

            getHeadPicture(li[6]);
        }else
            ui->looplab->setText("未识别");
    }else
        ui->looplab->setText("未识别");
    flag=false;
}

void AttendanceClient::getHeadPicture(QString picname)
{
    if(flag2)return;
    QNetworkRequest req(QUrl(QString("http://%1/cgi-bin/gethead?123456&%2").arg(ser_addr).arg(picname)));

    reply = manager.get(req);
    alldata.clear();
    connect(reply,&QNetworkReply::readyRead,this,&AttendanceClient::on_readyRead);
    connect(reply,&QNetworkReply::finished,this,&AttendanceClient::on_gethead_finished);
    flag2=true;
}

void AttendanceClient::on_gethead_finished()
{
    disconnect(reply,&QNetworkReply::readyRead,this,&AttendanceClient::on_readyRead);
    disconnect(reply,&QNetworkReply::finished,this,&AttendanceClient::on_gethead_finished);
    QFile f("./b.jpg");
    f.open(QIODevice::WriteOnly);
    f.write(alldata);
    f.close();
    ui->headimg->setStyleSheet("border:none;border-radius:50px;border-image:url(./b.jpg);");
    flag2=false;
}

