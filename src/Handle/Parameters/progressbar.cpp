#include "progressbar.h"
#include "handleparameters.h"
#include <QLayout>
#include <iostream>

ProgressBar::ProgressBar(const QString &label)
    : SourceParameters(label),
      m_progressbar(new QProgressBar() )
{
    m_progressbar->setOrientation(Qt::Horizontal);
    m_progressbar->setMinimum(0);
    connect( m_progressbar, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    m_progressbar->setValue(0);
}

void ProgressBar::valueChanged(int value) {
    m_progressbar->setValue(value);
}

void ProgressBar::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_progressbar);
}

void ProgressBar::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_progressbar->hide();
}

void ProgressBar::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_progressbar->value() );
}

void ProgressBar::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
    {
        hp->setValue( (int)value);
    }
 }

void ProgressBar::setValue(int percent)
{
    m_progressbar->setValue(percent);
}

void ProgressBar::setMaximum(int max)
{
    m_progressbar->setMaximum(max);
}

ProgressBar::~ProgressBar()
{

}
