#include "graphicsview.h"
#include <QMouseEvent>
#include <QGraphicsRectItem>

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
    QPen p( QColor(255,0,0));
    QGraphicsRectItem * rect = scene()->addRect(m_originClicX,m_originClicY,
                                                event->x() - m_originClicX,
                                                event->y() - m_originClicY);
    rect->setZValue(5);
    rect->setPen(p);

    event->accept();
}
