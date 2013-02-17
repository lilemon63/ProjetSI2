
#include "spinbox.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>

SpinBox::SpinBox(QString name)
    :SourceParameters(name)
{
    QObject::connect(&m_spinbox, SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
}


void SpinBox::showParameters(QWidget * parent)
{
    m_spinbox.setParent(parent);
    setParentLayout(parent, &m_name);
    setParentLayout(parent, &m_spinbox);
    m_spinbox.show();
}

void SpinBox::hideParameters(void)
{
    m_spinbox.hide();
}

void SpinBox::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_spinbox.value() );
}


void SpinBox::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
