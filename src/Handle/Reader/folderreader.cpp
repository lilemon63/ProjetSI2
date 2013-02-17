#include "folderreader.h"
#include "../parseexception.h"
#include <QRegExp>
#include <QStringList>

FolderReader::FolderReader(const std::string & path)
    : m_path(path)
{
    QDir dir( path.c_str() );
    if( ! dir.isReadable() )
        throw Exception::buildException("Attention le dossier " + path + " n'existe pas ou vous n'avez pas les droits pour y accéder.", "FolderReader", "Folderreader", EPC);
    QFileInfoList liste = dir.entryInfoList(QDir::Files);

    for(auto info : liste)
    {
        m_listePath[parseFileName(info.fileName())] = info.fileName();
    }
    m_iterator = m_listePath.end();
}


QDateTime FolderReader::parseFileName(QString fileName){
    QRegExp reg;
    QDateTime time;

    QStringList dataList;
    reg.setPattern("._(\\d+)-(\\d+)-(\\d+)-(\\d+)h(\\d+)m(\\d+)s(\\d+).*"); //QDateTime seems don't be able to accept regex for his format (?)
    fileName.replace(reg,"\\0\n\\1\n\\2\n\\3\n\\4\n\\5\n\\6\n\\7");
    dataList = fileName.split('\n');

    if(dataList.size() != 8)
        throw ParseException::buildParseException("The file's name " + fileName.toStdString() + "is incorrect.", "FolderReader", "parseFileName",EP);

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

void FolderReader::grab()
{
    if( m_iterator == m_listePath.end() )
        m_iterator = m_listePath.begin();
    else
        ++m_iterator;
}


bool FolderReader::acceptSeek(void)
{
    return true;
}


IplImage * FolderReader::getImage(void)
{
    static IplImage * data = NULL;
    if( data )
    {
        cvReleaseImage(&data);
    }
    if( m_iterator != m_listePath.end() )
        data = cvLoadImage( (m_path + m_iterator->second.toStdString() ).c_str() );
    return data;
}
