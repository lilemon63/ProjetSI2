#ifndef FOLDERREADER_H
#define FOLDERREADER_H

#include "../videoreader.h"
#include "../parseexception.h"
#include <QDateTime>


/** @brief Read a folder as an video stream */
class FolderReader : public VideoReader
{
public:
    FolderReader();

    /**
     * @brief parse a file with his own name : The file's name must be like that :<br/>
     *        *_[year]-[month]-[day]-[hours]h[minute]m[sec]s[msec].* <br/>
     *        The character '*' means every chain of car. the first '_' is optionnel if no previous text is entered.<br/>
     *        The first character of the file's name mustn't be a number if it isn't the date.
     * @param QString fileName : the fileName
     * @return QDataTime*      : a pointer on a QDataTime which is used to know the time when the data has been take.
     * @throw ParseException : if an error occured.
     */
    static QDateTime parseFileName(QString fileName);
};

#endif // FOLDERREADER_H
