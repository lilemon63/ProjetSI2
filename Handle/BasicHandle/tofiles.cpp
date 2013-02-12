#include "tofiles.h"
#include "exception.h"
#include <QDir>
#include <QDateTime>
#include <opencv2/opencv.hpp>

ToFiles::ToFiles(const std::string & path, unsigned int,const std::string &name)
    : VirtualHandle(name),
      m_path(path),
      m_compteur(0)
{
    QDir d(path.c_str() );
    if(! d.isReadable() )
        throw Exception::buildException("Le dossier " + path + " n'existe pas ou vous n'avez pas le droit d'y accéder", "ToFiles","ToFiles" , EPC);

    m_listParameters.resize(Max);


    m_listParameters[Frequence] = std::shared_ptr<HandleParameters>( new HandleParameters() );
}


ImageDataPtr ToFiles::startHandle(const ImageDataPtr src1, const ImageDataPtr)
{
    if( ! src1)
        throw Exception::buildException("La source est vide", "ToFiles", "startHandle", EPC);

    unsigned int nbFrame = m_listParameters[Frequence]->toInt();

    if( ++m_compteur >= nbFrame)
    {
        std::string imgPath = m_path + "/TIFF_Image_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh'\'h'mm'm'ss's'zzz").toStdString() + ".tiff";

        cvSaveImage( imgPath.c_str() , src1->getImage() );

        m_compteur = 0;
    }

    return src1;
}
