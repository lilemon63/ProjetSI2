#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <opencv2/opencv.hpp>
#include <memory>
#include <QPixmap>
#include <QMetaType>
#include <QMap>
#include <QVariant>
#include <QString>

class ImageData;

typedef std::shared_ptr<ImageData> ImageDataPtr;

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
    inline IplImage * getImage(void);

    /** @brief create a QPixmap from the image for an print in a Qt's widget
        @return QPixmap : QPixmap created */
    QPixmap toPixmap(void);

    ImageDataPtr getSubRegion(int x, int y, int width, int height);

    void merge( ImageDataPtr image, int x = 0, int y = 0);

    void addResults( const QString &, const QVariant &);

    QVariant operator[](const QString &);
private :
    ImageData(void){}
    /** @brief Image */
    IplImage * m_image;

    QMap<QString, QVariant> m_results ;
};

IplImage * ImageData::getImage(void)
{
    return m_image;
}


#endif // IMAGEDATA_H
