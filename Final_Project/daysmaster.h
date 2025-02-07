#ifndef DAYSMASTER_H
#define DAYSMASTER_H

#include <QMainWindow>
#include <QDateEdit>
#include <QPushButton>
#include <QLabel>

#include "moments.h"


namespace Ui {
class DaysMaster;
}

class DaysMaster : public QMainWindow
{
    Q_OBJECT

public:
    explicit DaysMaster(QWidget *parent = nullptr);
    ~DaysMaster();

private slots:
    void onCountdown();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();


signals:
    void textToTransfer(const QString &text);

private:
    Ui::DaysMaster *ui;
    DaysMaster *dm;
    QDateEdit *targetDateEdit;
    QLabel *countdownLabel;
    Moments *mt;
};

#endif // DAYSMASTER_H
