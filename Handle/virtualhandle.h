#ifndef VIRTUALHANDLE_H
#define VIRTUALHANDLE_H

#include <string>
#include <map>
#include <opencv2/opencv.hpp>
#include "imagedata.h"

/** @brief
    Class which handle two IplImage and return an IplImage.<br/>
    The method startHandle() must be called at each time we have new IplImage.<br/>
    <br/>
    If you want select the principal handle, edit Handle.h's mainHandle.<br/>
    If you want call an handle, include Handle.h<br/>
    If you want create your own Handle class, copy ModelHandle.h and ModelHandle.cpp and edit them.
*/
class VirtualHandle
{
public:
    /** @brief Create a new VirtualHandle.
      @param const std::string & name : handle's name. */
    VirtualHandle(const std::string & name);

    ~VirtualHandle(void){}

    /** @brief Get the handle's name.
      @return const std::string & : handle's name */
    inline const std::string & getName(void);

    /** @brief execute the handle's startHandle() of the handle which name is given in parameters.
    @param const std::string & name : handle's name
    @param ImageDataPtr src1  : first image
    @param ImageDataPtr src2 : second image, NULL if unused
    @return ImageDataPtr : handle's result. */
    static ImageDataPtr executeHandle(const std::string & name, const ImageDataPtr src1, const ImageDataPtr src2);

    /** @brief Handle one or two IplImage
        @param ImageDataPtr src1  : first image
        @param ImageDataPtr src2 : second image, NULL if unused
        @return ImageDataPtr : handle's result.
      */
    virtual ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2) = 0;

protected :

private:
    /** @brief Handle's name<br/>
        Thanks this, you can get this handle only with his name. */
    const std::string m_name;

    typedef std::map< std::string, VirtualHandle * > ListHandle;

    /** @brief Every handle will be registred in this.<br/>
    So we can call any handle process only with his name.*/
    static ListHandle m_listHandle;
};

const std::string & VirtualHandle::getName(void)
{
    return m_name;
}

#endif // VIRTUALHANDLE_H
