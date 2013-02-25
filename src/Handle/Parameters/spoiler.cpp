#include "spoiler.h"
#include <iostream>

Spoiler::Spoiler()
    :
    m_layout(new QHBoxLayout(this)),
    m_button(new QPushButton()),
    m_button_icon(new QPushButton()),
    m_frame(new QFrame() ),
    m_title(new QFrame())
{
    m_button_icon->setIcon(QIcon(QPixmap("low_arrow.png")));
    m_layout->addWidget(m_button_icon);
    m_layout->addWidget(m_button);
    m_layout->addStretch();
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setMargin(0);

    m_frame->setLayout( new QVBoxLayout() );

    m_button->setFlat(true);
    m_button_icon->setFlat(true);

    QObject::connect(m_button,SIGNAL(clicked()),this,SLOT(whenClicked()));

    QObject::connect(m_button_icon,SIGNAL(clicked()),this,SLOT(whenClicked()));

}

void Spoiler::hideAll()
{
    m_title->hide();
    m_frame->hide();
    m_hiden = true;
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

void Spoiler::hideParameters(void)
{
    m_frame->hide();
}

void Spoiler::setParam(VirtualHandle::ListParameters listParameters, std::shared_ptr<HandleParameters> viewParam,
                       VirtualHandle::ListDependancies dependancies,
                       std::string name, QWidget * parent){
    m_button->setText(name.c_str());
    for(auto param : listParameters)
        param->showParameters(m_frame );
    viewParam->showParameters(m_frame );
    for(auto mobile : dependancies)
        mobile->showParameters( m_frame );
    m_title->setLayout(m_layout);
    parent->layout()->addWidget(m_title);
    parent->layout()->addWidget(m_frame);
    m_title->show();
    m_frame->hide();

}

void Spoiler::whenClicked(){

    if(m_hiden){
        showAll();
        m_button_icon->setIcon(QIcon(QPixmap("high_arrow.png")));
    }
    else{
        hideParameters();
        m_button_icon->setIcon(QIcon(QPixmap("low_arrow.png")));
    }
    m_hiden = !m_hiden;

}
