#include <QLabel>
#include <QFrame>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>

#include "radiobutton.h"
#include "handleparameters.h"



RadioButton::RadioButton(const QString &label, const QStringList & boxes, const QString & defaultValue)
    : SourceParameters(label),
      m_frame(new QFrame() ),
      m_group( new QButtonGroup() )
{

    QLayout * layout = new QVBoxLayout();
    m_frame->setLayout( layout );
    for(auto label : boxes)
    {
        QRadioButton * bouton = new QRadioButton(label);

        if(label == defaultValue)
            bouton->setChecked(true);

        m_radiobuttons.push_back( bouton );

        m_group->addButton(bouton);
        layout->addWidget(bouton);
    }
    if(boxes.size() != 0 && defaultValue == "")
        m_radiobuttons[0]->setChecked(true);

    connect(  m_group, SIGNAL( buttonClicked(QAbstractButton*) ), this, SLOT( changeValue() ) );
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void RadioButton::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue( m_group->checkedButton()->text() );
}


void RadioButton::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_frame->hide();
}


void RadioButton::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void RadioButton::changeValue(void)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( m_group->checkedButton()->text() );
}
