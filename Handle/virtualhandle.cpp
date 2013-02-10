#include "virtualhandle.h"
#include "../exception.h"

VirtualHandle::VirtualHandle(const std::string & name)
    : m_name(name)
{
    if( name != "noname" && m_listHandle.find(name) != m_listHandle.end() )
        throw Exception::buildException(name + " est un nom de traitement déjà pris",
                                        "VirtualHandle",
                                        "VirtualHandle",
                                        EP);;
    m_listHandle[name] = this;
}

VirtualHandle::ListHandle VirtualHandle::m_listHandle;

ImageDataPtr VirtualHandle::executeHandle(const std::string & name, const ImageDataPtr src1, const ImageDataPtr src2)
{
    if( name == "noname" || ! m_listHandle[name] )
        throw Exception::buildException(name + " n'est pas un nom de traitement valide",
                                        "VirtualHandle",
                                        "executeHandle",
                                        EP);
    return m_listHandle[name]->startHandle(src1, src2);
}

void VirtualHandle::showParameters(QWidget * parent)
{
    for(HandleParameters & param : m_listParameters)
        param.showParameters(parent);
    for(VirtualHandle * handle : m_dependancies)
        handle->showParameters(parent);
}

void VirtualHandle::hideParameters(void)
{
    for(HandleParameters & param : m_listParameters)
        param.hideParameters();
    for(VirtualHandle * handle : m_dependancies)
        handle->hideParameters();
}

void VirtualHandle::changeSource(unsigned int idParameters, std::shared_ptr<SourceParameters> source)
{
    m_listParameters[idParameters].changeSources(source);
}
