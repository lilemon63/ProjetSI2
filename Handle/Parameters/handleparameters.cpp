#include "handleparameters.h"
#include "sourceparameters.h"

HandleParameters::HandleParameters()
    : m_source(nullptr)
{
}


void HandleParameters::showParameters(QWidget * parent)
{
    if(m_source)
        m_source->showParameters(parent);
}

void HandleParameters::changeSources(std::shared_ptr<SourceParameters> source)
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
