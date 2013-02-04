#ifndef VIDEOVIEW_H
#define VIDEOVIEW_H

#include <opencv2/opencv.hpp>
#include <QObject>
#include "imagedata.h"

/** @brief Abstract class which used for show IplImage.
    The method setImage() is called by VideoExtractor each time an IplImage have been handled  */
class VideoView : QObject
{
    Q_OBJECT
public:
    VideoView();
    virtual ~VideoView(){}

public slots :
    /** @brief called when the handle of the current images are finished.
      Don't forget to connect it.
        @param const ImageDataPtr result : handle result
        @param const ImageDataPtr src1 : first image source
        @param const ImageDataPtr src2 : second image source */
    virtual void setImage(const ImageDataPtr result, const ImageDataPtr src1 , const ImageDataPtr src2) = 0;
};

#endif // VIDEOVIEW_H
