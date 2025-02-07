#include "select.h"
#include "ui_select.h"
#include "moments.h"
#include "accounts.h"
#include "daysmaster.h"
#include "todolist.h"

#include <QWidget>
#include <QMessageBox>

Select::Select(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Select)
{
    ui->setupUi(this);
}

Select::~Select()
{
    delete ui;
}

//选择moments界面；
void Select::on_pushButton_3_clicked()
{
    this->close();
    mt = new Moments;
    mt->show();
    mt->setWindowTitle("Moments");
}

//选择accounts界面；
void Select::on_pushButton_clicked()
{
    this->close();
    at = new Accounts;
    at->show();
    at->setWindowTitle("Accounts");
}

//选择daysmaster界面；
void Select::on_pushButton_4_clicked()
{
    this->close();
    dm = new DaysMaster;
    dm->show();
    dm->setWindowTitle("DaysMaster");
}

//选择todolist界面；
void Select::on_pushButton_2_clicked()
{
    this->close();
    tdl = new ToDoList;
    tdl->show();
    tdl->setWindowTitle("ToDoList");
}

//期待后续开发界面；
void Select::on_pushButton_6_clicked()
{
    QMessageBox judge;
    judge.setWindowTitle("注意");
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText(" 敬请期待后续开发！");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        this->close();
    }
}

//选择退出；
void Select::on_pushButton_5_clicked()
{
    this->close();
}



