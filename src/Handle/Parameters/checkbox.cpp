#include "checkbox.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>
#include <QLabel>

CheckBox::CheckBox(QString label, QString name, QStringList boxes)
    : SourceParameters(label),
      m_group(name)
{
    for(int pos = 0; pos < boxes.size(); pos++){
        m_hboxs.push_back(new QHBoxLayout());
        m_checkboxs.push_back(new QCheckBox());
        m_hboxs[pos]->addWidget(m_checkboxs[pos]);
        m_hboxs[pos]->addWidget(new QLabel(boxes[pos]));
        m_vbox.addLayout(m_hboxs[pos]);
    }
    m_group.setLayout(&m_vbox);
}


void CheckBox::showParameters(QWidget * parent)
{
    setParentLayout(parent, &m_group);
}

void CheckBox::hideParameters(void)
{
    m_group.hide();
}

void CheckBox::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    //target->setValue(m_group.isChecked() );
}


void CheckBox::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
