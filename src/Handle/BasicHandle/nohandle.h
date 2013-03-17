#ifndef NOHANDLE_H
#define NOHANDLE_H

#include "../virtualhandle.h"

/** @brief VirtualHandle which does nothing. */
class NoHandle : public VirtualHandle
{
public:
    /** @brief Build a NoHandle.
    **  @param const QString & affName = "Untilted" : shown name.
    **  @param const std::string & = "noname" : VirtualHandle's name.
    */
    NoHandle(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};

#endif // NOHANDLE_H
