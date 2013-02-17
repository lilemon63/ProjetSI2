#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QObject>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "sourceparameters.h"

class RadioButton : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    RadioButton(QString name, QStringList boxes);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~RadioButton(){}

private :
    QGroupBox m_group;
    QList<QRadioButton *> m_radiobuttons;
    QList<QHBoxLayout *> m_hboxs;
    QVBoxLayout m_vbox;
private slots :
    void changeValue(int);
};

#endif // RADIOBUTTON_H
