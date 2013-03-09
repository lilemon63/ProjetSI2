#ifndef DIAL_H
#define DIAL_H

#include <QObject>

#include "sourceparameters.h"

class QDial;
class QFrame;
class QLabel;
class QLineEdit;

class Dial : public QObject, public SourceParameters
{
public:
    enum Helper  {None, PrintValue, EnterValue};
    Q_OBJECT;
public:
    Dial(const QString & label, int defaultAngle = 0, int min = 0, int max = 360, Helper = EnterValue);
    virtual ~Dial(){}

    virtual void addSuscriber(HandleParameters * target);
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);
private slots :
    void changeValue(void);
    void changeValue(int);
private :
    QDial * m_dial;
    QLineEdit * m_inputText;
    QFrame * m_frame;
    QLabel * m_label;
};

#endif // DIAL_H
