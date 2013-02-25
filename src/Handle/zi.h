#ifndef ZI_H
#define ZI_H

#include <QRectF>
#include "virtualhandle.h"

class ZI : public VirtualHandle
{
public:
    ZI(QRectF rect);
    virtual ImageDataPtr executeHandle(ImageDataPtr src1, const ImageDataPtr src2);
protected:
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{NAME, HANDLE, AREA,/* SIZE, */COLOR, ACTIVATION,/* DELETE,*/ MAX};
    QRectF m_rect; //replace by Area
};

#endif // ZI_H
