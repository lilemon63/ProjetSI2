#include "handleparameters.h"
#include "sourceparameters.h"
#include "slider.h"
#include "dial.h"
#include "spinbox.h"
#include "radiobutton.h"
#include "colorselection.h"
#include "inputtext.h"
#include "checkbox.h"

HandleParameters::HandleParameters()
    : m_source(nullptr)
{
}


void HandleParameters::showParameters(QWidget * parent)
{
    if(m_source)
        m_source->showParameters(parent);
}

void HandleParameters::changeSources(SourceParameters *source)
{
    if(m_source)
        m_source->removeSuscriber(this);
    m_source = source;
    if(source)
        source->addSuscriber(this);
}

void HandleParameters::hideParameters(void)
{
    if(m_source)
        m_source->hideParameters();
}

HandleParameters::~HandleParameters(void)
{
    if(m_source)
        m_source->removeSuscriber(this);
}


void HandleParameters::setActionOnChangeValue(std::function<void(QVariant, HandleParameters *)> fct)
{
    m_lambda = fct;
}

void HandleParameters::acceptChanges(QVariant value)
{
    QVariant::setValue(value);
}

std::shared_ptr<HandleParameters> HandleParameters::build_slider( const QString & label = QString(), int defaultValue, int min, int max)
{
    std::shared_ptr<HandleParameters> newParam = std::shared_ptr<HandleParameters>(new HandleParameters() );
    newParam->changeSources(new Slider(label, defaultValue, min, max));
    return newParam;
}

std::shared_ptr<HandleParameters> HandleParameters::build_dial(const QString & label, int defaultAngle)
{
    std::shared_ptr<HandleParameters> newParam = std::shared_ptr<HandleParameters>(new HandleParameters() );
    newParam->changeSources(new Dial(label, defaultAngle));
    return newParam;
}

std::shared_ptr<HandleParameters> HandleParameters::build_spinbox(const QString & label)
{
    std::shared_ptr<HandleParameters> newParam = std::shared_ptr<HandleParameters>(new HandleParameters() );
    newParam->changeSources(new SpinBox(label));
    return newParam;
}

std::shared_ptr<HandleParameters> HandleParameters::build_radiobutton(const QString & label, const QStringList & boxes)
{
    std::shared_ptr<HandleParameters> newParam = std::shared_ptr<HandleParameters>(new HandleParameters() );
    newParam->changeSources(new RadioButton(label,boxes));
    return newParam;
}

std::shared_ptr<HandleParameters> HandleParameters::build_colorselection(const QString & label, const QColor& c)
{

    std::shared_ptr<HandleParameters> newParam = std::shared_ptr<HandleParameters>(new HandleParameters() );
    newParam->changeSources(new ColorSelection(label, c));
    return newParam;
}

std::shared_ptr<HandleParameters> HandleParameters::build_inputtext(const QString & label, const QString &defaultValue)
{
    std::shared_ptr<HandleParameters> newParam = std::shared_ptr<HandleParameters>(new HandleParameters() );
    newParam->changeSources(new InputText(label, defaultValue));
    return newParam;
}

std::shared_ptr<HandleParameters> HandleParameters::build_checkbox(const QString & label, const QStringList & boxes)
{
    std::shared_ptr<HandleParameters> newParam = std::shared_ptr<HandleParameters>(new HandleParameters() );
    newParam->changeSources(new CheckBox(label, boxes));
    return newParam;
}
