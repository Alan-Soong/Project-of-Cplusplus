#ifndef SELECT_H
#define SELECT_H

#include <QWidget>
#include "moments.h"
#include "accounts.h"
#include "daysmaster.h"
#include "todolist.h"

namespace Ui {
class Select;
}

class Select : public QWidget
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = nullptr);
    ~Select();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Select *ui;
    Moments* mt = new Moments;
    Accounts* at = new Accounts;
    DaysMaster* dm = new DaysMaster;
    ToDoList* tdl = new ToDoList;
};

#endif // SELECT_H
