#ifndef SUBMDIWINDOWSRESULTS_H
#define SUBMDIWINDOWSRESULTS_H

#include "submdiwindows.h"
#include "../Handle/imagedata.h"

class QPlainTextEdit;


/** @brief SubMdiWindows used to show ImageData's extracted information. */
class SubMdiWindowsResults : public SubMdiWindows
{
    Q_OBJECT
public:
    /** @brief build a SubMdiWindowsResults.
    **  @param const QString &titre = QString() : window's title.
    **  @param Mdi *area = nullptr : Mdi where the SubMdiWindows will be shown.
    **  @param QWidget *parent = nullptr : SubMdiWindows' parent.
    */
    SubMdiWindowsResults(const QString &titre = QString(), Mdi *area = nullptr, QWidget *parent = nullptr);

    virtual ~SubMdiWindowsResults(){}


    /** @brief Add the text to the SubMdiWindowsResults.
    **  @param const QString & : text to add.
    */
    void addText(const QString &);


    /** @brief Attach the SubMdiWindowsResults to its Mdi. */
    virtual void attach(void);


    /** @brief Change all the SubMdiWindowsResults's text.
    **  @param const QString & : new text.
    */
    void changeText(const QString &);


    /** @brief Detach the SubMdiWindowsResults from the Mdi.
    **
    **  We will have a free windows which is useful when the user have several screens.
    */
    virtual void detach(void);


    /** @brief Extract information from an ImageData and add it to the SubMdiWindowsResults's text.
    **  @param ImageDataPtr : ImageData which contains the information we want.
    */
    virtual void extractInformationFromImage(ImageDataPtr);


    /** @brief Save all SubMdiWindowsResults's text into a file.
    **  @param const QString & : file path.
    */
    virtual void saveIntoFile(const QString &);
public slots :

    /** @brief Save all SubMdiWindowsResults's text into a file.
    **
    **   Call saveIntoFile(const QString &);
    */
    void saveIntoFile(void);
signals :

    /** @brief Emitted when the SubMdiWindowsResults's text have been saved into a file.
    **  @param QString : successfull, warning or error message.
    **  @param bool : if the saved success or not.
    */
    void resultFile(QString, bool);
private :

    /** @brief Shown text. */
    QPlainTextEdit * m_textEdit;
};

#endif // SUBMDIWINDOWSRESULTS_H
