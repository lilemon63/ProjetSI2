#include "submdiwindows.h"
#include <iostream>

SubMdiWindows::SubMdiWindows(const QString &titre, QMdiArea * area, QWidget *parent) :
    QMdiSubWindow(parent),
    m_image( m_scene.addPixmap(QPixmap()) ),
    m_graphicsView( new QGraphicsView(this) )
{
    m_graphicsView->setScene(&m_scene);
    setWidget(m_graphicsView);
    setWindowTitle(titre);
    m_image->setZValue(0);
    if( area )
        area->addSubWindow(this);
}

void SubMdiWindows::resizeEvent(QResizeEvent *resizeEvent)
{
    QMdiSubWindow::resizeEvent(resizeEvent);
    m_graphicsView->fitInView(m_image,Qt::KeepAspectRatio);
}

void SubMdiWindows::closeEvent(QCloseEvent *closeEvent)
{
    QMdiSubWindow::closeEvent(closeEvent);
    deleteLater();
}

void SubMdiWindows::updateImage(const QPixmap & img)
{
    m_image->setPixmap(img);
    // m_graphicsView->setMinimumHeight(m_image->pixmap().height() + 5);
    // m_graphicsView->setMinimumWidth(m_image->pixmap().width() + 5);
    m_graphicsView->fitInView(m_image,Qt::KeepAspectRatio);
}
