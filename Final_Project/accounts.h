#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <QMainWindow>

namespace Ui {
class Accounts;
}

class Accounts : public QMainWindow
{
    Q_OBJECT

public:
    explicit Accounts(QWidget *parent = nullptr);
    ~Accounts();

private slots:
    void on_pushButton_clicked();

    void extracted(bool &ok, int &number, QStringList &parts);
    void on_pushButton_2_clicked();

    void on_standardEdit_returnPressed();

    void on_standardEdit_textChanged(const QString &stanDard);

    void on_loadTrButton_clicked();

    void on_saveTrButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Accounts *ui;
    QList<QString> transactions;
};

#endif // ACCOUNTS_H
