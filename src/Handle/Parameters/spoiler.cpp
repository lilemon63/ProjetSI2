#include "spoiler.h"
#include <iostream>

Spoiler::Spoiler()
{
    m_button = new QPushButton();
    m_button_icon = new QPushButton();
    m_button_icon->setIcon(QIcon(QPixmap("low_arrow.png")));

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_button_icon);
    m_layout->addStretch();
    m_layout->addWidget(m_button);

    m_frame = new QFrame();
    m_frame->setLayout( new QVBoxLayout() );

    m_button->setFlat(true);
    m_button_icon->setFlat(true);

    QObject::connect(m_button,SIGNAL(clicked()),this,SLOT(whenClicked()));

    QObject::connect(m_button_icon,SIGNAL(clicked()),this,SLOT(whenClicked()));

}

void Spoiler::hideAll(){

    std::cerr << "hideAll" << std::endl;
    m_frame->hide();
}

void Spoiler::showAll(){
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

void Spoiler::setParam(VirtualHandle::ListParameters listParameters,VirtualHandle::ListDependancies dependancies,std::string name, QWidget * parent){
    m_button->setText(name.c_str());
    for(auto param : listParameters)
        param->showParameters(m_frame );
    for(auto mobile : dependancies)
        mobile->showParameters( m_frame );
    QFrame * tmp = new QFrame();
    tmp->setLayout(m_layout);
    parent->layout()->addWidget(tmp);
    parent->layout()->addWidget(m_frame);
    m_frame->hide();

}

void Spoiler::whenClicked(){

    if(m_hiden){
        showAll();
        m_button_icon->setIcon(QIcon(QPixmap("high_arrow.png")));
    }
    else{
        hideAll();
        m_button_icon->setIcon(QIcon(QPixmap("low_arrow.png")));
    }
    m_hiden = !m_hiden;

}
