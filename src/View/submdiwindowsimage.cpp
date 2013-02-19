#include "submdiwindowsimage.h"

SubMdiWindowsImage::SubMdiWindowsImage(const QString &titre, Mdi *area, QWidget *parent) :
    SubMdiWindows(titre, area, parent),
    m_image( m_scene.addPixmap(QPixmap()) ),
    m_graphicsView( new GraphicsView(this) )
{
    m_graphicsView->setScene(&m_scene);
    setWidget(m_graphicsView);
    m_image->setZValue(0);
    connect(this, SIGNAL(handleSignalUpdateImage(ImageDataPtr)), this, SLOT(handleSlotUpdateImage(ImageDataPtr)));
}


void SubMdiWindowsImage::updateImage(const QPixmap & img)
{
    m_image->setPixmap(img);
    // m_graphicsView->setMinimumHeight(m_image->pixmap().height() + 5);
    // m_graphicsView->setMinimumWidth(m_image->pixmap().width() + 5);
    m_graphicsView->fitInView(m_image,Qt::KeepAspectRatio);
}

void SubMdiWindowsImage::resizeEvent(QResizeEvent *resizeEvent)
{
    SubMdiWindows::resizeEvent(resizeEvent);
    m_graphicsView->fitInView(m_image,Qt::KeepAspectRatio);
}

void SubMdiWindowsImage::updateImageAsc(const ImageDataPtr image)
{
    ImageDataPtr img( new ImageData(*image->getImage()) );
    emit handleSignalUpdateImage(img);
}

void SubMdiWindowsImage::handleSlotUpdateImage(const ImageDataPtr image)
{
    updateImage( image->toPixmap() );
}


void SubMdiWindowsImage::attach(void)
{
    m_attach( m_graphicsView );
}

void SubMdiWindowsImage::detach(void)
{
    m_detach( m_graphicsView );
}
