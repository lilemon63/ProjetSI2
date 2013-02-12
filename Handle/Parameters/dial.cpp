#include "dial.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>

Dial::Dial(QString name)
    :SourceParameters(name)
{
    m_dial.setOrientation(Qt::Horizontal);
    QObject::connect(&m_dial, SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
}


void Dial::showParameters(QWidget * parent)
{
    m_dial.setParent(parent);
    setParentLayout(parent, &m_name);
    setParentLayout(parent, &m_dial);
    m_dial.show();
}

void Dial::hideParameters(void)
{
    m_dial.hide();
}

void Dial::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_dial.value() );
}


void Dial::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
