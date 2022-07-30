#include "networkapi.h"

#include <QFile>

NetWorkApi::NetWorkApi()
{
    connect(&t1,&QTimer::timeout,this,&NetWorkApi::on_deley_close);
}

NetWorkApi::~NetWorkApi()
{
    data.clear();
    delete reply;
}

void NetWorkApi::getRequest(QString url)
{
    if(flag)return;
    QNetworkRequest req(ser_addr+url);
    reply=manager.get(req);
    //qDebug()<<req.url();
    data.clear();
    QObject::connect(reply,&QNetworkReply::readyRead,this,&NetWorkApi::on_readyRead);
    QObject::connect(reply,&QNetworkReply::finished,this,&NetWorkApi::on_finished);
    flag=true;
    t1.start(3000);
}

void NetWorkApi::postRequest(QString url, QString head, QString file)
{
    if(flag)return;
    QFile *f= new QFile(file);
    f->open(QIODevice::ReadOnly);
    QNetworkRequest req(ser_addr+url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,head);
    //qDebug()<<req.url();
    reply=manager.post(req,f);
    data.clear();
    QObject::connect(reply, &QNetworkReply::readyRead, this, &NetWorkApi::on_readyRead);
    QObject::connect(reply, &QNetworkReply::finished, this, &NetWorkApi::on_finished);
    flag=true;
    t1.start(3000);
}


QString NetWorkApi::setUrl(QString url)
{
    return  ser_addr+url;
}



void NetWorkApi::on_readyRead()
{
    data.append(reply->readAll());
}

void NetWorkApi::on_finished()
{
    QObject::disconnect(reply,&QNetworkReply::readyRead,this,&NetWorkApi::on_readyRead);
    QObject::disconnect(reply,&QNetworkReply::finished,this,&NetWorkApi::on_finished);
    flag=false;
    send_req_data(data);
    reply->deleteLater();
}

void NetWorkApi::on_deley_close()
{
    if(flag==true){
          flag=false;
    }
    t1.stop();
}


