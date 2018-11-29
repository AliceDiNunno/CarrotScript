#include "BadAccessorException.hpp"

BadAccessorException::BadAccessorException(QString detail,
                                           QString fileName,
                                           QString line,
                                           int lineNumber,
                                           int colNumber):
                      CarrotScriptException ("BadAccessor",
                                             detail,
                                             fileName,
                                             line,
                                             lineNumber,
                                             colNumber)
{

}
