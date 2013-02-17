#ifndef SPINBOX_H
#define SPINBOX_H

#include <QObject>
#include <QSpinBox>

#include "sourceparameters.h"

class SpinBox : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    SpinBox(void);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~SpinBox(){}

private :
    QSpinBox m_spinbox;
private slots :
    void changeValue(int);
};

#endif // SPINBOX_H
