#include "combobox.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>

ComboBox::ComboBox(QString name, QStringList choices)
    :SourceParameters(name)
{
    for(int pos = 0; pos < choices.size() ; pos++)
        m_combobox.insertItem( pos, choices[pos]);
    //QObject::connect(&m_combobox, SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
}


void ComboBox::showParameters(QWidget * parent)
{
    m_combobox.setParent(parent);
    setParentLayout(parent, &m_name);
    setParentLayout(parent, &m_combobox);
    m_combobox.show();
}

void ComboBox::hideParameters(void)
{
    m_combobox.hide();
}

void ComboBox::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_combobox.currentIndex() );
}


void ComboBox::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
