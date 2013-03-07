#ifndef ZI_H
#define ZI_H

#include <QRectF>
#include "virtualhandle.h"

class ViewZI;
class InputsTexts;

// be carefull don't use parent's handle

class ZI : public VirtualHandle
{
public:
    enum Direction{ X, Y, WIDTH, HEIGHT};

    ZI(QRect rect, QWidget *parent, Numbering num = Numbering());
    virtual ImageDataPtr executeHandle(ImageDataPtr src1, const ImageDataPtr src2);
    ViewZI * view(void);
    void resize( Direction direction, int value);

     using VirtualHandle::showParameters;

    void showParameters(void);
protected:
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
private :
    enum Params{NAME, HANDLE, AREA, SIZE, COLOR, ACTIVATION, MAX};
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_width;
    unsigned int m_height;
    ViewZI * m_view;

    InputsTexts * m_size;
    InputsTexts * m_area;

    QRect m_rect;

    QWidget * m_parent;
};

#endif // ZI_H
