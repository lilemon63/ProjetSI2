
#include "spinbox.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>

SpinBox::SpinBox(const QString & label)
    : SourceParameters(label),
      m_spinbox(new QSpinBox() )
{
    QObject::connect(m_spinbox, SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
}


void SpinBox::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_spinbox);
}

void SpinBox::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_spinbox->hide();
}

void SpinBox::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_spinbox->value() );
}


void SpinBox::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
