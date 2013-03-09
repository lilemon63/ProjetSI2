#ifndef PUTYOURCODEHERE_H
#define PUTYOURCODEHERE_H

#include "virtualhandle.h"


/** @brief Put your code here
    @see ModelHandle */
class PutYourCodeHere : VirtualHandle
{
   enum{ COLOR, INPUT, CHECK, MAX }; // Parameter's identifiant
public:
    PutYourCodeHere();
protected :
    /** @brief Handle one or two IplImage<br>
        An ModelHandle's startHandle() will call startHandle one more time.
        @param ImageDataPtr src1  : first image
        @param ImageDataPtr src2 : second image, NULL if unused
        @return ImageDataPtr : handle's result.
      */
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};

#endif // PUTYOURCODEHERE_H
