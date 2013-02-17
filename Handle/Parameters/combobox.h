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
    ComboBox(QString name, QStringList choices);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~ComboBox(){}

private :
    QComboBox m_combobox;
private slots :
    void changeValue(int);
};



#endif // COMBOBOX_H

