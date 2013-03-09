#ifndef SUBMDIWINDOWSIMAGE_H
#define SUBMDIWINDOWSIMAGE_H

#include <QGraphicsScene>

#include "submdiwindows.h"

class GraphicsView;
class QGraphicsItem;
class QGraphicsPixmapItem;

class SubMdiWindowsImage : public SubMdiWindows
{
    Q_OBJECT
public:
    explicit SubMdiWindowsImage(const QString &titre = QString(), Mdi *area = nullptr,
                                QWidget *parent = nullptr);
    virtual ~SubMdiWindowsImage(){}

    virtual void attach(void);
    virtual void detach(void);
    void draw(QGraphicsItem * item);
    void resizeEvent(QResizeEvent *resizeEvent);
    void updateImage(const QPixmap &);
    void updateImageAsc(const ImageDataPtr );
signals:
    void handleSignalUpdateImage(const ImageDataPtr );
private slots :
    void createZI(QRect);
    void handleSlotUpdateImage(const ImageDataPtr );
private :
    GraphicsView * m_graphicsView;
    QGraphicsPixmapItem * m_image;
    QGraphicsScene m_scene;
};

#endif // SUBMDIWINDOWSIMAGE_H
