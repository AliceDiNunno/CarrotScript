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

CONFIG += c++11



FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mainwindow.h \
    Script/Binding/ScriptClassBinding.hpp \
    Script/Binding/ScriptMemoryBinding.hpp \
    Script/Exceptions/CarrotScriptException.hpp \
    Script/Exceptions/UnknownTokenException.hpp \
    Script/Lexer/Lexer.hpp \
    Script/Lexer/Token.hpp \
    Script/Lexer/TokenizeItem.hpp \
    Script/Lexer/TokenType.hpp \
    Script/Memory/MemoryManagement.hpp \
    Script/Memory/MemoryScriptVariable.hpp \
    Script/Memory/ParsingTreeAccessor.hpp \
    Script/Memory/ParsingTreeIdentifier.hpp \
    Script/Memory/ParsingTreeVariabeRead.hpp \
    Script/Operations/ParsingTreeComparison.hpp \
    Script/Operations/ParsingTreeOperation.hpp \
    Script/Operations/ParsingTreeOperationType.hpp \
    Script/Operations/ParsingTreeValueComparisonType.hpp \
    Script/Parser/Parser.hpp \
    Script/Parser/ParsingTreeCalculateValuePriority.hpp \
    Script/Parser/ParsingTreeCondition.hpp \
    Script/Parser/ParsingTreeEntryPoint.hpp \
    Script/Parser/ParsingTreeEntryPointPriority.hpp \
    Script/Parser/ParsingTreeExecutable.hpp \
    Script/Parser/ParsingTreeFunctionCall.hpp \
    Script/Parser/ParsingTreeFunctionDeclaration.hpp \
    Script/Parser/ParsingTreeKeyword.hpp \
    Script/Parser/ParsingTreeKeywordType.hpp \
    Script/Types/ParsingTreeArray.hpp \
    Script/Types/ParsingTreeBoolean.hpp \
    Script/Types/ParsingTreeFloat.hpp \
    Script/Types/ParsingTreeInteger.hpp \
    Script/Types/ParsingTreeString.hpp \
    Script/Types/ParsingTreeValue.hpp \
    Script/Types/ParsingTreeValueType.hpp \
    Script/Parser/ParsingTreeAssignment.hpp \
    Script/Lexer/TokenStrings.hpp \
    Script/Exceptions/BadAccessorException.hpp \
    Script/Exceptions/UnknownVariableException.hpp \
    Script/Exceptions/InterpreterErrorException.hpp \
    Script/Exceptions/InvalidMemoryOperationException.hpp \
    Script/Exceptions/InvalidComparisonException.hpp \
    Script/Exceptions/InvalidOperationException.hpp \
    Script/Exceptions/UnxpectedTokenException.hpp \
    Script/Library/StandardLibrary.hpp

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Script/Exceptions/CarrotScriptException.cpp \
    Script/Exceptions/UnknownTokenException.cpp \
    Script/Lexer/Lexer.cpp \
    Script/Lexer/Token.cpp \
    Script/Lexer/TokenType.cpp \
    Script/Memory/MemoryManagement.cpp \
    Script/Memory/ParsingTreeAccessor.cpp \
    Script/Parser/Parser.cpp \
    Script/Parser/ParsingTreeExecutable.cpp \
    Script/Types/ParsingTreeBoolean.cpp \
    Script/Types/ParsingTreeFloat.cpp \
    Script/Types/ParsingTreeInteger.cpp \
    Script/Types/ParsingTreeString.cpp \
    Script/Memory/ParsingTreeIdentifier.cpp \
    Script/Memory/ParsingTreeVariableRead.cpp \
    Script/Operations/ParsingTreeComparison.cpp \
    Script/Operations/ParsingTreeOperation.cpp \
    Script/Parser/ParsingTreeAssignment.cpp \
    Script/Parser/ParsingTreeCondition.cpp \
    Script/Parser/ParsingTreeEntryPoint.cpp \
    Script/Parser/ParsingTreeFunctionCall.cpp \
    Script/Parser/ParsingTreeFunctionDeclaration.cpp \
    Script/Parser/ParsingTreeKeyword.cpp \
    Script/Types/ParsingTreeArray.cpp \
    Script/Types/ParsingTreeValue.cpp \
    Script/Binding/ScriptMemoryBinding.cpp \
    Script/Parser/ParsingTreeKeywordType.cpp \
    Script/Operations/ParsingTreeValueComparisonType.cpp \
    Script/Parser/ParsingTreeCalculateValuePriority.cpp \
    Script/Exceptions/BadAccessorException.cpp \
    Script/Exceptions/UnknownVariableException.cpp \
    Script/Exceptions/InterpreterErrorException.cpp \
    Script/Exceptions/InvalidMemoryOperationException.cpp \
    Script/Exceptions/InvalidComparisonException.cpp \
    Script/Exceptions/InvalidOperationException.cpp \
    Script/Exceptions/UnxpectedTokenException.cpp \
    Script/Binding/ScriptClassBinding.cpp \
    Script/Library/StandardLibrary.cpp
