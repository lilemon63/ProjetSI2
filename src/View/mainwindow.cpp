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
    m_subImage(nullptr),
    m_subImageSource1(nullptr),
    m_subImageSource2(nullptr),
    m_areaMode( Default )
{


    ui->setupUi(this);

    connect(ui->mdiAreaMode, SIGNAL(currentIndexChanged(int)), this, SLOT(changeMdiMode(int)) );
    connect(ui->mdiArea, SIGNAL(onResize()), this, SLOT(resizeMdi()) );

    ui->mdiAreaMode->addItem("Default", Default);
    ui->mdiAreaMode->addItem("Tabulation", Tabulation);
    ui->mdiAreaMode->addItem("Libre", Free);

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

    ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(m_areaMode) );

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

void MainWindow::changeMdiMode(int index)
{
    Mode mode = m_areaMode;
    if(index != -1)
        mode = (Mode)ui->mdiAreaMode->itemData(index).toInt();
    switch(mode)
    {
        case Default :
        {
            if( ! m_subImage) {
                m_subImage = new SubMdiWindows("Image Finale", ui->mdiArea);
                m_subImage->show();
                connect(m_subImage, SIGNAL(destroyed(QObject*)), this, SLOT(onCloseMainSubWindows()));
            }
            if( ! m_subImageSource1) {
                m_subImageSource1 = new SubMdiWindows("Image Source1", ui->mdiArea);
                m_subImageSource1->show();
                connect(m_subImageSource1, SIGNAL(destroyed(QObject*)), this, SLOT(onCloseMainSubWindows()));
            }
            if( ! m_subImageSource2) {
                m_subImageSource2 = new SubMdiWindows("Image Source2", ui->mdiArea);
                m_subImageSource2->show();
                connect(m_subImageSource2, SIGNAL(destroyed(QObject*)), this, SLOT(onCloseMainSubWindows()));
            }
            if(m_areaMode == Tabulation)
                ui->mdiArea->setViewMode( QMdiArea::SubWindowView );
            int midX = ui->mdiArea->size().width()/2;
            int midY = ui->mdiArea->size().height()/2;
            m_subImageSource1->move(0,0);
            m_subImageSource1->resize(midX, midY);
            m_subImageSource2->move(midX,0);
            m_subImageSource2->resize(midX, midY);
            m_subImage->move(0,midY);
            m_subImage->resize(midX, midY);
        }
        break;

        case Tabulation :
            if(m_areaMode != Tabulation)
                ui->mdiArea->setViewMode( QMdiArea::TabbedView );
        break;
        case Free :
            if(m_areaMode == Tabulation)
                ui->mdiArea->setViewMode( QMdiArea::SubWindowView );
        break;
    }
    m_areaMode = mode;
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
    if( m_areaMode == Default )
        ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(Free) );
}

void MainWindow::resizeMdi(void)
{
    changeMdiMode(-1);
}
