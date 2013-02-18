#include <QGraphicsView>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Handle/Handle.h"
#include "../Handle/Parameters/slider.h"
#include "../Handle/Parameters/combobox.h"
#include "../Handle/Reader/folderreader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_extractor(new VideoExtractor() ),
    m_areaMode( QMdiArea::SubWindowView )
{


    ui->setupUi(this);
    m_subImage = new SubMdiWindows("Image Finale", ui->mdiArea);
    m_subImageSource1 = new SubMdiWindows("Image Source1", ui->mdiArea);
    m_subImageSource2 = new SubMdiWindows("Image Source2", ui->mdiArea);

    connect(ui->mdiAreaMode, SIGNAL(clicked()), this, SLOT(changeMdiMode()) );
    connect(m_subImage, SIGNAL(destroyed(QObject*)), this, SLOT(onCloseMainSubWindows()));

    int max = 1<<(sizeof(int)*8-2) ;

    m_extractor->changeHandleParameters( new ComboBox("Traitement", VirtualHandle::getAllHandleName(), MainHandle),
                                            ui->scrollAreaWidgetContents );
    m_extractor->changePeriodeParameters( new Slider("Time", 200000000, 0, max) ,
                                          ui->scrollAreaWidgetContents );


    qRegisterMetaType<ImageDataPtr>("ImageDataPtr");/* obligatoire, à n'appeler qu'une fois et dans une fonction /!\ */
    connect( m_extractor, SIGNAL(imageHandled(ImageDataPtr,ImageDataPtr,ImageDataPtr)),
             this, SLOT(setImage(ImageDataPtr,ImageDataPtr,ImageDataPtr)));

    VideoReader * cam1 = new VideoReader();
    cam1->useCamera();

    //FolderReader * cam1 = new FolderReader("img/");

    m_extractor->useSource(cam1, 0);
    m_extractor->showParameters( ui->scrollAreaWidgetContents );

    m_extractor->start();
}

MainWindow::~MainWindow()
{
    m_extractor->stop();
    delete ui;
}

void MainWindow::setImage(const ImageDataPtr result, const ImageDataPtr source1, const ImageDataPtr source2)
{
    if(m_subImage)
    {
        m_subImage->updateImage(result->toPixmap());
    }
    if(m_subImageSource1 && source1)
    {
        m_subImageSource1->updateImage(source1->toPixmap());
    }
    if( m_subImageSource2 && source2)
    {
        m_subImageSource2->updateImage(source2->toPixmap());
    }
}

void MainWindow::changeMdiMode(void)
{
    if(m_areaMode == QMdiArea::TabbedView)
    {
        ui->mdiArea->setViewMode( QMdiArea::SubWindowView );
        m_areaMode = QMdiArea::SubWindowView;
    }
    else
    {
        ui->mdiArea->setViewMode( QMdiArea::TabbedView );
        m_areaMode = QMdiArea::TabbedView;
    }
    //addMode
}

void MainWindow::onCloseMainSubWindows(void)
{
    QObject * ptr = QObject::sender();
    if(ptr == m_subImage)
        m_subImage = nullptr;
    else if(ptr == m_subImageSource1)
        m_subImageSource1 = nullptr;
    else
        m_subImageSource2 = nullptr;
}
