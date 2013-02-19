#include "submdiwindows.h"
#include <iostream>

SubMdiWindows::SubMdiWindows(const QString &titre, Mdi * area, QWidget *parent) :
    QMdiSubWindow(parent),
    m_nbSystemResize(0),
    m_handle(nullptr)
{

    setWindowTitle(titre);
    if( area )
        area->addSubWindow(this);
}

void SubMdiWindows::resizeEvent(QResizeEvent *resizeEvent)
{
    QMdiSubWindow::resizeEvent(resizeEvent);
    if( ! m_nbSystemResize )
        emit onMove();
    else
        m_nbSystemResize--;
}

void SubMdiWindows::moveEvent(QMoveEvent *moveEvent)
{
    QMdiSubWindow::moveEvent(moveEvent);
    if( ! m_nbSystemResize )
        emit onMove();
    else
        m_nbSystemResize--;
}

void SubMdiWindows::closeEvent(QCloseEvent *closeEvent)
{
    QMdiSubWindow::closeEvent(closeEvent);
    if(m_handle)
        m_handle->viewClosed();
    emit destroyed();
    mdiArea()->removeSubWindow(this);
}

void SubMdiWindows::systemResize(int x, int y)
{
    m_nbSystemResize++;
    resize(QSize(x, y));
}

void SubMdiWindows::systemMove(int x, int y)
{
    m_nbSystemResize++;
    move(QPoint(x,y));
}

void SubMdiWindows::linkHandle( VirtualHandle * handle )
{
    m_handle = handle;
}
