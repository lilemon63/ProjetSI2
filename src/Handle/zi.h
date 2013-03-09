#ifndef ZI_H
#define ZI_H

#include <QRect>
#include "virtualhandle.h"

class ViewZI;
class InputsTexts;

// be carefull don't use parent's handle

class ZI : public VirtualHandle
{

public:
    enum Direction{ X, Y, WIDTH, HEIGHT};
private :
    enum Params{NAME, HANDLE, AREA, SIZE, COLOR, ACTIVATION, MAX};
public :
    ZI( QRect rect, QWidget *parent, Numbering num = Numbering() );
    virtual ~ZI(void){}

    virtual ImageDataPtr executeHandle( ImageDataPtr src1, const ImageDataPtr src2 );

    virtual void resize( Direction direction, int value);

    using VirtualHandle::showParameters;

    virtual void showParameters(void);

    virtual ViewZI * view(void);
protected:
    typedef std::function< void( QVariant value, HandleParameters * hp )> M_Lambda;

    virtual M_Lambda generateLambdaArea(void);
    virtual M_Lambda generateLambdaHandle(void);
    virtual M_Lambda generateLambdaSize(void);


    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);

private :

    InputsTexts * m_area;



    QWidget * m_parent;

    QRect m_rect;

    InputsTexts * m_size;

    ViewZI * m_view;


};

#endif // ZI_H
