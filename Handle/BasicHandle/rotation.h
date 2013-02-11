#ifndef ROTATION_H
#define ROTATION_H

#include "../virtualhandle.h"

class Rotation : VirtualHandle
{
public:
    Rotation( int defaultValue = 0 , const std::string & name = "noname");

    virtual ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{AngleRotation};
};

#endif // ROTATION_H
