#ifndef FOLDERREADER_H
#define FOLDERREADER_H

#include <QString>
#include <QDateTime>
#include "videoreader.h"
#include "parseexception.h"

/** @brief
  Class which will read a folder and handle all files.
  */
class FolderReader : public VideoReader
{
public:
    FolderReader();

    /**
      * @brief parse a file with his own name
      * @param QString fileName : the fileName
      * @return QDataTime*      : a pointer on a QDataTime which is used to know the time when the data has been take.
      */
    static QDateTime *parseFileName(QString fileName) throw (parseException);
};

#endif // FOLDERREADER_H
