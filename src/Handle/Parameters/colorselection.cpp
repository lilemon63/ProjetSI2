#include "handleparameters.h"
#include "colorselection.h"
#include <QColorDialog>

ColorSelection::ColorSelection(const QString & label, const QColor & color)
    : SourceParameters(label),
      m_button(new QPushButton() ),
      m_color(color)
{
    QString style ="background-color:" + m_color.name() + "; border-color:" + m_color.name();
    m_button->setStyleSheet(style);
    connect(m_button, SIGNAL(clicked()), this, SLOT(openPopUp()));
}


void ColorSelection::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_button);
}

void ColorSelection::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_button->hide();
}

void ColorSelection::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue( m_color );
}

void ColorSelection::openPopUp(void)
{
   QColor color = QColorDialog::getColor(m_color);
   m_color = color;
   if(color != QColor() )
   {
       QString style ="background-color:" + m_color.name() + "; border-color:" + m_color.name();
       m_button->setStyleSheet(style);
       for(HandleParameters * hp : m_suscribers )
       {
            hp->setValue( color );
       }
   }
}
