#ifndef NOHANDLE_H
#define NOHANDLE_H

#include "../virtualhandle.h"

class NoHandle : public VirtualHandle
{
public:
    NoHandle(const std::string &);
protected :
    ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};

#endif // NOHANDLE_H
