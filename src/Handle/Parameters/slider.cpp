#include "slider.h"
#include "handleparameters.h"
#include <QLayout>
#include <iostream>

Slider::Slider(QString label, int defaultValue, int min, int max)
    : SourceParameters(label),
      m_slider(new QSlider() )
{
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setMinimum(min);
    m_slider->setMaximum(max);
    connect( m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    m_slider->setValue(defaultValue);
}


void Slider::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_slider);
}

void Slider::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_slider->hide();
}

void Slider::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_slider->value() );
}

void Slider::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
    {
        hp->setValue( (int)value);
    }
 }

Slider::~Slider()
{

}
