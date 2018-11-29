#include "Parser.hpp"
#include <QDebug>

#include "ParsingTreeAssignment.hpp"
#include "ParsingTreeCalculateValuePriority.hpp"
#include "ParsingTreeCondition.hpp"
#include "ParsingTreeEntryPoint.hpp"
#include "ParsingTreeEntryPointPriority.hpp"
#include "ParsingTreeFunctionCall.hpp"
#include "ParsingTreeFunctionDeclaration.hpp"
#include "../Exceptions/UnknownTokenException.hpp"
#include "../Lexer/Lexer.hpp"
#include "../Lexer/TokenStrings.hpp"
#include "../Memory/ParsingTreeVariabeRead.hpp"
#include "../Operations/ParsingTreeValueComparisonType.hpp"
#include "../Operations/ParsingTreeOperationType.hpp"
#include "../Operations/ParsingTreeOperation.hpp"
#include "../Operations/ParsingTreeComparison.hpp"
#include "../Types/ParsingTreeValueType.hpp"
#include "../Types/ParsingTreeArray.hpp"
#include "../Types/ParsingTreeString.hpp"
#include "../Types/ParsingTreeInteger.hpp"
#include "../Types/ParsingTreeFloat.hpp"
#include "../Types/ParsingTreeBoolean.hpp"

Parser::Parser()
{

}

ParsingTreeEntryPoint *Parser::parse(QList<QList<Token> > tokens)
{
    QList<ParsingTreeEntryPoint *> entrypoints;
    for (int iLiner = 0; iLiner < tokens.count(); iLiner++)
    {
        int start = 0;
        QList<Token> tokenGroups = createTokenGroups(tokens.at(iLiner), &start);
        ParsingTreeEntryPoint *entryPoint = getEntryPoint(tokenGroups, findEntryPoint(tokenGroups));
        entryPoints << entryPoint;
    }
    return join(entryPoints);
}

ParsingTreeFunctionCall *Parser::makeFunctionCall(QList<Token> tokens)
{
    ParsingTreeFunctionCall *fnc = new ParsingTreeFunctionCall();

    QList<Token> accessorTokens = tokens.mid(0, tokens.count() - 1);
    Token functionParameter = tokens.mid(tokens.count() - 1, 1).at(0);

    ParsingTreeAccessor *pta = makeAccessor(accessorTokens);

    fnc->source = pta;
    fnc->arguments = makeFunctionParameters(functionParameter);

    return fnc;
}

QList<ParsingTreeValue *> Parser::makeFunctionParameters(Token t)
{
    QList<ParsingTreeValue *> values;
    QList<Token> subtokens = t.subTokens;
    QList<QList<Token>> tokenParameters;

    QList<Token> currentList = QList<Token>();
    for (int i = 0; i < subtokens.count(); i++)
    {
        if (subtokens.at(i).type == T_ArgumentSeparator)
        {
            tokenParameters << currentList;
            currentList = QList<Token>();
            continue;
        }
        currentList << subtokens.at(i);
    }
    if (!currentList.isEmpty())
        tokenParameters << currentList;

    for(int i = 0; i < tokenParameters.count(); i++)
    {
        ParsingTreeValue *pv = makeValue(tokenParameters.at(i));

        values << pv;
    }

    return values;
}

ParsingTreeFunctionDeclaration *Parser::makeFunctionDeclaration(QList<Token> tokens)
{
    ParsingTreeFunctionDeclaration *fnc = new ParsingTreeFunctionDeclaration();

    fnc->name = tokens.at(1).content;

    for (int i = 2; i < tokens.count(); i++)
    {
        if (tokens.at(i).type == T_Identifier)
            fnc->variableNames.append(tokens.at(i).content);
        else if (tokens.at(i).type == T_ArgumentSeparator)
        {
            //Do Nothing
            //Todo: err management
        }
        else
        {
            //Err
        }
    }

    return fnc;
}

ParsingTreeAssignment *Parser::makeAssignment(QList<Token> tokens, int position)
{
    Token token = tokens.at(position);
    ParsingTreeAssignment *ass = new ParsingTreeAssignment();

    QList<Token> leftTokens = tokens.mid(0, position);

    ParsingTreeAccessor *accessor = makeAccessor(leftTokens);


    if (token.content != CS_LEXER_PLUSPLUS_OPERATOR &&
        token.content != CS_LEXER_MINUSMINUS_OPERATOR &&
        token.content != CS_LEXER_PLUSEQUAL_OPERATOR &&
        token.content != CS_LEXER_MINUSEQUAL_OPERATOR &&
        token.content != CS_LEXER_DIVIDEEQUAL_OPERATOR &&
        token.content != CS_LEXER_MULTIPLYEQUAL_OPERATOR)
    {
        QList<Token> rightTokens = tokens.mid(position + 1, tokens.count());

        ParsingTreeValue *value = makeValue(rightTokens);

        ass->symbol = token.content;
        ass->from = value;
    }
    else if (token.content == CS_LEXER_PLUSPLUS_OPERATOR ||
             token.content == CS_LEXER_MINUSMINUS_OPERATOR)
    {
        Token tok;
        tok.column = token.column;
        tok.lineNumber = token.lineNumber;
        tok.lineStr = token.lineStr;
        tok.content = "1";
        tok.type = T_NumericLitteral;

        ParsingTreeValue *value = makeValue({tok});
        ass->symbol = tok.content;
        ass->from = value;
        /////////////////////
        QList<Token> rightTokens = tokens.mid(position + 1, tokens.count());

        ass->symbol = CS_LEXER_EQUAL_OPERATOR;
        Token tokOp;
        tokOp.column = token.column;
        tokOp.lineNumber = token.lineNumber;
        tokOp.lineStr = token.lineStr;
        tokOp.type = T_Operation;
        if (token.content == CS_LEXER_PLUSPLUS_OPERATOR)
        {
            tokOp.content = CS_LEXER_PLUS_OPERATOR;
        }
        else if (token.content == CS_LEXER_MINUSMINUS_OPERATOR)
        {
            tokOp.content = CS_LEXER_MINUS_OPERATOR;
        }
        ass->from = makeOperation(leftTokens, tokOp, {tok});

    }
    else
    {
        QList<Token> rightTokens = tokens.mid(position + 1, tokens.count());

        ass->symbol = CS_LEXER_EQUAL_OPERATOR;
        Token tok;
        tok.column = token.column;
        tok.lineNumber = token.lineNumber;
        tok.lineStr = token.lineStr;
        tok.type = T_Operation;
        if (token.content == CS_LEXER_PLUSEQUAL_OPERATOR)
        {
            tok.content = CS_LEXER_PLUS_OPERATOR;
        }
        else if (token.content == CS_LEXER_MINUSEQUAL_OPERATOR)
        {
            tok.content = CS_LEXER_MINUS_OPERATOR;
        }
        else if (token.content == CS_LEXER_DIVIDEEQUAL_OPERATOR)
        {
            tok.content = CS_LEXER_DIVIDE_OPERATOR;
        }
        else if (token.content == CS_LEXER_MULTIPLYEQUAL_OPERATOR)
        {
            tok.content = CS_LEXER_MULTIPLY_OPERATOR;
        }
        ass->from = makeOperation(leftTokens, tok, rightTokens);
    }

    ass->to = accessor;

    return ass;
}

ParsingTreeAccessor *Parser::makeAccessorFromIdentifier(ParsingTreeIdentifier *ids)
{
    ParsingTreeAccessor *pta = dynamic_cast<ParsingTreeAccessor *>(ids);
    if (!pta)
    {
        pta = new ParsingTreeAccessor();
        pta->child = nullptr;
        pta->fallback = ids->fallback;
        pta->line = ids->line;
        pta->lineNumber = ids->lineNumber;
        pta->name = ids->name;
        pta->next = ids->next;
        pta->success = ids->success;
    }
    return pta;
}

ParsingTreeOperationType operationFromToken(Token tkn)
{
    if (tkn.content == CS_LEXER_PLUS_OPERATOR)
        return PTOT_Add;
    else if (tkn.content == CS_LEXER_MINUS_OPERATOR)
        return PTOT_Remove;
    else if (tkn.content == CS_LEXER_MULTIPLY_OPERATOR)
        return PTOT_Multiply;
    else if (tkn.content == CS_LEXER_DIVIDE_OPERATOR)
        return PTOT_Divide;
    else
    {
        return PTOT_Unknown;
    }
}

ParsingTreeAccessor *Parser::makeAccessor(QList<Token> tokens)
{
    ParsingTreeAccessor *accessor = new ParsingTreeAccessor();
    ParsingTreeAccessor *current = accessor;

    TokenType lastType = T_Unknown;

    for (int iToken = 0; iToken < tokens.count(); iToken++)
    {
        Token t = tokens.at(iToken);
        if (t.type == T_Identifier)
        {
            ParsingTreeString *str = new ParsingTreeString();
            str->value = t.content;
            current->name = str;
        }
        else if (iToken > 0 && (t.type == T_ModuleAccess || t.type == T_EnterArray))
        {
            ParsingTreeAccessor *child = new ParsingTreeAccessor();
            current->child = child;
            current = child;

            if (t.type == T_EnterArray && t.subTokens.count() > 0)
            {
                current->name = makeValue(t.subTokens);
            }
        }
        lastType = t.type;
    }
    return accessor;
}

ParsingTreeArray *Parser::makeArray(QList<Token> tokens)
{
    QList<QList<Token>> values;
    QList<Token> currentValue;
    for (int iToken = 0; iToken < tokens.count(); iToken++)
    {
        Token t = tokens.at(iToken);
        if (t.type == T_ArgumentSeparator)
        {
            values << currentValue;
            currentValue.clear();
        }
        else
        {
            currentValue << t;
        }
    }


    ParsingTreeArray *pta = new ParsingTreeArray();

    for (int iP = 0; iP < values.count(); iP++)
    {
        QList<Token> valval = values.at(iP);
        pta->values.append(makeValue(valval));
    }

    return pta;
}

ParsingTreeValue *Parser::readVariable(QList<Token> t)
{
    ParsingTreeVariabeRead *ptvr = new ParsingTreeVariabeRead();

    ptvr->id = makeAccessor(t);

    return ptvr;
}

ParsingTreeValue *Parser::makeValue(QList<Token> tokens)
{
    if (tokens.count() == 0)
        return nullptr;
    int lessPrioritizedItem = PTCVP_Parenthesis + 1;
    int lessPrioritizedItemIndex = -1;

    if (tokens.count() == 1)
    {
        if (tokens.at(0).type == T_EnterPriority)
            return makeValue(tokens.at(0).subTokens);
        else if (tokens.at(0).type == T_EnterDefineArray)
            return makeArray(tokens.at(0).subTokens);
        else if (tokens.at(0).type == T_Identifier)
        {
            return readVariable(tokens);
        }
        ParsingTreeValue *val = makeLitteral(tokens.at(0));
        return val;
    }

    //Actually building the tree in the inverse order so that the execution will be made from bottom to top (with priorities right)
    for (int iToken = 0; iToken < tokens.count(); iToken++)
    {
        Token currentToken = tokens.at(iToken);

        //qDebug() << "check " << currentToken.content << tts(currentToken.type);
        ParsingTreeCalculateValuePriority precedence = getPrecedenceFromToken(currentToken);
        if (currentToken.type == T_Comparison && currentToken.content == CS_LEXER_NOT_OPERATOR)
            continue;

        if (precedence == PTCVP_Unsupported)
            continue;

        if (precedence < lessPrioritizedItem)
        {
            //qDebug() << "prio";
            lessPrioritizedItem = precedence;
            lessPrioritizedItemIndex = iToken;
        }
    }

    if (lessPrioritizedItemIndex == -1 && tokens.count() > 0)
    {
        if (Lexer::isFunction(tokens))
        {
            return makeFunctionCall(tokens);
        }
        return makeAccessor(tokens);
    }

    Token currentToken = tokens.at(lessPrioritizedItemIndex);
    if (lessPrioritizedItem == PTCVP_Parenthesis)
    {
        return makeValue(currentToken.subTokens);
    }
    else
    {
        QList<Token> leftTokens = tokens.mid(0, lessPrioritizedItemIndex);
        QList<Token> rightTokens = tokens.mid(lessPrioritizedItemIndex + 1, tokens.count());

        ParsingTreeValue *value = nullptr;
        if (lessPrioritizedItem == PTCVP_PlusMinus || lessPrioritizedItem == PTCVP_MultiplyDivide)
        {
            value = makeOperation(leftTokens, currentToken, rightTokens);
        }
        else if (lessPrioritizedItem == PTCVP_And || lessPrioritizedItem == PTCVP_Or || lessPrioritizedItem == PTCVP_Comparison)
        {
            value = makeComparison(leftTokens, currentToken, rightTokens);
        }
        return value; //err on nullptr ?
    }
}

ParsingTreeValue *Parser::makeOperation(QList<Token> left, Token operation, QList<Token> right)
{
    ParsingTreeOperation *op = new ParsingTreeOperation();

    op->left = makeValue(left);
    op->type = operationFromToken(operation);
    op->right = makeValue(right);

    return op;
}

ParsingTreeValue *Parser::makeComparison(QList<Token> left, Token operation, QList<Token> right)
{
    ParsingTreeComparison *cmp = new ParsingTreeComparison();

    cmp->left = makeValue(left);
    cmp->type = comparisonTypeFromToken(operation);
    cmp->right = makeValue(right);

    return cmp;
}

ParsingTreeValue *Parser::makeLitteral(Token t)
{
    if (t.type == T_StringLitteral)
    {
        ParsingTreeString *str = new ParsingTreeString();
        str->value = t.content;
        return str;
    }
    if (t.type == T_NumericLitteral)
    {
        ParsingTreeInteger *intg = new ParsingTreeInteger();
        intg->value = t.content.toInt();
        return intg;
    }
    if (t.type == T_FloatLitteral)
    {
        ParsingTreeFloat *flt = new ParsingTreeFloat();
        flt->value = t.content.toDouble();
        return flt;
    }
    if (t.type == T_BoolLitteral)
    {
        ParsingTreeBoolean *bln = new ParsingTreeBoolean();
        bln->value = (t.content == CS_LEXER_TRUE_BOOL);
        return bln;
    }
    return nullptr;
}

ParsingTreeKeyword *Parser::makeKeyword(QList<Token> tokens)
{
    ParsingTreeKeyword *keyword = new ParsingTreeKeyword();

    keyword->type = getKeywordType(tokens.at(0).content);
    tokens = tokens.mid(1, tokens.count());

    if (tokens.count() == 1 && tokens.at(0).subTokens.count() > 0 && tokens.at(0).content == CS_LEXER_FUNCTION_SEPARATOR)
        tokens = tokens.at(0).subTokens;

    if ((keyword->type == PTKT_Else || keyword->type == PTKT_End) && tokens.count() > 0)
    {
        //Error
    }

    if (keyword->type == PTKT_If || keyword->type == PTKT_While)
    {
        bool invertCondition = false;
        if (tokens.count() > 1 && tokens.at(0).content == CS_LEXER_NOT_OPERATOR && tokens.at(0).type == T_Comparison)
        {
            invertCondition = true;
            tokens.removeFirst();
        }

        ParsingTreeKeywordType type = keyword->type;
        delete keyword;
        keyword = new ParsingTreeCondition();
        keyword->type = type;

        ParsingTreeValue *ptv = makeValue(tokens);

        ParsingTreeComparison *ptc = dynamic_cast<ParsingTreeComparison *>(ptv);
        ParsingTreeBoolean *ptb = dynamic_cast<ParsingTreeBoolean *>(ptv);
        ParsingTreeVariabeRead *ptr = dynamic_cast<ParsingTreeVariabeRead *>(ptv);

        if (ptc)
        {
            ptc->successOnFailure = invertCondition;
            ((ParsingTreeCondition *)keyword)->condition = ptc;
        }
        else if (ptb)
        {
            ptc = new ParsingTreeComparison();
            ptc->successOnFailure = invertCondition;
            ptc->left = ptb;
            ParsingTreeBoolean *ptbb = new ParsingTreeBoolean();
            ptbb->value = true;
            ptc->right = ptbb;
            ptc->type = PTVCT_Equals;
            ((ParsingTreeCondition *)keyword)->condition = ptc;
        }
        else if (ptr)
        {
            ptc = new ParsingTreeComparison();
            ptc->successOnFailure = invertCondition;
            ptc->left = ptr;
            ParsingTreeBoolean *ptbb = new ParsingTreeBoolean();
            ptbb->value = true;
            ptc->right = ptbb;
            ptc->type = PTVCT_Equals;
            ((ParsingTreeCondition *)keyword)->condition = ptc;
        }
        else
        {
            //qDebug() << "COMPARISON, VAR AND BOOL FAIL" << MemoryManagement::translateValue(ptv);
        }

    }

    if (keyword->type == PTKT_Return)
    {
        keyword->value = makeValue(tokens);
    }

    return keyword;
}

ParsingTreeEntryPoint *Parser::getEntryPoint(QList<Token> tokens, int pos)
{
    Token entryPointToken = tokens.at(pos);
    ParsingTreeEntryPoint *ptep = nullptr;
    if (entryPointToken.type == T_EnterFunction)
    {
        ptep = makeFunctionCall(tokens);
    }
    else if (entryPointToken.type == T_Assignement)
    {
        ptep = makeAssignment(tokens, pos);
    }
    else if (entryPointToken.type == T_Keyword)
    {
        if (pos != 0)
        {
            //TODO err because keyword can't be preceded
        }

        if (entryPointToken.content == CS_LEXER_FUNC_KEYWORD)
        {
            ptep = makeFunctionDeclaration(tokens);
        }
        else
        {
            ptep = makeKeyword(tokens);
        }
    }

    ptep->line = entryPointToken.lineStr;
    ptep->lineNumber = entryPointToken.lineNumber;

    return ptep;
}

int Parser::findEntryPoint(QList<Token> tokens)
{
    ParsingTreeEntryPointPriority iCurrentPriority = PTEPP_Unknown;
    int entryPointPosition = -1;
    for (int iToken = 0; iToken < tokens.count(); iToken++)
    {
        ParsingTreeEntryPointPriority currentPriority = PTEPP_Unknown;

        Token t = tokens.at(iToken);
        if (t.type == T_Assignement)
            currentPriority = PTEPP_Assignation;
        else if (t.type == T_EnterFunction)
            currentPriority = PTEPP_FunctionCall;
        else if (t.type == T_Keyword)
            currentPriority = PTEPP_Keyword;
        if (iCurrentPriority < currentPriority)
        {
            iCurrentPriority = currentPriority;
            entryPointPosition = iToken;
        }
    }
    return entryPointPosition;
}

QList<Token> Parser::createTokenGroups(QList<Token> tokens, int *start)
{
    QList<Token> tk;
    while ((*start) < tokens.count())
    {
        Token t = tokens.at(*start);
        if (Lexer::isTokenEnter(t.type))
        {
            (*start)++;

            Token separator;
            separator.type = t.type;
            separator.content = contentFromTokenType(t.type);
            separator.lineNumber = t.lineNumber;
            separator.lineStr = t.lineStr;
            separator.column = t.column;

            separator.subTokens.append(createTokenGroups(tokens, start));
            tk.append(separator);
        }
        else
        {
            (*start)++;
            if (Lexer::isTokenExit(t.type))
            {
                return tk;
            }
            tk.append(t);
        }
    }
    return tk;
}

ParsingTreeEntryPoint *Parser::joinCondition(QList<ParsingTreeEntryPoint *> eps, int *from)
{
    ParsingTreeCondition *currentCondition = dynamic_cast<ParsingTreeCondition *>(eps.at(*from));
    (*from)++;

    ParsingTreeEntryPoint *lastOne = currentCondition;

    bool shouldSwitchToElse = false;
    bool shouldStart = true;
    for (; (*from) < eps.count(); (*from)++)
    {
        ParsingTreeEntryPoint *pCurrentEntryPoint = eps.at(*from);

        if (ParsingTreeKeyword *kwrd = dynamic_cast<ParsingTreeKeyword *>(pCurrentEntryPoint))
        {
            if (currentCondition->type == PTKT_If && kwrd->type == PTKT_Else)
            {
                shouldSwitchToElse = true;
                kwrd->type = PTKT_End;
                lastOne->next = kwrd;
                continue;
            }
            else if ((currentCondition->type != PTKT_If && kwrd->type == PTKT_Else) ||
                     (kwrd->type == PTKT_Return))
            {
                //err
            }
            else if (kwrd->type == PTKT_End)
            {
                lastOne->next = kwrd;
                break;
            }
            else if (currentCondition != pCurrentEntryPoint)
            {
                pCurrentEntryPoint = joinKeyword(eps, from);
            }
        }

        if (shouldStart)
        {
            pCurrentEntryPoint->scopeChange = 1;
            shouldStart = false;
            currentCondition->success = pCurrentEntryPoint;
        }
        else if (shouldSwitchToElse)
        {
            pCurrentEntryPoint->scopeChange = 1;
            shouldSwitchToElse = false;
            currentCondition->fallback = pCurrentEntryPoint;
        }
        else
        {
            lastOne->next = pCurrentEntryPoint;
        }

        lastOne = pCurrentEntryPoint;
    }

    return currentCondition;
}

ParsingTreeEntryPoint *Parser::joinFunctionDeclaration(QList<ParsingTreeEntryPoint *> eps, int *from)
{
    Q_UNUSED(from);

    ParsingTreeFunctionDeclaration *currentFunction = dynamic_cast<ParsingTreeFunctionDeclaration *>(eps.at(0));

    return currentFunction;
}

ParsingTreeEntryPoint *Parser::joinKeyword(QList<ParsingTreeEntryPoint *> eps, int *from)
{
    ParsingTreeKeyword *pCurrentEntryPoint = dynamic_cast<ParsingTreeKeyword *>(eps.at(*from));

    if (dynamic_cast<ParsingTreeCondition *>(pCurrentEntryPoint))
    {
        ParsingTreeEntryPoint *decl;
        decl = joinCondition(eps, from);
        return decl;
    }
    //err here
    return nullptr;
}

ParsingTreeEntryPoint *Parser::join(QList<ParsingTreeEntryPoint *> eps)
{
    ParsingTreeEntryPoint *pLastEntryPoint = eps.at(0);
    for (int i = 0; i < eps.count(); i++)
    {
        ParsingTreeEntryPoint *pCurrentEntryPoint = eps.at(i);
        if (pCurrentEntryPoint)
        {
            if (dynamic_cast<ParsingTreeFunctionDeclaration *>(pCurrentEntryPoint))
            {
                ParsingTreeEntryPoint *decl;
                decl = joinFunctionDeclaration(eps, &i);

                pLastEntryPoint->next = pCurrentEntryPoint;
                pLastEntryPoint = pCurrentEntryPoint;
                continue;
            }
            else if (dynamic_cast<ParsingTreeKeyword *>(pCurrentEntryPoint))
            {
                pCurrentEntryPoint = joinKeyword(eps, &i);

                pLastEntryPoint->next = pCurrentEntryPoint;
                pLastEntryPoint = pCurrentEntryPoint;
                continue;
            }

            if (pCurrentEntryPoint != pLastEntryPoint)
            {
                pLastEntryPoint->next = pCurrentEntryPoint;
                pLastEntryPoint = pCurrentEntryPoint;
            }
        }
    }
    return eps.first();
}


