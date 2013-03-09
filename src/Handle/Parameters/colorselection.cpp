#include <QPalette>
#include <QPushButton>
#include <QColorDialog>

#include "colorselection.h"
#include "handleparameters.h"

ColorSelection::ColorSelection(const QString & label, const QColor & color)
    : SourceParameters(label),
      m_color(color),
      m_button(new QPushButton() )
{
    QString style = "background-color:" + m_color.name() + "; border-color:" + m_color.name();
    m_button->setStyleSheet(style);
    connect(m_button, SIGNAL( clicked() ), this, SLOT( openPopUp() ) );
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void ColorSelection::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue( m_color );
}


void ColorSelection::hideParameters(void)
{
    SourceParameters::hideParameters();
    m_button->hide();
}


void ColorSelection::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_button);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

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
