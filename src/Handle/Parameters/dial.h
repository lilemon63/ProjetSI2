#ifndef DIAL_H
#define DIAL_H

#include <QObject>
#include <QDial>

#include "sourceparameters.h"

class Dial : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    Dial(QString label, int defaultAngle = 0);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~Dial(){}

private :
    QDial * m_dial;
private slots :
    void changeValue(int);
};

#endif // DIAL_H
