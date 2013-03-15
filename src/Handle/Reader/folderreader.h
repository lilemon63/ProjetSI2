#ifndef FOLDERREADER_H
#define FOLDERREADER_H

#include <QDateTime>
#include "../videoreader.h"


/** @brief Create a video stream from image in a folder */
class FolderReader final : public VideoReader
{
public:

    /** @brief Create a reader from all image which is in a same folder.
    **  @warning All image in the folder must be correctly named else a ParseException is thown.
    **  @param const std::string & path : folder's path.
    */
    FolderReader(const std::string & path);


    /** @brief Return true if the stream can be seeked ie reading cursor can be moved.
    **  @brief bool : true if the reading cursor can be moved else false.
    */
    bool acceptSeek(void);


    /** @brief Get the last image grabbed.
    **  @return IplImage * : last image grabbed.
    */
    IplImage * getImage(void);


    /** @brief grab the current image from the video stream.
    **
    **  There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy. */
    void grab(void);


    /** @brief Get the maximum frame we can get from this stream, 0 for infinity.
    **  @return int : maximum frame we can get from this stream, 0 for infinity.
    */
    int nbFrame(void);


    /** @brief Parse a file with its name.
    **
    **  The file's name must be like that :
    **  *_[year]-[month]-[day]-[hours]h[minute]m[sec]s[msec].*
    **  The character '*' means every chain of car. the first '_' is optionnel if no previous text is entered.
    **  The first character of the file's name mustn't be a number if it isn't the date.
    **  @param const QString & fileName : the fileName
    **  @return QDataTime : Time and Data when the image has been take.
    **  @throw ParseException : if an error occured when parsing the filename.
    */
    static QDateTime parseFileName(const QString & fileName);


    /** @brief Grab the previous image from the video stream.
    **
    **  There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy.
    **
    **  If the stream doesn't accepted seek, do nothing.
    */
    void r_grab(void);


    /** @brief Grab the ième image from the video stream.
    **
    **  There is no copy so it's faster so we can get several image from several video stream at the same time
        with more accuracy.
    **
    **  If the stream doesn't accepted seek, do nothing.
    **  @param int : image number to gran
    */
    void slid(int);


    /** @brief Specified the camera to use as source (if there is several cameras).
    **
    **  VideoReader's child, this method can be unused, but you can use it to create some "virtual cameras".
    **  @note Do nothing in this case.
    **  @param int = 0 : camera to use as source.
    */
    virtual void useCamera(int = 0){}

private :
    /** @brief Type to store the list path according to their QDateTime. */
    typedef std::map<QDateTime, QString> ListPath;

    /** @brief Iterator on the current image. */
    ListPath::iterator m_iterator;

    /** @brief All image path and their associated date time. */
    ListPath m_listePath;

    /** @brief Folder's path. */
    std::string m_path;
};

#endif // FOLDERREADER_H
