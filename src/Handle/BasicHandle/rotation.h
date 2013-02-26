#ifndef ROTATION_H
#define ROTATION_H

#include "../virtualhandle.h"

/** @brief Rotate the image */
class Rotation : public VirtualHandle
{
public:
    /** @brief Create a Rotation handle
        @param int AngleRotation = 0 :default angle rotation
        @param const std::string & name = "noname" : Handle's name
        */
    Rotation( int defaultAngleRotation = 0 , const QString &affName="untilted", const std::string &name= "noname");
protected :
    virtual ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{AngleRotation, Max};
};

#endif // ROTATION_H
