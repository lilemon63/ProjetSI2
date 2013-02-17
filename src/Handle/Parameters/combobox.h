#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QObject>
#include <QComboBox>

#include "sourceparameters.h"

class ComboBox : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    ComboBox(QString label, QStringList choices, QString defaultValue = QString());

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~ComboBox(){}

private :
    QComboBox * m_combobox;
private slots :
    void changeValue(QString newValue);
};



#endif // COMBOBOX_H

