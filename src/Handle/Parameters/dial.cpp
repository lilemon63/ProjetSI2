#include "dial.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>

Dial::Dial(QString label, int angle)
    : SourceParameters(label),
      m_dial( new QDial() )
{
    m_dial->setOrientation(Qt::Horizontal);
    QObject::connect(m_dial, SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
    m_dial->setValue(angle);
}


void Dial::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_dial);
}

void Dial::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_dial->hide();
}

void Dial::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_dial->value() );
}


void Dial::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
