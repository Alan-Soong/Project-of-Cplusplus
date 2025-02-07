#ifndef FORMDETAIL_H
#define FORMDETAIL_H

#include <QWidget>

namespace Ui {
class FormDetail;
}

class FormDetail : public QWidget
{
    Q_OBJECT

public:
    explicit FormDetail(QWidget *parent = nullptr);
    ~FormDetail();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FormDetail *ui;
};

#endif // FORMDETAIL_H
