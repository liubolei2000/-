#include "attendanceadmin.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./date.db");
    db.open();
    QSqlQuery query;
    query.exec("create table if not exists dates(day integer primary key,"
               "state bool,uptime text,lowtime text)");
//    for(int i=1;i<=7;i++){
//        query.exec(QString("INSERT INTO dates(day) values(%1)").arg(i));
//    }
    AttendanceAdmin w;
    w.show();
    return a.exec();
}
