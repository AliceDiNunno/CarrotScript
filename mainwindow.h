#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "interpreter.h"
#include "Lexer.hpp"
#include "DataSanatizer.hpp"
#include "ByteReader.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void interpreterTimedOut();

    void on_loadButton_clicked();

    void InterpreterInfo(QString);
    void InterpreterAlert(QString);
    void InterpreterError(QString);
    void InterpreterMessage(QString);

    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;
    Interpreter *_pInterpreter;
    QTimer *_pTimeOut;
    Lexer *_pLexer;
};

#endif // MAINWINDOW_H
