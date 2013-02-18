#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include <QObject>
#include <QLineEdit>
#include <QFrame>
#include "sourceparameters.h"

class InputText : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    enum Helper{None, Directory, SaveFile, OpenFile};

    explicit InputText(const QString & label = QString(), const QString &defaultValue = QString(), Helper= None);
    virtual void showParameters(QWidget * parent);
    virtual void hideParameters(void);
    virtual void addSuscriber(HandleParameters * target);
    virtual ~InputText(){}
signals:
    
public slots:
private slots :
    void valueChanged(void);
    void openPopUp(void);
private :
    QLineEdit * m_inputText;
    QFrame * m_frame;
    Helper m_helper;
    
};

#endif // INPUTTEXT_H
