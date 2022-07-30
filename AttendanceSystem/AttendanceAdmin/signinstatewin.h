#ifndef SIGNINSTATEWIN_H
#define SIGNINSTATEWIN_H

#include <QWidget>
#include "networkapi.h"
#include <QSqlQuery>
#include <QMap>
typedef struct{
QString name;
QDate Date;
QString time;
}signDate;
typedef struct{
bool state;
QTime uptime;
QTime lowtime;
}WorkDate;

namespace Ui {
class SignInStateWin;
}

class SignInStateWin : public QWidget
{
    Q_OBJECT

public:
    explicit SignInStateWin(QWidget *parent = nullptr);
    ~SignInStateWin();
private:
    void show_list();
    void upSqlData();

private slots:
    void on_pushButton_clicked();
    void recv_data(QByteArray &da);
    void on_pushButton_2_clicked();

private:
    Ui::SignInStateWin *ui;
    NetWorkApi nwapi;
    QSqlQuery query;
    QList<signDate> DateList;
    QMap<QString,WorkDate> day2work;
    QStringList int2day;
    WorkDate currentWork;
};

#endif // SIGNINSTATEWIN_H
