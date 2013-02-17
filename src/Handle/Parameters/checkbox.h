#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QObject>
#include <QCheckBox>

#include "sourceparameters.h"

class CheckBox : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    CheckBox(QString label, QStringList boxes);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~CheckBox(){}

private :
    QList<QCheckBox *> m_checkboxs;
    QFrame * m_frame;
private slots :
    void changeValue(int);
};

#endif // CHECKBOX_H
