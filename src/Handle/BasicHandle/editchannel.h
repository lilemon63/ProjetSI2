#ifndef EDITCHANNEL_H
#define EDITCHANNEL_H

#include "../virtualhandle.h"

/** @brief VirtualHandle which edit pixel's channel in an Image.
**
**  Set in each channel's image a value given by the user.
**  The channel can be red, green and blue.
**  The value understand logic and arithmetic operator.
**
**  Use R, G, B, Gr as red, green, blue and gray current pixel's value.
**  @todo we can add other variable as W (Widht), H ( Height), X (abscissa), Y (ordinate), RANDOM, MAX_R,
    etc...
**  @note We use 8bit for each channel so each channel have a value beetween 0 and 255.
*/
class EditChannel : public VirtualHandle
{
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
    enum PARAM_ID{
                 /** @brief Value given by the user for the red channel. */
                 SCRIPT_R,
                 /** @brief Value given by the user for the green channel. */
                 SCRIPT_G,
                 /** @brief Value given by the user for the blue channel. */
                 SCRIPT_B,
                 /** @brief This value is used to determinate the HandleParameters' list's size.
                 **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other
                     values.
                 */
                 MAX};
public:
    /** @brief Build an EditPixel.
    **  @param const QString & affName = "Untilted" : shown name.
    **  @param const std::string & = "noname" : VirtualHandle's name.
    */
    EditChannel(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};


#endif // EDITCHANNEL_H
