#ifndef PARSER_HPP
#define PARSER_HPP

#include <QList>
#include <QByteArray>
#include <QVariant>

#include "../Lexer/Token.hpp"

struct ParsingTreeEntryPoint;
struct ParsingTreeValue;
struct ParsingTreeAssignment;
struct ParsingTreeFunctionCall;
struct ParsingTreeFunctionDeclaration;
struct ParsingTreeKeyword;
struct ParsingTreeAccessor;
struct ParsingTreeArray;
struct ParsingTreeIdentifier;
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
    ParsingTreeAccessor *makeAccessorFromIdentifier(ParsingTreeIdentifier *ids);
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
    ParsingTreeEntryPoint *joinCondition(QList<ParsingTreeEntryPoint *> eps, int *from);
    ParsingTreeEntryPoint *joinFunctionDeclaration(QList<ParsingTreeEntryPoint *> eps, int *from);
    ParsingTreeEntryPoint *joinKeyword(QList<ParsingTreeEntryPoint *> eps, int *from);

    QList<ParsingTreeEntryPoint *> entryPoints;
};

#endif // PARSER_HPP
