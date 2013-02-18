#ifndef SUBMDIWINDOWS_H
#define SUBMDIWINDOWS_H

#include <QMdiSubWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QMdiArea>

class SubMdiWindows : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit SubMdiWindows(const QString &titre = QString(), QMdiArea *area = 0, QWidget *parent = nullptr);
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
