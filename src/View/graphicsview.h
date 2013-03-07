#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QRectF>

enum { idViewZI =  QGraphicsItem::UserType + 1 };
class ViewZI;

class GraphicsView : public QGraphicsView
{
    int m_resizeDirection;
    ViewZI * m_selectedZI;

    Q_OBJECT
public:
    enum { NONE,
           TOP = 1<<0,
           BOTTOM = 1<<1,
           LEFT = 1<<2,
           RIGHT = 1<<3};

    explicit GraphicsView(QWidget *parent = 0);
    

    void mouseReleaseEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);
signals:
    void createZI(QRectF);
public slots:
private :
    int m_originClicX, m_originClicY;
};

#endif // GRAPHICSVIEW_H
