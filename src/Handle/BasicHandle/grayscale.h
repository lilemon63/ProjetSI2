#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../virtualhandle.h"

class Grayscale : public VirtualHandle
{
public:
    Grayscale(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    ImageDataPtr startHandle(ImageDataPtr src1, ImageDataPtr src2);
};


#endif // GRAYSCALE_H
