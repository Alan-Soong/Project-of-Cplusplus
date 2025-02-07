#ifndef MOMENTS_H
#define MOMENTS_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextCursor>
#include <QPixmap>

namespace Ui {
class Moments;
}

class Moments : public QMainWindow
{
    Q_OBJECT

public:
    explicit Moments(QWidget *parent = nullptr);
    QTextEdit* textEdit;
    ~Moments();


public slots:

    void onActionNewTriggered(bool checked);//新建；
    void onActionOpenTriggered(bool checked);//打开；
    void onActionSaveTriggered(bool checked);//保存；
    void onActionOtherSaveTriggered(bool checked);//另存为；
    void onActionPasteTriggered(bool checked);//粘贴；
    void onActionUndoTriggered(bool checked);//撤销；
    void onActionRedoTriggered(bool checked);//重做；
    void onActionCopyTriggered(bool checked);//复制；

    void receiveText(const QString &text);
    void receiveTxt(const QString &text);

private slots:

    void on_pushButton_clicked();

    void on_pushButton1_clicked(bool checked);

    void on_pushButton_2_clicked();

    void onEdited();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:
    void open();


private:
    Ui::Moments *ui;
    Moments *mt;
    QString savePath;
    bool saved;
    QString filename;
    QFile file;
};

#endif // MOMENTS_H
