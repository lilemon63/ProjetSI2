#ifndef TOFILES_H
#define TOFILES_H

#include <string>

#include "../virtualhandle.h"

class ToFiles : VirtualHandle
{
public:
    /** @brief Build a ToFile handle
        @param const std::string & path : existant folder where we put the image
        @param unsigned int defaultFrequence = 0 : default frequence in frame number
        @param const std::string & name = "noname" : handle's name */
    ToFiles(const std::string & path , unsigned int defaultFrequence = 0, const std::string & name = "noname");

    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);
private :
    /** @brief existant folder where we put the image */
    const std::string m_path;

    unsigned int m_compteur;

    enum{ Frequence , Max};
};

#endif // TOFILES_H
