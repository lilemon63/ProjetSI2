#ifndef IMAGEDATA_H
#define IMAGEDATA_H


#include <QMap>
#include <memory>
#include <QPixmap>
#include <QString>
#include <QVariant>
#include <QMetaType>
#include <opencv2/opencv.hpp>

class ImageData;

typedef std::shared_ptr<ImageData> ImageDataPtr;

/** @brief Contains an Image and his data */
class ImageData
{
public:
    /** @brief Construct an ImageData from an existant IplImage
        @param const IplImage & image : image which will be stocked */
    ImageData(const IplImage & image);

    ImageData( const ImageData & );
    ImageData & operator=( const ImageData & );

    virtual ~ImageData();

    void addResults( const QString &, const QVariant &);

    //TODO to it in GPU (?) Multi-thread (?)
    void forEachPixel( std::function< void(unsigned char & r, unsigned char & g, unsigned char & b) > );

    /** @brief Get the stocked Image
        @return IplImage * : pointer to the stocked image. */
    inline IplImage * getImage(void);

    ImageDataPtr getSubRegion(int x, int y, int width, int height);

    virtual void merge( ImageDataPtr image, int x = 0, int y = 0);


    QVariant operator[](const QString &);

    /** @brief create a QPixmap from the image for an print in a Qt's widget
        @return QPixmap : QPixmap created */
    QPixmap toPixmap(void);
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
