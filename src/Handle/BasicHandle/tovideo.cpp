#include "tovideo.h"
#include "../Parameters/spinbox.h"
#include "../../exception.h"
#include <QDateTime>
#include <QObject>
#include "../Parameters/checkbox.h"

ToVideo::ToVideo(const std::string &path, const QString & affName,const std::string &name)
    :VirtualHandle(affName,name),
      m_Path(new InputText("Path",QString(path.c_str()),InputText::SaveFile)),
      m_progress( new ProgressBar("progression") ),
      m_checkBox( new CheckBox("Video", QStringList({"Actif"}) ) ),
      m_isActif(false)
{
    m_listParameters.resize(Max);
    m_listParameters[FrameRate] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[FrameRate]->changeSources( new SpinBox("Framerate") );
    m_listParameters[Duree] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Duree]->changeSources( new SpinBox("Durée en secondes") );

    m_listParameters[Progress] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Progress]->changeSources( m_progress );

    m_listParameters[Prise] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Prise]->changeSources( m_checkBox );

    m_listParameters[PathV] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[PathV]->changeSources(m_Path);

    auto lambdaMax = [this](QVariant Value, HandleParameters * hp) {
            m_progress->setMaximum( Value.toInt() );
            hp->acceptChanges(Value);
    };
    m_listParameters[Duree]->setActionOnChangeValue( lambdaMax );

    auto lambdaActif = [this](QVariant Value, HandleParameters * hp) {
            hp->acceptChanges(Value);
            if( m_listParameters[Prise]->toMap()["Actif"].toBool() )
            {
                    m_timer.start();
                    m_progress->setValue(0);
            }

    };
    m_listParameters[Prise]->setActionOnChangeValue( lambdaActif );
}

void ToVideo::init(const ImageDataPtr src1)
{
    int FPS = m_listParameters[FrameRate]->toInt();
    std::string videoPath = m_listParameters[PathV]->toString().toStdString (); // + "/TIFF_Image_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh'h'mm'm'ss's'zzz").toStdString() + ".avi";
    m_writer = cvCreateAVIWriter(videoPath.c_str(),CV_FOURCC('M','J','P','G'),FPS,cvGetSize(src1->getImage()),1);
    m_progress->setMaximum( m_listParameters[Duree]->toInt() );
}

ImageDataPtr ToVideo::startHandle(const ImageDataPtr src1, const ImageDataPtr)
{
    if( ! src1)
        throw Exception::buildException("La source est vide", "ToVideo", "startHandle", EPC);

    bool isActif = m_listParameters[Prise]->toMap()["Actif"].toBool();


    if( m_isActif != isActif)
    {
        if( isActif )
            init(src1);
        else
            onEnding();
        m_isActif = isActif;
    }

    if( isActif )
    {
        int time = m_listParameters[Duree]->toInt();
        time *= 1000;
        if( m_timer.elapsed() > time )
        {
            onEnding();
            m_checkBox->changeValue("Actif", false);
        }
        else
        {
            saveFrame( src1 );//ImageDataPtr(new ImageData(*src1) ) );
        }
        std::cerr << m_timer.elapsed()/1000 << std::endl;
        m_progress->setValue( m_timer.elapsed()/1000 );
    }
    return src1;
}

void ToVideo::onEnding()
{
    cvReleaseVideoWriter(& m_writer);
}

void ToVideo::saveFrame( ImageDataPtr src1)
{
    cvWriteFrame(m_writer,src1->getImage());
}
