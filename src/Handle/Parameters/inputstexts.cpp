#include <QFrame>
#include <QLineEdit>
#include <QHBoxLayout>

#include "inputstexts.h"
#include "handleparameters.h"


InputsTexts::InputsTexts(const QString & label, unsigned int number, const QStringList &defaultValue) :
    SourceParameters(label),
    m_inputText(new QLineEdit *[number]),
    m_frame(new QFrame() )
{
    m_frame->setLayout( new QHBoxLayout() );
    m_frame->layout()->setContentsMargins(0,0,0,0);
    m_frame->layout()->setSpacing(0);

    unsigned int max = defaultValue.size();
    for(unsigned int i = 0; i != number; ++i)
    {
        m_inputText[i] = new QLineEdit();
        m_frame->layout()->addWidget(m_inputText[i]);

        m_values.push_back( m_inputText[i]->text() );
        m_inputText[i]->setMaximumWidth(50);

        m_ids[m_inputText[i] ] = i;
        connect(m_inputText[i], SIGNAL(textChanged(QString)), this, SLOT(valueChanged()));
        if( i < max)
            m_inputText[i]->setText(defaultValue[i]);
    }
}


InputsTexts::~InputsTexts()
{
    delete [] m_inputText;
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void InputsTexts::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue( m_values );
}


void InputsTexts::changeValue( const QString & newValue, int id )
{
    if( m_values[id] != newValue)
        m_inputText[id]->setText(newValue);
}


void InputsTexts::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}


void InputsTexts::hideParameters(void)
{
    m_frame->hide();
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void InputsTexts::valueChanged(void)
{
    QObject * obj = QObject::sender();
    int id = m_ids[(QLineEdit*)obj];
    m_values[id] = m_inputText[id]->text();

    for(HandleParameters * hp : m_suscribers )
        hp->setValue( m_values );
}
