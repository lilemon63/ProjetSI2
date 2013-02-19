#ifndef VIRTUALHANDLE_H
#define VIRTUALHANDLE_H

#include <string>
#include <map>
#include <opencv2/opencv.hpp>
#include "imagedata.h"
#include "Parameters/handleparameters.h"
#include "Parameters/checkbox.h"
#include "../View/mdi.h"
#include "imagedata.h"

class SubMdiWindowsImage;

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
      @param const std::string & name  = "noname": handle's name. */
    VirtualHandle(const std::string & name  = "noname");

    ~VirtualHandle(void){};

    /** @brief Get the handle's name.
      @return const std::string & : handle's name */
    inline const std::string & getName(void);

    /** @brief execute the handle's startHandle() of the handle which name is given in parameters.
    @param const std::string & name : handle's name
    @param ImageDataPtr src1  : first image
    @param ImageDataPtr src2 : second image, NULL if unused
    @return ImageDataPtr : handle's result. */
    static ImageDataPtr executeHandle(const std::string & name, ImageDataPtr src1, const ImageDataPtr src2);

    /** @brief Handle one or two IplImage
        @param ImageDataPtr src1  : first image
        @param ImageDataPtr src2 : second image, NULL if unused
        @return ImageDataPtr : handle's result.
      */
    virtual ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2) = 0;

    /** @brief Show all the Parameters on the parameters' area
        @param QWidget * parent : parent */
    virtual void showParameters(QWidget * parent);

    /** @brief Show all the Parameters on the parameters' area
        @param QWidget * parent : parent
        @param const std::string & name : Handle name which will be shown */
    static void showParameters(QWidget * parent, const std::string & name);

    /** @brief Hide all the Parameters on the parameters' area<br/>
                N.B. the parameters values will be conserved for the next use. */
    virtual void hideParameters(void);

    static void hideParameters(const std::string & name);

    /** @brief Change the source for a paramters
        @param unsigned int idParameters : paramenters' identifiant, see the class documentation for more details.
        @param std::shared_ptr<SourceParameters> source : new sources
      */
    virtual void changeSource(unsigned int idParameters, SourceParameters *source);

    static QStringList getAllHandleName(void);

protected :
    typedef std::vector<std::shared_ptr<HandleParameters> > M_ListParameters;
    /** @brief List of all handle parameters */
    M_ListParameters m_listParameters;

    typedef std::vector<VirtualHandle *> M_ListDependancies;
    /** @brief All dependancies for this handle (for show parameters) */
    M_ListDependancies m_dependancies;

    VirtualHandle * getHandleForDependancies(const std::string &);

    void updateImageForView(ImageDataPtr image);

private:
    /** @brief Handle's name<br/>
        Thanks this, you can get this handle only with his name. */
    const std::string m_name;

    typedef std::map< std::string, VirtualHandle * > ListHandle;

    /** @brief Every handle will be registred in this.<br/>
    So we can call any handle process only with his name.*/
    static ListHandle m_listHandle;

    // Outside the m_listParameters to allow inherited class having enum
    std::shared_ptr<HandleParameters> m_viewParameters;
    CheckBox * m_visibleCheckBox;

    void showView(bool visible);

    // videoCréée à l'occasion
    // setImage
    static Mdi * m_view;
    SubMdiWindowsImage * m_windows;
public :
    static void setView(Mdi *m_view);
    void viewClosed(void);
};

const std::string & VirtualHandle::getName(void)
{
    return m_name;
}

#endif // VIRTUALHANDLE_H
