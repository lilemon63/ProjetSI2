#ifndef VIEWZI_H
#define VIEWZI_H

#include <QColor>
#include <QGraphicsRectItem>

class ZI;

/** @brief View's part for a ZI.
**
**  Show a rectangle and permit to resize the ZI with the mouse.
*/
class ViewZI : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:

    /** @brief Build a ViewZI.
    **  @param ZI * zi : ViewZI's ZI.
    **  @param const QRectF & rect :  ZI's area's rectangle
    */
    ViewZI(ZI * zi, const QRectF & rect);

    ViewZI( const ViewZI & ) = delete;
    ViewZI & operator=( const ViewZI & ) = delete;
    virtual ~ViewZI(void);

    /** @brief Change the ZI's rectangle color.
    **  @param const QColor & color : new ZI's rectangle color.
    */
    void changeColor( const QColor & color );


    /** @brief Resize the ZI's rectangle by move a side to a point.
    **  @param int direction : direction.
    **  @param int x : point's abscissa.
    **  @param int y : point's ordinate.
    **  @see GraphicsView::DIRECTION
    */
    void resize( int direction, int x, int y );


    /** @brief select the ZI rectangle */
    void select(void);


    /** @brief Return the user types of QGraphicsItem for ViewZI.
    **  @see UserType
    **  @return type :  user types of QGraphicsItem for ViewZI.
    */
    int type(void) const;


    /** @brief unselect the ZI rectangle */
    void unselect(void);
public slots :
    /** @brief finelize the ZI creation.
    **
    **  Close the ZiDialog and show the ZI's parameters in the parameters' area.
    */
    void finelize(void);
private :

    /** @brief ViewZI's ZI */
    ZI * m_zi;

    /** @brief ZI's rectangle's color */
    QColor m_color;
};

#endif // VIEWZI_H
