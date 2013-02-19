#ifndef SUBMDIWINDOWSRESULTS_H
#define SUBMDIWINDOWSRESULTS_H

#include <QPlainTextEdit>
#include "submdiwindows.h"
#include "../Handle/imagedata.h"

class SubMdiWindowsResults : public SubMdiWindows
{
    Q_OBJECT
public:
    SubMdiWindowsResults(const QString &titre = QString(), Mdi *area = nullptr, QWidget *parent = nullptr);
    void addText(const QString &);
    void changeText(const QString &);
    void extractInformationFromImage(ImageDataPtr);
    void saveIntoFile(const QString &);
    virtual void attach(void);
    virtual void detach(void);
public slots :
    void saveIntoFile(void);
signals :
    void resultFile(QString, bool);
private :
    QPlainTextEdit * m_textEdit;
};

#endif // SUBMDIWINDOWSRESULTS_H
