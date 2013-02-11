#ifndef ROTATION_H
#define ROTATION_H

#include "../virtualhandle.h"

/** @brief Rotate the image */
class Rotation : VirtualHandle
{
public:
    /** @brief Create a Rotation handle
        @param int AngleRotation = 0 :default angle rotation
        @param const std::string & name = "noname" : Handle's name
        */
    Rotation( int defaultAngleRotation = 0 , const std::string & name = "noname");

    virtual ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{AngleRotation};
};

#endif // ROTATION_H
