#include "slider.h"
#include "handleparameters.h"

Slider::Slider()
{
    m_slider.setOrientation(Qt::Horizontal);
    connect( &m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
}


void Slider::showParameters(QWidget * parent)
{
    m_slider.setParent(parent);
    m_slider.setLayout(parent->layout());
    m_slider.show();
}

void Slider::hideParameters(void)
{
    m_slider.hide();
}

void Slider::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_slider.value() );
}


void Slider::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
