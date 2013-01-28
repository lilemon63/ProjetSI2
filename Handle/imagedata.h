#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <opencv2/opencv.hpp>
#include <memory>
#include <QPixmap>

/** @brief Contains an Image and his data */
class ImageData
{
public:
    /** @brief Construct an ImageData from an existant IplImage
        @param const IplImage & image : image which will be stocked */
    ImageData(const IplImage & image);

    virtual ~ImageData();

    /** @brief Get the stocked Image
        @return IplImage * : pointer to the stocked image. */
    IplImage * getImage(void);

    /** @brief create a QPixmap from the image for an print in a Qt's widget
        @return QPixmap : QPixmap created */
    QPixmap toPixmap(void);
private :

    /** @brief Image */
    IplImage * m_image;
};

typedef std::shared_ptr<ImageData> ImageDataPtr;

#endif // IMAGEDATA_H
