#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QObject>

#include "sourceparameters.h"

class QComboBox;

class ComboBox : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    ComboBox( const QString & label, const QStringList & choices, const QString & defaultValue = QString() );
    virtual ~ComboBox(){}

    virtual void addSuscriber(HandleParameters * target);
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);

private slots :
    void changeValue(QString newValue);
private :
    QComboBox * m_combobox;

};



#endif // COMBOBOX_H

