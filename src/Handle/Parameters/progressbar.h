#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QObject>

#include "sourceparameters.h"

class QProgressBar;

class ProgressBar : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    ProgressBar(const QString & label = QString());
    virtual ~ProgressBar();

    virtual void addSuscriber(HandleParameters * target);

    virtual void hideParameters(void);

    virtual void setMaximum(int max);

    virtual void showParameters(QWidget * parent);

public slots:
    virtual void setValue(int number);
    virtual void addValue(int number);
signals:
    void m_changeValue(int); //do not use it
private slots :
    void changeValue(int);
private :
    QProgressBar * m_progressbar;
};

#endif // PROGRESSBAR_H
