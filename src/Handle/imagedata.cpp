#include "imagedata.h"
#include "../exception.h"

ImageData::ImageData(const IplImage & image)
    : m_image( cvCloneImage(&image) )
{
    if( ! m_image )
        throw Exception::buildException( "Erreur lors de la creation de l'image", "ImageData",
                                         "ImageData()", EP);
}


QPixmap ImageData::toPixmap(void)
{
    if( m_image->depth != IPL_DEPTH_8U)
    {
        throw Exception::buildException("This type of IplImage is not implemented in QOpenCVWidget\ndepth must be 'IPL_DEPTH_8U",
                                        "ImageData", "toPixmap", EP);
    }
    if( m_image->nChannels != 3)
    {
        throw Exception::buildException("This number of channels is not supported\n",
                                        "ImageData", "toPixmap",
                                        EP);
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

ImageDataPtr ImageData::getSubRegion(int x, int y, int width, int height)
{
    ImageData * retour = new ImageData();
    CvRect cvrect = cvRect(x,y,width, height);
    if( width < 0 )
    {
        cvrect.x = x + width;
        cvrect.width = -width;
    }
    if( height < 0 )
    {
        cvrect.y = y + height;
        cvrect.height = -height;
    }

    retour->m_image = cvCreateImage( cvSize(cvrect.width,cvrect.height),m_image->depth,m_image->nChannels);

    // définit la région d'intérêt
    cvSetImageROI(m_image,cvrect);
    // copier le bout sélectionné dans dest
    cvCopy(m_image, retour->m_image,0);

    return ImageDataPtr( retour );
}

void ImageData::merge( ImageDataPtr image, int x, int y)
{
    IplImage * dst = m_image;
    IplImage * src = image->m_image;

    if(m_image->depth != IPL_DEPTH_8U || image->m_image->depth != IPL_DEPTH_8U)
      Exception::buildException("Erreur, profondeur non-supportée", "ImageData", "merge", EPC);
    if( m_image->nChannels != image->m_image->nChannels )
        Exception::buildException("Erreur, nombre de cannaux différents", "ImageData", "merge", EPC);


    char * begin = dst->imageData + m_image->widthStep*y + x*3;

    char * lineSrc = src->imageData;
    char * lineDst = begin;
    while( lineSrc < src->imageData + src->imageSize)
    {

        char * pSrc = lineSrc;
        char * pDst = lineDst;
        while( pSrc - lineSrc < src->width * src->nChannels )
        {
            *pDst = *pSrc;

            ++pSrc;
            ++pDst;
        }

        lineSrc += src->widthStep;
        lineDst += dst->widthStep;
    }
}
