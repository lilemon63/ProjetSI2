#ifndef COUNTPIXEL_H
#define COUNTPIXEL_H

#include "../virtualhandle.h"


/** @brief VirtualHandle which count pixel in an Image.
**
**  Count the pixel which match with a condition given by the user and put the resultat in the image.
**  The condition understand logic and arithmetic operator.
**
**  Use R, G, B, Gr as red, green, blue and gray current pixel's value.
**  @todo we can add other variable as W (Widht), H ( Height), X (abscissa), Y (ordinate), RANDOM, MAX_R,
    etc...
**  @note We use 8bit for each channel so each channel have a value beetween 0 and 255.
*/
class CountPixel : public VirtualHandle
{
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
    enum PARAM_ID{
                  /** @brief Condition given by the user. */
                  SCRIPT,
                  /** @brief CountPixel's result name in the final ImageData. */
                  NAME,
                  /** @brief This value is used to determinate the HandleParameters' list's size.
                  **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other
                      values.
                  */
                  MAX};
public:
    /** @brief Build a CountPixel.
    **  @param const QString & affName = "Untilted" : shown name.
    **  @param const std::string & = "noname" : VirtualHandle's name.
    */
    CountPixel(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};

#endif // COUNTPIXEL_H
