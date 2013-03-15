#include <opencv2/opencv.hpp>

#include "grayscale.h"
#include "../../exception.h"
#include "../Parameters/handleparameters.h"

Grayscale::Grayscale(const QString & affName, const std::string & name)
    :VirtualHandle(affName, name)
{
    m_listParameters.resize(MAX);
    m_listParameters[ACTIVE] = HandleParameters::build_checkbox("Grayscale",QStringList({"on"}));
}

ImageDataPtr Grayscale::startHandle(const ImageDataPtr src1, ImageDataPtr)
{
    if( ! src1 )
        throw Exception::buildException("La source est vide", "GrayScale", "startHandle", EPC);

    bool gray = m_listParameters[0]->toMap()["on"].toBool();

    IplImage * grayImage = src1->getImage();

    if(gray)
    {
        IplImage * tmp = cvCreateImage( cvSize(grayImage->width, grayImage->height), IPL_DEPTH_8U, 1);
        cvCvtColor(grayImage, tmp ,CV_BGR2GRAY);

        cvCvtColor(tmp, grayImage,CV_GRAY2BGR);

        cvReleaseImage(&tmp);
    }
    return src1;
}
