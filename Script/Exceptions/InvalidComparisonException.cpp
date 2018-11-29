#include "InvalidComparisonException.hpp"

InvalidComparisonException::InvalidComparisonException(QString detail,
                                                       QString fileName,
                                                       QString line,
                                                       int lineNumber,
                                                       int colNumber):
                                  CarrotScriptException ("InvalidComparison",
                                                         detail,
                                                         fileName,
                                                         line,
                                                         lineNumber,
                                                         colNumber)
{

}
