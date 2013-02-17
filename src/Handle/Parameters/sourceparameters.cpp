#include "sourceparameters.h"
#include <QLabel>
#include <QLayout>

SourceParameters::SourceParameters(const QString & label)
    : m_label(label),
      m_labelView(nullptr)
{
}


void SourceParameters::addSuscriber(HandleParameters * target)
{
    m_suscribers.insert(target);
}

void SourceParameters::removeSuscriber(HandleParameters * target)
{
    m_suscribers.erase(target);
}

void SourceParameters::setParentLayout(QWidget * parent, QWidget * fils)
{

    fils->setParent(parent);

    if( m_label != "")
    {
        if( ! m_labelView )
            m_labelView = new QLabel(m_label);
        m_labelView->setParent(parent);
        if(parent)
            parent->layout()->addWidget(m_labelView);
        m_labelView->show();
    }

    if(parent)
        parent->layout()->addWidget(fils);
    fils->show();
}

void SourceParameters::hideParameters(void)
{
    if(m_labelView)
        m_labelView->hide();
}
