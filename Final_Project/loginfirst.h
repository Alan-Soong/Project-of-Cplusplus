#ifndef LOGINFIRST_H
#define LOGINFIRST_H

#include <QMainWindow>
#include "formdetail.h"
#include "select.h"

#include "moments.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginFirst;
}
QT_END_NAMESPACE

class LoginFirst : public QMainWindow
{
    Q_OBJECT

public:
    LoginFirst(QWidget *parent = nullptr);
    ~LoginFirst();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton1_clicked();

    void on_pushButton_clicked();

private:
    Ui::LoginFirst *ui;
    FormDetail* fd = new FormDetail;
    Select* s = new Select;
    Moments* mt;

};
#endif // LOGINFIRST_H
