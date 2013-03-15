#ifndef TOFILES_H
#define TOFILES_H

#include <string>

#include "../virtualhandle.h"


/** @brief VirtualHandle which save the current stream into a folder as images files.
**
**  The new files will have a formated name. For more details, take a look at FolderReader.
**  The user can specified the number of frame beetween each new image file.
*/
class ToFiles : public VirtualHandle
{
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
   enum PARAM_ID{
                 /** @brief number of frame -1 beetween each new image file. */
                 Frequence,
                 /** @brief Path in which we will save the new images files. */
                 Path,
                 /** @brief This value is used to determinate the HandleParameters' list's size.
                 **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other
                     values.
                 */
                 Max};
public:
    /** @brief Build a ToFile.
    **  @param const std::string & path : existant folder where we put the image
    **  @param unsigned int defaultFrequence = 0 : default frequence in frame number
    **  @param const std::string & name = "noname" : handle's name
    */
    ToFiles(const std::string & path , unsigned int defaultFrequence = 0,
            const QString & affName = "untilted", const std::string & name = "noname");
protected :

    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
private :
    /** @brief internal counter for the frequency */
    unsigned int m_compteur;
};

#endif // TOFILES_H
