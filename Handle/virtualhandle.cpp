#include "virtualhandle.h"
#include "../exception.h"

VirtualHandle::VirtualHandle(const std::string & name)
    : m_name(name)
{
    m_listHandle[name] = this;
}

VirtualHandle::ListHandle VirtualHandle::m_listHandle;

ImageDataPtr VirtualHandle::executeHandle(const std::string & name, const ImageDataPtr src1, const ImageDataPtr src2)
{
    if( ! m_listHandle[name] )
        throwExcOutClass(name + " n'est pas un nom de traitement valide", "VirtualHandle", "executeHandle");
    return m_listHandle[name]->startHandle(src1, src2);
}
