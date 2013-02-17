#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QObject>
#include <QGroupBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "sourceparameters.h"

class CheckBox : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    CheckBox(QString label, QString name, QStringList boxes);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~CheckBox(){}

private :
    QGroupBox m_group;
    QList<QCheckBox *> m_checkboxs;
    QList<QHBoxLayout *> m_hboxs;
    QVBoxLayout m_vbox;
private slots :
    void changeValue(int);
};

#endif // CHECKBOX_H
