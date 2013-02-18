#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QObject>
#include <QGroupBox>
#include <QRadioButton>
#include <QFormLayout>

#include "sourceparameters.h"

class RadioButton : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    RadioButton(const QString & label, QStringList boxes);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~RadioButton(){}

private :
    QList<QRadioButton *> m_radiobuttons;
    QButtonGroup * m_group;
    QFrame * m_frame;
private slots :
    void changeValue();
};

#endif // RADIOBUTTON_H
