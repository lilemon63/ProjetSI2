#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "../virtualhandle.h"

class Threshold : public VirtualHandle
{
public:
    Threshold(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    ImageDataPtr startHandle(ImageDataPtr src1, ImageDataPtr src2);
};

#endif // THRESHOLD_H
