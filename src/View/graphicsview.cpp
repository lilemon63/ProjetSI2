#include "graphicsview.h"
#include <QMouseEvent>
#include <QRectF>
#include <QGraphicsRectItem>
#include <iostream>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    m_originClicX = event->x();
    m_originClicY = event->y();
    event->accept();
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint topLeft( m_originClicX,m_originClicY );
    QPoint bottomRight( event->x(),
                        event->y() );
    QRectF rectInScene( mapToScene(topLeft),
                        mapToScene(bottomRight)
                        );

    emit createZI(rectInScene);
    /*
    QPen p( QColor(255,0,0));
    QGraphicsRectItem * rect = scene()->addRect(rectInScene);
    rect->setZValue(5);
    rect->setPen(p);
*/
    event->accept();
}
