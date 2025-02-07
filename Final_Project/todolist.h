#ifndef TODOLIST_H
#define TODOLIST_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QCheckBox>

namespace Ui {
class ToDoList;
}

class ToDoList : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToDoList(QWidget *parent = nullptr);
    ~ToDoList();

private slots:
    void on_addButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ToDoList *ui;
    QVBoxLayout *checkLayout; // 水平布局
    QVBoxLayout *lineeditLayout; // 水平布局
    ToDoList *tdl;
};

#endif // TODOLIST_H
