/*
描述:http通信接口
功能说明:用于减少qt网络通信接口的代码量

*/

#ifndef NETWORKAPI_H
#define NETWORKAPI_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QTimer>
//const QString ser_addr = "http://192.168.51.42/cgi-bin/";//设置主机地址
const QString ser_addr = "http://43.138.136.251/cgi-bin/";
class NetWorkApi:public QObject
{
    Q_OBJECT
signals:
    //调用了getRequest/postRequest函数 如果服务器返回数据，将触发该信号通知读取
    void send_req_data(QByteArray &db);
public:
    NetWorkApi();
    ~NetWorkApi();
    //向服务器发送get请求,参数填写请求路径
    void getRequest(QString url);
     //向服务器发送post请求,参数填写请求路径+请求头+请求文件路径，文件路径可以为空
    void postRequest(QString url,QString head,QString file="");

    QString setUrl(QString url);
protected slots:
    void on_readyRead();
    void on_finished();
    //当一直收不到http响应的数据，延时3s关闭
    void on_deley_close();
private:
    //qt定时器,用于延时
    QTimer t1;
    //定义全局network接口
    //发送
    QNetworkAccessManager manager;
    //接收
    QNetworkReply *reply;
    //接收网络数据
    QByteArray data;
    //请求标志位 当发送请求时该标志为真，但返回数据则为假 为真时无法继续发送请求
    bool flag=false;

};

#endif // NETWORKAPI_H
