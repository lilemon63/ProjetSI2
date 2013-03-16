#include <QDir>
#include <QRegExp>
#include <QStringList>

#include "folderreader.h"
#include "../parseexception.h"


FolderReader::FolderReader(const std::string & path)
    : m_path(path)
{
    QDir dir( path.c_str() );
    if( ! dir.isReadable() )
        throw Exception::buildException("Attention le dossier " + path
                                        + " ("+ dir.absolutePath().toStdString()
                                        +") n'existe pas ou vous n'avez pas les droits pour y accéder.",
                                        "FolderReader", "Folderreader", EPC);
    QFileInfoList liste = dir.entryInfoList(QDir::Files);

    for(auto info : liste)
    {
        m_listePath[ parseFileName( info.fileName() ) ] = info.fileName();
    }
    m_iterator = m_listePath.end();
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/


bool FolderReader::acceptSeek(void)
{
    return true;
}

IplImage * FolderReader::getImage(void)
{
    static IplImage * data = nullptr;
    if( data )
        cvReleaseImage(&data);

    if( m_iterator != m_listePath.end() )
        data = cvLoadImage( (m_path + "/" + m_iterator->second.toStdString() ).c_str() );
    return data;
}


void FolderReader::grab()
{
    if( m_iterator == m_listePath.end() )
        m_iterator = m_listePath.begin();
    else
        ++m_iterator;
}


int FolderReader::nbFrame(void)
{
    return m_listePath.size();
}


QDateTime FolderReader::parseFileName(const QString & file)
{
    QRegExp reg;
    reg.setPattern("._(\\d+)-(\\d+)-(\\d+)-(\\d+)h(\\d+)m(\\d+)s(\\d+).*");
    //QDateTime seems don't be able to accept regex for his format (?)

    QString fileName = file;
    fileName.replace(reg,"\\0\n\\1\n\\2\n\\3\n\\4\n\\5\n\\6\n\\7");
    QStringList dataList = fileName.split('\n');

    if(dataList.size() != 8)
        throw ParseException::buildParseException("The file's name " + fileName.toStdString() + " is incorrect.",
                                                  "FolderReader", "parseFileName",EP);
    QDateTime time;
    time.setDate( QDate(dataList[1].toInt(),
                        dataList[2].toInt(),
                        dataList[3].toInt()
                      ) );

    time.setTime( QTime(dataList[4].toInt(),
                        dataList[5].toInt(),
                        dataList[6].toInt(),
                        dataList[7].toInt()
                        ) );
    return time;
}


void FolderReader::r_grab()
{
    if( m_iterator == m_listePath.end() )
        m_iterator = m_listePath.begin();
    else if(m_iterator != m_listePath.begin() )
        --m_iterator;
}


void FolderReader::slid(int value)
{
    auto it = m_listePath.begin();
    for( int i = 0; value != i; ++i)
        it++;
    m_iterator = it;
}
