#ifndef ZI_H
#define ZI_H

#include <QRectF>
#include "virtualhandle.h"

class ViewZI;
class InputsTexts;

class ZI : public VirtualHandle
{
public:
    enum Direction{ X, Y, WIDTH, HEIGHT};

    ZI(QRectF rect, Numbering num = Numbering() );
    virtual ImageDataPtr executeHandle(ImageDataPtr src1, const ImageDataPtr src2);
    ViewZI * view(void);
    void resize( Direction direction, int value);
protected:
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{NAME, HANDLE, AREA, SIZE, COLOR, ACTIVATION, DELETE, MAX};
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_width;
    unsigned int m_height;
    ViewZI * m_view;

    InputsTexts * m_size;
    InputsTexts * m_area;

    QRectF m_rect;
};

#endif // ZI_H
