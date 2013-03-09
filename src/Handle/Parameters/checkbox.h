#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QMap>
#include <QString>
#include <QObject>
#include <QVariant>

#include "sourceparameters.h"

class QCheckBox;

class CheckBox : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    CheckBox(const QString & label, const QStringList & boxes,
             const QStringList & defaultChecked = QStringList() );
    virtual ~CheckBox(){}

    virtual void addSuscriber(HandleParameters * target);

    virtual void changeValue(const QString & txt, bool  value);

    virtual void hideParameters(void);

    virtual void showParameters(QWidget * parent);
private slots :
    void changeValue(bool);
private :
    QList<QCheckBox *> m_checkboxs;
    QFrame * m_frame;
    QMap<QString, QVariant> m_values;
};

#endif // CHECKBOX_H
