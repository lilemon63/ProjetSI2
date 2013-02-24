#ifndef SUBMDIWINDOWSIMAGE_H
#define SUBMDIWINDOWSIMAGE_H

#include "submdiwindows.h"
#include "graphicsview.h"

class SubMdiWindowsImage : public SubMdiWindows
{
    Q_OBJECT
public:
    explicit SubMdiWindowsImage(const QString &titre = QString(), Mdi *area = nullptr, QWidget *parent = nullptr);
    void updateImage(const QPixmap &);
    void resizeEvent(QResizeEvent *resizeEvent);
    void updateImageAsc(const ImageDataPtr );
    virtual void attach(void);
    virtual void detach(void);
signals:
    void handleSignalUpdateImage(const ImageDataPtr );
public slots:
private slots :
    void handleSlotUpdateImage(const ImageDataPtr );
    void createZI(QRectF);
private :
    QGraphicsScene m_scene;
    QGraphicsPixmapItem * m_image;
    GraphicsView * m_graphicsView;


};

#endif // SUBMDIWINDOWSIMAGE_H
