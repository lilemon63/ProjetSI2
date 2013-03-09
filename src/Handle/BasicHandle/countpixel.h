#ifndef COUNTPIXEL_H
#define COUNTPIXEL_H

#include "../virtualhandle.h"

class CountPixel : public VirtualHandle
{
    enum{SCRIPT, NAME, MAX};
public:
    CountPixel(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};

#endif // COUNTPIXEL_H
