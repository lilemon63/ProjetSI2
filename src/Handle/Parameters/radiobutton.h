#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QObject>

#include "sourceparameters.h"

class QFrame;
class QRadioButton;
class QButtonGroup;

class RadioButton : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    RadioButton(const QString & label, const QStringList & boxes, const QString & defaultValue = "");
    virtual ~RadioButton(){}


    virtual void addSuscriber(HandleParameters * target);
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);
private slots :
    void changeValue();
private :
    QFrame * m_frame;
    QButtonGroup * m_group;
    QList<QRadioButton *> m_radiobuttons;
};

#endif // RADIOBUTTON_H
