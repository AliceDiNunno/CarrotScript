#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _pInterpreter = new Interpreter();
    _pTimeOut = new QTimer();
    connect(_pTimeOut, SIGNAL(timeout()), this, SLOT(interpreterTimedOut()));

    connect(_pInterpreter, SIGNAL(alert(QString)), this, SLOT(InterpreterAlert(QString)));
    connect(_pInterpreter, SIGNAL(info(QString)), this, SLOT(InterpreterInfo(QString)));
    connect(_pInterpreter, SIGNAL(error(QString)), this, SLOT(InterpreterError(QString)));
    connect(_pInterpreter, SIGNAL(message(QString)), this, SLOT(InterpreterMessage(QString)));
    connect(_pInterpreter, SIGNAL(finished()), _pTimeOut, SLOT(stop()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Script"),
                                                    "~",
                                                    tr("Carrot CloudScript (*.ccs)"));
    ui->filePathLabel->setText("Loaded: " + fileName);

    QFile *f = new QFile(fileName);
    if (f->open(QIODevice::ReadOnly))
    {
        emit InterpreterInfo("Loaded file: " + fileName);
        QByteArray data = f->readAll();
        _pInterpreter->parseAll(data);
    }
    else
        emit InterpreterError("Unable to open file: " + fileName);
}

void MainWindow::InterpreterAlert(QString m)
{
    m.replace(">", "&gt;");
    m.replace("<", "&lt;");
    ui->outputText->append("<font color=\"yellow\">alert: " + m + "</font>");
}

void MainWindow::InterpreterInfo(QString m)
{
    ui->outputText->append("<font color=\"cyan\">info: " + m + "</font>");
}

void MainWindow::InterpreterError(QString m)
{
    ui->outputText->append("<font color=\"red\">err: " + m + "</font>");
}
void MainWindow::InterpreterMessage(QString m)
{
    ui->outputText->append("<font color=\"blue\">msg: " + m + "</font>");
}

void MainWindow::interpreterTimedOut()
{
    _pInterpreter->blockSignals(true);
    _pInterpreter->terminate();
    InterpreterError("Stopped due to timeout");
}

void MainWindow::on_runButton_clicked()
{
    _pTimeOut->start();
    _pTimeOut->setSingleShot(true);
    _pTimeOut->setInterval(1000);

    _pInterpreter->blockSignals(false);
    _pInterpreter->start();
}
