#include "todolist.h"
#include "ui_todolist.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QWidget>
#include <QMessageBox>

ToDoList::ToDoList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ToDoList)
{
    ui->setupUi(this);

    // 获取布局
    checkLayout = ui->verticalLayout;

    // 获取布局
    lineeditLayout = ui->verticalLayout;
}

ToDoList::~ToDoList()
{
    delete ui;
}

//设置额度；
static int i = 0;
void ToDoList::on_addButton_clicked()
{
    QString amountStr = ui->lineEdit->text();
    if(i>amountStr.toInt())
    {
        QMessageBox judge;
        judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                            "font-size:20px;""}");
        judge.setText(" 太累了，别这么忙！");
        judge.setStandardButtons(QMessageBox::Yes);
        judge.exec();
    }
    else
    {
        // 创建一个新的
        QLineEdit *newLineEdit = new QLineEdit("New LineEdit", this);
        lineeditLayout->addWidget(newLineEdit);
        // 可选：更新布局
        lineeditLayout->update();
        newLineEdit->clear();
        newLineEdit->setStyleSheet("font-size: 12pt;");
        newLineEdit->setStyleSheet("background-image: url(:/new/prefix3/R-C.jpg);");

        // 创建一个新的
        QCheckBox *newCheckBox = new QCheckBox("New CheckBox", this);
        checkLayout->addWidget(newCheckBox);
        // 可选：更新布局
        checkLayout->update();
        newCheckBox->setText("BINGO!");
        newCheckBox->setStyleSheet("background-image: url(:/new/prefix3/R-C.jpg);");
    }
    i++;
}

//清空记录；
void ToDoList::on_pushButton_clicked()
{
    QMessageBox judge;
    judge.setWindowTitle("注意");
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("    是否清空记录？");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        this->close();
        tdl = new ToDoList;
        tdl->show();
        tdl->setWindowTitle("ToDoList");
        i=0;
    }
}

//关闭页面；
void ToDoList::on_pushButton_2_clicked()
{
    QMessageBox judge;
    judge.setWindowTitle("注意");
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("    是否清空记录？");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        this->close();
    }
}

