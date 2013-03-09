#include "mdi.h"
#include "mainwindow.h"
#include "submdiwindows.h"


Mdi::Mdi(QWidget *parent) :
    QMdiArea(parent),
    m_mainWindow(nullptr)
{
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void Mdi::addSubWindow(QWidget *widget, Qt::WindowFlags flags)
{
    if(m_mainWindow)
    {
        SubMdiWindows * wind = static_cast<SubMdiWindows*>(widget);
        if(wind)
        {
            connect(wind, SIGNAL( windowStateChanged( Qt::WindowStates,Qt::WindowStates) ),
                    m_mainWindow, SLOT( windowStateChanged( Qt::WindowStates,Qt::WindowStates) ) );
            connect(wind, SIGNAL( destroyed() ), m_mainWindow, SLOT( onCloseMainSubWindows() ) );
            connect(wind, SIGNAL( onMove() ), m_mainWindow, SLOT( quitDefaultMode() ) );
        }
    }
    QMdiArea::addSubWindow(widget, flags);
}


void Mdi::reductAllExcept(const std::set<SubMdiWindows *> & exceptions)
{
    for( auto wind : subWindowList() )
        if( exceptions.find( static_cast<SubMdiWindows*>(wind) ) ==  exceptions.end() && wind->isVisible() )
            wind->showMinimized();
}


void Mdi::setMainWindow(MainWindow * mw)
{
    m_mainWindow = mw;
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PROTECTED--------------------------------------------
---------------------------------------------------------------------------------------------------*/

void Mdi::resizeEvent(QResizeEvent *resizeEvent)
{
    QMdiArea::resizeEvent(resizeEvent);
    emit onResize();
}
