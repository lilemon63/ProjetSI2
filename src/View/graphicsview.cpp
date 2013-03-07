#include "graphicsview.h"
#include "viewzi.h"
#include <QMouseEvent>
#include <QRectF>
#include <QGraphicsRectItem>
#include <iostream>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    m_resizeDirection(NONE),
    m_selectedZI(nullptr)
{
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    m_resizeDirection = NONE;
    m_originClicX = event->x();
    m_originClicY = event->y();

    if( event->button() == Qt::RightButton)
    {
        QPointF p = mapToScene(event->x(), event->y() );
        int x = p.x();
        int y = p.y();

        QList<QGraphicsItem *> listItem = items();
        m_selectedZI = nullptr;
        for( QGraphicsItem * item : listItem)
        {
            if( item->type() == idViewZI )
            {
                ViewZI * tmpItem = (ViewZI *)item;
                int rx = tmpItem->rect().x();
                int ry = tmpItem->rect().y();
                int rw = tmpItem->rect().width();
                int rh = tmpItem->rect().height();
                int border = 3;
                QRectF borders[4];
                borders[0] = QRectF( rx-border,ry-border,rw+2*border,2*border+1);//TOP
                borders[1] = QRectF( rx-border,ry + rh-border, rw + 2*border,2*border);//BOTTOM
                borders[2] = QRectF( rx-border,ry-border,2*border+1,rh+2*border);//LEFT
                borders[3] = QRectF( rx + rw-border,ry-border,2*border,rh+2*border);//RIGHT

                for( int i = 0; i != 4; ++i )
                    if( borders[i].contains(x , y) )
                        m_resizeDirection += 1<<i;

                if( m_resizeDirection != NONE )
                {
                    m_selectedZI = tmpItem;
                    tmpItem->select();
                    break;
                }
            }
        }
    }
    event->accept();
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() ==  Qt::LeftButton)
    {
        QPoint topLeft( m_originClicX,m_originClicY );
        QPoint bottomRight( event->x(),
                            event->y() );
        if( topLeft != bottomRight )
        {
            QRectF rectInScene( mapToScene(topLeft),
                                mapToScene(bottomRight)
                                );
            emit createZI(rectInScene);
        }
    }
    else if( event->button() == Qt::RightButton)
    {
        if( m_resizeDirection != NONE && m_selectedZI)
        {
            QPoint origin( m_originClicX,m_originClicY );
            QPoint final( event->x(),
                          event->y() );
            if( origin != final )
            {
                QPointF point = mapToScene(final);
                m_selectedZI->resize( m_resizeDirection, point.x(), point.y() );
            }
        }
        if( m_selectedZI )
            m_selectedZI->unselect();
    }
    event->accept();
}
