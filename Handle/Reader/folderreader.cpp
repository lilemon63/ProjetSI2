#include "folderreader.h"
#include <QRegExp>
#include <QStringList>

FolderReader::FolderReader(const std::string & path)
{
    QDir dir( path.c_str() );
    if( ! dir.isReadable() )
        throw Exception::buildException("Attention le dossier " + path + " n'existe pas ou vous n'avez pas les droits pour y accéder.", "FolderReader", "Folderreader", EPC);
    QFileInfoList liste = dir.entryInfoList(QDir::Files);

    std::for_each(liste.begin(), liste.end(), [this](QFileInfo & info){
        m_listePath[parseFileName(info.fileName())] = info.fileName();
    });
    m_iterator = m_listePath.begin();
}


QDateTime FolderReader::parseFileName(QString fileName){
    QRegExp reg;
    QDateTime time;
    QStringList dataList;
    reg.setPattern("._(\\d+)-(\\d+)-(\\d+)-(\\d+)h(\\d+)m(\\d+)s(\\d+).*");
    fileName.replace(reg,"\\0\n\\1\n\\2\n\\3\n\\4\n\\5\n\\6\n\\7");
    dataList = fileName.split('\n');

    if(dataList.size() != 8)
        throw ParseException::buildParseException("The file's name " + fileName.toStdString() + "is incorrect.", "FolderReader", "parseFileName",EP);

    time.addYears(dataList[1].toInt());
    time.addMonths(dataList[2].toInt());
    time.addDays(dataList[3].toInt());

    time.addSecs(dataList[4].toInt() * 3600);
    time.addSecs(dataList[5].toInt() * 60);
    time.addSecs(dataList[6].toInt());

    time.addMSecs(dataList[7].toInt());

    return time;
}

void FolderReader::grab()
{
    ++m_iterator;
}


bool FolderReader::acceptSeek(void)
{
    return true;
}
