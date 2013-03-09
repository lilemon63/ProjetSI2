#ifndef HANDLETOOLS_H
#define HANDLETOOLS_H

#include "Handle.h"

/** @brief Keep alive some named Handle as long we don't destroy it */
class HandleTools
{
public :
    HandleTools();
private :
    ToVideo video;
    ToFiles tofiles;
    NoHandle noHandle;
    Rotation rotation;
    ModelHandle model;
    CountPixel countPixel;
    EditChannel editChannel;
    PutYourCodeHere putYourCodeHere;
};
#endif // HANDLETOOLS_H
