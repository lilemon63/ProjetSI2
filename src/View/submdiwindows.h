#ifndef SUBMDIWINDOWS_H
#define SUBMDIWINDOWS_H

#include <QMdiSubWindow>

#include "../Handle/imagedata.h"

class Mdi;
class VirtualHandle;


/** @brief Mdi's sub windows.
**  @see SubMdiWindowsImage.
**  @see SubMdiWindowsResults.
*/
class SubMdiWindows : public QMdiSubWindow
{
    Q_OBJECT
public:
    /** @brief build a SubMdiWindows.
    **  @param const QString &titre = QString() : window's title.
    **  @param Mdi *area = nullptr : Mdi where the SubMdiWindows will be shown.
    **  @param QWidget *parent = nullptr : SubMdiWindows' parent.
    */
    explicit SubMdiWindows(const QString &titre = QString(), Mdi *area = nullptr,
                           QWidget *parent = nullptr);

    SubMdiWindows( const SubMdiWindows &) = delete;
    SubMdiWindows & operator=(const SubMdiWindows & ) = delete;
    virtual ~SubMdiWindows(){}


    /** @brief Detach the SubMdiWindows from the Mdi.
    **
    **  We will have a free windows which is useful when the user have several screens.
    */
    virtual void detach(void);


    /** @brief Return true if this SubMdiWindows is attached.
    **  @param bool : true if this SubMdiWindows is attached, else false.
    */
    bool isAttached(void) const;


    /** @brief Link the SubMdiWindows to a VirtualHandle.
    **
    **  When a SubMdiWindows is link to a VirtualHandle, the VirtualHandle can update the SubMdiWindows
        data.
    **  @param VirtualHandle * : VirtualHandle which with we will link the SubMdiWindows.
    */
    virtual void linkHandle( VirtualHandle * );


    /** @brief Move the SubMdiWindows without send onMove() signal ie without quit the default mode. */
    void systemMove(int x, int y);


    /** @brief Resize the SubMdiWindows without send onMove() signal ie without quit the default mode. */
    void systemResize(int x, int y);
public slots:

    /** @brief Attach the SubMdiWindows to its Mdi. */
    virtual void attach(void);
signals:

    /** @brief emitted when the SubMdiWindows is moved. */
    void onMove(void);
protected :

    /** @brief Process close event.
    **  @param QCloseEvent *closeEvent : close event.
    */
    virtual void closeEvent(QCloseEvent *closeEvent);


    /** @brief Process move event.
    **  @param QMoveEvent *moveEvent : move event.
    */
    virtual void moveEvent(QMoveEvent *moveEvent);


    /** @brief attach the  SubMdiWindows.
    **  @param QWidget * : SubMdiWindows's main widget.
    */
    virtual void m_attach(QWidget *);


    /** @brief detach the  SubMdiWindows
    **  @param QWidget * : SubMdiWindows's main widget.
    */
    virtual void m_detach(QWidget *);


    /** @brief Process resize event.
    **  @param QResizeEvent *resizeEvent : resize event.
    */
    virtual void resizeEvent(QResizeEvent *resizeEvent);


    /** @brief linked VirtualHandle or nullptr if there are any. */
    VirtualHandle * m_handle;
private :

    /** @brief SubMdiWindows's Mdi. */
    Mdi * m_area;


    /** @brief if the SubMdiWindows is attached or not. */
    bool m_attached;


    /** @brief Number of system*() called and didn't processed yet. */
    int m_nbSystemResize;
};

#endif // SUBMDIWINDOWS_H
