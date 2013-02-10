#include "sourceparameters.h"

SourceParameters::SourceParameters(QWidget *)
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
