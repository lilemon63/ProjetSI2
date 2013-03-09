#ifndef SUBMDIWINDOWS_H
#define SUBMDIWINDOWS_H

#include <QMdiSubWindow>

#include "../Handle/imagedata.h"

class Mdi;
class VirtualHandle;

class SubMdiWindows : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit SubMdiWindows(const QString &titre = QString(), Mdi *area = nullptr, QWidget *parent = nullptr);
    SubMdiWindows( const SubMdiWindows &) = delete;
    SubMdiWindows & operator=(const SubMdiWindows & ) = delete;
    virtual ~SubMdiWindows(){}

    virtual void detach(void);
    bool isAttached(void) const;
    virtual void linkHandle( VirtualHandle * );
    void systemMove(int x, int y);
    void systemResize(int x, int y);
public slots:
    virtual void attach(void);
signals:
    void onMove(void);
protected :
    virtual void closeEvent(QCloseEvent *closeEvent);
    virtual void moveEvent(QMoveEvent *moveEvent);
    virtual void m_attach(QWidget *);
    virtual void m_detach(QWidget *);
    virtual void resizeEvent(QResizeEvent *resizeEvent);
    VirtualHandle * m_handle;
private :
    Mdi * m_area;
    bool m_attached;
    int m_nbSystemResize;
};

#endif // SUBMDIWINDOWS_H
