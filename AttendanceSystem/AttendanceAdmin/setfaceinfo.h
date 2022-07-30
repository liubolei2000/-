#ifndef SETFACEINFO_H
#define SETFACEINFO_H

#include <QWidget>
#include "networkapi.h"

namespace Ui {
class setFaceInfo;
}

class setFaceInfo : public QWidget
{
    Q_OBJECT

public:
    explicit setFaceInfo(QWidget *parent = nullptr);
    ~setFaceInfo();
private slots:
    void recv_cheese();
    void recv_data(QByteArray &data);
    void on_send_post_but_clicked();

    void on_label_clicked();

private:
    Ui::setFaceInfo *ui;
    NetWorkApi nwapi;
    bool flag =false;
};

#endif // SETFACEINFO_H
