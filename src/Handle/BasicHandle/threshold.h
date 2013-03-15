#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "../virtualhandle.h"

/** @brief VirtualHandle which do a threshold on an image.
**
**  The image will be convert in gray and the process will look at each pixel's gray value and if it's greater
    than the threshold, the pixel will be white, else it will be black.
*/
class Threshold : public VirtualHandle
{
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
    enum PARAM_ID{
                 /** @brief Threshold's Value. */
                 SEUIL,
                 /** @brief If we invert white and black */
                 INVERSION,
                 /** @brief This value is used to determinate the HandleParameters' list's size.
                 **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other
                     values.
                 */
                 MAX};
public:
    /** @brief Build a Threshold.
    **  @param const QString & affName = "Untilted" : shown name.
    **  @param const std::string & = "noname" : VirtualHandle's name.
    */
    Threshold(const QString & affName = "Untilted", const std::string & = "noname");
protected :

    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    ImageDataPtr startHandle(ImageDataPtr src1, ImageDataPtr src2);
};

#endif // THRESHOLD_H
