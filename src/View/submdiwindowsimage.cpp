#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include "submdiwindowsimage.h"
#include "../Handle/zi.h"
#include "viewzi.h"

SubMdiWindowsImage::SubMdiWindowsImage(const QString &titre, Mdi *area, QWidget *parent) :
    SubMdiWindows(titre, area, parent),
    m_image( m_scene.addPixmap(QPixmap()) ),
    m_graphicsView( new GraphicsView(this) )
{
    m_graphicsView->setScene(&m_scene);
    setWidget(m_graphicsView);
    m_image->setZValue(0);
    connect(this, SIGNAL(handleSignalUpdateImage(ImageDataPtr)), this, SLOT(handleSlotUpdateImage(ImageDataPtr)));
    connect(m_graphicsView, SIGNAL(createZI(QRectF)), this, SLOT(createZI(QRectF)));
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

void SubMdiWindowsImage::createZI(QRectF rect)
{
    if( ! m_handle )
    {
        QMessageBox::information(nullptr, "Erreur lors de la creation d'une Zone d'Interet", "Vous ne pouvez pas creer une Zone d'Interet ici :\nLa vue n'est liee a aucun traitement");
        return;
    }

    QDialog * dialog = new QDialog();
    dialog->setLayout( new QVBoxLayout() );
    dialog->layout()->setSpacing(0);
    QFrame * frame = new QFrame();
    frame->setLayout( new QHBoxLayout() );

    QPushButton * buttonConfirm = new QPushButton("Creer");
    QPushButton * buttonCancel = new QPushButton("Annuler");
    frame->layout()->addWidget(buttonConfirm);
    frame->layout()->addWidget(buttonCancel);
    ZI * zi = m_handle->createZI(rect);
    zi->showParameters( dialog );
    dialog->layout()->addWidget(frame);
    buttonConfirm->setDefault(true);
    dialog->setBaseSize(200, 400);
    dialog->setWindowTitle("Creation d'une nouvelle Zone d'interet");

    m_scene.addItem( zi->view() );
    dialog->show();
}
