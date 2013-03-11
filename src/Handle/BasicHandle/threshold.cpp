#include "threshold.h"
#include "../Parameters/handleparameters.h"
#include "../../exception.h"

Threshold::Threshold(const QString & affName, const std::string & name)
    :VirtualHandle(affName, name)
{
    m_listParameters.resize(2);
    m_listParameters[0] = HandleParameters::build_slider("value",0,0,255);
    m_listParameters[1] = HandleParameters::build_checkbox("option",QStringList({"inversion couleurs"}));
}

ImageDataPtr Threshold::startHandle(ImageDataPtr src1, ImageDataPtr)
{
    if( ! src1 )
        throw Exception::buildException("La source est vide", "Threshold", "startHandle", EPC);

    int threshold_value = m_listParameters[0]->toInt();
    bool inversion = m_listParameters[1]->toMap()["inversion couleurs"].toBool();

    IplImage * ThresholdImage = src1->getImage();

    cvThreshold( ThresholdImage, ThresholdImage, threshold_value,255, inversion ? CV_THRESH_BINARY_INV : CV_THRESH_BINARY);

    return src1;
}
