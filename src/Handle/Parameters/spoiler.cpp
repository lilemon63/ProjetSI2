#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

#include "spoiler.h"
#include "handleparameters.h"
#include "sourceparameters.h"

Spoiler::Spoiler()
    :
    m_button( new QPushButton() ),
    m_button_icon( new QPushButton() ),
    m_frame( new QFrame() ),
    m_layout( new QHBoxLayout(this) ),
    m_title( new QFrame() )
{
    m_button_icon->setIcon(QIcon(QPixmap("low_arrow.png")));

    m_layout->addWidget(m_button_icon);
    m_layout->addWidget(m_button);

    m_layout->addStretch();
    m_layout->setContentsMargins(0,0,0,0);

    m_layout->setMargin(0);
    m_title->setLayout(m_layout);

    m_frame->setLayout( new QVBoxLayout() );

    m_button->setFlat(true);
    m_button_icon->setFlat(true);

    QObject::connect(m_button,SIGNAL(clicked()),this,SLOT(whenClicked()));
    QObject::connect(m_button_icon,SIGNAL(clicked()),this,SLOT(whenClicked()));
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/


void Spoiler::changeAffName( const QString & affname, Numbering & num)
{
    m_button->setText( num.text() + " " + affname );
}


void Spoiler::hideAll()
{
    m_title->hide();
    m_frame->hide();
    m_hiden = true;
}


void Spoiler::hideParameters(void)
{
    m_frame->hide();
}


void Spoiler::setParam(const VirtualHandle::ListParameters &listParameters,
                       std::shared_ptr<HandleParameters> viewParam,
                       const VirtualHandle::ListDependancies &dependancies,
                       const QString &name, QWidget * parent, Numbering &num )
{
    m_button->setText( num.text() + " " + name );

    for(auto param : listParameters)
        param->showParameters(m_frame );
    viewParam->showParameters(m_frame );

    for(auto mobile : dependancies)
        mobile->showParameters( m_frame , num );

    parent->layout()->addWidget(m_title);
    parent->layout()->addWidget(m_frame);
    m_title->show();
    m_frame->hide();
}


void Spoiler::showAll()
{
    m_title->show();
    m_frame->show();
}


void Spoiler::showParameters(QWidget * parent)
{
    m_frame->setParent(parent);

    if(parent)
        parent->layout()->addWidget(m_frame);
    m_frame->show();
}


QWidget * Spoiler::widget(void)
{
    return m_frame;
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC SLOT------------------------------------------
---------------------------------------------------------------------------------------------------*/

void Spoiler::whenClicked()
{
    if(m_hiden)
    {
        showAll();
        m_button_icon->setIcon( QIcon( QPixmap("high_arrow.png") ) );
    }
    else
    {
        hideParameters();
        m_button_icon->setIcon( QIcon( QPixmap("low_arrow.png") ) );
    }
    m_hiden = !m_hiden;
}
