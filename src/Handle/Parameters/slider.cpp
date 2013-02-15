#include "slider.h"
#include "handleparameters.h"
#include <QLayout>
#include <iostream>

Slider::Slider(int defaultValue, int min, int max)
    : m_slider(new QSlider() )
{
    m_slider->setValue(defaultValue);
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setMinimum(min);
    m_slider->setMaximum(max);
    connect( m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
}


void Slider::showParameters(QWidget * parent)
{
    m_slider->setParent(parent);
    if(parent)
        parent->layout()->addWidget(m_slider);
    m_slider->show();
}

void Slider::hideParameters(void)
{
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
