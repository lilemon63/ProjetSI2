#include "sourceparameters.h"
#include <QLabel>
#include <QLayout>

SourceParameters::SourceParameters(QString label)
    : m_label(label)
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

    if(m_label != "")
    {
        QLabel * label = new QLabel(m_label);
        label->setParent(parent);
        if(parent)
            parent->layout()->addWidget(label);
        label->show();
    }

    if(parent)
        parent->layout()->addWidget(fils);
    fils->show();
}
