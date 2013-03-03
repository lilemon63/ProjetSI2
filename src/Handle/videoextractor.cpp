#include "videoextractor.h"

#include <QElapsedTimer>

#include "../exception.h"
#include "Handle.h"

VideoExtractor::VideoExtractor(bool dual, VideoReader * source1, VideoReader * source2 )
    : m_stopped(true), m_dual(dual), m_videoStream{ source1 , source2 },
    m_currentParent(nullptr),
    m_autoPlay(false),
    m_isHandleActived(true)
{
    auto lambda = [this]( QVariant Value, HandleParameters * hp )
    {
            hideParameters();
            hp->acceptChanges(Value);
            if( m_currentParent )
                showParameters(m_currentParent);
    };
    m_paramHandle.setActionOnChangeValue( lambda );
}

void VideoExtractor::showParameters(QWidget *parent)
{
        m_currentParent = parent;
        VirtualHandle::showParameters(parent, m_paramHandle.toString().toStdString());
}

void VideoExtractor::hideParameters(void)
{
    if( m_paramHandle.toString() != "" )
        VirtualHandle::hideParameters(m_paramHandle.toString().toStdString());
}

void VideoExtractor::start(qint64 timeMax, qint64 nbMaxImage)
{
    if( m_stopped != true )
        return;
    m_timeMax = timeMax;
    m_nbMaxImage = nbMaxImage;
    m_stopped = false;
    m_nbImageHandled = 0;
    QThread::start();
}


void VideoExtractor::run(void)
{
    QElapsedTimer timer;
    //qint64 endOfCapture;
    //qint64 endOfHandle;
    qint64 begin;
    timer.start();
    while( ! m_stopped )
    {
        m_mutex.lock();
        while( ! m_autoPlay )
            m_cond.wait(&m_mutex);

        begin = timer.nsecsElapsed();

        m_videoStream[0]->grab(); // a for for that ... I'm too lazy
        m_videoStream[1]->grab();

        if( m_timeMax && m_timeMax > begin)
            m_autoPlay = false;

        processFrame();


        if( m_nbMaxImage && m_nbImageHandled == m_nbMaxImage )
            m_autoPlay = false;

        m_mutex.unlock();

        qint64 waitTime = ( m_paramPeriod.toInt() - timer.nsecsElapsed() + begin )/1000;
        if(waitTime < 0)
        {
         /*   std::cerr << "Warning : la boucle a du retard : " <<  waitTime
                      << "\nDuree de la boucle : " << m_paramPeriod.toInt()
                      << "\nDuree reelle : " << timer.nsecsElapsed() << std::endl; */
        }
        else
            QThread::usleep( waitTime );
    }

    emit finished();
    deleteLater();
}

void VideoExtractor::useSource(VideoReader * source, int channel)
{
    delete m_videoStream[channel];
    m_videoStream[channel] = source;
}

VideoExtractor::~VideoExtractor()
{
    delete m_videoStream[0];
    delete m_videoStream[1];
}

void VideoExtractor::changeHandleParameters( SourceParameters * source, QWidget * area)
{
    m_paramHandle.changeSources(source);
    m_paramHandle.showParameters( area );
}

void VideoExtractor::changePeriodeParameters( SourceParameters *source, QWidget * area)
{
    m_paramPeriod.changeSources(source);
    m_paramPeriod.showParameters( area );
}


void VideoExtractor::processFrame(void)
{
    IplImage * src1, * src2;

    src1 = m_videoStream[0]->getImage();
    src2 = m_videoStream[1]->getImage();

    ImageDataPtr source1 = nullptr, source2 = nullptr;

    if(src1)
        source1 = ImageDataPtr(new ImageData(*src1));
    if(src2)
        source2 = ImageDataPtr(new ImageData(*src2));
    else if(! src1)
        throw Exception::buildException("Aucune source valable", "VideoExtractor",
                                        "run", EPC);

    ImageDataPtr result;
    //endOfCapture = timer.nsecsElapsed();
    if( m_isHandleActived )
        result = VirtualHandle::executeHandle(m_paramHandle.toString().toStdString(), source1, source2);
    else
        result = source1;
    //endOfHandle = timer.nsecsElapsed();
    if( ! result)
    {
        throw Exception::buildException("Votre traitement ne retourne pas de résultat!", "VideoExtractor",
                                        "run", EPC);
    }

    m_nbImageHandled++;
    emit imageHandled(result, source1, source2);
}


void VideoExtractor::next(void)
{
    m_mutex.lock();

    m_autoPlay = false;
    m_videoStream[0]->grab();
    m_videoStream[1]->grab();

    processFrame();

    m_mutex.unlock();
}

void VideoExtractor::previous(void)
{
    m_mutex.lock();

    m_autoPlay = false;
    m_videoStream[0]->r_grab();
    m_videoStream[1]->r_grab();

    processFrame();

    m_mutex.unlock();
}

void VideoExtractor::slid(void)
{
    m_mutex.lock();

    m_autoPlay = false;

    //TODO

    processFrame();

    m_mutex.unlock();
}

void VideoExtractor::play(void)
{
    m_autoPlay = true;
    m_cond.wakeAll();
}

void VideoExtractor::pause(void)
{
    m_autoPlay = false;
}

void VideoExtractor::activeHandle(bool newValue)
{
    m_isHandleActived = newValue;
}
