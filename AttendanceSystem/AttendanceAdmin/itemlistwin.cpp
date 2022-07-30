#include "itemlistwin.h"
#include "ui_itemlistwin.h"

ItemListWin::ItemListWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemListWin)
{
    ui->setupUi(this);
}

ItemListWin::~ItemListWin()
{
    delete ui;
}

void ItemListWin::setLabelText(QString l1, QString l2, QString l3)
{
    ui->label->setText(l1);
    ui->label_2->setText(l2);
    ui->label_3->setText(l3);
}

void ItemListWin::setColor(QString backcolor)
{
    ui->groupBox->setStyleSheet(QString("background-color:%1;")
                                .arg(backcolor));
}
