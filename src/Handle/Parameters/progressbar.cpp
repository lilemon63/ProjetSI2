#include "progressbar.h"
#include "handleparameters.h"

#include <QProgressBar>

ProgressBar::ProgressBar(const QString &label)
    : SourceParameters(label),
      m_progressbar(new QProgressBar() )
{
    m_progressbar->setOrientation(Qt::Horizontal);
    m_progressbar->setMinimum(0);

    connect( m_progressbar, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    connect( this, SIGNAL(m_changeValue(int)), m_progressbar, SLOT(setValue(int)));

    m_progressbar->setValue(0);
}


ProgressBar::~ProgressBar()
{

}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void ProgressBar::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_progressbar->value() );
}


void ProgressBar::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_progressbar->hide();
}


void ProgressBar::setMaximum(int max)
{
    m_progressbar->setMaximum(max);
}


void ProgressBar::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_progressbar);
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void ProgressBar::addValue(int number)
{
    emit m_changeValue(number + m_progressbar->value() );
}


void ProgressBar::setValue(int number)
{
    emit m_changeValue(number);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/


void ProgressBar::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
    {
        hp->setValue( (int)value);
    }
}
