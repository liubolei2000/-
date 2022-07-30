#ifndef ATTENDANCEADMIN_H
#define ATTENDANCEADMIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AttendanceAdmin; }
QT_END_NAMESPACE

class AttendanceAdmin : public QMainWindow
{
    Q_OBJECT

public:
    AttendanceAdmin(QWidget *parent = nullptr);
    ~AttendanceAdmin();
protected:
    void switchTab(int index);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::AttendanceAdmin *ui;
};
#endif // ATTENDANCEADMIN_H
