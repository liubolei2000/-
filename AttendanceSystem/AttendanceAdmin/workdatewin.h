#ifndef WORKDATEWIN_H
#define WORKDATEWIN_H

#include <QSqlQuery>
#include <QWidget>

namespace Ui {
class WorkDateWin;
}

class WorkDateWin : public QWidget
{
    Q_OBJECT

public:
    explicit WorkDateWin(QWidget *parent = nullptr);
    ~WorkDateWin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WorkDateWin *ui;
    QSqlQuery query;
};

#endif // WORKDATEWIN_H
