#include <QDialog>
#include <QVBoxLayout>

#include "mdi.h"
#include "submdiwindows.h"
#include "../Handle/virtualhandle.h"

SubMdiWindows::SubMdiWindows(const QString &titre, Mdi * area, QWidget *parent) :
    QMdiSubWindow(parent),
    m_area(area),
    m_attached(true),
    m_handle(nullptr),
    m_nbSystemResize(0)
{
    setWindowTitle(titre);
    if( area )
        area->addSubWindow(this);
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void SubMdiWindows::detach(void)
{
    this->m_detach(nullptr);
}


bool SubMdiWindows::isAttached(void) const
{
    return m_attached;
}


void SubMdiWindows::linkHandle( VirtualHandle * handle )
{
    m_handle = handle;
}


void SubMdiWindows::systemMove(int x, int y)
{
    m_nbSystemResize++;
    move( QPoint(x,y) );
}


void SubMdiWindows::systemResize(int x, int y)
{
    m_nbSystemResize++;
    resize( QSize(x, y) );
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC SLOT------------------------------------------
---------------------------------------------------------------------------------------------------*/

void SubMdiWindows::attach(void)
{
    m_attach(nullptr);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PROTECTED--------------------------------------------
---------------------------------------------------------------------------------------------------*/

void SubMdiWindows::closeEvent(QCloseEvent *closeEvent)
{
    QMdiSubWindow::closeEvent(closeEvent);
    if(m_handle)
        m_handle->viewClosed();
    emit destroyed();
    mdiArea()->removeSubWindow(this);
}


void SubMdiWindows::moveEvent(QMoveEvent *moveEvent)
{
    QMdiSubWindow::moveEvent(moveEvent);
    if( ! m_nbSystemResize )
        emit onMove();
    else
        m_nbSystemResize--;
}


void SubMdiWindows::m_attach(QWidget * widget)
{
    if( widget->parent() )
        widget->parent()->deleteLater();
    widget->setParent(this);
    setWidget(widget);
    widget->show();
    m_attached = true;
    setStyleSheet("");
}


void SubMdiWindows::m_detach(QWidget * widget)
{
    setWidget(nullptr);

    QDialog * dialog = new QDialog();
    dialog->setLayout( new QVBoxLayout() );
    dialog->layout()->addWidget(widget );
    dialog->layout()->setMargin(0);
    dialog->setWindowTitle( windowTitle() );
    connect(dialog, SIGNAL( finished(int) ), this, SLOT( attach() ) );
    dialog->show();

    m_attached = false;
    setStyleSheet("background-color: black");
}


void SubMdiWindows::resizeEvent(QResizeEvent *resizeEvent)
{
    QMdiSubWindow::resizeEvent(resizeEvent);
    if( ! m_nbSystemResize )
        emit onMove();
    else
        m_nbSystemResize--;
}
