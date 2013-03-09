#ifndef VIEWZI_H
#define VIEWZI_H

#include <QColor>
#include <QGraphicsRectItem>

class ZI;

class ViewZI : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    ViewZI(ZI * zi, const QRectF & rect);
    ViewZI( const ViewZI & ) = delete;
    ViewZI & operator=( const ViewZI & ) = delete;
    virtual ~ViewZI(void);

    void changeColor( const QColor & color );
    void resize( int direction, int x, int y );
    void select(void);
    int type(void) const;
    void unselect(void);
public slots :
    void finelize(void);
private :
    ZI * m_zi;
    QColor m_color;
};

#endif // VIEWZI_H
