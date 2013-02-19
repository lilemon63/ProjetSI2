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
    virtual void detach(void);
    bool isAttached(void);
protected :
    virtual void resizeEvent(QResizeEvent *resizeEvent);
    virtual void closeEvent(QCloseEvent *closeEvent);
    virtual void moveEvent(QMoveEvent *moveEvent);
signals:
    void onMove(void);
public slots:
    virtual void attach(void);
private :
    int m_nbSystemResize;
    VirtualHandle * m_handle;
    bool m_attached;
    Mdi * m_area;
protected :
    virtual void m_attach(QWidget *);
    virtual void m_detach(QWidget *);
};

#endif // SUBMDIWINDOWS_H
