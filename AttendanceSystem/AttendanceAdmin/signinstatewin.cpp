#include "signinstatewin.h"
#include "ui_signinstatewin.h"
#include "itemlistwin.h"

#include <QSqlRecord>
SignInStateWin::SignInStateWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInStateWin)
{
    ui->setupUi(this);
    int2day<<"周一"<<"周二"<<"周三"<<"周四"<<"周五"<<"周六"<<"周日";
    ui->dateTimeEdit->setDate(QDate::currentDate());
    on_pushButton_clicked();
}

SignInStateWin::~SignInStateWin()
{
    delete ui;
}

void SignInStateWin::show_list()
{
    ui->listWidget->clear();
    QListWidgetItem *ITEM = new QListWidgetItem();
    ItemListWin *it =new ItemListWin;
    ITEM->setSizeHint(it->sizeHint());
    ui->listWidget->addItem(ITEM);
    it->setColor("#f0f0f0");
    it->setLabelText("名字","签到时间","签到情况");
    ui->listWidget->setItemWidget(ITEM,it);
    for(int i =0;i<DateList.size();i++){
        QString signInfo;
        if(ui->dateTimeEdit->date()==DateList[i].Date and currentWork.state){
            ITEM = new QListWidgetItem();
            it =new ItemListWin;
            ITEM->setSizeHint(it->sizeHint());
            QTime itTime=QTime::fromString(DateList[i].time);

            ui->listWidget->addItem(ITEM);
            if(i%2==0)
                it->setColor("#ffffff");
            else
                it->setColor("#f0f0f0");
            if(itTime<=currentWork.uptime){
                    signInfo="正常打卡";
            }else if(itTime>currentWork.uptime&&itTime<currentWork.lowtime){
                    signInfo="迟到";
            }else if(itTime>=currentWork.lowtime){
                    signInfo="下班打卡";
            }
            it->setLabelText(DateList[i].name,DateList[i].time,signInfo);
            ui->listWidget->setItemWidget(ITEM,it);
        }
    }
}

void SignInStateWin::upSqlData()
{
    query.exec("select *from dates");
    WorkDate data;
    day2work.clear();
    while (query.next()) {
        QSqlRecord rec = query.record();
        data.state=rec.value(1).toBool();
        data.uptime=QTime::fromString(rec.value(2).toString(),"HH:mm");
        data.lowtime=QTime::fromString(rec.value(3).toString(),"HH:mm");
        day2work[int2day[rec.value(0).toInt()-1]]=data;
    }
}


void SignInStateWin::on_pushButton_clicked()
{
    upSqlData();
    nwapi.getRequest("gettime?123456");
    connect(&nwapi,&NetWorkApi::send_req_data,this,&SignInStateWin::recv_data);
}

void SignInStateWin::recv_data(QByteArray &da)
{
    disconnect(&nwapi,&NetWorkApi::send_req_data,this,&SignInStateWin::recv_data);
    QStringList li = QString(da).split('&');
    DateList.clear();
    signDate data;
    int size = li.size()/2;
    for(int i = 0;i<size;i++){
        data.name=li[(i*2)+1];
        QStringList lili =li[(i*2)+2].split(' ');
        data.Date=QDate::fromString(lili[0],"yyyy-MM-dd");
        data.time=lili[1];
        DateList.append(data);
    }
    show_list();
}

void SignInStateWin::on_pushButton_2_clicked()
{
    QString day= ui->dateTimeEdit->date().toString("ddd");
    currentWork=day2work[day];
    show_list();
}
