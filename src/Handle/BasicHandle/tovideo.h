#ifndef TOVIDEO_H
#define TOVIDEO_H

#include<QTime>

#include "../virtualhandle.h"
#include "../Parameters/inputtext.h"
#include "../Parameters/progressbar.h"


/** @brief VirtualHandle which save the current stream into a new video file.
**
**  The user can specified the new video's framerate and the video stream input time.
**  @todo We can create a FileVideoReader to read video file.
*/
class ToVideo : public VirtualHandle
{
private:
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
    enum PARAM_ID{
                 /** @brief Frame's number per seconds */
                 FrameRate,
                 /** @brief Maximal time for the input stream.
                 **  @warning : the real time for the final video depends on it and on the framerate.
                 */
                 Duree,
                 /** @brief path to the new video file. */
                 PathV,
                 /** @brief show the capture's progression. */
                 Progress,
                 /** @brief Determinate if the stream's capture is enable or not. */
                 Prise,
                 /** @brief This value is used to determinate the HandleParameters' list's size.
                 **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other
                     values.
                 */
                 Max};
public:

    /** @brief Build a ToVideo.
    **  @param const std::string &path : path's name for the new video file.
    **  @param const QString & affName = "Untilted" : shown name.
    **  @param const std::string & = "noname" : VirtualHandle's name.
    */
    ToVideo(const std::string &path, const QString & affName,const std::string &name);
protected :
    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr);
private :

    /** @brief Stop the capture and realize some ressources */
    void onEnding();

    /** @brief Start the capture and initialize some ressources.
    **  @param const ImageDataPtr : video stream's ImageData used to know the video's resolution. */
    void init(const ImageDataPtr);

    /** @brief Save the frame into the video file. */
    void saveFrame( ImageDataPtr );


    /** @brief Determinate if the stream's capture is enable or not. */
    CheckBox * m_checkBox;

    /** @brief If the capture is really started or not. */
    bool m_isActif;


    /** @brief ProgressBar used to view the capture's progression. */
    ProgressBar * m_progress;

    /** @brief Measure the input stream time. */
    QTime m_timer;

    /** @brief Write frame into the video file. */
    CvVideoWriter * m_writer;
};

#endif // TOVIDEO_H
