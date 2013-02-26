#include <QVariant>
#include "virtualhandle.h"
#include "../exception.h"
#include "Parameters/checkbox.h"
#include "../View/submdiwindowsimage.h"
#include "zi.h"
#include "Parameters/spoiler.h"

Mdi* VirtualHandle::m_view = nullptr;

VirtualHandle::VirtualHandle(const QString affName, const std::string & name)
    : m_listParameters(0),
      m_name(name),
      m_affName(affName),
      m_viewParameters(new HandleParameters() ),
      m_windows(nullptr),
      m_spoiler( new Spoiler() )
{
    if( name != "noname" && m_listHandle.find(name) != m_listHandle.end() )
        throw Exception::buildException(name + " est un nom de traitement déjà pris",
                                        "VirtualHandle",
                                        "VirtualHandle",
                                        EP);;

    m_visibleCheckBox = new CheckBox("", QStringList("Vue active"));
    m_viewParameters->changeSources( m_visibleCheckBox );
    auto lambda = [this]( QVariant Value, HandleParameters * hp )
    {
            hp->acceptChanges(Value);
            showView(hp->toMap()["Vue active"].toBool() );
    };
    m_viewParameters->setActionOnChangeValue( lambda );

    if(name != "noname")
        m_listHandle[name] = this;
}

VirtualHandle::ListHandle VirtualHandle::m_listHandle;

ImageDataPtr VirtualHandle::executeHandle(const std::string & name, ImageDataPtr src1, const ImageDataPtr src2)
{
    if( name == "noname" || m_listHandle.find(name) == m_listHandle.end() )
        throw Exception::buildException(name + " n'est pas un nom de traitement valide",
                                        "VirtualHandle",
                                        "executeHandle",
                                        EP);
    return m_listHandle[name]->executeHandle(src1, src2);
}


ImageDataPtr VirtualHandle::executeHandle(const ImageDataPtr src1, const ImageDataPtr src2)
{
    ImageDataPtr image = startHandle(src1, src2);
    if(m_windows)
        m_windows->updateImageAsc(image);
    for(ZI * zi : m_listZI)
        image = zi->executeHandle(image, src1);

    return image;
}

void VirtualHandle::showParameters(QWidget * parent, Numbering num )
{
    m_spoiler->setParam(m_listParameters, m_viewParameters, m_dependancies, m_affName, parent, num);
}

void VirtualHandle::showParameters(QWidget * parent)
{
    Numbering num;
    m_spoiler->setParam(m_listParameters, m_viewParameters, m_dependancies, m_affName, parent, num);
}

void VirtualHandle::hideParameters(const std::string & name)
{
    if( name == "noname" || m_listHandle.find(name) == m_listHandle.end() )
        throw Exception::buildException(name + " n'est pas un nom de traitement valide",
                                        "VirtualHandle",
                                        "executeHandle",
                                        EP);
    m_listHandle[name]->hideParameters();
}

void VirtualHandle::hideParameters(void)
{
    m_spoiler->hideAll();
}

void VirtualHandle::changeSource(unsigned int idParameters, SourceParameters * source)
{
    m_listParameters[idParameters]->changeSources(source);
}

void VirtualHandle::showParameters(QWidget * parent, const std::string & name)
{
    if( name == "noname" || m_listHandle.find(name) == m_listHandle.end() )
        throw Exception::buildException(name + " n'est pas un nom de traitement valide",
                                        "VirtualHandle",
                                        "executeHandle",
                                        EP);
    m_listHandle[name]->showParameters(parent);
}

VirtualHandle * VirtualHandle::getHandleForDependancies(const std::string & name)
{
    if( name == "noname" || m_listHandle.find(name) == m_listHandle.end() )
        throw Exception::buildException(name + " n'est pas un nom de traitement valide",
                                        "VirtualHandle",
                                        "executeHandle",
                                        EP);
    return m_listHandle[name];
}

QStringList VirtualHandle::getAllHandleName(void)
{
    QStringList temp;

    for( auto nom : m_listHandle)
        temp.append( nom.first.c_str() );

    return temp;
}

void VirtualHandle::showView(bool visible)
{
    if( ! m_view )
        return;
    if( ! visible )
    {
        if( m_windows )
            m_windows->hide();
    }
    else
    {
        if( ! m_windows )
        {
            m_windows = new SubMdiWindowsImage(m_affName, m_view);
            m_windows->move(0,0);
            m_windows->resize(300,300);
            m_windows->linkHandle(this);
        }
        m_windows->show();
    }
}

void VirtualHandle::setView(Mdi * view)
{
    m_view = view;
}


void VirtualHandle::viewClosed(void)
{
    m_visibleCheckBox->changeValue("Vue active", false);
    m_windows = nullptr;
}


ZI * VirtualHandle::createZI(QRectF rect)
{
    ZI * zi = new ZI(rect);
    m_listZI.push_back(zi);
    return zi;
}

void VirtualHandle::changeAffName(const QString & name)
{
    m_affName = name;            //changeName (spoiler + fenêtre)
}
