#ifndef TOFILES_H
#define TOFILES_H

#include <string>

#include "../virtualhandle.h"

class ToFiles : VirtualHandle
{
public:
    ToFiles(const std::string & path , const std::string & name = "noname");
};

#endif // TOFILES_H
