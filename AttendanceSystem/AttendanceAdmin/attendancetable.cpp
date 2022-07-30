#include "attendancetable.h"
#include "ui_attendancetable.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

AttendanceTable::AttendanceTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttendanceTable)
{
    ui->setupUi(this);
}

AttendanceTable::~AttendanceTable()
{
    delete ui;
}

void AttendanceTable::show_table()
{
    ui->tableWidget->clear();
    QTableWidgetItem *item;

    for(int i =0 ;i<InfoList.size();i++){
        //QTableWidgetItem(const QIcon &icon, const QString &text, int type = Type)
        if(InfoList[i].state)
            item=new QTableWidgetItem(QIcon(":/image/ok.png"),InfoList[i].name);
        else
            item=new QTableWidgetItem(QIcon(":/image/no.png"),InfoList[i].name);
        ui->tableWidget->setItem(i/5,i%5,item);
    }
}





void AttendanceTable::on_pushButton_clicked()
{
    setheadflag=false;
    update_table();

}

void AttendanceTable::recv_data(QByteArray &data)
{
    disconnect(&nwapi,&NetWorkApi::send_req_data,this,&AttendanceTable::recv_data);
    QStringList li= QString(data).split("&");
    userInfo db;
    InfoList.clear();
    int cnt = li.size()/7;
    for(int i=0;i<cnt;i++){
         db.id=li[(i*7)+1].toInt();
         db.name=li[(i*7)+2];
         db.zhiwei=li[(i*7)+3];
         db.bumen=li[(i*7)+4];
         db.num=li[(i*7)+5];
         db.state=li[(i*7)+6].toInt();
         db.path=li[(i*7)+7];
         InfoList.append(db);
    }
    show_table();
    find_picture();
}

void AttendanceTable::on_tableWidget_cellClicked(int row, int column)
{
    int index=row*5+column;
    setheadflag=false;
    if(index<InfoList.size()){
        ui->lineEdit->setText(InfoList[index].name);
        ui->lineEdit_2->setText(InfoList[index].zhiwei);
        ui->lineEdit_3->setText(InfoList[index].bumen);
        ui->lineEdit_4->setText(InfoList[index].num);
        ui->head_but->setStyleSheet(QString("border-radius:32px;border-image:\
         url(./head/%1);background-color: rgba(255, 255, 255,0);")
                .arg(InfoList[index].path));
    }else{
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->head_but->setStyleSheet("border-image:\
         url(:/image/head.png);background-color: rgba(255, 255, 255,0);");
    }
}

void AttendanceTable::on_pushButton_3_clicked()
{
    setheadflag=false;
    int index = ui->tableWidget->currentRow()*5+ui->tableWidget->currentColumn();
    if(index<InfoList.size()){
        nwapi.getRequest(QString("delinfo?123456&%1").arg(InfoList[index].id));
        connect(&nwapi,&NetWorkApi::send_req_data,this,&AttendanceTable::recv_result);
    }
}

void AttendanceTable::on_pushButton_2_clicked()
{

    int index = ui->tableWidget->currentRow()*5+ui->tableWidget->currentColumn();
    if(index<InfoList.size()){
        QString sql;
        if(setheadflag){
            QString filename =QFileInfo(hpath).fileName();
            sql = QString("&update users set name='%1',zhiwei='%2',bumen='%3',num='%4',picpath='%5' where id=%6;")
                       .arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text()).arg(ui->lineEdit_3->text())
                       .arg(ui->lineEdit_4->text()).arg(filename).arg(InfoList[index].id);
            setheadflag=false;
            nwapi.postRequest("updateinfo",filename+sql,hpath);
        }else{
            sql = QString("update users set name='%1',zhiwei='%2',bumen='%3',num='%4' where id=%6;")
                       .arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text()).arg(ui->lineEdit_3->text())
                       .arg(ui->lineEdit_4->text()).arg(InfoList[index].id);
            nwapi.postRequest("updateinfo",sql,"");
        }

        connect(&nwapi,&NetWorkApi::send_req_data,this,&AttendanceTable::recv_result);
        //qDebug()<<url;
    }

}

void AttendanceTable::recv_result(QByteArray &data)
{
    disconnect(&nwapi,&NetWorkApi::send_req_data,this,&AttendanceTable::recv_result);
    QMessageBox *mes= new QMessageBox(this);
    mes->setStyleSheet("color:#000000;");
    if(QString(data)=="ok"){
        mes->setText("操作成功");
        update_table();
    }else{
        mes->setText("操作失败");
    };
    mes->show();
}

void AttendanceTable::on_readyRead()
{
    allarr.append(reply->readAll());
}
void AttendanceTable::download_picture()
{
    allarr.clear();
    if(!picture_name.isEmpty()){
        tmpPath=picture_name.dequeue();
        QString url =nwapi.setUrl(QString("gethead?123456&%1").arg(tmpPath));
        QNetworkRequest req(url);
        reply=manager.get(req);

        connect(reply,&QNetworkReply::readyRead,this,&AttendanceTable::on_readyRead);
        connect(reply,&QNetworkReply::finished,this,&AttendanceTable::download_end);
    }
}

void AttendanceTable::find_picture()
{
    QDir d("./head");
    quint32 j;
    for(int i=0;i<InfoList.size();i++){
        QString path = InfoList[i].path;
        for(j=2;j<d.count();j++){
            if(d[j]==path)break;
        }
        if(j==d.count()){
            picture_name.enqueue(path);
        }
    }
    download_picture();
}

void AttendanceTable::update_table()
{
    nwapi.getRequest("getinfo?123456");
    connect(&nwapi,&NetWorkApi::send_req_data,this,&AttendanceTable::recv_data);
}

void AttendanceTable::download_end()
{
     disconnect(reply,&QNetworkReply::readyRead,this,&AttendanceTable::on_readyRead);
     disconnect(reply,&QNetworkReply::finished,this,&AttendanceTable::download_end);
    QFile f("./head/"+tmpPath);
    f.open(QIODevice::WriteOnly);
    f.write(allarr);
    f.close();
    download_picture();
}

void AttendanceTable::on_head_but_clicked()
{
    hpath = QFileDialog::getOpenFileName(this,"选择图片","C:\\","JPEG Files(*.jpg);;PNG Files(*.png)");
    if(hpath=="")return;
    ui->head_but->setStyleSheet(QString("border-radius:32px;border-image:\
     url(%1);background-color: rgba(255, 255, 255,0);")
            .arg(hpath));
    setheadflag=true;
}

void AttendanceTable::on_pushButton_4_clicked()
{
    nwapi.getRequest("reinfo?123456");
    connect(&nwapi,&NetWorkApi::send_req_data,this,&AttendanceTable::recv_result);
}
