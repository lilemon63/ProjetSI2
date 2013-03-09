#include "tovideo.h"
#include "../../exception.h"
#include "../Parameters/checkbox.h"

ToVideo::ToVideo(const std::string &path, const QString & affName,const std::string &name)
    : VirtualHandle(affName,name),
      m_checkBox( new CheckBox("Video", QStringList({"Actif"}) ) ),
      m_isActif(false),
      m_progress( new ProgressBar("progression") )
{
    m_listParameters.resize(Max);
    m_listParameters[FrameRate] = HandleParameters::build_spinbox("Framerate");
    m_listParameters[Duree] = HandleParameters::build_spinbox("Durée en secondes");

    m_listParameters[Progress] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Progress]->changeSources( m_progress );

    m_listParameters[Prise] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Prise]->changeSources( m_checkBox );

    m_listParameters[PathV] = HandleParameters::build_inputtext("Path",
                                                                QString(path.c_str()),
                                                                InputText::SaveFile );
    m_listParameters[Duree]->setActionOnChangeValue( [this](QVariant Value, HandleParameters * hp)
                                                    {
                                                         m_progress->setMaximum( Value.toInt() );
                                                         hp->acceptChanges(Value);
                                                    } );

    auto lambdaActif = [this](QVariant Value, HandleParameters * hp)
    {
            hp->acceptChanges(Value);
            if( m_listParameters[Prise]->toMap()["Actif"].toBool() )
            {
                    m_timer.start();
                    m_progress->setValue(0);
            }

    };
    m_listParameters[Prise]->setActionOnChangeValue( lambdaActif );
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

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
            saveFrame( src1 );
        m_progress->setValue( m_timer.elapsed()/1000 );
    }
    return src1;
}
/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE----------------------------------------------
---------------------------------------------------------------------------------------------------*/


void ToVideo::init(const ImageDataPtr src1)
{
    int FPS = m_listParameters[FrameRate]->toInt();
    std::string videoPath = m_listParameters[PathV]->toString().toStdString ();
    m_writer = cvCreateAVIWriter( videoPath.c_str(),
                                  CV_FOURCC('M','J','P','G'),
                                  FPS,
                                  cvGetSize(src1->getImage()),
                                  1 );
    m_progress->setMaximum( m_listParameters[Duree]->toInt() );
}


void ToVideo::onEnding()
{
    cvReleaseVideoWriter(& m_writer);
}


void ToVideo::saveFrame( ImageDataPtr src1)
{
    cvWriteFrame(m_writer,src1->getImage());
}
