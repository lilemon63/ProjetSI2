#ifndef SUBMDIWINDOWSRESULTS_H
#define SUBMDIWINDOWSRESULTS_H

#include "submdiwindows.h"
#include "../Handle/imagedata.h"

class QPlainTextEdit;

class SubMdiWindowsResults : public SubMdiWindows
{
    Q_OBJECT
public:
    SubMdiWindowsResults(const QString &titre = QString(), Mdi *area = nullptr, QWidget *parent = nullptr);
    virtual ~SubMdiWindowsResults(){}

    void addText(const QString &);
    virtual void attach(void);
    void changeText(const QString &);
    virtual void detach(void);
    void extractInformationFromImage(ImageDataPtr);
    void saveIntoFile(const QString &);
public slots :
    void saveIntoFile(void);
signals :
    void resultFile(QString, bool);
private :
    QPlainTextEdit * m_textEdit;
};

#endif // SUBMDIWINDOWSRESULTS_H
