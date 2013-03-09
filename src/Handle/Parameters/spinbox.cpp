#include <QLayout>
#include <QSpinBox>

#include "spinbox.h"
#include "handleparameters.h"

SpinBox::SpinBox(const QString & label, int defaultValue, int min, int max)
    : SourceParameters(label),
      m_spinbox(new QSpinBox() )
{
    m_spinbox->setMaximum(max);
    m_spinbox->setMinimum(min);
    QObject::connect(m_spinbox, SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
    m_spinbox->setValue(defaultValue);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void SpinBox::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_spinbox->value() );
}


void SpinBox::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_spinbox->hide();
}


void SpinBox::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_spinbox);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void SpinBox::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
