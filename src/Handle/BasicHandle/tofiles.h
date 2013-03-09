#ifndef TOFILES_H
#define TOFILES_H

#include <string>

#include "../virtualhandle.h"

class ToFiles : public VirtualHandle
{
   enum{ Frequence ,Path, Max};
public:
    /** @brief Build a ToFile handle
        @param const std::string & path : existant folder where we put the image
        @param unsigned int defaultFrequence = 0 : default frequence in frame number
        @param const std::string & name = "noname" : handle's name */
    ToFiles(const std::string & path , unsigned int defaultFrequence = 0, const QString & affName = "untilted", const std::string & name = "noname");
protected :
    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
private :
    unsigned int m_compteur;
};

#endif // TOFILES_H
