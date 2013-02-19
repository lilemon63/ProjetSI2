#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QObject>
#include <QCheckBox>
#include <QMap>
#include <QString>
#include <QVariant>

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

    virtual void changeValue(const QString & txt, bool  value);

private :
    QList<QCheckBox *> m_checkboxs;
    QFrame * m_frame;
    QMap<QString, QVariant> m_values;
private slots :
    void changeValue(bool);
};

#endif // CHECKBOX_H
