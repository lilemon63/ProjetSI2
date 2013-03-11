#ifndef HANDLETOOLS_H
#define HANDLETOOLS_H

#include "Handle.h"

/**
**  @brief Keep alive some named VirtualHandle as long we don't destroy it.
**
**  It's used to acces some VirtualHandle by their names in other VirtualHandle, or into a ComboBox for
    example for the handle selection when creating a ZI.
**
*/
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
