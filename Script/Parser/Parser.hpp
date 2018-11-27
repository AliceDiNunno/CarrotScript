#ifndef PARSER_HPP
#define PARSER_HPP

#include <QList>
#include <QByteArray>
#include <QVariant>
#include "../Lexer/Lexer.hpp"
#include "../Memory/MemoryManagement.hpp"

#include "ParsingTreeEntryPoint.hpp"
#include "ParsingTreeFunctionCall.hpp"
#include "ParsingTreeFunctionDeclaration.hpp"
#include "ParsingTreeAssignement.hpp"
#include "ParsingTreeKeyword.hpp"
#include "../Types/ParsingTreeArray.hpp"

class Parser
{
public:
    Parser();
    ParsingTreeEntryPoint *parse(QList<QList<Token>>);

private:
    QList<Token> createTokenGroups(QList<Token>, int *start);
    ParsingTreeEntryPoint *getEntryPoint(QList<Token>, int entryPointPosition);

    ParsingTreeFunctionCall *makeFunctionCall(QList<Token>);
    ParsingTreeFunctionDeclaration *makeFunctionDeclaration(QList<Token>);
    ParsingTreeAssignment *makeAssignment(QList<Token>, int position);
    ParsingTreeKeyword *makeKeyword(QList<Token>);
    ParsingTreeAccessor *makeAccessor(QList<Token>);
    ParsingTreeValue *makeValue(QList<Token>);
    ParsingTreeValue *makeLitteral(Token );
    ParsingTreeArray *makeArray(QList<Token> );
    ParsingTreeValue *readVariable(QList<Token> t);
    QList<ParsingTreeValue *> makeFunctionParameters(Token );
    ParsingTreeValue *makeOperation(QList<Token> left, Token operation, QList<Token> right);
    ParsingTreeValue *makeComparison(QList<Token> left, Token operation, QList<Token> right);
    int findEntryPoint(QList<Token> );

    ParsingTreeEntryPoint *join(QList<ParsingTreeEntryPoint *>);

    QList<ParsingTreeEntryPoint *> entryPoints;
};

#endif // PARSER_HPP
