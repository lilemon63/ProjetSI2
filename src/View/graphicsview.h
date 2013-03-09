#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>

enum { ID_VIEWZI =  QGraphicsItem::UserType + 1 };
class ViewZI;

class GraphicsView : public QGraphicsView //final
{
    Q_OBJECT
public:
    enum { NONE,
           TOP = 1<<0,
           BOTTOM = 1<<1,
           LEFT = 1<<2,
           RIGHT = 1<<3};

    explicit GraphicsView(QWidget *parent = 0);
    GraphicsView( const GraphicsView & ) = delete;
    GraphicsView & operator=( const GraphicsView & ) = delete;

    void feetInScene(QPointF & point);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


signals:
    void createZI(QRect);
private :
    int m_originClicX, m_originClicY;
    int m_resizeDirection;
    ViewZI * m_selectedZI;
};

#endif // GRAPHICSVIEW_H
