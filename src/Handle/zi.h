#ifndef ZI_H
#define ZI_H

#include <QRectF>
#include "virtualhandle.h"

class ViewZI;

class ZI : public VirtualHandle
{
public:
    ZI(QRectF rect, Numbering num = Numbering() );
    virtual ImageDataPtr executeHandle(ImageDataPtr src1, const ImageDataPtr src2);
    ViewZI * view(void);
protected:
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{NAME, HANDLE, AREA, SIZE, COLOR, ACTIVATION, DELETE, MAX};
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_width;
    unsigned int m_height;
    ViewZI * m_view;
};

#endif // ZI_H
