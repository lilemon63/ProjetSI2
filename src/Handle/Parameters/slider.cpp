#include "slider.h"
#include "handleparameters.h"
#include <QString>
#include <QSlider>

Slider::Slider(const QString &label, int defaultValue, int min, int max, Helper helper)
    : SourceParameters(label),
      m_frame( new QFrame() ),
      m_inputText(nullptr),
      m_label(nullptr),
      m_slider(new QSlider() )
{
    m_frame->setLayout( new QHBoxLayout);

    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setMinimum(min);
    m_slider->setMaximum(max);

    m_frame->layout()->addWidget(m_slider);
    if( helper == PrintValue )
    {
        m_label = new QLabel();
        m_frame->layout()->addWidget( m_label );
    }
    else if( helper == EnterValue)
    {
        m_inputText = new QLineEdit();
        m_frame->layout()->addWidget( m_inputText );
        connect(m_inputText, SIGNAL(editingFinished()), this, SLOT(changeValue()));
    }
    connect( m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    m_slider->setValue(defaultValue);
}


Slider::~Slider()
{

}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void Slider::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_slider->value() );
}


void Slider::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_frame->hide();
}


void Slider::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void Slider::changeValue(void)
{
    m_slider->setValue(m_inputText->text().toInt());
}


void Slider::changeValue(int  value)
{
    if(m_label)
        m_label->setText( QString::number(value ) );

    if(m_inputText)
        m_inputText->setText( QString::number(value ) );

    for(HandleParameters * hp : m_suscribers )
    {
        hp->setValue( (int)value);
    }
 }
