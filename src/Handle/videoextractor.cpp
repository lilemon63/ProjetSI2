#include <QElapsedTimer>

#include "../exception.h"
#include "videoextractor.h"
#include "Handle.h"

VideoExtractor::VideoExtractor(bool dual, VideoReader * source1, VideoReader * source2 )
    : m_autoPlay(false),
      m_currentParent(nullptr),
      m_dual(dual),
      m_isHandleActived(true),
      m_stopped(true),
      m_videoStream{ source1 , source2 }
{
    m_paramHandle.setActionOnChangeValue( [this]( QVariant Value, HandleParameters * hp )
                                            {
                                                    hideParameters();
                                                    hp->acceptChanges(Value);
                                                    if( m_currentParent )
                                                        showParameters(m_currentParent);
                                            } );
}


VideoExtractor::~VideoExtractor()
{
    delete m_videoStream[0];
    delete m_videoStream[1];
}
/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

bool VideoExtractor::acceptSeek(void)
{
    if( m_videoStream[0]->acceptSeek() )
        return true;
    if( m_dual && m_videoStream[1]->acceptSeek() )
        return true;
    return false;
}


void VideoExtractor::changeHandleParameters( SourceParameters * source, QWidget * area)
{
    m_paramHandle.changeSources(source);
    m_paramHandle.showParameters( area );
}


void VideoExtractor::changePeriodeParameters( SourceParameters *source, QWidget *area)
{
    m_paramPeriod.changeSources(source);
    m_paramHandle.showParameters( area );
}


void VideoExtractor::hideParameters(void)
{
    if( m_paramHandle.toString() != "" )
        VirtualHandle::hideParameters(m_paramHandle.toString().toStdString());
}


int VideoExtractor::numberOfFrame(void)
{
    int nFrame1 = m_videoStream[0]->nbFrame();
    int nFrame2 = m_dual ? m_videoStream[1]->nbFrame() : 0;
    return nFrame1 > nFrame2 ? nFrame1 : nFrame2;
}


void VideoExtractor::showParameters(QWidget *parent)
{
        m_currentParent = parent;
        VirtualHandle::showParameters( parent, m_paramHandle.toString().toStdString() );
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


void VideoExtractor::useSource(VideoReader * source, int channel)
{
    delete m_videoStream[channel];
    m_videoStream[channel] = source;
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC SLOTS-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void VideoExtractor::activeHandle(bool newValue)
{
    m_isHandleActived = newValue;
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


void VideoExtractor::pause(void)
{
    m_autoPlay = false;
}


void VideoExtractor::play(void)
{
    m_autoPlay = true;
    m_cond.wakeAll();
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


void VideoExtractor::slid(int value)
{
    m_mutex.lock();

    m_autoPlay = false;

    m_videoStream[0]->slid(value);
    m_videoStream[1]->slid(value);

    processFrame();

    m_mutex.unlock();
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PROTECTED--------------------------------------------
---------------------------------------------------------------------------------------------------*/


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


void VideoExtractor::processFrame(void)
{
    IplImage * src1, * src2;

    src1 = m_videoStream[0]->getImage();
    if(m_dual)
        src2 = m_videoStream[1]->getImage();

    ImageDataPtr source1 = nullptr, source2 = nullptr;
    ImageDataPtr copySrc1 = nullptr, copySrc2 = nullptr;

    if(src1)
    {
        source1 = ImageDataPtr(new ImageData(*src1) );
        copySrc1 = ImageDataPtr(new ImageData(*source1) );
    }
    if( m_dual && src2 )
    {
        source2 = ImageDataPtr(new ImageData(*src2));
        copySrc2 = ImageDataPtr(new ImageData(*source2) );
    }
    else if(! src1)
        throw Exception::buildException("Aucune source valable", "VideoExtractor",
                                        "run", EPC);

    ImageDataPtr result;
    //endOfCapture = timer.nsecsElapsed();
    if( m_isHandleActived )
        result = VirtualHandle::executeHandle(m_paramHandle.toString().toStdString(), copySrc1, copySrc2);
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
