#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include <QObject>
#include <QLineEdit>
#include "sourceparameters.h"

class InputText : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    explicit InputText(const QString & label = QString(), const QString &defaultValue = QString());
    virtual void showParameters(QWidget * parent);
    virtual void hideParameters(void);
    virtual void addSuscriber(HandleParameters * target);
    virtual ~InputText(){}
signals:
    
public slots:
private slots :
    void valueChanged(void);//QString value);
private :
    QLineEdit * m_inputText;
    
};

#endif // INPUTTEXT_H
