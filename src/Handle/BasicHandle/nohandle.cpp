#include "nohandle.h"

NoHandle::NoHandle(const std::string & name)
    : VirtualHandle(name)
{
}

ImageDataPtr NoHandle::startHandle(ImageDataPtr src1, const ImageDataPtr)
{
    return src1;
}
