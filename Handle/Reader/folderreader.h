#ifndef FOLDERREADER_H
#define FOLDERREADER_H

#include "../videoreader.h"
#include <QDateTime>


/** @brief Read a folder as an video stream */
class FolderReader : public VideoReader
{
public:
    FolderReader();
    /** @brief Commentary */
    static QDateTime *parseFileName(QString fileName);
};

#endif // FOLDERREADER_H
