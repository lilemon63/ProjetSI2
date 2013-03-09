#ifndef SPINBOX_H
#define SPINBOX_H

#include <QObject>

#include "sourceparameters.h"

class QSpinBox;

class SpinBox : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    SpinBox(const QString & label = QString(), int defaultvalue = 0, int min = 0, int max = 100 );
    virtual ~SpinBox(){}

    virtual void addSuscriber(HandleParameters * target);
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);
private slots :
    void changeValue(int);
private :
    QSpinBox * m_spinbox;
};

#endif // SPINBOX_H
