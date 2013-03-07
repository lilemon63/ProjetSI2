#ifndef VIEWZI_H
#define VIEWZI_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QColor>
#include <iostream>
#include "graphicsview.h"

class ZI;

class ViewZI : public QGraphicsRectItem
{
public:
    ViewZI(ZI * zi, const QRectF & rect);
    void changeColor( const QColor & color );
    void select(void);
    void unselect(void);
    int type(void) const;
    virtual ~ViewZI(void);
    void resize( int direction, int x, int y );
private :
    ZI * m_zi;
    QColor m_color;
};

#endif // VIEWZI_H
