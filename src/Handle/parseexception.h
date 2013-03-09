#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <string>

#include "../exception.h"

class ParseException : public Exception
{
public:
    template<typename T>
    static ParseException buildParseException(const std::string &MsgError, EXCEPTIONS_ARGS);
protected:
    ParseException(EXCEPTIONS_ARGS_CST);
};

template<typename T>
ParseException ParseException::buildParseException(const std::string &MsgError, EXCEPTIONS_ARGS_IMPL)
{
    std::string errorMessage = Exception::buildErrorMessage(MsgError,EXCEPTIONS_VALUES);
    return ParseException(errorMessage, MsgError, EXCEPTIONS_VALUES);
}


#endif // PARSEEXCEPTION_H
