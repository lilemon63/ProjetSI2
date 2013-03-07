#include "zi.h"
#include "Parameters/colorselection.h"
#include "Parameters/checkbox.h"
#include "Parameters/inputtext.h"
#include "Parameters/combobox.h"
#include "Parameters/inputstexts.h"
#include "../View/viewzi.h"
#include <QString>
#include <QVariant>

//TODO join

//TODO aff sous-traitement

ZI::ZI(QRect rect, QWidget *parent, Numbering num)
    : VirtualHandle("ZI"),
      m_view( new ViewZI(this, rect) ),
      m_size(new InputsTexts("Taille", 2, QStringList( {QString::number( (long long int)rect.height() ),
                                                       QString::number( (long long int)rect.width() )
                                                         } ) )),
      m_area(new InputsTexts("Coordonnees", 4, QStringList( { QString::number( (long long int)rect.x() ),
                                                            QString::number( (long long int)rect.y() ),
                                                            QString::number( (long long int)(rect.x() + rect.height() ) ),
                                                            QString::number( (long long int)(rect.y() + rect.width() ) )
                                                              } ) ) ),
      m_rect( rect ),
      m_parent(parent)
{
    m_numbering.clone(num);

    m_listParameters.resize(MAX);
    m_listParameters[AREA] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[AREA]->changeSources( m_area );


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
    m_listParameters[AREA]->setActionOnChangeValue(lambdaArea);

    m_listParameters[SIZE] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[SIZE]->changeSources( m_size );


    auto lambdaSize = [this](QVariant value, HandleParameters * hp)
    {
            hp->acceptChanges(value);
            QStringList list = value.toStringList();

            m_rect.setWidth( list[0].toInt() );
            m_rect.setHeight( list[1].toInt() );
            m_area->changeValue( QString::number( m_rect.x() + m_rect.width() ) , WIDTH );
            m_area->changeValue( QString::number( m_rect.y() + m_rect.height() ), HEIGHT );
    };
    m_listParameters[SIZE]->setActionOnChangeValue(lambdaSize);


    auto lambdaColor = [this](QVariant value, HandleParameters * hp)
    {
            hp->acceptChanges(value);
            m_view->changeColor( value.value<QColor>() );
    };
    m_listParameters[COLOR] = std::shared_ptr<HandleParameters>( new HandleParameters() );

    m_listParameters[COLOR]->setActionOnChangeValue(lambdaColor);
    m_listParameters[COLOR]->changeSources( new ColorSelection("Couleur"));


    m_listParameters[ACTIVATION] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[ACTIVATION]->changeSources( new CheckBox("", QStringList("Activation") ));

    m_listParameters[NAME] =  HandleParameters::build_inputtext("Nom", "ZI");
    m_listParameters[NAME]->setActionOnChangeValue([this]( QVariant Value, HandleParameters * hp )
                                                    {
                                                            hp->acceptChanges(Value);
                                                            changeAffName( hp->toString() );
                                                    });

    auto lambdaName = [this](QVariant value, HandleParameters * hp)
    {
            hp->acceptChanges(value);
            changeAffName(value.toString() );
    };
    m_listParameters[NAME]->setActionOnChangeValue(lambdaName);


    m_listParameters[HANDLE] = std::shared_ptr<HandleParameters>( new HandleParameters() );
    m_listParameters[HANDLE]->changeSources( new ComboBox("Traitement", getAllHandleName(), "NOHANDLE" ));
    auto lambdaHandle = [this](QVariant value, HandleParameters * hp)
    {
            hideParameters(hp->toString().toStdString());

            hp->acceptChanges(value);
            QString handle = value.toString();
            if(handle != "NOHANDLE")
            {
                this->getHandleForDependancies(handle.toStdString() )->showParameters( this->widget(),
                                                                                       m_numbering );
            }
    };

    m_listParameters[HANDLE]->setActionOnChangeValue(lambdaHandle);


}

ImageDataPtr ZI::startHandle(ImageDataPtr src1, const ImageDataPtr src2)
{
    ImageDataPtr result = VirtualHandle::executeHandle(m_listParameters[HANDLE]->toString().toStdString() , src1, src2);
    return result;
}

ImageDataPtr ZI::executeHandle(ImageDataPtr src1, const ImageDataPtr src2)
{
    int x = m_rect.x();
    int y = m_rect.y();
    int w = m_rect.width();
    int h = m_rect.height();

    ImageDataPtr srcZi = src1->getSubRegion(x, y, w, h);
    ImageDataPtr srcZi2 = src2->getSubRegion(x, y, w, h);

    ImageDataPtr result = src1;
    if( m_listParameters[ACTIVATION]->toMap()["Activation"].toBool() )
        VirtualHandle::executeHandle(srcZi,srcZi2);

    //TODO merge ZI
    return src1;
}

ViewZI * ZI::view(void)
{
    return m_view;
}

void ZI::resize( Direction direction, int value)
{
    m_area->changeValue( QString::number(value), direction);
}


void ZI::showParameters(void)
{
    showParameters(m_parent);
}
