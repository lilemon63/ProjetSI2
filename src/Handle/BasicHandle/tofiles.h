#ifndef TOFILES_H
#define TOFILES_H

#include <string>

#include "../virtualhandle.h"
#include "../Parameters/inputtext.h"
class ToFiles : public VirtualHandle
{
public:
    /** @brief Build a ToFile handle
        @param const std::string & path : existant folder where we put the image
        @param unsigned int defaultFrequence = 0 : default frequence in frame number
        @param const std::string & name = "noname" : handle's name */
    ToFiles(const std::string & path , unsigned int defaultFrequence = 0, const QString & affName = "untilted", const std::string & name = "noname");
protected :
    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
private :
    /** @brief existant folder where we put the image */
    InputText * m_Path;
    unsigned int m_compteur;

    enum{ Frequence ,Path, Max};
};

#endif // TOFILES_H
