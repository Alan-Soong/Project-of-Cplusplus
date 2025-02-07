#include "daysmaster.h"
#include "ui_daysmaster.h"
#include <QDateEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDateTime>
#include <QLineEdit>

#include <QFile>
#include <QTextStream>
#include <QFileDialog>

#include "moments.h"

DaysMaster::DaysMaster(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DaysMaster)
{
    ui->setupUi(this);

    // 初始化日期选择器和标签
    targetDateEdit = ui->dateEdit;
    targetDateEdit->setDate(QDate::currentDate());
    countdownLabel = ui->label;

    // 连接按钮的点击信号到槽函数
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onCountdown()));

}

DaysMaster::~DaysMaster()
{
    delete ui;
}


void DaysMaster::onCountdown()
{
    //目标日和预计日期；
    QDateTime targetDateTime = targetDateEdit->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();

    //计算剩余的天数；
    qint64 msecs = targetDateTime.msecsTo(currentDateTime.addDays(0)) / 1000;
    qint64 days = msecs / (24 * 60 * 60);

    if (targetDateTime > currentDateTime) {
        //更新标签显示剩余天数；
        countdownLabel->setText("距离这一天还有 " + QString::number(-days+1) + " 天");
    }
    else{
        //更新标签显示剩余天数；
        countdownLabel->setText("这一天已经过去了 " + QString::number(days) + " 天");
    }
}

//清空记录；
void DaysMaster::on_pushButton_2_clicked()
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
        targetDateEdit->setDate(QDate::currentDate());
        ui->label->clear();
        ui->lineEdit->clear();
    }
}

//关闭页面；
void DaysMaster::on_pushButton_3_clicked()
{
    QMessageBox judge;
    judge.setWindowTitle("注意");
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("    是否关闭？");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        this->close();
    }
}

//保存记录为txt文件；
void DaysMaster::on_pushButton_4_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "保存记录", "", "文本文件 (*.txt)");
    if (filePath.isEmpty()) {
        //用户取消对话框或未选择文件
        return;
    }
    //确保文件路径具有.txt扩展名
    if (!filePath.endsWith(".txt", Qt::CaseInsensitive)) {
        filePath += ".txt";
    }
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "指定的日期：" << ui->dateEdit->date().toString("yyyy-MM-dd") << Qt::endl;
        out << "指定的事件：" << ui->lineEdit->text() << Qt::endl;
        out << ui->label->text() << Qt::endl;
        file.close();
    } else {
        // 处理文件打开失败的情况
        qDebug() << "无法打开文件：" << filePath;
    }
    //特别的功能：保存日期后可以在moments里面打开写入想法！
}

//为了不多此一举，可以直接在moments里面打开
void DaysMaster::on_pushButton_5_clicked()
{
    QMessageBox judge;
    judge.setWindowTitle("注意");
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("    是否关闭？");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        mt = new Moments;
        mt->show();
        mt->setWindowTitle("Moments");
        mt->receiveText(ui->dateEdit->text()+"\n"
                        +ui->label->text()+"\n"+ui->lineEdit->text());
        this->close();
    }
}



