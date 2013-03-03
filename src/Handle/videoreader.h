#ifndef VIDEOREADER_H
#define VIDEOREADER_H

#include <opencv2/opencv.hpp>


class VideoReader
{
public:
    VideoReader();

    virtual ~VideoReader() = default;

    virtual void useCamera(int idCamera = 0);

    /** @brief grab the current image from the video stream.<br/>
        There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy. */
    virtual inline void grab(void); // N.B. the "inline" as no effect when we call grab on a pointer or a references.

    virtual inline void r_grab(void);

    /** @brief get the last image grabbed
        @return IplImage * : last image grabbed */
    virtual IplImage * getImage(void);

    /** @brief Return true if the reading cursor can be moved
        @brief bool : true if the reading cursor can be moved else false */
    virtual bool acceptSeek(void);
    virtual int nbFrame(void);
    virtual void slid(int);
private :
    /** @brief video stream */
    CvCapture * m_video;
};

void VideoReader::grab(void)
{
    if(m_video)
       cvGrabFrame(m_video);
}

void VideoReader::r_grab(void)
{
}

#endif // VIDEOREADER_H
