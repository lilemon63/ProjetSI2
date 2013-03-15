#include <QVariant>

#include "zi.h"
#include "virtualhandle.h"


#include "../exception.h"
#include "../View/viewzi.h"
#include "../View/submdiwindowsimage.h"
#include "Parameters/spoiler.h"
#include "Parameters/checkbox.h"


VirtualHandle::ListHandle VirtualHandle::m_listHandle;
Mdi* VirtualHandle::m_view = nullptr;

VirtualHandle::VirtualHandle(const QString affName, const std::string & name)
    : m_listParameters(0),
      m_affName(affName),
      m_name(name),
      m_spoiler( new Spoiler() ),
      m_viewParameters( new HandleParameters() ),
      m_visibleCheckBox( new CheckBox( "", QStringList({"Vue active"} ) ) ),
      m_windows(nullptr)
{
    if( name != "noname" && m_listHandle.find(name) != m_listHandle.end() )
        throw Exception::buildException(name + " est un nom de traitement déjà  pris",
                                        "VirtualHandle",
                                        "VirtualHandle",
                                        EP);

    m_viewParameters->changeSources( m_visibleCheckBox );
    m_viewParameters->setActionOnChangeValue( [this]( QVariant Value, HandleParameters * hp )
                                                {
                                                        hp->acceptChanges(Value);
                                                        showView(hp->toMap()["Vue active"].toBool() );
                                                } );
    if(name != "noname")
        m_listHandle[name] = this;
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

ZI * VirtualHandle::createZI(QRect rect)
{
    ZI * zi = new ZI(rect, m_spoiler->widget(), m_numbering);
    m_listZI.push_back(zi);
    return zi;
}


ImageDataPtr VirtualHandle::executeHandle(ImageDataPtr src1, ImageDataPtr src2)
{
    ImageDataPtr image = startHandle(src1, src2);
    if(m_windows)
        m_windows->updateImageAsc(image);

    for(ZI * zi : m_listZI)
        image = zi->executeHandle(image, src1);
    return image;
}


ImageDataPtr VirtualHandle::executeHandle(const std::string & name, ImageDataPtr src1, ImageDataPtr src2)
{
    if( name == "noname" || m_listHandle.find(name) == m_listHandle.end() )
        throw Exception::buildException(name + " n'est pas un nom de traitement valide",
                                        "VirtualHandle",
                                        "executeHandle",
                                        EP);
    return m_listHandle[name]->executeHandle(src1, src2);
}


QStringList VirtualHandle::getAllHandleName(void)
{
    QStringList temp;

    for( auto nom : m_listHandle)
        temp.append( nom.first.c_str() );

    return temp;
}


const std::string & VirtualHandle::getName(void) const
{
    return m_name;
}


void VirtualHandle::hideParameters(void)
{
    m_spoiler->hideAll();
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


void VirtualHandle::setView(Mdi * view)
{
    m_view = view;
}


void VirtualHandle::showParameters(QWidget * parent, Numbering num )
{
    m_numbering.cloneFrom(num);
    m_spoiler->setParam(m_listParameters, m_viewParameters, m_dependancies, m_affName, parent, num);
}


void VirtualHandle::showParameters(QWidget * parent, bool reinit)
{
    if(reinit)
        m_numbering.cloneFrom( Numbering() );
    m_spoiler->setParam(m_listParameters, m_viewParameters, m_dependancies, m_affName, parent, m_numbering);
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


void VirtualHandle::viewClosed(void)
{
    m_visibleCheckBox->changeValue("Vue active", false);
    m_windows = nullptr;
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PROTECTED--------------------------------------------
---------------------------------------------------------------------------------------------------*/

void VirtualHandle::changeAffName(const QString & name)
{
    if( m_windows )
        m_windows->setWindowTitle(name);
    m_spoiler->changeAffName( name, m_numbering );
    m_affName = name;
}


void VirtualHandle::changeSource(unsigned int idParameters, SourceParameters * source)
{
    m_listParameters[idParameters]->changeSources(source);
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


QWidget * VirtualHandle::widget(void)
{
    return m_spoiler->widget();
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PRIVATE----------------------------------------------
---------------------------------------------------------------------------------------------------*/

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
            for( ZI * zi : m_listZI)
                m_windows->draw( zi->view() );
        }
        m_windows->show();
    }
}
