#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <iostream>

#include "Script/Memory/MemoryManagement.hpp"
#include "Script/Parser/ParsingTreeEntryPoint.hpp"
#include "Script/Exceptions/UnknownTokenException.hpp"
#include "Script/Exceptions/UnknownVariableException.hpp"
#include "Script/Exceptions/CarrotScriptException.hpp"
#include "Script/Exceptions/BadAccessorException.hpp"
#include "Script/Parser/Parser.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _pLexer = new Lexer();
    _pTheMotherfucking = new Parser();

    _pTimeOut = new QTimer();
    connect(_pTimeOut, SIGNAL(timeout()), this, SLOT(interpreterTimedOut()));

    on_loadButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = "/Users/alice/CarrotScript/CCS/logic.ccs";

    QFile *f = new QFile(fileName);
    if (f->open(QIODevice::ReadOnly))
    {
        try
        {
            QByteArray data = f->readAll();
            QTime executionTime;
            executionTime.start();

            _pLexer = new Lexer();
            _pLexer->parseFile(data);
            QList<QList<Token>> tokens = _pLexer->getAllTokens();
            for (int iLine = 0; iLine < tokens.count(); iLine++)
            {
                for (int iToken = 0; iToken < tokens.at(iLine).count(); iToken++)
                {
                    QString str = QString("%1: %2").arg(tokenToString(tokens.at(iLine).at(iToken).type), QString(tokens.at(iLine).at(iToken).content));
                }
            }
            ParsingTreeEntryPoint *entrypoint = _pTheMotherfucking->parse(_pLexer->getAllTokens());
            _pTree = entrypoint;
            emit InterpreterInfo(QString("spent time: %1 ms").arg(executionTime.elapsed()));
        }
        catch (const CarrotScriptException &except)
        {
            emit InterpreterError(except.what());
        }
        catch (...)
        {
            emit InterpreterError("Unknown Exception");
        }
    }
    else
        emit InterpreterError("Unable to open file: " + fileName);
}

void MainWindow::InterpreterAlert(QString m)
{
    m.replace(">", "&gt;");
    m.replace("<", "&lt;");
    ui->outputText->append("<font color=\"yellow\">" + m + "</font>");
}

void MainWindow::InterpreterInfo(QString m)
{
    ui->outputText->append("<font color=\"cyan\">" + m + "</font>");
}

void MainWindow::InterpreterError(QString m)
{
    ui->outputText->append("<font color=\"red\">" + m + "</font>");
}
void MainWindow::InterpreterMessage(QString m)
{
    ui->outputText->append("<font color=\"blue\">" + m + "</font>");
}

void MainWindow::interpreterTimedOut()
{
    InterpreterError("Stopped due to timeout");
}

void MainWindow::on_runButton_clicked()
{
    try
    {
        MemoryManagement *pMemory = new MemoryManagement();
        connect(pMemory, SIGNAL(message(QString )), this, SLOT(InterpreterMessage(QString )));
        connect(pMemory, SIGNAL(info(QString )), this, SLOT(InterpreterInfo(QString )));
        connect(pMemory, SIGNAL(warn(QString )), this, SLOT(InterpreterAlert(QString )));
        _pTree->execute(pMemory);
        _pTimeOut->start();
        _pTimeOut->setSingleShot(true);
        _pTimeOut->setInterval(1000);
    }
    catch (const CarrotScriptException &except)
    {
        QString exstr = except.exceptionDetail();
        exstr = exstr.replace("\n", "<br />");
        emit InterpreterError(exstr);
    }
    catch (...)
    {
        emit InterpreterError("Unknown Exception");
    }
}
