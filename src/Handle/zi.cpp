#include <QString>
#include <QVariant>

#include "zi.h"
#include "Parameters/combobox.h"
#include "Parameters/checkbox.h"
#include "Parameters/inputtext.h"
#include "Parameters/inputstexts.h"
#include "Parameters/colorselection.h"
#include "../View/viewzi.h"

ZI::ZI(QRect rect, QWidget *parent, Numbering num)
    : VirtualHandle("ZI"),
      m_area(new InputsTexts("Coordonnees", 4, QStringList( { QString::number( (long long int)rect.x() ),
                                                              QString::number( (long long int)rect.y() ),
                                                              QString::number( (long long int)(rect.x() + rect.height() ) ),
                                                              QString::number( (long long int)(rect.y() + rect.width() ) )
                                                             } ) ) ),
      m_parent(parent),
      m_rect( rect ),

      m_size(new InputsTexts("Taille", 2, QStringList( {QString::number( m_rect.height() ),
                                                        QString::number( m_rect.width() )
                                                        } ) ) ),
      m_view( new ViewZI(this, rect) )
{
    m_numbering.cloneFrom(num);
    m_listParameters.resize(MAX);

    m_listParameters[AREA] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[AREA]->changeSources( m_area );
    m_listParameters[AREA]->setActionOnChangeValue( generateLambdaArea() );


    m_listParameters[SIZE] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[SIZE]->changeSources( m_size );
    m_listParameters[SIZE]->setActionOnChangeValue( generateLambdaSize() );


    m_listParameters[COLOR] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[COLOR]->setActionOnChangeValue( [this](QVariant value, HandleParameters * hp)
                                                    {
                                                            hp->acceptChanges(value);
                                                            m_view->changeColor( value.value<QColor>() );
                                                    });
    m_listParameters[COLOR]->changeSources( new ColorSelection("Couleur"));


    m_listParameters[ACTIVATION] = HandleParameters::build_checkbox("", QStringList("Activation") );


    m_listParameters[NAME] =  HandleParameters::build_inputtext("Nom", "ZI");
    m_listParameters[NAME]->setActionOnChangeValue([this]( QVariant Value, HandleParameters * hp )
                                                    {
                                                            hp->acceptChanges(Value);
                                                            changeAffName( hp->toString() );
                                                    });


    m_listParameters[HANDLE] = HandleParameters::build_comboBox("Traitement", getAllHandleName(), "NOHANDLE");
    m_listParameters[HANDLE]->setActionOnChangeValue( generateLambdaHandle() );


}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

ImageDataPtr ZI::executeHandle(ImageDataPtr src1, const ImageDataPtr src2)
{
    int x = m_rect.x();
    int y = m_rect.y();
    int w = m_rect.width();
    int h = m_rect.height();

    ImageDataPtr srcZi = src1->getSubRegion(x, y, w, h);
    ImageDataPtr srcZi2 = src2->getSubRegion(x, y, w, h);

    if( m_listParameters[ACTIVATION]->toMap()["Activation"].toBool() )
    {
        ImageDataPtr result = VirtualHandle::executeHandle(srcZi,srcZi2);
        src1->merge(result, x, y);
    }
    return src1;
}


void ZI::resize( Direction direction, int value)
{
    m_area->changeValue( QString::number(value), direction);
}


void ZI::showParameters(void)
{
    showParameters(m_parent);
}


ViewZI * ZI::view(void)
{
    return m_view;
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PROTECTED--------------------------------------------
---------------------------------------------------------------------------------------------------*/


ZI::M_Lambda ZI::generateLambdaArea(void)
{
    auto lambdaArea = [this](QVariant value, HandleParameters * hp)
    {
            hp->acceptChanges(value);
            QStringList list = value.toStringList();

            m_rect.setX( list[X].toInt() );
            m_rect.setY( list[Y].toInt() );

            m_rect.setWidth( list[WIDTH].toInt() - m_rect.x() );
            m_rect.setHeight( list[HEIGHT].toInt() - m_rect.y() );

            m_size->changeValue( QString::number( m_rect.width() ), 0 );
            m_size->changeValue( QString::number( m_rect.height() ), 1 );

            m_view->setRect(m_rect);
    };
    return lambdaArea;
}


ZI::M_Lambda ZI::generateLambdaHandle(void)
{
    auto lambdaHandle = [this](QVariant value, HandleParameters * hp)
    {
            hideParameters(hp->toString().toStdString());

            hp->acceptChanges(value);
            QString handle = value.toString();
            if(handle != "NOHANDLE")
            {
                this->getHandleForDependancies(handle.toStdString() )->showParameters( this->widget(),
                                                                                       m_numbering );
                --m_numbering;
            }
    };
    return lambdaHandle;
}


ZI::M_Lambda ZI::generateLambdaSize(void)
{
    auto lambdaSize = [this](QVariant value, HandleParameters * hp)
    {
            hp->acceptChanges(value);
            QStringList list = value.toStringList();

            m_rect.setWidth( list[0].toInt() );
            m_rect.setHeight( list[1].toInt() );
            m_area->changeValue( QString::number( m_rect.x() + m_rect.width() ) , WIDTH );
            m_area->changeValue( QString::number( m_rect.y() + m_rect.height() ), HEIGHT );
    };
    return lambdaSize;
}


ImageDataPtr ZI::startHandle(ImageDataPtr src1, const ImageDataPtr src2)
{
    ImageDataPtr result = VirtualHandle::executeHandle(m_listParameters[HANDLE]->toString().toStdString() , src1, src2);
    return result;
}
