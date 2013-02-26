#ifndef NOHANDLE_H
#define NOHANDLE_H

#include "../virtualhandle.h"

class NoHandle : public VirtualHandle
{
public:
    NoHandle(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};

#endif // NOHANDLE_H
