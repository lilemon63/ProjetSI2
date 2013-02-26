#include "nohandle.h"

NoHandle::NoHandle(const QString & affName, const std::string & name)
    : VirtualHandle(affName, name)
{
}

ImageDataPtr NoHandle::startHandle(ImageDataPtr src1, const ImageDataPtr)
{
    return src1;
}
