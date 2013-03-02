#include "tovideo.h"
#include "../Parameters/spinbox.h"
#include "../../exception.h"
#include <QDateTime>
#include <QObject>
#include "../Parameters/checkbox.h"

ToVideo::ToVideo(const std::string &path, const QString & affName,const std::string &name)
    :VirtualHandle(affName,name),
      m_path(path),
      max(0),
      m_progress( new ProgressBar("progression") )
{
    m_timer.setInterval(1000);
    m_timer.setSingleShot(false);
    m_listParameters.resize(Max);
    m_listParameters[FrameRate] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[FrameRate]->changeSources( new SpinBox("Framerate") );
    m_listParameters[Duree] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Duree]->changeSources( new SpinBox("Durée max") );
    m_listParameters[Duree]->setValue(0);

    m_listParameters[Progress] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Progress]->changeSources( m_progress );

    m_listParameters[Prise] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[Prise]->changeSources(new CheckBox("Video", QStringList({"Activé"})));
    //m_listParameters[Prise]->setActionOnChangeValue(fin()); comment utiliser ?
    prise=false;
}

void ToVideo::init(const ImageDataPtr src1)
{
    std::cout << "init" << std::endl;
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(incrementeTemps()));
    int FPS = m_listParameters[FrameRate]->toInt();
    writer=cvCreateAVIWriter(m_path.c_str(),CV_FOURCC('M','J','P','G'),FPS,cvGetSize(src1->getImage()),1);
    m_progress->setMaximum(m_listParameters[Duree]->toInt());
    m_timer.start();
    prise = true;
    max=0;
}

ImageDataPtr ToVideo::startHandle(const ImageDataPtr src1, const ImageDataPtr)
{
    if( ! src1)
        throw Exception::buildException("La source est vide", "ToVideo", "startHandle", EPC);
    std::cout << "Valeur m_listParameters[Prise]->toBool():" << m_listParameters[Prise]->toBool() << std::endl; //actualisation ? reste a false
    if(m_listParameters[Prise]->toBool() && max < m_listParameters[Duree]->toInt())
    {
        if(!prise)
        {
            init(src1);
        }
        else
        {
            std::cout << "write " << max << std::endl;
            cvWriteFrame(writer,src1->getImage());
        }
    }
    else
    {
        if(prise)
        {
            fin();
        }
    }
    return src1;
}

void ToVideo::incrementeTemps() {
    max++;
}

void ToVideo::fin() {
    if(prise) { //en vu pour le set setActionOnChangeValue
        std::cout << "FIN VIDEO" << std::endl;
        m_progress->setValue(max);
        cvReleaseVideoWriter(&writer);
        m_timer.stop();
        prise=false;
        m_listParameters[Prise]->setValue(false);
    }
}
