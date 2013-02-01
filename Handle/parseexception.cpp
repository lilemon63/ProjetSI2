#include "parseexception.h"
#include <iostream>



parseException::parseException(string s)
{
    std::cerr << "Exception when the file is parsed : " << s << std::endl;
}
