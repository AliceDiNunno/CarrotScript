#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Lexer.hpp"
#include "Parser.hpp"

namespace Ui {
    class MainWindow;
}

class BuildExecutionTree;
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
    QTimer *_pTimeOut;
    Lexer *_pLexer;
    Parser *_pTheMotherfucking;
    ParsingTreeEntryPoint * _pTree;
};

#endif // MAINWINDOW_H
