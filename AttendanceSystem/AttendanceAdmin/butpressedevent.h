/*
描述:pushButton控件的升级
用途:当点击按键改变样式
*/

#ifndef BUTPRESSEDEVENT_H
#define BUTPRESSEDEVENT_H
#include <QMouseEvent>
#include <QPushButton>
class butPressedEvent:public QPushButton
{
public:
    butPressedEvent(QWidget *p);
    //鼠标点击事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标松开事件
    void mouseReleaseEvent(QMouseEvent *e);
   //光标进入事件
    void leaveEvent(QEvent *event);
    //光标离开事件
    void enterEvent(QEvent *event);
private:
    //保存之前样式
    QString backSty;
};

#endif // BUTPRESSEDEVENT_H
