#include "loginfirst.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginFirst w;
    w.show();
    return a.exec();
}
