#ifndef ROTATION_H
#define ROTATION_H

#include "../virtualhandle.h"

/** @brief VirtualHandle which rotate the image. */
class Rotation : public VirtualHandle
{
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
    enum PARAM_ID{
                    /** @brief Rotation's angle. */
                    AngleRotation,
                    /** @brief This value is used to determinate the HandleParameters' list's size.
                    **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other values.
                    */
                    Max};
public:
    /** @brief Create a Rotation.
    **  @param int AngleRotation = 0 : default rotation's angle.
    **  @param const QString &affName="untilted" : shown name.
    **  @param const std::string & name = "noname" : VirutalHandle's name
    */
    Rotation( int defaultAngleRotation = 0 , const QString &affName="untilted", const std::string &name= "noname");
protected :

    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    virtual ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
};

#endif // ROTATION_H
