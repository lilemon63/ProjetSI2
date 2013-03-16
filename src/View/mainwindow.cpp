#include <QDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Handle/Handle.h"
#include "../Handle/videoextractor.h"
#include "../Handle/Reader/folderreader.h"
#include "../Handle/Parameters/slider.h"
#include "../Handle/Parameters/combobox.h"
#include "../Handle/Parameters/handleparameters.h"
#include "submdiwindowsimage.h"
#include "submdiwindowsresults.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_areaMode( Default ),
    m_extractor(new VideoExtractor() ),
    m_isHandleActived(true),
    m_isPlay(false),
    m_subImage(nullptr),
    m_subImageSource1(nullptr),
    m_subImageSource2(nullptr),
    m_subResults(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mdiArea->setMainWindow(this);

    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT( quit() ) );

    connect(ui->buttonPrevious, SIGNAL(clicked()), m_extractor, SLOT(previous()));
    connect(ui->buttonNext, SIGNAL(clicked()), m_extractor, SLOT(next()));

    ui->mdiAreaMode->addItem("Default", Default);
    ui->mdiAreaMode->addItem("Tabulation", Tabulation);
    ui->mdiAreaMode->addItem("Libre", Free);

    int max = 1<<(sizeof(int)*8-2) ;

    m_extractor->changeHandleParameters( new ComboBox("Traitement", VirtualHandle::getAllHandleName(),
                                                      MainHandle),
                                            ui->scrollAreaWidgetContents );
    m_extractor->changePeriodeParameters( new Slider("Time", 200000000, 0, max) ,
                                          ui->scrollAreaWidgetContents );

    /* obligatoire, à n'appeler qu'une unique fois et dans une fonction /!\ */
    qRegisterMetaType<ImageDataPtr>("ImageDataPtr");
    connect( m_extractor, SIGNAL(imageHandled(ImageDataPtr,ImageDataPtr,ImageDataPtr) ),
             this, SLOT(setImage(ImageDataPtr,ImageDataPtr,ImageDataPtr) ) );

    VideoReader * cam1 = new VideoReader();
    cam1->useCamera(); //or FolderReader * cam1 = new FolderReader("img/");

    m_extractor->useSource(cam1, 0);
    m_extractor->showParameters( ui->scrollAreaWidgetContents );

    ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(m_areaMode) );
    VirtualHandle::setView(ui->mdiArea);

    m_extractor->start();
    updateSeek();
}


MainWindow::~MainWindow()
{
    m_extractor->stop();
    delete ui;
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC SLOT------------------------------------------
---------------------------------------------------------------------------------------------------*/

void MainWindow::activeHandle()
{
    m_isHandleActived = ! m_isHandleActived;
    m_extractor->activeHandle(m_isHandleActived);

    if( m_isHandleActived )
        ui->buttonactiveHandle->setText("Arreter les traitements");
    else
        ui->buttonactiveHandle->setText("Lancer les traitements");
}


void MainWindow::attachDetach(void)
{
    SubMdiWindows * subWind = static_cast<SubMdiWindows *>(ui->mdiArea->currentSubWindow() );
    if( subWind )
    {
        if( subWind->isAttached() )
            subWind->detach();
        else
            subWind->attach();
    }
}


void MainWindow::changeMdiMode(int index)
{
    Mode mode = ( index == -1 ) ?  m_areaMode : (Mode)ui->mdiAreaMode->itemData(index).toInt() ;
    if( mode == Default)
    {
        if( ! m_subImage)           m_subImage = new SubMdiWindowsImage("Image Finale", ui->mdiArea);
        if( ! m_subImageSource1)    m_subImageSource1 = new SubMdiWindowsImage("Image Source1", ui->mdiArea);
        if( ! m_subImageSource2)    m_subImageSource2 = new SubMdiWindowsImage("Image Source2", ui->mdiArea);
        if( ! m_subResults )
        {
            m_subResults = new SubMdiWindowsResults("Donnees issues du traitement", ui->mdiArea);
            connect(ui->actionSauvegarder_les_donn_es_acquises, SIGNAL(triggered() ),
                    m_subResults, SLOT(saveIntoFile() ) );
            connect(m_subResults, SIGNAL(resultFile(QString,bool) ) ,ui->statusbar, SLOT(showMessage(QString) ) );
        }
        m_subImageSource1->showNormal();                m_subImageSource2->showNormal();
        m_subImage->showNormal();                       m_subResults->showNormal();

        if( m_areaMode == Tabulation )
            ui->mdiArea->setViewMode( QMdiArea::SubWindowView );

        int midX = ui->mdiArea->size().width()/2;       int midY = ui->mdiArea->size().height()/2;

        m_subImageSource1->systemMove(0,0);             m_subImageSource2->systemMove(midX,0);
        m_subImageSource1->systemResize(midX, midY);    m_subImageSource2->systemResize(midX, midY);

        m_subImage->systemMove(0,midY);                 m_subResults->systemMove(midX,midY);
        m_subImage->systemResize(midX, midY);           m_subResults->systemResize(midX, midY);

        ui->mdiArea->reductAllExcept( std::set<SubMdiWindows *>({m_subImage, m_subImageSource1,
                                                                m_subImageSource2, m_subResults}) );
    }
    else if( mode == Tabulation)
    {
        if(m_areaMode != Tabulation)
            ui->mdiArea->setViewMode( QMdiArea::TabbedView );
    }
    else
    {
        if(m_areaMode == Tabulation)
            ui->mdiArea->setViewMode( QMdiArea::SubWindowView );
    }
    m_areaMode = mode;
}


void MainWindow::enterInDefaultMode(void)
{
    ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(Default) );
}


void MainWindow::enterInFreeMode(void)
{
    if( m_areaMode != Free )
        ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(Free) );
}


void MainWindow::enterInTabulationMode(void)
{
    if( m_areaMode != Tabulation )
        ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(Tabulation) );
}


void MainWindow::fullscreen(void)
{
    if( isFullScreen() )
        showNormal();
    else
        showFullScreen();
}


void MainWindow::nextFrame(void)
{
    m_isPlay = false;
    ui->buttonPlay->setText("Lancer les flux");
    m_extractor->next();
}


void MainWindow::onCloseMainSubWindows(void)
{
    QObject * ptr = QObject::sender();
    if(ptr == m_subImage)
        m_subImage = nullptr;
    else if(ptr == m_subImageSource1)
        m_subImageSource1 = nullptr;
    else if(ptr == m_subImageSource2)
        m_subImageSource2 = nullptr;
    else
        m_subResults = nullptr;
    if( m_areaMode == Default )
        ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(Free) );
}


void MainWindow::playPause(void)
{
    m_isPlay = ! m_isPlay;
    if( m_isPlay )
    {
        m_extractor->play();
        ui->buttonPlay->setText("Stopper les flux");
    }
    else
    {
        m_extractor->pause();
        ui->buttonPlay->setText("Lancer les flux");
    }
}


void MainWindow::previousFrame(void)
{
    m_isPlay = false;
    ui->buttonPlay->setText("Lancer les flux");
    m_extractor->previous();
}


void MainWindow::quitDefaultMode(void)
{
    if( m_areaMode == Default )
        ui->mdiAreaMode->setCurrentIndex( ui->mdiAreaMode->findData(Free) );
}


void MainWindow::resizeMdi(void)
{
    changeMdiMode(-1);
}


void MainWindow::saveDataFileName(void)
{
    //TODO : add params
}


void MainWindow::setImage(ImageDataPtr result, ImageDataPtr source1, ImageDataPtr source2)
{
    if(m_subImage)
        m_subImage->updateImage(result->toPixmap());

    if(m_subImageSource1 && source1)
        m_subImageSource1->updateImage(source1->toPixmap());

    if( m_subImageSource2 && source2)
        m_subImageSource2->updateImage(source2->toPixmap());

    if( m_subResults )
        m_subResults->extractInformationFromImage(result);

    int value = ui->sliderCurseur->value() + 1;
    ui->sliderCurseur->setValue( value );
    ui->labelCurseur->setText( QString::number( value ) );
}


void MainWindow::showHideDockParameters(void)
{
    ui->dockWidget_2->setVisible( ! ui->dockWidget_2->isVisible() );
}


void MainWindow::showHideDockStreamControl(void)
{
    ui->dockWidget->setVisible(! ui->dockWidget->isVisible());
}


void MainWindow::sliderMoved(int value)
{
    m_extractor->slid(value);
    ui->labelCurseur->setText( QString::number( value ) );
}


void MainWindow::windowStateChanged(Qt::WindowStates, Qt::WindowStates states)
{
    if( states == Qt::WindowActive || states == Qt::WindowNoState)
        return;
    if( m_areaMode == Default )
    {
        QObject * sender = QObject::sender();
        if ( states &  Qt::WindowMinimized
             && ( sender == m_subImage || sender == m_subImageSource1
                  || sender == m_subImageSource2 || sender == m_subResults
                )
            )
            enterInFreeMode();
    }
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void MainWindow::openChangeSourcesDialog( int idSource )
{
    QDialog * dialog = new QDialog();
    dialog->setModal(true);
    dialog->setLayout( new QVBoxLayout() );

    auto sourceType = HandleParameters::build_comboBox( "Type de la source",
                                                        {"Camera", "Dossier", "Aucune"} );
    auto path = HandleParameters::build_inputtext( "Chemin", ".",  InputText::Directory );
    QFrame * pathFrame = new QFrame();
    pathFrame->setLayout( new QVBoxLayout() );
    path->showParameters( pathFrame );
    sourceType->setActionOnChangeValue( [this, &pathFrame, &dialog](QVariant value, HandleParameters * hp)
        {
            hp->acceptChanges(value);
            if( hp->toString() == "Dossier")
                pathFrame->show();
            else
                pathFrame->hide();
        }
                                        );
    sourceType->showParameters( dialog );
    ( (QVBoxLayout *)dialog->layout() )->addStretch(0);
    dialog->layout()->addWidget( pathFrame );
    pathFrame->hide();

    QFrame * frame = new QFrame();
    frame->setLayout(new QHBoxLayout() );
    QPushButton * changeSource = new QPushButton("Changer source");
    QPushButton * cancel = new QPushButton("Annuler");
    frame->layout()->addWidget( changeSource );
    frame->layout()->addWidget( cancel );
    dialog->layout()->addWidget( frame );

    connect( changeSource, SIGNAL(clicked() ), dialog, SLOT(accept()));
    connect( cancel, SIGNAL(clicked() ), dialog, SLOT(reject()));

    dialog->setWindowTitle("Configuration de la source " + QString::number(idSource) );



    if( dialog->exec() == QDialog::Accepted )
    {
        m_extractor->useSource( new VideoReader() , idSource - 1);
        VideoReader * reader;
        if( sourceType->toString() == "Camera")
        {
            reader = new VideoReader();
            reader->useCamera();
        }
        else if( sourceType->toString() == "Dossier" )
            reader = new FolderReader( path->toString().toStdString() );

        m_extractor->useSource( reader , idSource - 1);
    }
    dialog->deleteLater();
}


void MainWindow::updateSeek()
{
    bool enable = m_extractor->acceptSeek();

    ui->buttonNext->setEnabled(enable);
    ui->buttonPrevious->setEnabled(enable);
    ui->sliderCurseur->setEnabled(enable);

    ui->sliderCurseur->setValue(0);
    ui->labelCurseur->setText("0");

    ui->sliderCurseur->setMaximum( m_extractor->numberOfFrame() );
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void MainWindow::changeSource1(void)
{
    openChangeSourcesDialog(1);
}

void MainWindow::changeSource2(void)
{
    openChangeSourcesDialog(2);
}
