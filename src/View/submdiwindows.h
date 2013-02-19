#ifndef SUBMDIWINDOWS_H
#define SUBMDIWINDOWS_H

#include <QMdiSubWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QMdiArea>
#include "../Handle/virtualhandle.h"

class SubMdiWindows : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit SubMdiWindows(const QString &titre = QString(), Mdi *area = nullptr, QWidget *parent = nullptr);
    virtual ~SubMdiWindows(){}
    void systemResize(int x, int y);
    void systemMove(int x, int y);
    virtual void linkHandle( VirtualHandle * );
protected :
    virtual void resizeEvent(QResizeEvent *resizeEvent);
    virtual void closeEvent(QCloseEvent *closeEvent);
    virtual void moveEvent(QMoveEvent *moveEvent);
signals:
    void onMove(void);
public slots:
private :
    int m_nbSystemResize;
    VirtualHandle * m_handle;
};

#endif // SUBMDIWINDOWS_H
