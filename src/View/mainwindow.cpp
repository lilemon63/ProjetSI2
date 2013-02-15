#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Handle/Parameters/slider.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_extractor(new VideoExtractor() )
{


    ui->setupUi(this);

    int max = 1<<(sizeof(int)*8-2) ;
    m_extractor->changePeriodeParameters( std::shared_ptr<SourceParameters>(new Slider(200000000, 0, max) ),
                                          ui->scrollAreaWidgetContents );

    qRegisterMetaType<ImageDataPtr>("ImageDataPtr");/* obligatoire, à n'appeler qu'une fois et dans une fonction /!\ */
    connect( m_extractor, SIGNAL(imageHandled(ImageDataPtr,ImageDataPtr,ImageDataPtr)),
             this, SLOT(setImage(ImageDataPtr,ImageDataPtr,ImageDataPtr)));

    VideoReader * cam1 = new VideoReader();
    cam1->useCamera();
    m_extractor->useSource(cam1, 0);
    m_extractor->showParameters( ui->scrollAreaWidgetContents );

    m_extractor->start();
}

MainWindow::~MainWindow()
{
    m_extractor->stop();
    delete ui;
}

void MainWindow::setImage(const ImageDataPtr result, const ImageDataPtr , const ImageDataPtr)
{
    ui->labelImage->setPixmap(result->toPixmap());
}
