#ifndef CMDWIN_H
#define CMDWIN_H

#include <QWidget>
#include "networkapi.h"
namespace Ui {
class cmdWin;
}

class cmdWin : public QWidget
{
    Q_OBJECT

public:
    explicit cmdWin(QWidget *parent = nullptr);
    ~cmdWin();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void recv_data(QByteArray &data);
private:
    Ui::cmdWin *ui;
    NetWorkApi nwapi;
};

#endif // CMDWIN_H
