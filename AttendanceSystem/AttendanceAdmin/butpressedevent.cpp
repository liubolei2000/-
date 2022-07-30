#include "butpressedevent.h"
#include <QDebug>
butPressedEvent::butPressedEvent(QWidget *p):QPushButton(p)
{

}

void butPressedEvent::mousePressEvent(QMouseEvent *e)
{
    backSty=this->styleSheet();
    this->setStyleSheet("padding:10px;\n\nbackground-color: #009cea;\nborder:none;\nborder-radius:20px;");
    e->accept();
    this->clicked();
}

void butPressedEvent::mouseReleaseEvent(QMouseEvent *e)
{
    this->setStyleSheet(backSty);
    e->accept();
}

void butPressedEvent::leaveEvent(QEvent *event)
{
    this->setStyleSheet(backSty);
    event->accept();
}

void butPressedEvent::enterEvent(QEvent *event)
{
     backSty=this->styleSheet();
     event->accept();
}
