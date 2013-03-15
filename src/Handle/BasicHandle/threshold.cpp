#include "threshold.h"
#include "../Parameters/handleparameters.h"
#include "../../exception.h"

Threshold::Threshold(const QString & affName, const std::string & name)
    :VirtualHandle(affName, name)
{
    m_listParameters.resize(MAX);
    m_listParameters[SEUIL] = HandleParameters::build_slider("value",0,0,255);
    m_listParameters[INVERSION] = HandleParameters::build_checkbox("option",QStringList({"inversion couleurs"}));
}

ImageDataPtr Threshold::startHandle(ImageDataPtr src1, ImageDataPtr)
{
    if( ! src1 )
        throw Exception::buildException("La source est vide", "Threshold", "startHandle", EPC);

    int threshold_value = m_listParameters[0]->toInt();
    bool inversion = m_listParameters[1]->toMap()["inversion couleurs"].toBool();

    IplImage * thresholdImage = src1->getImage();

    IplImage * tmp = cvCreateImage( cvSize(thresholdImage->width, thresholdImage->height), IPL_DEPTH_8U, 1);
    cvCvtColor(thresholdImage, tmp ,CV_BGR2GRAY);


    cvThreshold( tmp, tmp, threshold_value,255, inversion ? CV_THRESH_BINARY_INV : CV_THRESH_BINARY);


    cvCvtColor(tmp, thresholdImage,CV_GRAY2BGR);
    cvReleaseImage(&tmp);

    return src1;
}
