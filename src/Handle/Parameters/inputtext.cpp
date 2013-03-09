#include <QFrame>
#include <QLineEdit>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QPushButton>

#include "inputtext.h"
#include "handleparameters.h"


InputText::InputText(const QString &label, const QString & defaultValue, Helper helper) :
    SourceParameters(label),
    m_inputText(new QLineEdit()),
    m_frame(new QFrame() ),
    m_helper(helper)
{
    m_frame->setLayout( new QHBoxLayout() );
    m_frame->layout()->addWidget(m_inputText);

    m_frame->layout()->setContentsMargins(0,0,0,0);
    m_frame->layout()->setMargin(0);
    m_frame->layout()->setSpacing(0);

    if( helper != None)
    {
        QPushButton * button = new QPushButton("...");
        button->setMaximumWidth(50);
        m_frame->layout()->addWidget( button );
        connect(button, SIGNAL(clicked(bool)), this, SLOT(openPopUp()));
    }

    connect(m_inputText, SIGNAL(editingFinished()), this, SLOT(valueChanged()));
    m_inputText->setText(defaultValue);
}


/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void InputText::addSuscriber(HandleParameters * target)
{
    SourceParameters::addSuscriber(target);
    target->setValue(m_inputText->text() );
}


void InputText::hideParameters(void)
{
    m_frame->hide();
}


void InputText::openPopUp(void)
{
    QString result;
    switch( m_helper )
    {
        case None :
        break;
        case Directory :
            result = QFileDialog::getExistingDirectory();
        break;
        case SaveFile :
            result = QFileDialog::getSaveFileName();
        break;
        case OpenFile :
            result = QFileDialog::getOpenFileName();
        break;
    }
    if( result != "" )
    {
        m_inputText->setText(result);
        valueChanged();
    }
}


void InputText::showParameters(QWidget * parent)
{
    setParentLayout(parent, m_frame);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE SLOT-----------------------------------------
---------------------------------------------------------------------------------------------------*/

void InputText::valueChanged(void)
{
    for(HandleParameters * hp : m_suscribers )
        hp->setValue( (QString)m_inputText->text());
}
