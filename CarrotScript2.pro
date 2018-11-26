#-------------------------------------------------
#
# Project created by QtCreator 2018-10-25T10:26:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG+=sdk_no_version_check
TARGET = CarrotScript
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Lexer.cpp \
    Parser.cpp \
    Token.cpp \
    CarrotScriptException.cpp \
    UnknownTokenException.cpp \
    TokenType.cpp \
    MemoryManagement.cpp \
    ParsingTreeBoolean.cpp \
    ParsingTreeFloat.cpp \
    ParsingTreeInteger.cpp \
    ParsingTreeString.cpp \
    ParsingTreeExecutable.cpp

HEADERS += \
    mainwindow.h \
    Lexer.hpp \
    Parser.hpp \
    Token.hpp \
    CarrotScriptException.hpp \
    UnknownTokenException.hpp \
    TokenType.hpp \
    TokenizeItem.hpp \
    ParsingTreeOperationType.hpp \
    ParsingTreeValueType.hpp \
    ParsingTreeValueComparisonType.hpp \
    ParsingTreeExecutable.hpp \
    ParsingTreeEntryPoint.hpp \
    ParsingTreeValue.hpp \
    ParsingTreeString.hpp \
    ParsingTreeIdentifier.hpp \
    ParsingTreeInteger.hpp \
    ParsingTreeFloat.hpp \
    ParsingTreeBoolean.hpp \
    ParsingTreeArray.hpp \
    ParsingTreeAccessor.hpp \
    ParsingTreeComparison.hpp \
    ParsingTreeFunctionCall.hpp \
    ParsingTreeFunctionDeclaration.hpp \
    ParsingTreeAssignement.hpp \
    ParsingTreeKeywordType.hpp \
    ParsingTreeKeyword.hpp \
    ParsingTreeCondition.hpp \
    ParsingTreeEntryPointPriority.hpp \
    ParsingTreeCalculateValuePriority.hpp \
    MemoryManagement.hpp \
    ScriptMemoryBinding.hpp \
    MemoryScriptVariable.hpp \
    ScriptClassBinding.hpp \
    ParsingTreeOperation.hpp \
    ParsingTreeVariabeRead.hpp

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
