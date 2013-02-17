#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);
    

    void mouseReleaseEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);
signals:
    
public slots:
private :
    int m_originClicX, m_originClicY;
    
};

#endif // GRAPHICSVIEW_H
