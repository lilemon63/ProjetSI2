#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <string>

#include "../exception.h"

/** @brief Exception thrown when a parse error is encounter.
**  @see Exception
*/
class ParseException : public Exception
{
public:
    /** @brief create a ParseException to throw
    **  @param const std::string &MsgError : error's message
    **  @param const std::string & ClassName : name of the class which throw the exception
    **  @param const std::string & MethodName : name of the method which throw the exception
    **  @param Others : must be EPC in a class or EP out a class
    */
    template<typename T>
    static ParseException buildParseException(const std::string &MsgError, EXCEPTIONS_ARGS);
protected:
    /** @brief Build a ParseException */
    ParseException(EXCEPTIONS_ARGS_CST);
};

template<typename T>
ParseException ParseException::buildParseException(const std::string &MsgError, EXCEPTIONS_ARGS_IMPL)
{
    std::string errorMessage = Exception::buildErrorMessage(MsgError,EXCEPTIONS_VALUES);
    return ParseException(errorMessage, MsgError, EXCEPTIONS_VALUES);
}


#endif // PARSEEXCEPTION_H
