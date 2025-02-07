#include "formdetail.h"
#include "ui_formdetail.h"

FormDetail::FormDetail(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDetail)
{
    ui->setupUi(this);
}

FormDetail::~FormDetail()
{
    delete ui;
}

//显示详情介绍；
//关闭界面；
void FormDetail::on_pushButton_clicked()
{
    this->close();
}

