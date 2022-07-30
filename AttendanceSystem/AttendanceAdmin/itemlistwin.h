#ifndef ITEMLISTWIN_H
#define ITEMLISTWIN_H

#include <QWidget>

namespace Ui {
class ItemListWin;
}

class ItemListWin : public QWidget
{
    Q_OBJECT

public:
    explicit ItemListWin(QWidget *parent = nullptr);
    ~ItemListWin();
    void setLabelText(QString l1,QString l2,QString l3);
    void  setColor(QString backcolor);

private:
    Ui::ItemListWin *ui;
};

#endif // ITEMLISTWIN_H
