#include "attendanceadmin.h"
#include "ui_attendanceadmin.h"

#include <QTabBar>

AttendanceAdmin::AttendanceAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceAdmin)
{
    ui->setupUi(this);
    ui->tabWidget->findChildren<QTabBar*>().at(0)->hide();
    switchTab(0);
}

AttendanceAdmin::~AttendanceAdmin()
{
    delete ui;
}

void AttendanceAdmin::switchTab(int index)
{
    ui->tabWidget->setCurrentIndex(index);
    if(index==0){
        ui->pushButton->setStyleSheet("\
        image: url(:/image/lr_p.png);image-position:left;text-align:right;color:#06da95;");
        ui->pushButton_2->setStyleSheet("\
        image: url(:/image/qd.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_3->setStyleSheet("\
        image: url(:/image/szt.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_4->setStyleSheet("\
        image: url(:/image/date.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_5->setStyleSheet("\
        image: url(:/image/cmd.png);image-position:left;text-align:right;color:#8a8a8a;");
    }else if(index==1){
        ui->pushButton->setStyleSheet("\
        image: url(:/image/lr.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_2->setStyleSheet("\
        image: url(:/image/qd_p.png);image-position:left;text-align:right;color:#06da95;");
        ui->pushButton_3->setStyleSheet("\
        image: url(:/image/szt.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_4->setStyleSheet("\
        image: url(:/image/date.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_5->setStyleSheet("\
        image: url(:/image/cmd.png);image-position:left;text-align:right;color:#8a8a8a;");
    }else if(index==2){
        ui->pushButton->setStyleSheet("\
        image: url(:/image/lr.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_2->setStyleSheet("\
        image: url(:/image/qd.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_3->setStyleSheet("\
        image: url(:/image/szt_p.png);image-position:left;text-align:right;color:#06da95;");
        ui->pushButton_4->setStyleSheet("\
        image: url(:/image/date.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_5->setStyleSheet("\
        image: url(:/image/cmd.png);image-position:left;text-align:right;color:#8a8a8a;");
    }else if(index==3){
        ui->pushButton->setStyleSheet("\
        image: url(:/image/lr.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_2->setStyleSheet("\
        image: url(:/image/qd.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_3->setStyleSheet("\
        image: url(:/image/szt.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_4->setStyleSheet("\
        image: url(:/image/date_p.png);image-position:left;text-align:right;color:#06da95;");
        ui->pushButton_5->setStyleSheet("\
        image: url(:/image/cmd.png);image-position:left;text-align:right;color:#8a8a8a;");
    }else if(index==4){
        ui->pushButton->setStyleSheet("\
        image: url(:/image/lr.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_2->setStyleSheet("\
        image: url(:/image/qd.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_3->setStyleSheet("\
        image: url(:/image/szt.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_4->setStyleSheet("\
        image: url(:/image/date.png);image-position:left;text-align:right;color:#8a8a8a;");
        ui->pushButton_5->setStyleSheet("\
        image: url(:/image/cmd_p.png);image-position:left;text-align:right;color:#06da95;");
    }
}


void AttendanceAdmin::on_pushButton_clicked()
{
    switchTab(0);
}

void AttendanceAdmin::on_pushButton_2_clicked()
{
    switchTab(1);
}

void AttendanceAdmin::on_pushButton_3_clicked()
{
    switchTab(2);
}

void AttendanceAdmin::on_pushButton_4_clicked()
{
    switchTab(3);
}

void AttendanceAdmin::on_pushButton_5_clicked()
{
    switchTab(4);
}
