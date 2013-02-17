#ifndef SUBMDIWINDOWS_H
#define SUBMDIWINDOWS_H

#include <QMdiSubWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>

class SubMdiWindows : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit SubMdiWindows(const QString &titre = QString(), QWidget *parent = 0);
    void updateImage(const QPixmap &);
protected :
    void resizeEvent(QResizeEvent *resizeEvent);
signals:
public slots:
private :
    QGraphicsScene m_scene;
    QGraphicsPixmapItem * m_image;
    QGraphicsView * m_graphicsView;
};

#endif // SUBMDIWINDOWS_H
