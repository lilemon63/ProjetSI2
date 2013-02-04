#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include "exception.h"
#include <string>

using std::string;


class ParseException : public Exception
{
public:
    template<typename T>
    static ParseException buildParseException(const string &MsgError, EXCEPTIONS_ARGS);
protected:
    ParseException(EXCEPTIONS_ARGS_CST);
};

template<typename T>
ParseException ParseException::buildParseException(const string &MsgError, EXCEPTIONS_ARGS_IMPL)
{
    string errorMessage = Exception::buildErrorMessage(MsgError,EXCEPTIONS_VALUES);
    return ParseException(errorMessage, MsgError, EXCEPTIONS_VALUES);

}


#endif // PARSEEXCEPTION_H
