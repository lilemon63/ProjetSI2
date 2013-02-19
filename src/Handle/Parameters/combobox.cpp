#include "combobox.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>

ComboBox::ComboBox(const QString & label, const QStringList & choices, const QString & defaultValue)
    : SourceParameters(label),
      m_combobox( new QComboBox() )
{
    for( auto value : choices)
        m_combobox->addItem(value);
    QObject::connect(m_combobox, SIGNAL(currentIndexChanged(QString)),this,SLOT(changeValue(QString)));
    if(defaultValue != "")
    {
        int i = m_combobox->findText(defaultValue);
        m_combobox->setCurrentIndex(i);
    }
}


void ComboBox::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_combobox);
}

void ComboBox::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_combobox->hide();
}

void ComboBox::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_combobox->currentText() );
}


void ComboBox::changeValue(QString newValue)
{
    for(HandleParameters * hp : m_suscribers )
    {
        hp->setValue( (QString)newValue);
    }
}
