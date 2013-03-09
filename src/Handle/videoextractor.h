#ifndef VIDEOEXTRACTOR_H
#define VIDEOEXTRACTOR_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "imagedata.h"
#include "videoreader.h"
#include "Parameters/handleparameters.h"

/** @brief Extract one or two video stream and call VideoView::setImage after handle the image with the MainHandle
  specified in Handle.h.
  Have his own thread.
  */
class VideoExtractor : public QThread // final
{
    Q_OBJECT
public :

    /** @brief Create a new VideoExtractor
      @param bool dual : true if we use two camera, false if we use only one camera */
    VideoExtractor(bool dual = true, VideoReader *source1 = new VideoReader(), VideoReader *source2= new VideoReader());

    ~VideoExtractor();

    VideoExtractor( const VideoExtractor & ) = delete;

    VideoExtractor & operator=( const VideoExtractor & ) = delete;

    bool acceptSeek(void);

    void changeHandleParameters( SourceParameters *source, QWidget * area = nullptr);

    /** @brief Change the source for the period Parameters (time beetwen each handle)
        @param std::shared_ptr<SourceParameters> source : source for the period Parameters (time beetwen each handle) */
    void changePeriodeParameters( SourceParameters * source, QWidget * area = nullptr);

    /** @brief return the number of Handle Cycle.<br/>
        Can return a false value in 32 bits process when the Image number % 2^32 = -1 and is incremented when this method is called.

        @return : qint64 : number of Handle Cycle. */
    inline qint64 getNbHandleCycle(void);

    void hideParameters(void);

    /** @brief return true if the handle is stopped
      @return bool : true if the handle is stopped else return false.
      */
    inline bool isStopped(void);

    int numberOfFrame(void);

    /** @brief Show the parameters in the widget "parent"
        @param QWidget * parent : Widget where the parameters will be shown */
    void showParameters(QWidget * parent);

    /** @brief start the video stream handle in his own thread.
        @param qint64 timeMax : maximal time in nanosecond for the all handle, zero for infinite
        @param qint64 nbMaxImage : number of image we want, zero for infinite */
    void start(qint64 timeMax = 0 , qint64 nbMaxImage = 0);

    /** @brief stop the video stream handle */
    inline void stop(void);

    void useSource(VideoReader * source, int channel);

public slots :
    void activeHandle(bool);
    void next(void);
    void pause(void);
    void play(void);
    void previous(void);
    void slid(int);

signals :
    /** @brief emitted when the handle of the current image is finish
        @param const ImageDataPtr result : handle result
        @param const ImageDataPtr src1 : first image source
        @param const ImageDataPtr src2 : second image source
      */
    void imageHandled(const ImageDataPtr result, const ImageDataPtr src1, const ImageDataPtr src2);
    /** @brief emitted when the handle is finished.
        @param bool : true if the handle has been stopped by the user */
    void finished(void);

private :
    void processFrame(void);
    /** @brief start the VideoExtractor's thread */
    void run(void);
private :
    bool m_autoPlay;
    QWaitCondition m_cond; // We lock and unlock the mutex in different thread
    QWidget * m_currentParent;
    /** @brief true if we use two camera, false if we use only one camera */
    bool m_dual;

    bool m_isHandleActived;
    /** @brief number of handle cycle */
    qint64 m_nbImageHandled;
    /** @brief number of image we want, zero for infinite */
    qint64 m_nbMaxImage;
    QMutex m_mutex;

    HandleParameters m_paramHandle;
    /** @brief parameters for period (time beetwen each handle) */
    HandleParameters m_paramPeriod;

    /** @brief true if the handle is stopped else return false */
    bool m_stopped;
    /** @brief maximal time in nanosecond for the all handle, zero for infinite */
    qint64 m_timeMax;

    /** @brief video stream to handled */
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
