#include "videoreader.h"
#include "../exception.h"

VideoReader::VideoReader()
    : m_video(nullptr)
{
}


IplImage * VideoReader::getImage(void)
{
    return cvQueryFrame(m_video);
    /*
    if (webcam)
        cvFlip(frame, frame, 1);
        */
}

void VideoReader::useCamera(int idCamera)
{
    auto tmp = cvCreateCameraCapture(idCamera);
    if( ! tmp )
        throwExc("Can't use this camera as source", "VideoReader", "useCamera");
    m_video = tmp;
}
