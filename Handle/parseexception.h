#ifndef PARSEEXCEPTION_H
#define PARSEEXCEPTION_H

#include <exception>
#include <string>

using std::exception;
using std::string;

class parseException : public exception
{
public:
    parseException(string s);
};

#endif // PARSEEXCEPTION_H
