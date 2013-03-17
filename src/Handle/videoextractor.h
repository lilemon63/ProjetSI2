#ifndef VIDEOEXTRACTOR_H
#define VIDEOEXTRACTOR_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "imagedata.h"
#include "videoreader.h"
#include "Parameters/handleparameters.h"

/** @brief Extract image from one or two video stream then call the selected VirtualHandle to process it.
**
** VideoExtractor will extract image from VideoReader and call the selected VirtualHandle to process one or
   two image. Then send a signal : imageHandled().
** VideoExtractor run in its own thread.
** @todo We can remove m_dual and see if the second sources is nullptr or not.
*/
class VideoExtractor : public QThread // final
{
    Q_OBJECT
public :

    /** @brief Create a new VideoExtractor.
    **  @todo : Change pointer to references (?).
    **  @param bool dual : true if we use two VideoReader, false if we use only one.
    **  @param VideoReader *source1 : first source, it must be a valid pointer.
    **  @param VideoReader *source2 : second source, it must be a valid pointer if dual is true.
    */
    VideoExtractor(bool dual = true,
                   VideoReader *source1 = new VideoReader(),
                   VideoReader *source2= new VideoReader());

    /** @brief Free the VideoReader */
    ~VideoExtractor();

    VideoExtractor( const VideoExtractor & ) = delete;

    VideoExtractor & operator=( const VideoExtractor & ) = delete;


    /** @brief Return true if one of the used source accept to be seeked ie if we can seek in the stream
      with slider for example.
    **  @return bool : true if one of the used source accept to be seeked else false.
    */
    bool acceptSeek(void);


    /** @brief Change the SourceParameters for the selected Handle, the new SourceParameters will determine
      the VirtualHandle to use for process the images.
    **  @param SourceParameters *source : new SourceParameters for select the VirtualHandle to use.
    **  @param QWidget * area = nullptr : QWidget in which we will show the SourceParameters.
    */
    void changeHandleParameters( SourceParameters *source, QWidget * area = nullptr);


    /** @brief Change the SourceParameters for the period, the new SourceParameters will determine
      the time beetween each process.
    **  @param SourceParameters *source : new SourceParameters for select the period to apply.
    **  @param QWidget * area = nullptr : QWidget in which we will show the SourceParameters.
    */
    void changePeriodeParameters( SourceParameters * source, QWidget * area = nullptr);


    /** @brief return the number of process done ("process cycle").
    **
    ** @warning Can return a false value in 32 bits processor when the Image number % 2^32 = -1 and is
       incremented when this method is called.
    **
    ** @return : qint64 : number of process cycle.
    */
    inline qint64 getNbHandleCycle(void);


    /** @brief Hide all parameters in the parameter's view */
    void hideParameters(void);

    /** @brief return true if the VideoExtractor is stopped.
    **
    **  When the VideoExtractor is stopped it will be remove by Qt.
    **  @return bool : true if the VideoExtractor is stopped else return false.
    */
    inline bool isStopped(void);


    /** @brief Return the maximal number of image (frame) from seeked VideoReader sources.
    **
    **  It's used to set the maximal value to the slidbar to seek the video's stream.
    **  @return int : maximal number of image (frame) from seeked VideoReader sources.
    */
    int numberOfFrame(void);


    /** @brief Show the parameters in the widget parent.
    **  @param QWidget * parent : Widget where the parameters will be shown.
    */
    void showParameters(QWidget * parent);


    /** @brief Launch its own thread by default, the stream's reading doesn't start but the process will
        start as soon as the stream's reading start.
    **  @warning : we didn't really test the stream limitation as the maximal time and the maximal image.
    **  @param qint64 timeMax : maximal time in nanosecond for the all handle, zero for infinity
    **  @param qint64 nbMaxImage : number of image we want, zero for infinity.
    */
    void start(qint64 timeMax = 0 , qint64 nbMaxImage = 0);


    /** @brief stop the VideoExtractor's thread. */
    inline void stop(void);


    /** @brief Specifies the video stream source to use.
    **  @param VideoReader * source : video stream source.
    **  @param int channel : channel, ie if the VideoReader will be the first source (0) or the second (1)
    **  @warning : for now we only have 2 channel (0 and 1).
    **  @warning : you must give valid pointer.
    */
    void useSource(VideoReader * source, int channel);

public slots :
    /** @brief Active the image process or stop it.
    **  @param bool : true if we active the process, false to stop it.
    */
    void activeHandle(bool);

    /** @brief Seek the video stream to the next frame, if the source can be seeked.
    **  If process is enable, do the process in this frame.
    **  @warning If the video stream is readed, stop the automatic reading.
    */
    void next(void);


    /** @brief Stop the automatic reading of the video stream. Also stop the process. */
    void pause(void);


    /** @brief Start the automatic reading of the video stream. */
    void play(void);


    /** @brief Seek the video stream to the previous frame, if the source can be seeked.
    **  If process is enable, do the process in this frame.
    **  @warning If the video stream is readed, stop the automatic reading.
    */
    void previous(void);


    /** @brief Seek the video stream to the ième frame, if the source can be seeked.
    **  If process is enable, do the process in this frame.
    **  @warning If the video stream is readed, stop the automatic reading.
    **  @param int : number of frame to show (and process).
    */
    void slid(int);

signals :
    /** @brief emitted when the process of the current image is finish
        @param ImageDataPtr result : handle result
        @param ImageDataPtr src1 : first image source
        @param ImageDataPtr src2 : second image source
      */
    void imageHandled(ImageDataPtr result, ImageDataPtr src1, ImageDataPtr src2);


    /** @brief emitted when the VideoExtractor's thread is finished. */
    void finished(void);

    /** @brief emitted when the video stream's automatic reading is finished. */
    void streamFinished(void);
private :
    /** @brief process a frame */
    void processFrame(void);


    /** @brief start the VideoExtractor's thread */
    void run(void);
private :

    /** @brief specifies if the automatic reading is enabled or disabled */
    bool m_autoPlay;

    /** @brief Condition to lock and unlock a mutex in different thread.
    **
    **  In some plateforms, somes mutex can't be lock and unlock in different thread so we use a
    **  QWaitCondition.
    */
    QWaitCondition m_cond;


    /** @brief Current graphics parent for the paramters.
    **
    **  Used to change the parameters when the selected VirtualHandle is modified by the user.
    */
    QWidget * m_currentParent;


    /** @brief True if we use two camera, false if we use only one. */
    bool m_dual;

    /** @brief True if the process in the video stream is enabled, false if disabled */
    bool m_isHandleActived;


    /** @brief Number of process cycle, incremented at each loop, when a frame process is finished. */
    qint64 m_nbImageHandled;


    /** @brief Number of maximal image we want, zero for infinity. */
    qint64 m_nbMaxImage;


    /** @brief Mutex used to wait when automatic reading is disabled without destroy the thread. */
    QMutex m_mutex;


    /** @brief Parameters for the used VirtualHandle. */
    HandleParameters m_paramHandle;


    /** @brief Parameters for the period (time beetwen each process). */
    HandleParameters m_paramPeriod;


    /** @brief True if the VideoExtractor's thread is stopped else false. */
    bool m_stopped;


    /** @brief maximal time in nanosecond for the all process, zero for infinity. */
    qint64 m_timeMax;


    /** @brief Video streams to process. */
    VideoReader * m_videoStream[2];
};

bool VideoExtractor::isStopped(void)
{
    return m_stopped;
}

void VideoExtractor::stop(void)
{
    m_stopped = true;
}

qint64 VideoExtractor::getNbHandleCycle(void)
{
    return m_nbImageHandled;
}

#endif // VIDEOEXTRACTOR_H
