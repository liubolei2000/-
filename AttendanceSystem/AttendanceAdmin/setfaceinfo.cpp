#include "setfaceinfo.h"
#include "ui_setfaceinfo.h"
#include "camerawin.h"

#include <QFileDialog>
#include <QMessageBox>
setFaceInfo::setFaceInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setFaceInfo)
{
    ui->setupUi(this);
    connect(ui->widget,&CameraWin::send_cheese,this,&setFaceInfo::recv_cheese);
}

setFaceInfo::~setFaceInfo()
{
    delete ui;
}

void setFaceInfo::recv_cheese()
{
    flag=true;
    ui->label->setStyleSheet("border-image: url(./t.jpg);border-radius:50px;");
}

void setFaceInfo::on_send_post_but_clicked()
{
    if(!flag){
        QMessageBox::information(this,"info","未录入头像");
        return;
    }
    if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isEmpty()){
        QMessageBox::information(this,"info","请输入信息");
        return;
    }
    QDateTime begin_time = QDateTime::currentDateTime();//获取系统现在的时间
    uint stime = begin_time.toTime_t();
    QString head = QString("%1.jpg,%2,%3,%4,%5")
                  .arg(stime).arg(ui->lineEdit->text()).arg(ui->comboBox_3->currentText())
                  .arg(ui->comboBox_4->currentText()).arg(ui->lineEdit_2->text());
    nwapi.postRequest("setface",head,"./h.jpg");
    connect(&nwapi,&NetWorkApi::send_req_data,this,&setFaceInfo::recv_data);
    ui->label->setStyleSheet("border-image: url(:/image/head.png);border-radius:50px;");
    flag=false;
}

void setFaceInfo::recv_data(QByteArray &data)
{
    disconnect(&nwapi,&NetWorkApi::send_req_data,this,&setFaceInfo::recv_data);
    QString recvstr = QString(data);
    qDebug()<<recvstr;
    if(recvstr.contains("insert",Qt::CaseSensitive)){
        QMessageBox::information(this,"info","该员工已经录入!!");
    }else if(recvstr.contains("ok",Qt::CaseSensitive)){
        QMessageBox::information(this,"info","录入成功!!");
    }else{
        QMessageBox::information(this,"info","请重新录入人脸!!");
    };
}


void setFaceInfo::on_label_clicked()
{
    QString hpath = QFileDialog::getOpenFileName(this,"选择图片","C:\\","JPEG Files(*.jpg)");
    if(hpath=="")return;
    ui->label->setStyleSheet(QString("border-radius:50px;border-image:url(%1);")
            .arg(hpath));
    QFile f(hpath),sf("./h.jpg");
    f.open(QIODevice::ReadOnly);
    sf.open(QIODevice::WriteOnly);
    sf.write(f.readAll());
    f.close();
    sf.close();
    flag=true;
}
