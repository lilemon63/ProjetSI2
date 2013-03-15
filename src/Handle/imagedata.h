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

/** @typedef ImageDataPtr
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
    **  You should use the VirtualHandle's adress as part of the name.
    **  @warning If there is already a result which the same name, it will be replaced.
    **  @todo I think we should use a non-const version of the operator[] instead
    **  @todo A function isResultExist() may be good.
    **  @param const QString & : result's name
    **  @param const QVariant & : result's value
    */
    void addResults( const QString &, const QVariant &);


    /**
    ** @brief Execute a process given in parameters for each pixel
    ** @todo This method is really long. We can :
    ** @list
    ** - do the process in the GPU
    ** - used few thread instead using only one
    ** @endlist
    ** @param std::function< void(unsigned char & r, unsigned char & g, unsigned char & b) >  : function
       or lambda which we will call for each pixel. You can get and set the red, green and blue composant
    ** thanks to the parameters r, g and b.
    */
    void forEachPixel( std::function< void(unsigned char & r, unsigned char & g, unsigned char & b) > );


    /** @brief Get the stocked Image for avanced process.
    **
    **  @warning All modification in this image will be reported to the internal image
    **  @return IplImage * : pointer to the stocked image.
    */
    inline IplImage * getImage(void);


    /** @brief Get a subregion for this image by copy
    **  @param int x : abscissa for the subregion's top-left corner
    **  @param int y : ordinate for the subregion's top-left corner
    **  @param int width : subregion's width
    **  @param int height : subregion's heifht
    */
    ImageDataPtr getSubRegion(int x, int y, int width, int height) const;


    /** @brief merge two ImageData.
    **
    **  The image source will be copied into the image destination and the source's results will be copied
    **  into the destination's results.
    **  @param ImageDataPtr image : ImageData source
    **  @param int x = 0 : abscissa where the source's top-left corner will be copied in the destination
    **  @param int y = 0 : ordinate where the source's top-left corner will be copied in the destination
    */
    virtual void merge( ImageDataPtr image, int x = 0, int y = 0);


    /** @brief
    **  @todo This method will create a result if it doesn't exist, we should create a find() method and an
    **  insert() method.
    **  @param const QString & : result's name
    **  @return QVariant : result's value
    */
    QVariant & operator[](const QString &);


    /** @brief create a QPixmap from this ImageData. QPixmap is used to print an ImageData Qt's widget
    **  @return QPixmap : created QPixmap
    */
    QPixmap toPixmap(void);
private :

    /** @brief Only an ImageData can create an empty ImageData */
    ImageData(void){}


    /** @brief Internal image */
    IplImage * m_image;


    /** @brief ImageData's results
    **
    **  Be carefull, we don't use QMap as a multimap but as a stl map
    */
    QMap<QString, QVariant> m_results ;
};

IplImage * ImageData::getImage(void)
{
    return m_image;
}


#endif // IMAGEDATA_H
