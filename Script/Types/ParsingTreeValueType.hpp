#ifndef PARSINGTREEVALUETYPE_HPP
#define PARSINGTREEVALUETYPE_HPP

enum ParsingTreeValueType
{
    PTVT_String, // "Hello World"
    PTVT_Array, // ["A", "B"]
    PTVT_Int, // 12
    PTVT_Float, // 12.34
    PTVT_Bool, // true, false
    PTVT_Unknown, // For functions
};

#endif // PARSINGTREEVALUETYPE_HPP
