#include "zi.h"
#include "Parameters/colorselection.h"
#include "Parameters/checkbox.h"
#include "Parameters/inputtext.h"
#include "Parameters/combobox.h"
#include "Parameters/inputstexts.h"
#include <QString>

ZI::ZI(QRectF rect)
    : m_x(rect.x()),
      m_y(rect.y()),
      m_width(rect.width()),
      m_height(rect.height())

{
    m_listParameters.resize(MAX);
    m_listParameters[AREA] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[AREA]->changeSources( new InputsTexts("Coordonnees", 4, QStringList( { QString::number(m_x),
                                                                                          QString::number(m_y),
                                                                                          QString::number(m_x + m_height),
                                                                                          QString::number(m_y + m_width)
                                                                                            } ) ) );

    m_listParameters[SIZE] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[SIZE]->changeSources( new InputsTexts("Taille", 2, QStringList( {QString::number(m_height),
                                                                                      QString::number(m_width)
                                                                                        } ) ) );
    m_listParameters[COLOR] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[COLOR]->changeSources( new ColorSelection("Couleur"));
    m_listParameters[ACTIVATION] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[ACTIVATION]->changeSources( new CheckBox("", QStringList("Activation") ));

    m_listParameters[DELETE] = HandleParameters::build_checkbox("Supprimer");

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
    ImageDataPtr srcZi2 = src2->getSubRegion(100, 100, 200, 200);

    ImageDataPtr result = VirtualHandle::executeHandle(srcZi,srcZi2);

    //TODO merge ZI
    return src1;
}
