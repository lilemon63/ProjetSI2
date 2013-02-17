#include "radiobutton.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>
#include <QLabel>

RadioButton::RadioButton(QString label, QString name, QStringList boxes)
    : SourceParameters(label),
      m_group(name)
{
    for(int pos = 0; pos < boxes.size(); pos++){
        m_hboxs.push_back(new QHBoxLayout());
        m_radiobuttons.push_back(new QRadioButton());
        m_hboxs[pos]->addWidget(m_radiobuttons[pos]);
        m_hboxs[pos]->addWidget(new QLabel(boxes[pos]));
        m_vbox.addWidget(m_radiobuttons[pos]);
    }
    if(boxes.size() != 0)
        m_radiobuttons[0]->setChecked(true);
    m_group.setLayout(&m_vbox);
}


void RadioButton::showParameters(QWidget * parent)
{
    m_group.setParent(parent);
    setParentLayout(parent, &m_group);
    m_group.show();
}

void RadioButton::hideParameters(void)
{
    m_group.hide();
}

void RadioButton::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    //target->setValue(m_group.isChecked() );
}


void RadioButton::changeValue(int  value)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (int)value);
}
