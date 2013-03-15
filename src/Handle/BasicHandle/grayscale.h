#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../virtualhandle.h"

/** @brief VirtualHandle which convert a color Image into a gray Image.
**
**  @note the final ImageData still have three channel with in each channel the gray value.
*/
class Grayscale : public VirtualHandle
{
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
    enum PARAM_ID{
                 /** @brief Determinate if we active and stop this specific process. */
                 ACTIVE,
                 /** @brief This value is used to determinate the HandleParameters' list's size.
                 **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other
                     values.
                 */
                 MAX};
public:
    /** @brief Build an Grayscale.
    **  @param const QString & affName = "Untilted" : shown name.
    **  @param const std::string & = "noname" : VirtualHandle's name.
    */
    Grayscale(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    ImageDataPtr startHandle(ImageDataPtr src1, ImageDataPtr src2);
};


#endif // GRAYSCALE_H
