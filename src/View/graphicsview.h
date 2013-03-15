#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>

/** @brief Define some user types of QGraphicsItem. */
enum UserType {
    /** @brief Type for a ViewZI */
    ID_VIEWZI =  QGraphicsItem::UserType + 1 };

class ViewZI;

/** @brief QGraphics view used to process user mouse's event in a VirtualHandle's View.
**
**  The user can resize and create ZI.
** @warning Do not inherit of it.
** @see SubMdiWindowsImage
*/
class GraphicsView : public QGraphicsView //final
{
    Q_OBJECT
public:
    enum DIRECTION{ NONE,
                   TOP = 1<<0,
                   BOTTOM = 1<<1,
                   LEFT = 1<<2,
                   RIGHT = 1<<3};

    /** @brief Build a new GraphicsView.
    **  @param QWidget *parent = 0 : GraphicsView's parent.
    */
    explicit GraphicsView(QWidget *parent = 0);

    GraphicsView( const GraphicsView & ) = delete;
    GraphicsView & operator=( const GraphicsView & ) = delete;

    /** @brief Place the point in the scene if it isn't.
    **
    **  If the point isn't in the scene, we change it to the near point in the scene.
    */
    void feetInScene(QPointF & point);


    /** @brief Process mouse press event.
    **  @param QMouseEvent *event : event.
    */
    void mousePressEvent(QMouseEvent *event);


    /** @brief Process mouse release event.
    **  @param QMouseEvent *event : event.
    */
    void mouseReleaseEvent(QMouseEvent *event);


signals:
    /** @brief Emitted when the user wants to create a ZI */
    void createZI(QRect);
private :
    /** @brief Abscissa of the last mouse press event */
    int m_originClicX;

    /** @brief Ordinate of the last mouse press event */
    int m_originClicY;

    /** @brief resize direction */
    int m_resizeDirection;

    /** @brief ViewZI selected by the user. */
    ViewZI * m_selectedZI;
};

#endif // GRAPHICSVIEW_H
