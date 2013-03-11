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

/** @class ImageDataPtr
** std::shared_ptr for an ImageData
*/
typedef std::shared_ptr<ImageData> ImageDataPtr;

/** @brief An Image.
**
** This class store an Image and somes "Results" which are in fact a QVariant with a name.
** You can execute some basics proccess as execute a function for each pixel or obtain a subregion.
*/
class ImageData
{
public:
    /** @brief Construct an ImageData from an existant IplImage
        @param const IplImage & image : image which will be stocked */
    ImageData(const IplImage & image);


    /** @brief Construct an ImageData from an existant ImageData
    **
    **  The image and the results will be copied.
    **  @param const ImageData & : image which will be copied.
    */
    ImageData( const ImageData & );


    /** @brief Copy an existant ImageData into another ImageData
    **
    **  The image and the results will be replaced by the other ImageData's.
    **  @param const ImageData & : image which will be copied.
    */
    ImageData & operator=( const ImageData & );


    /** @brief Destroy an ImageData
    **
    **  Realase the stored Image
    */
    virtual ~ImageData();


    /** @brief Add a result
    **
    **  Becarefull, if there is already a result which the same name, it will be replaced.
    **  You should use the VirtualHandle's adress as part of the name.
    **  @todo I think we should use a non-const version of the operator[] instead
    **  @todo A function isResultExist() may be good.
    **  @param const QString & : result's name
    **  @param const QVariant & : result's value
    */
    void addResults( const QString &, const QVariant &);


    /**

    */
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
