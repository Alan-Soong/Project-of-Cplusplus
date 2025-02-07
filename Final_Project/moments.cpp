#include "moments.h"
#include "ui_moments.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QTextEdit>
#include <QTextCursor>
#include <QPixmap>

Moments::Moments(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Moments)
{
    ui->setupUi(this);

    this->connect(ui->actionnew,SIGNAL(triggered(bool)),this,SLOT(onActionNewTriggered(bool)));
    connect(ui->actionopen,SIGNAL(triggered(bool)),this,SLOT(onActionOpenTriggered(bool)));
    connect(ui->actionsave,SIGNAL(triggered(bool)),this,SLOT(onActionSaveTriggered(bool)));
    connect(ui->actionother_save,SIGNAL(triggered(bool)),this,SLOT(onActionOtherSaveTriggered(bool)));
    connect(ui->actionpaste,SIGNAL(triggered(bool)),this,SLOT(onActionPasteTriggered(bool)));
    connect(ui->actionundo,SIGNAL(triggered(bool)),this,SLOT(onActionuUndoTriggered(bool)));
    connect(ui->actionredo,SIGNAL(triggered(bool)),this,SLOT(onActionRedoTriggered(bool)));
    connect(ui->actioncopy,SIGNAL(triggered(bool)),this,SLOT(onActionCopyTriggered(bool)));

    this->saved = true;
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(onEdited()));

}

Moments::~Moments()
{
    delete ui;
}

//确认是否退出；
void Moments::on_pushButton_clicked()
{
    QMessageBox judge;
    judge.setWindowTitle("注意");
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:20px;""}");
    judge.setText("    请确认该操作！");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        this->close();
    }
}

//清空所留下的记录；
void Moments::on_pushButton_2_clicked()
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
        ui->textEdit->clear();
    }
}

//保存所写的内容；
void Moments::on_pushButton1_clicked(bool checked)
{
    qDebug()<<"进行保存:"<<checked<<Qt::endl;
    if(savePath.isEmpty())
    {
        QString file_path;
        while(file_path.isEmpty())
        {
            file_path = QFileDialog::getSaveFileName(this,"选择路径",".","*.txt;;*.doc;;*.docx");
            if (file_path.isEmpty()) {
                //用户取消对话框或未选择文件
                return;
            }
            break;
        }
        qDebug()<<file_path<<Qt::endl;
        this->savePath = file_path;
    }

    QFile txt(this->savePath);

    bool tag = txt.open(QIODevice::WriteOnly);
    if(tag)
    {
        txt.write(ui->textEdit->toPlainText().toStdString().data());
    }
    else
    {
        qDebug()<<"打开文件失败"<<Qt::endl;
        QMessageBox::critical(NULL,"错误","无法打开文件，请检查权限",
                              QMessageBox::Yes,QMessageBox::Yes);
    }
    txt.close();
    this->saved = true;
}

//新建文件；
void Moments::onActionNewTriggered(bool checked)
{
    qDebug()<<"新建文件…"<<checked<<Qt::endl;
    if(this->saved)
    {
        ui->textEdit->clear();
        this->saved = true;
    }
    else
    {
        int tag = QMessageBox::question(NULL,"注意","是否保存文件？",
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(tag == QMessageBox::Yes)
        {
            this->onActionSaveTriggered(false);
        }
        ui->textEdit->clear();
        this->saved = true;
    }
}

//打开文件；
void Moments::onActionOpenTriggered(bool checked)
{
    qDebug()<<"打开文件…"<<checked<<Qt::endl;
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

        // 使用 QTextStream 读取文件内容
        QTextStream in(&file);
        QString fileContent = in.readAll(); // 读取所有内容

        // 将文件内容设置到 QTextEdit 控件中
        ui->textEdit->setPlainText(fileContent); // 假设你的 QTextEdit 对象名为 textEdit
    }
}


//保存文件；
void Moments::onActionSaveTriggered(bool checked)
{
    qDebug()<<"进行保存:"<<checked<<Qt::endl;
    if(savePath.isEmpty())
    {
        QString file_path;
        while(file_path.isEmpty())
        {
            file_path = QFileDialog::getSaveFileName(this,"选择路径",".","*.txt;;*.doc;;*.docx");
            break;
        }
        qDebug()<<file_path<<Qt::endl;
        this->savePath = file_path;
    }

    QFile txt(this->savePath);

    bool tag = txt.open(QIODevice::WriteOnly);
    if(tag)
    {
        txt.write(ui->textEdit->toPlainText().toStdString().data());
    }
    else
    {
        qDebug()<<"打开文件失败"<<Qt::endl;
        QMessageBox::critical(NULL,"错误","无法打开文件，请检查权限",
                              QMessageBox::Yes,QMessageBox::Yes);
    }
    txt.close();
    this->saved = true;
}

void Moments::onActionOtherSaveTriggered(bool checked)
{
    qDebug()<<"另存为…"<<Qt::endl;
    this->savePath.clear();
    this->onActionSaveTriggered(checked);
}

void Moments::onActionPasteTriggered(bool checked)
{
    qDebug()<<"粘贴…"<<checked<<Qt::endl;
    ui->textEdit->paste();
}

void Moments::onActionUndoTriggered(bool checked)
{
    qDebug()<<"撤销…"<<checked<<Qt::endl;
    ui->textEdit->undo();
}

void Moments::onActionRedoTriggered(bool checked)
{
    qDebug()<<"重做…"<<checked<<Qt::endl;
    ui->textEdit->redo();
}

void Moments::onActionCopyTriggered(bool checked)
{
    qDebug()<<"复制…"<<checked<<Qt::endl;
    ui->textEdit->copy();
}

void Moments::onEdited()
{
    qDebug()<<"文本已修改…"<<Qt::endl;
    saved = false;
}

//插入图片 需要注意的是，这会导致最后的txt文件中没有你所插入的图片；
void Moments::on_pushButton_3_clicked()
{
    QMessageBox judge;
    judge.setStyleSheet("QLabel{""min-width:200px;""min-height:80px;"
                        "font-size:15px;""}");
    judge.setText("图片可能无法在其他文件中打开，是否插入？");
    judge.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    judge.setDefaultButton(QMessageBox::No);

    int res=judge.exec();
    if(res==QMessageBox::Yes)
    {
        ui->textEdit->setAcceptRichText(true);
        QString imageFilePath = QFileDialog::getOpenFileName(this, tr("插入图片"), "", tr("图片文件 (*.png *.jpg *.jpeg)"));
        if (!imageFilePath.isEmpty()) {
            QPixmap pixmap(imageFilePath);
            if (!pixmap.isNull()) { // 检查图片是否成功加载
                QImage image = pixmap.toImage(); // 将 QPixmap 转换为 QImage
                QTextCursor cursor = ui->textEdit->textCursor(); // 获取当前文本光标
                cursor.insertImage(image); // 使用 QImage 插入图片
                QTextImageFormat imageFormat;
                imageFormat.setWidth(image.width()/10);
                imageFormat.setHeight(image.height()/10);
                ui->textEdit->setTextCursor(cursor); // 设置 textEdit 的光标
                ui->textEdit->ensureCursorVisible(); // 确保光标位置可见
            } else {
                QMessageBox::warning(this, "错误", "无法打开文件！");
            }
        }
    }
}

//打开文件；
void Moments::on_pushButton_4_clicked()
{
    qDebug()<<"打开文件…"<<Qt::Checked<<Qt::endl;
    // 弹出文件对话框，让用户选择文本文件
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "",
                                                    tr("文本文件 (*.txt);;word文件(*.doc);;word文件(*.docx)"));
    if (!fileName.isEmpty()) {
        // 用户选择了文件，尝试打开并读取
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // 无法打开文件，显示错误消息
            QMessageBox::warning(this, "错误", "无法打开文件！");
            return;
        }

        // 使用 QTextStream 读取文件内容
        QTextStream in(&file);
        QString fileContent = in.readAll(); // 读取所有内容

        // 将文件内容设置到 QTextEdit 控件中
        ui->textEdit->setPlainText(fileContent); // 假设你的 QTextEdit 对象名为 textEdit
    }
}

void Moments::receiveText(const QString &text) {
    ui->textEdit->setPlainText(text);
}

void Moments::receiveTxt(const QString &text) {
    ui->textEdit->setPlainText(text);
}

