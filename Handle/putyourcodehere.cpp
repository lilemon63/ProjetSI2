#include "putyourcodehere.h"

namespace
{
    PutYourCodeHere forHandle;
}

PutYourCodeHere::PutYourCodeHere()
    : VirtualHandle("PutYourCodeHere") //handle's name
{
}

// your handle
ImageDataPtr PutYourCodeHere::startHandle(const ImageDataPtr source, const ImageDataPtr)
{
    //put your code here !
    return source;
}
