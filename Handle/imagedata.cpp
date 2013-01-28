#include "imagedata.h"
#include "../exception.h"

ImageData::ImageData(const IplImage & image)
    : m_image( cvCloneImage(&image) )
{
    if( ! m_image )
        throwExc( "Erreur lors de la creation de l'image", "ImageData", "ImageData()");
}


QPixmap ImageData::toPixmap(void)
{
    if( m_image->depth != IPL_DEPTH_8U)
    {
        throwExc("This type of IplImage is not implemented in QOpenCVWidget\ndepth must be 'IPL_DEPTH_8U", "ImageData", "toPixmap");
    }
    if( m_image->nChannels != 3)
    {
        throwExc("This number of channels is not supported\n", "ImageData", "toPixmap");
        return QPixmap();
    }
    QImage image(m_image->width, m_image->height, QImage::Format_RGB32);
    int cvIndex = 0;
    int cvLineStart = 0;
    for (int y = 0; y < m_image->height; y++)
    {
        unsigned char red,green,blue;
        cvIndex = cvLineStart;
        for (int x = 0; x < m_image->width; x++)
        {
            red = m_image->imageData[cvIndex+2];
            green = m_image->imageData[cvIndex+1];
            blue = m_image->imageData[cvIndex+0];

            image.setPixel(x,y,qRgb(red, green, blue));
            cvIndex += 3;
        }
        cvLineStart += m_image->widthStep;
    }

    return QPixmap::fromImage(image);
}

ImageData::~ImageData()
{
    cvReleaseImage(&m_image);
}
