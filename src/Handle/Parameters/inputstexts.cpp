#include "inputstexts.h"
#include "handleparameters.h"
#include <QHBoxLayout>

InputsTexts::InputsTexts(const QString & label, unsigned int number, const QStringList &defaultValue) :
    SourceParameters(label),
    m_inputText(new QLineEdit *[number]),
    m_frame(new QFrame() )
{
    m_frame->setLayout( new QHBoxLayout() );
    unsigned int max = defaultValue.size();
    for(unsigned int i = 0; i != number; ++i)
    {
        m_inputText[i] = new QLineEdit();
        m_frame->layout()->addWidget(m_inputText[i]);
        connect(m_inputText[i], SIGNAL(textChanged(QString)), this, SLOT(valueChanged()));
        if( i != max)
            m_inputText[i]->setText(defaultValue[i]);
        m_values.push_back( m_inputText[i]->text() );
        m_ids[m_inputText[i] ] = i;
    }
}


void InputsTexts::valueChanged(void)
{
    QObject * obj = QObject::sender();
    int id = m_ids[(QLineEdit*)obj];
    m_values[id] = m_inputText[id]->text();
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( m_values );
}

void InputsTexts::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}

void InputsTexts::hideParameters(void)
{
    m_frame->hide();
}

void InputsTexts::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue( m_values );
}

InputsTexts::~InputsTexts()
{
    delete [] m_inputText;
}
