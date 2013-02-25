#include "zi.h"
#include "Parameters/colorselection.h"
#include "Parameters/checkbox.h"
#include "Parameters/inputtext.h"
#include "Parameters/combobox.h"

ZI::ZI(QRectF rect)
    : m_rect(rect)
{
    m_listParameters.resize(MAX);
    m_listParameters[AREA] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    //m_listParameters[AREA]->changeSources( );
    //m_listParameters[SIZE]; //TODO to
    m_listParameters[COLOR] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[COLOR]->changeSources( new ColorSelection("Couleur"));
    m_listParameters[ACTIVATION] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[ACTIVATION]->changeSources( new CheckBox("", QStringList("Activation") ));
    //m_listParameters[DELETE] TODO

    m_listParameters[NAME] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[NAME]->changeSources( new InputText("Nom", "ZI"));

    m_listParameters[HANDLE] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[HANDLE]->changeSources( new ComboBox("Traitement", getAllHandleName(), "NOHANDLE" ));



}

ImageDataPtr ZI::startHandle(ImageDataPtr src1, const ImageDataPtr src2)
{
    ImageDataPtr result = VirtualHandle::executeHandle(m_listParameters[HANDLE]->toString().toStdString() , src1, src2);
    return result;
}

ImageDataPtr ZI::executeHandle(ImageDataPtr src1, const ImageDataPtr src2)
{
    ImageDataPtr srcZi = src1->getSubRegion(100, 100, 200, 200);
    ImageDataPtr srcZi2 = src1->getSubRegion(100, 100, 200, 200);

    ImageDataPtr result = VirtualHandle::executeHandle(srcZi,srcZi2);

    //TODO merge ZI
    return src1;
}
