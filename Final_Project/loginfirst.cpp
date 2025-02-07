#include "loginfirst.h"
#include "ui_loginfirst.h"
#include <QMessageBox>
#include "formdetail.h"
#include "select.h"

#include <QResource>
#include <QUrl>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QDebug>

#include "moments.h"

LoginFirst::LoginFirst(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginFirst)
{
    ui->setupUi(this);

}

LoginFirst::~LoginFirst()
{
    delete ui;
}

//登录界面；

//退出按钮；
void LoginFirst::on_pushButton_2_clicked()
{
    QMessageBox judge;
    judge.setWindowTitle("选择格式");
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("   请确认该操作！");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        this->close();
    }
}

//打开详细信息界面；
void LoginFirst::on_pushButton_3_clicked()
{
    fd = new FormDetail;
    fd->show();
    fd->setWindowTitle("FormDetail");
}

//打开选择界面；
void LoginFirst::on_pushButton1_clicked()
{
    s = new Select;
    s->show();
    s->setWindowTitle("Select");
}

//打开历史记录；
void LoginFirst::on_pushButton_clicked()
{
    QMessageBox judge;
    judge.setStyleSheet("QLabel{""min-width:300px;""min-height:120px;"
                        "font-size:30px;""}");
    judge.setText("   请选择打开方式！");
    judge.addButton("moments",QMessageBox::AcceptRole);
    judge.addButton("其它文件",QMessageBox::RejectRole);

    int res=judge.exec();
    switch(res)
    {
    case QMessageBox::AcceptRole:
    {
        qDebug()<<"打开文件…"<<Qt::Checked<<Qt::endl;
        QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "",
                                                        tr("文本文件(*.txt);;word文件(*.doc);;word文件(*.docx)"));
        if (!fileName.isEmpty()) {
            // 用户选择了文件，尝试打开并读取
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // 无法打开文件，显示错误消息
                QMessageBox::warning(this, "错误", "无法打开文件！");
                return;
            }
            else
            {
                mt = new Moments;

                // 使用 QTextStream 读取文件内容
                QTextStream in(&file);
                QString fileContent = in.readAll(); // 读取所有内容

                // 将文件内容设置到 QTextEdit 控件中
                mt->receiveText(fileContent);
                // 假设你的 QTextEdit 对象名为 textEdit

                mt->show();
                mt->setWindowTitle("Moments");
            }
        }break;
    }
    case QMessageBox::RejectRole:
    {
        qDebug()<<"打开文件…"<<Qt::Checked<<Qt::endl;
        // 弹出文件对话框，让用户选择文本文件
        QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "",
                                                        tr("文本文件(*.txt);;word文件(*.doc);;word文件(*.docx)"));
        if (!fileName.isEmpty()) {
            // 用户选择了文件，尝试打开并读取
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // 无法打开文件，显示错误消息
                QMessageBox::warning(this, "错误", "无法打开文件！");
                return;
            }
            else
            {
                QUrl url = QUrl::fromLocalFile(fileName);
                if (!QDesktopServices::openUrl(url)) {
                    qDebug() << "无法打开文件：" << fileName;
                }
            }
        }break;
    }
    default:break;
    }
}


