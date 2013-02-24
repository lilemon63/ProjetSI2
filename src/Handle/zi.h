#ifndef ZI_H
#define ZI_H

#include <QRectF>
#include "virtualhandle.h"

class ZI : public VirtualHandle
{
public:
    ZI(QRectF rect);
protected:
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{NAME, HANDLE,/* AREA, SIZE, */COLOR, ACTIVATION,/* DELETE,*/ MAX};
    QRectF m_rect;
};

#endif // ZI_H
