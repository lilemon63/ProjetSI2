#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    VideoReader * cam1 = new VideoReader();
    cam1->useCamera();
    ui->setupUi(this);
    qRegisterMetaType<ImageDataPtr>("ImageDataPtr");/* obligatoire, à n'appeler qu'une fois et dans une fonction /!\ */
    connect( &m_extractor, SIGNAL(imageHandled(ImageDataPtr,ImageDataPtr,ImageDataPtr)),
             this, SLOT(setImage(ImageDataPtr,ImageDataPtr,ImageDataPtr)));
    m_extractor.useSource(cam1, 0);
    m_extractor.start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage(const ImageDataPtr result, const ImageDataPtr , const ImageDataPtr)
{
    ui->labelImage->setPixmap(result->toPixmap());
}
