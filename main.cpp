#include "mainwindow.h"
#include <QApplication>
#include <cxxabi.h>
#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << abi::__cxa_demangle(typeid(&MainWindow::inherits).name(), nullptr, nullptr, nullptr);
    w.show();

    return a.exec();
}
