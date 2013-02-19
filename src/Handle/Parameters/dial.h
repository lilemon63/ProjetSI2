#ifndef DIAL_H
#define DIAL_H

#include <QObject>
#include <QDial>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>

#include "sourceparameters.h"

class Dial : public QObject, public SourceParameters
{
public:
    enum Helper  {None, PrintValue, EnterValue};
    Q_OBJECT;
public:
    Dial(const QString & label, int defaultAngle = 0, Helper = EnterValue);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~Dial(){}

private :
    QDial * m_dial;
    QFrame * m_frame;
    QLabel * m_label;
    QLineEdit * m_inputText;
private slots :
    void changeValue(int);
    void changeValue(void);
};

#endif // DIAL_H
