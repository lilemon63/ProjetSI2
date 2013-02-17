#ifndef HANDLETOOLS_H
#define HANDLETOOLS_H

#include "Handle.h"

/** @brief Keep alive some named Handle as long we don't destroy it */
class HandleTools
{
public :
    HandleTools();
private :
    ModelHandle m;
    Rotation rotation;
    ToFiles tofiles;
    PutYourCodeHere p;
};
#endif // HANDLETOOLS_H
