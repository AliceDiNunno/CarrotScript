#ifndef PARSINGTREEKEYWORDTYPE_HPP
#define PARSINGTREEKEYWORDTYPE_HPP

#include "QByteArray"

enum ParsingTreeKeywordType
{
    PTKT_While,
    PTKT_If,
    PTKT_Else,
    PTKT_Require,
    PTKT_Return,
    PTKT_End,
    PTKT_Unknown,
};

extern ParsingTreeKeywordType getKeywordType(QByteArray keyword);

#endif // PARSINGTREEKEYWORDTYPE_HPP
