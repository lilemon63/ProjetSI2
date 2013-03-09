#include <QDir>
#include <QDateTime>
#include <opencv2/opencv.hpp>

#include "tofiles.h"
#include "../Parameters/inputtext.h"
#include "../../exception.h"


ToFiles::ToFiles(const std::string & path, unsigned int, const QString & affName,const std::string &name)
    : VirtualHandle(affName, name),
      m_compteur(0)
{
    QDir d(path.c_str() );
    if(! d.isReadable() )
        throw Exception::buildException("Le dossier " + path + " n'existe pas ou vous n'avez pas le droit d'y accéder", "ToFiles","ToFiles" , EPC);

    m_listParameters.resize(Max);

    m_listParameters[Frequence] = HandleParameters::build_spinbox("Frequence");
    m_listParameters[Path] = HandleParameters::build_inputtext("Path",
                                                               QString(path.c_str()),
                                                               InputText::Directory );
}


ImageDataPtr ToFiles::startHandle(const ImageDataPtr src1, const ImageDataPtr)
{
    if( ! src1)
        throw Exception::buildException("La source est vide", "ToFiles", "startHandle", EPC);

    unsigned int nbFrame = m_listParameters[Frequence]->toInt();

    if( ++m_compteur >= nbFrame)
    {
        std::string imgPath = m_listParameters[Path]->toString().toStdString ()
                + "/TIFF_Image_"
                + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh'h'mm'm'ss's'zzz").toStdString()
                + ".tiff";
        cvSaveImage( imgPath.c_str() , src1->getImage() );
        m_compteur = 0;
    }
    return src1;
}
