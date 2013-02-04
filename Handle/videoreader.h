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
    inline void grab(void);

    /** @brief get the last image grabbed
        @return IplImage * : last image grabbed */
    IplImage * getImage(void);
private :
    /** @brief video stream */
    CvCapture * m_video;
};

void VideoReader::grab(void)
{
    if(m_video)
       cvGrabFrame(m_video);
}

#endif // VIDEOREADER_H
