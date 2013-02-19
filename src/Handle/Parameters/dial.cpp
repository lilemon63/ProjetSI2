#include "dial.h"
#include "handleparameters.h"
#include <iostream>
#include <QVBoxLayout>

Dial::Dial(const QString & label, int angle, int min, int max, Helper helper)
    : SourceParameters(label),
      m_dial( new QDial() ),
      m_frame( new QFrame() ),
      m_label(nullptr),
      m_inputText(nullptr)
{
    m_frame->setLayout( new QVBoxLayout() );

    m_frame->layout()->addWidget(m_dial);
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

    m_dial->setMaximum( max);
    m_dial->setMinimum( min );
    m_dial->setOrientation(Qt::Horizontal);
    QObject::connect(m_dial, SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
    m_dial->setValue(angle);
}


void Dial::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}

void Dial::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_frame->hide();
}

void Dial::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_dial->value() );
}


void Dial::changeValue(int  value)
{
    if(m_label)
        m_label->setText( QString::number(value ) );
    if(m_inputText)
        m_inputText->setText( QString::number(value ) );
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}

void Dial::changeValue(void)
{
    m_dial->setValue(m_inputText->text().toInt());
}
