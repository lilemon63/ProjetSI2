#include <QRectF>
#include <QMouseEvent>

#include "viewzi.h"
#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    m_resizeDirection(NONE),
    m_selectedZI(nullptr)
{
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void GraphicsView::feetInScene(QPointF & point)
{
    QRectF rectScene = scene()->sceneRect();
    if(point.x() < 0)
        point.setX(0);
    else if( point.x() >=  rectScene.width() )
        point.setX( rectScene.width() );

    if( point.y() < 0)
        point.setY(0);
    else if( point.y() >= rectScene.height() )
        point.setY( rectScene.height() );
}



void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF origin = mapToScene( m_originClicX,m_originClicY );
    QPointF final = mapToScene( event->x(), event->y()  );

    feetInScene( origin );
    feetInScene( final );

    if( event->button() ==  Qt::LeftButton) //if the user wants to create a ZI
    {
        if( origin != final )
        {
            QRect rectInScene( origin.x(), origin.y(),
                               final.x() - origin.x(), final.y() - origin.y()
                                );
            emit createZI(rectInScene);
        }
    }
    else if( event->button() == Qt::RightButton) //if the user wants to resize a ZI
    {
        if( m_resizeDirection != NONE && m_selectedZI)
            if( origin != final )
                m_selectedZI->resize( m_resizeDirection, final.x(), final.y() );

        if( m_selectedZI )
            m_selectedZI->unselect();
    }
    event->accept();
}


void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    m_resizeDirection = NONE;
    m_originClicX = event->x();
    m_originClicY = event->y();

    if( event->button() == Qt::RightButton) //if the user wants to select a ZI.
    {
        QPointF p = mapToScene(event->x(), event->y() );
        int x = p.x();
        int y = p.y();
        QList<QGraphicsItem *> listItem = items();
        m_selectedZI = nullptr;
        for( QGraphicsItem * item : listItem) // search the selected area by the user
            if( item->type() == ID_VIEWZI )
            {
                ViewZI * tmpItem = (ViewZI *)item;
                int rx = tmpItem->rect().x();
                int ry = tmpItem->rect().y();
                int rw = tmpItem->rect().width();
                int rh = tmpItem->rect().height();
                //create rectangle from each ZI's side to permit error margin to the user.
                int border = 3;//margin thickness.
                QRectF borders[4];
                borders[0] = QRectF( rx-border,ry-border,rw+2*border,2*border+1);//TOP
                borders[1] = QRectF( rx-border,ry + rh-border, rw + 2*border,2*border);//BOTTOM
                borders[2] = QRectF( rx-border,ry-border,2*border+1,rh+2*border);//LEFT
                borders[3] = QRectF( rx + rw-border,ry-border,2*border,rh+2*border);//RIGHT

                for( int i = 0; i != 4; ++i )  // search collision wich rectangles
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
    event->accept();
}
