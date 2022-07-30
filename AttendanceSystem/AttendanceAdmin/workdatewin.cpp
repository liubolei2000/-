#include "workdatewin.h"
#include "ui_workdatewin.h"
#include <QDateTime>
#include <QDebug>
#include <QSqlRecord>

WorkDateWin::WorkDateWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkDateWin)
{
    ui->setupUi(this);

    query.exec("select *from dates");
    while (query.next()) {
        QSqlRecord rec = query.record();
        int day = rec.value(0).toInt();
        if(day==1){
            ui->radioButton->setChecked(rec.value(1).toBool());
            ui->dateTimeEdit->setTime(QTime::fromString(rec.value(2).toString()));
            ui->dateTimeEdit_8->setTime(QTime::fromString(rec.value(3).toString()));
        }else if(day==2){
            ui->radioButton_2->setChecked(rec.value(1).toBool());
            ui->dateTimeEdit_2->setTime(QTime::fromString(rec.value(2).toString()));
            ui->dateTimeEdit_9->setTime(QTime::fromString(rec.value(3).toString()));
        }else if(day==3){
            ui->radioButton_3->setChecked(rec.value(1).toBool());
            ui->dateTimeEdit_3->setTime(QTime::fromString(rec.value(2).toString()));
            ui->dateTimeEdit_10->setTime(QTime::fromString(rec.value(3).toString()));
        }else if(day==4){
            ui->radioButton_4->setChecked(rec.value(1).toBool());
            ui->dateTimeEdit_4->setTime(QTime::fromString(rec.value(2).toString()));
            ui->dateTimeEdit_11->setTime(QTime::fromString(rec.value(3).toString()));
        }else if(day==5){
            ui->radioButton_5->setChecked(rec.value(1).toBool());
            ui->dateTimeEdit_5->setTime(QTime::fromString(rec.value(2).toString()));
            ui->dateTimeEdit_12->setTime(QTime::fromString(rec.value(3).toString()));
        }else if(day==6){
            ui->radioButton_6->setChecked(rec.value(1).toBool());
            ui->dateTimeEdit_6->setTime(QTime::fromString(rec.value(2).toString()));
            ui->dateTimeEdit_13->setTime(QTime::fromString(rec.value(3).toString()));
        }else if(day==7){
            ui->radioButton_7->setChecked(rec.value(1).toBool());
            ui->dateTimeEdit_7->setTime(QTime::fromString(rec.value(2).toString()));
            ui->dateTimeEdit_14->setTime(QTime::fromString(rec.value(3).toString()));
        }
    }
}

WorkDateWin::~WorkDateWin()
{
    delete ui;
}

void WorkDateWin::on_pushButton_clicked()
{

    query.exec(QString("update dates set state=%1,uptime='%2',lowtime='%3' where day=1")
               .arg(ui->radioButton->isChecked()).arg( ui->dateTimeEdit->time().toString("hh:mm"))
               .arg( ui->dateTimeEdit_8->time().toString("hh:mm")));
    query.exec(QString("update dates set state=%1,uptime='%2',lowtime='%3' where day=2")
               .arg(ui->radioButton_2->isChecked()).arg( ui->dateTimeEdit_2->time().toString("hh:mm"))
               .arg( ui->dateTimeEdit_9->time().toString("hh:mm")));
    query.exec(QString("update dates set state=%1,uptime='%2',lowtime='%3' where day=3")
               .arg(ui->radioButton_3->isChecked()).arg( ui->dateTimeEdit_3->time().toString("hh:mm"))
               .arg( ui->dateTimeEdit_10->time().toString("hh:mm")));
    query.exec(QString("update dates set state=%1,uptime='%2',lowtime='%3' where day=4")
               .arg(ui->radioButton_4->isChecked()).arg( ui->dateTimeEdit_4->time().toString("hh:mm"))
               .arg( ui->dateTimeEdit_11->time().toString("hh:mm")));
    query.exec(QString("update dates set state=%1,uptime='%2',lowtime='%3' where day=5")
               .arg(ui->radioButton_5->isChecked()).arg( ui->dateTimeEdit_5->time().toString("hh:mm"))
               .arg( ui->dateTimeEdit_12->time().toString("hh:mm")));
    query.exec(QString("update dates set state=%1,uptime='%2',lowtime='%3' where day=6")
               .arg(ui->radioButton_6->isChecked()).arg( ui->dateTimeEdit_6->time().toString("hh:mm"))
               .arg( ui->dateTimeEdit_13->time().toString("hh:mm")));
    query.exec(QString("update dates set state=%1,uptime='%2',lowtime='%3' where day=7")
               .arg(ui->radioButton_7->isChecked()).arg( ui->dateTimeEdit_7->time().toString("hh:mm"))
               .arg( ui->dateTimeEdit_14->time().toString("hh:mm")));
}
