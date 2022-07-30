#include "cmdwin.h"
#include "ui_cmdwin.h"
#include <QDebug>
cmdWin::cmdWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cmdWin)
{
    ui->setupUi(this);
}

cmdWin::~cmdWin()
{
    delete ui;
}

void cmdWin::on_pushButton_clicked()
{
    QString query = ui->textEdit_2->toPlainText().replace(' ','&');
    QString url = QString("sqlquery?%1").arg(query);
    nwapi.getRequest(url);
    connect(&nwapi,&NetWorkApi::send_req_data,this,&cmdWin::recv_data);
}

void cmdWin::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
}

void cmdWin::recv_data(QByteArray &data)
{
    ui->textEdit_2->clear();
    ui->textEdit->setText(QString(data));
    disconnect(&nwapi,&NetWorkApi::send_req_data,this,&cmdWin::recv_data);
}
