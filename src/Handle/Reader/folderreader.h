#ifndef FOLDERREADER_H
#define FOLDERREADER_H

#include "../videoreader.h"
#include <QDateTime>
#include <QDir>


/** @brief Read a folder as an video stream */
class FolderReader final : public VideoReader
{
public:

    /** @brief Create a reader from all image which is in a same folder.
        @param const std::string & path : folder's path */
    FolderReader(const std::string & path);

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

    /** @brief grab the current image from the video stream.<br/>
        There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy. */
    void grab();

    void remplissage(const std::string nom, QDateTime date, QString s);

    /** @brief Return true if the reading cursor can be moved
        @brief bool : true if the reading cursor can be moved else false */
    bool acceptSeek(void);


    // TODO : IplImage * getImage(void); un petit oublie ? ^^

private :
    typedef std::map<QDateTime, QString> ListPath;
    /** @brief iterator on the current image */
    ListPath::iterator m_iterator;

    /** @brief All image path and their associated date time */
    ListPath m_listePath;
};

#endif // FOLDERREADER_H
