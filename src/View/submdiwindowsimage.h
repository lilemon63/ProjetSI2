#ifndef SUBMDIWINDOWSIMAGE_H
#define SUBMDIWINDOWSIMAGE_H

#include <QGraphicsScene>

#include "submdiwindows.h"

class GraphicsView;
class QGraphicsItem;
class QGraphicsPixmapItem;

/** @brief SubMdiWindows used to show ImageData. */
class SubMdiWindowsImage : public SubMdiWindows
{
    Q_OBJECT
public:
    /** @brief build a SubMdiWindowsImage.
    **  @param const QString &titre = QString() : window's title.
    **  @param Mdi *area = nullptr : Mdi where the SubMdiWindows will be shown.
    **  @param QWidget *parent = nullptr : SubMdiWindows' parent.
    */
    explicit SubMdiWindowsImage(const QString &titre = QString(), Mdi *area = nullptr,
                                QWidget *parent = nullptr);

    virtual ~SubMdiWindowsImage(){}


    /** @brief Attach the SubMdiWindowsImage to its Mdi. */
    virtual void attach(void);


    /** @brief Detach the SubMdiWindowsImage from the Mdi.
    **
    **  We will have a free windows which is useful when the user have several screens.
    */
    virtual void detach(void);


    /** @brief draw a QGraphicsItem on the SubMdiWindowsImage.
    **  @param QGraphicsItem * item : QGraphicsItem to draw.
    */
    void draw(QGraphicsItem * item);


    /** @brief Process resize event.
    **  @param QResizeEvent *resizeEvent : resize event.
    */
    void resizeEvent(QResizeEvent *resizeEvent);


    /** @brief Update the image.
    **  @param const QPixmap & : new image.
    **  @warning if you aren't into the main thread, call updateImageAsc instead because we shouldn't
        use QPixmap out tje main thread, it's not safe.
    */
    void updateImage(const QPixmap &);


    /** @brief Update the image asynchronous.
    **  @param const ImageDataPtr : new image.
    */
    void updateImageAsc(const ImageDataPtr );
signals:

    /** @brief Send by updateImageAsc().
    **  @param const ImageDataPtr.
    */
    void handleSignalUpdateImage(const ImageDataPtr );
private slots :

    /** @brief Create a ZI.
    **  @param QRect : rectangle which delimitate the ZI's area.
    */
    void createZI(QRect);


    /** @brief Call updateImage().
    **  @param const ImageDataPtr : ImageData to shown.
    */
    void handleSlotUpdateImage(const ImageDataPtr );
private :
    /** @brief view used. */
    GraphicsView * m_graphicsView;

    /** @brief shown image. */
    QGraphicsPixmapItem * m_image;


    /** @brief used scene. */
    QGraphicsScene m_scene;
};

#endif // SUBMDIWINDOWSIMAGE_H
