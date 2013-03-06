#ifndef VIEWZI_H
#define VIEWZI_H

#include <QGraphicsRectItem>

class ZI;

class ViewZI : public QGraphicsRectItem
{
public:
    ViewZI(ZI * zi, const QRectF & rect);
private :
    ZI * m_zi;
};

#endif // VIEWZI_H
