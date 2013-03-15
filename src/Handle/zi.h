#ifndef ZI_H
#define ZI_H

#include <QRect>
#include "virtualhandle.h"

class ViewZI;
class InputsTexts;


/** @brief Create a ZI (interest area).
**
**  In each ZI you can define the VirtualHandle to use for processing the selected area.
**  You can also creator other ZI in a ZI.
**  @warning do not use the ZI's VirtualHandle as ZI's process, you will create an infinite loop.
*/
class ZI : public VirtualHandle
{

public:
    /** @brief */
    enum Direction{ X, Y, WIDTH, HEIGHT};
private :
    /** @brief Identify the paramters. */
    enum Params{
        /** @brief ZI's shown name. */
        NAME,
        /** @brief VirtualHandle used in the ZI. */
        HANDLE,
        /** @brief Delimit the ZI's area. */
        AREA,
        /** @brief Change the ZI's size and update its area. */
        SIZE,
        /** @brief Change the ZI's rectangle color. */
        COLOR,
        /** @brief Activate or desactivate the ZI */
        ACTIVATION,
        /** @brief Give the number of parameters */
        MAX};
public :

    /** @brief Build a ZI and initialize the its view.
    **  @param QRect rect : delimit the ZI's area.
    **  @param QWidget *parent : parameters' area widget. The ZI's parameters will shown in it.
    **  @param const Numbering num : Numbering to use.
    */
    ZI( QRect rect, QWidget *parent, const Numbering num = Numbering() );

    virtual ~ZI(void){}


    /** @brief Call startHandle() to proccess Images if the ZI's process is activate then update the view,
        launch ZI's ZI's process and merge the original image and the ZI's result
    **  @param ImageDataPtr src1 : Image from the first source.
    **  @param ImageDataPtr src2 : Image from the second source.
    **  @return ImageDataPtr : process and ZI result.
    */
    virtual ImageDataPtr executeHandle( ImageDataPtr src1, const ImageDataPtr src2 );


    /** @brief Move one side of the ZI's area
    **
    ** @param Direction direction : resize direction.
    ** @param int value : value used to move the side matching to the direction (new abscissa or ordinate)
       for the side.
    */
    virtual void resize( Direction direction, int value);


    using VirtualHandle::showParameters;


    /** @brief Show all the Parameters on the parameters' area.
    **
    ** We will use the stored Numbering.
    */
    virtual void showParameters(void);


    /** @brief Return the ZI's ViewZI.
    **  @param ViewZI * : ZI's View ZI.
    */
    virtual ViewZI * view(void);
protected:

    /** @brief Type for lambda used to execute action when a parameter is modified. */
    typedef std::function< void( QVariant value, HandleParameters * hp )> M_Lambda;


    /** @brief Return the M_Lambda to execute when the user change the ZI's area.
    **  @return M_Lambda : M_Lambda to execute when the user change the ZI's area.
    */
    virtual M_Lambda generateLambdaArea(void);


    /** @brief Return the M_Lambda to execute when the user change the ZI's VirtualHandle.
    **  @return M_Lambda : M_Lambda to execute when the user change the ZI's VirtualHandle.
    */
    virtual M_Lambda generateLambdaHandle(void);


    /** @brief Return the M_Lambda to execute when the user change the ZI's size.
    **  @return M_Lambda : M_Lambda to execute when the user change the ZI's size.
    */
    virtual M_Lambda generateLambdaSize(void);


    /** @brief Call the ZI's VirtualHandle's process.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);

private :

    /** @brief InputsTexts to modify the ZI's area. */
    InputsTexts * m_area;


    /** @brief QWidget where the ZI's paramters will shown. */
    QWidget * m_parent;


    /** @brief Delimit the Zi's area. */
    QRect m_rect;


    /** @brief InputsTexts to modify the ZI's size. */
    InputsTexts * m_size;


    /** @brief ZI's ViewZI.
    **
    **  Each ZI have his own ViewZI.
    */
    ViewZI * m_view;
};

#endif // ZI_H
