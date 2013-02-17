#include "radiobutton.h"
#include "handleparameters.h"
#include <iostream>
#include <QLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QFrame>
#include <QVBoxLayout>

RadioButton::RadioButton(const QString &label, QStringList boxes)
    : SourceParameters(label),
      m_group( new QButtonGroup() ),
      m_frame(new QFrame() )
{

    QLayout * layout = new QVBoxLayout();
    m_frame->setLayout( layout );
    for(auto label : boxes)
    {
        QRadioButton * bouton = new QRadioButton(label);
        m_radiobuttons.push_back( bouton );
        m_group->addButton(bouton);
        layout->addWidget(bouton);
    }
    if(boxes.size() != 0)
        m_radiobuttons[0]->setChecked(true);

    //m_group.setLayout(m_layout);
}


void RadioButton::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}

void RadioButton::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_frame->hide();
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
