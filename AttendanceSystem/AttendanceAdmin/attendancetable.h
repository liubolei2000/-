#ifndef ATTENDANCETABLE_H
#define ATTENDANCETABLE_H

#include <QTimer>
#include <QWidget>
#include "networkapi.h"
#include <QList>
#include <QQueue>
typedef struct{
int id;
QString name;
QString zhiwei;
QString bumen;
QString num;
bool state;
QString path;
}userInfo;

namespace Ui {
class AttendanceTable;
}

class AttendanceTable : public QWidget
{
    Q_OBJECT

public:
    explicit AttendanceTable(QWidget *parent = nullptr);
    ~AttendanceTable();
protected:
    void show_table();
    void download_picture();
    void find_picture();
    void update_table();
private slots:
    void recv_data(QByteArray &data);

    void on_pushButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();
    void recv_result(QByteArray &data);
    void on_readyRead();
    void download_end();
    void on_head_but_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AttendanceTable *ui;
    NetWorkApi nwapi;
    QList<userInfo> InfoList;
    QQueue<QString> picture_name;
    QString tmpPath,hpath;
    QByteArray allarr;
    QNetworkReply *reply;
    QNetworkAccessManager manager;
    bool setheadflag=false;
};

#endif // ATTENDANCETABLE_H
