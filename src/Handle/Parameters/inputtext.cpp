#include "inputtext.h"
#include "handleparameters.h"
#include <iostream>

InputText::InputText(const QString &label, const QString & defaultValue) :
    SourceParameters(label),
    m_inputText(new QLineEdit())
{
    connect(m_inputText, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
    m_inputText->setText(defaultValue);
}


void InputText::valueChanged(void)
{
    std::cerr << m_inputText->text().toStdString() << std::endl;
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (QString)m_inputText->text());
}

void InputText::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_inputText);
}

void InputText::hideParameters(void)
{
    m_inputText->hide();
}

void InputText::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_inputText->text() );
}
