#include "accounts.h"
#include "ui_accounts.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

Accounts::Accounts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Accounts)
{
    ui->setupUi(this);
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    //connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
}

double amount0 = 0;
double standard = 0;
double amount1 = 0;

Accounts::~Accounts()
{
    delete ui;
    on_saveTrButton_clicked();
}

//新建记录；
void Accounts::on_pushButton_clicked()
{
    QString description = ui->descriptionlineEdit->text();
    QString amountStr = ui->amountlineEdit->text();
    bool valid;
    double amount = amountStr.toDouble(&valid);

    if (!description.isEmpty() && valid) {
        QString transaction = description + " - " + amountStr;
        transactions.append(transaction);
        ui->listWidget->addItem(transaction);
        ui->descriptionlineEdit->clear();
        ui->amountlineEdit->clear();

        //这里设计了一个限定额度；
        amount0+=amount;
        if(amount0 >= standard)
        {
            QMessageBox::warning(this, "消费过高", "请注意钱财余额！");
        }
    }
    else {
        QMessageBox::warning(this, "非法输入", "请输入正确的描述和额度！");
    }
}


//删除记录；
//获取删除记录中的金额值；
void Accounts::extracted(bool &ok, int &number, QStringList &parts) {
    if (!parts.isEmpty()) {
        // 尝试将最后一个部分转换为整数
        number = parts.last().toInt(&ok);
    }
}
//删除相应行，同时更新已经花掉金钱的额度；
void Accounts::on_pushButton_2_clicked() {
    QString amountStr = ui->amountlineEdit->text();
    bool valid;
    amount1 = amountStr.toDouble(&valid);

    int currentRow = ui->listWidget->currentRow();
    if (currentRow != -1) {
        QString itemText = ui->listWidget->currentItem()->text();
        transactions.removeAt(currentRow);
        ui->listWidget->takeItem(currentRow);

        //假设已经获取了当前项的文本，进行分割文本
        QStringList parts = itemText.split('-', Qt::SkipEmptyParts);

        bool ok = false;
        int number = 0;
        extracted(ok, number, parts);

        if (ok) {
            amount0 -= number;
        } else {
            // 提取失败，可能因为最后一个部分不是有效的数字
            qDebug() << "未能找到数字！";
        }
    }
}

//获取限定额度；
void Accounts::on_standardEdit_returnPressed()
{
    QString stanDard = ui->standardEdit->text();
    standard = stanDard.toDouble();
}

//当限定额度变化时返回当前值；
void Accounts::on_standardEdit_textChanged(const QString &stanDard)
{
    standard = stanDard.toDouble();
}

//清空记录；
void Accounts::on_loadTrButton_clicked()
{
    QMessageBox judge;
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("    是否清空记录？");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        ui->standardEdit->clear();
        ui->listWidget->clear();
        standard = 0;
    }
}

//保存txt文件；
void Accounts::on_saveTrButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "保存交易记录", "", "文本文件 (*.txt)");
    if (path.isEmpty()) {
        //用户取消对话框或未选择文件
        return;
    }

    //确保文件路径具有.txt扩展名
    if (!path.endsWith(".txt", Qt::CaseInsensitive)) {
        path += ".txt";
    }

    QFile file("transactions.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开记账记录！");
        return;
    }

    QTextStream out(&file);
    for (const QString &transaction : transactions) {
        out << transaction << Qt::endl;
    }

    file.close();
}

//关闭页面；
void Accounts::on_pushButton_3_clicked()
{
    QMessageBox judge;
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("    是否关闭页面？");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        this->close();
    }
}

