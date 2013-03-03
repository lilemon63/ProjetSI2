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
        throw Exception::buildException("Can't use this camera as source", "VideoReader", "useCamera", EPC);
    m_video = tmp;
}

bool VideoReader::acceptSeek(void)
{
    return false;
}

int VideoReader::nbFrame(void)
{
    return 0;
}

void VideoReader::slid(int)
{

}
