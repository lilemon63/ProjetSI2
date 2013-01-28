#include "modelhandle.h"

//initialise your handle
namespace
{
    ModelHandle forTest;
}
/*
Rq :    You can give parameters when you initialise your handle.
        You can also give your handle's name in parameters.
*/

ModelHandle::ModelHandle()
    : VirtualHandle("Modele"), //put the handle's name
      tour(1) //for exemple
{
}

// your handle
ImageDataPtr ModelHandle::startHandle(const ImageDataPtr source, const ImageDataPtr)
{
    //write your own handle process here

    //for example :
    if(tour--)
        return VirtualHandle::executeHandle("Modele", source, NULL ); //call the handle named "modele".
    else
        return source;
}

//now you just have to edit Handle.h
