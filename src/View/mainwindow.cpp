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
    m_subImage = new SubMdiWindows("Image Finale");
    ui->mdiArea->addSubWindow(m_subImage);

    m_subImage->setWindowTitle("Image finale");

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

    //VideoReader * cam1 = new VideoReader();
    //cam1->useCamera();

    FolderReader * cam1 = new FolderReader("img/");

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
    if(m_subImage)
    {
        m_subImage->updateImage(result->toPixmap());
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
}

void MainWindow::onCloseMainSubWindows(void)
{
    m_subImage = nullptr;
}
