#ifndef VIDEOEXTRACTOR_H
#define VIDEOEXTRACTOR_H

#include <QThread>
#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include <QMutex>
#include <QWaitCondition>
#include "videoreader.h"
#include "imagedata.h"
#include "Parameters/handleparameters.h"

/** @brief Extract one or two video stream and call VideoView::setImage after handle the image with the MainHandle
  specified in Handle.h.
  Have his own thread.
  */
class VideoExtractor : public QThread
{
    Q_OBJECT
public :

    /** @brief Create a new VideoExtractor
      @param bool dual : true if we use two camera, false if we use only one camera */
    VideoExtractor(bool dual = true, VideoReader *source1 = new VideoReader(), VideoReader *source2= new VideoReader());

    virtual ~VideoExtractor();

    /** @brief stop the video stream handle */
    inline void stop(void);

    /** @brief return true if the handle is stopped
      @return bool : true if the handle is stopped else return false.
      */
    inline bool isStopped(void);

    /** @brief return the number of Handle Cycle.<br/>
        Can return a false value in 32 bits process when the Image number % 2^32 = -1 and is incremented when this method is called.

        @return : qint64 : number of Handle Cycle. */
    inline qint64 getNbHandleCycle(void);

    /** @brief start the video stream handle in his own thread.
        @param qint64 timeMax : maximal time in nanosecond for the all handle, zero for infinite
        @param qint64 nbMaxImage : number of image we want, zero for infinite */
    void start(qint64 timeMax = 0 , qint64 nbMaxImage = 0);

    void useSource(VideoReader * source, int channel);


    /** @brief Show the parameters in the widget "parent"
        @param QWidget * parent : Widget where the parameters will be shown */
    void showParameters(QWidget * parent);

    void hideParameters(void);


    /** @brief Change the source for the period Parameters (time beetwen each handle)
        @param std::shared_ptr<SourceParameters> source : source for the period Parameters (time beetwen each handle) */
    void changePeriodeParameters( SourceParameters * source, QWidget * area = nullptr);

    void changeHandleParameters( SourceParameters *source, QWidget * area = nullptr);


    bool acceptSeek(void);

    int numberOfFrame(void);
private :

    /** @brief true if the handle is stopped else return false */
    bool m_stopped;

    /** @brief true if we use two camera, false if we use only one camera */
    bool m_dual;

    /** @brief maximal time in nanosecond for the all handle, zero for infinite */
    qint64 m_timeMax;

    /** @brief number of image we want, zero for infinite */
    qint64 m_nbMaxImage;

    /** @brief number of handle cycle */
    qint64 m_nbImageHandled;

    /** @brief video stream to handled */
    VideoReader * m_videoStream[2];

    bool m_autoPlay;

    QMutex m_mutex;
    QWaitCondition m_cond; // We lock and unlock the mutex in different thread

    /** @brief start the VideoExtractor's thread */
    void run(void);

    /** @brief parameters for period (time beetwen each handle) */
    HandleParameters m_paramPeriod;

    HandleParameters m_paramHandle;

    QWidget * m_currentParent;

    bool m_isHandleActived;

    void processFrame(void);

signals :
    /** @brief emitted when the handle of the current image is finish
        @param const ImageDataPtr result : handle result
        @param const ImageDataPtr src1 : first image source
        @param const ImageDataPtr src2 : second image source
      */
    void imageHandled(const ImageDataPtr result, const ImageDataPtr src1, const ImageDataPtr src2);
    /** @brief emitted when the handle is finished.
        @param bool : true if the handle has been stopped by the user */
signals :
    void finished(void);
public slots :
    void previous(void);
    void next(void);
    void slid(int);
    void pause(void);
    void play(void);

    void activeHandle(bool);
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
