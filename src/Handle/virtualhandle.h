#ifndef VIRTUALHANDLE_H
#define VIRTUALHANDLE_H

#include <map>
#include <QRect>
#include <string>

#include "imagedata.h"
#include "numbering.h"
#include "Parameters/handleparameters.h"


class ZI;
class Mdi;
class Spoiler;
class CheckBox;
class SubMdiWindowsImage;

/** @brief Process two ImageData and return a result as an ImageData.
**
**  The method executeHandle() will be called at each time we have new ImageData.
**
**  If you want call an VirtualHandle, include Handle.h.
**  If you want create your own Handle class, copy ModelHandle.h and ModelHandle.cpp and edit them.
**  @todo maybe we should rename VirtualHandle to VirtualProcess.
*/
class VirtualHandle
{
public:
    /** @brief Create a new VirtualHandle.
    **  @param const QString affName = "untiltled" : shown name.
    **  @param const std::string & name  = "noname": VirtualHandle's name. If the VirtualHandle have "noname"
        as name it will be considered as an unamed VirtualHandle.
    */
    VirtualHandle(const QString affName = "untiltled", const std::string & name  = "noname");


    virtual ~VirtualHandle(void){};

    VirtualHandle(const VirtualHandle &) = delete;
    VirtualHandle & operator=(const VirtualHandle &) = delete;


    /** @brief Type for the VirtualHandle's parameters' list */
    typedef std::vector<std::shared_ptr<HandleParameters> > ListParameters;


    /** @brief Type for the VirtualHandle's depandancies' list */
    typedef std::vector<VirtualHandle *> ListDependancies;


    /** @brief Create a ZI (Interest Area).
    **  @param QRect rect : rectangle which delimit the ZI area.
    */
    ZI * createZI(QRect rect);


    /** @brief Call startHandle() to proccess Images then update the view and launch ZI's process.
    **  @param ImageDataPtr src1 : Image from the first source.
    **  @param ImageDataPtr src2 : Image from the second source.
    **  @return ImageDataPtr : process and ZI result.
    */
    virtual ImageDataPtr executeHandle(ImageDataPtr src1, ImageDataPtr src2);


    /** @brief Call executeHandle() from the VirtualHandle with the giving name.
    **  @param const std::string & name : VirtualHandle's name
    **  @param ImageDataPtr src1 : Image from the first source.
    **  @param ImageDataPtr src2 : Image from the second source.
    **  @return ImageDataPtr : process and ZI result.
    */
    static ImageDataPtr executeHandle(const std::string & name, ImageDataPtr src1, ImageDataPtr src2);


    /** @brief Return a list of all named VirtualHandle.
    **  @return QStringList : list of all named VirtualHandle.
    */
    static QStringList getAllHandleName(void);


    /** @brief Get the VirtualHandle's name.
    **  @return const std::string & : VirtualHandle's name
    */
    const std::string & getName(void) const;


    /** @brief Hide all the Parameters in the parameters' area.
    **
    **  The parameters' values will be conserved for the next use.
    */
    virtual void hideParameters(void);


    /** @brief Hide all the Parameters in the parameters' area for the VirtualHandle with the given name.
    **
    **  The parameters' values will be conserved for the next use.
    **  @param const std::string & name : VirtualHandle's name
    */
    static void hideParameters(const std::string & name);


    /** @brief Set the Mdi where we will shown Images.
    **  @param Mdi * view : Mdi where we will shown Images.
    */
    static void setView(Mdi * view);

    /** @brief Show all the Parameters on the parameters' area
    **  @param QWidget * parent : parent in the parameters' area
    **  @param bool reinit = false : if we create a new Numbering (true) or if we use the saved
        Numbering (false).
    */
    virtual void showParameters(QWidget * parent, bool reinit = false);


    /** @brief Show all the Parameters on the parameters' area
    **  @param QWidget * parent : parent in the parameters' area
    **  @param Numbering : Numbering to use.
    */
    virtual void showParameters(QWidget * parent, Numbering );


    /** @brief Show all the Parameters on the parameters' area for the VirtualHandle named with the given name.
    **  @param QWidget * parent : parent in the parameters' area.
    **  @param const std::string & name : VirtualHandle's name.
    */
    static void showParameters(QWidget * parent, const std::string & name);


    /** @brief To Call when the SubMdiWindowsImage which shown the VirtualHandle's result is closed. */
    void viewClosed(void);

protected :
    /** @brief Change the shown VirtualHandle's name.
    **
    **  Used particularly by ZI.
    **  @param const QString & name : new shown name.
    */
    void changeAffName(const QString & name);


    /** @brief Change the source for a parameters.
    **  @param unsigned int idParameters : parameters' identifiant, see the class documentation of your
    **  VirtualHandle for more details.
    **  @param std::shared_ptr<SourceParameters> source : new source.
    */
    virtual void changeSource(unsigned int idParameters, SourceParameters *source);


    /** @brief Return a pointer to the VirtualHandle's name.
    **
    **  @warning : To use only for dependancies.
    **  @param const std::string & : VirtualHandle's name.
    */
    static VirtualHandle * getHandleForDependancies(const std::string &);


    /** @brief Process one or two ImageData.
    **  @param ImageDataPtr src1  : first image.
    **  @param ImageDataPtr src2 : second image, nullptr if unused.
    **  @return ImageDataPtr : process' result.
    */
    virtual ImageDataPtr startHandle(ImageDataPtr src1, ImageDataPtr src2) = 0;


    /** @brief Return the widget where the SourceParameters are shown.
    **
    **  Used to add new gui element.
    **  @return QWidget * : widget where the SourceParameters are shown.
    */
    QWidget * widget(void);
private :

    /** @brief Type to associate each named VirtualHandle to a name */
    typedef std::map< std::string, VirtualHandle * > ListHandle;

    /** @brief Type to store all VirtualHandle's ZI */
    typedef std::list<ZI *> M_ListZI;

    /** @brief Shown or hide the result Image in a SubWindows.
    **  @param bool visible : true for shown the Image, false to hide it.
    */
    void showView(bool visible);

protected :
    /** @brief All dependancies for this VirtualHandle used to show dependancies' parameters. */
    ListDependancies m_dependancies;

    /** @brief List of the VirtualHandle's parameters */
    ListParameters m_listParameters;

    /** @brief Used Numbering. */
    Numbering m_numbering;

private:
    /** @brief Shown name. */
    QString m_affName;


    /** @brief List of all named VirtualHandle parameters.
    **
    **  Used to find a VirtualHandle thanks to his name, used for exemple to execute a VirtualHandle
        with his name. */
    static ListHandle m_listHandle;


    /** @brief List of all Zi for this VirtualHandle's */
    M_ListZI m_listZI;

    /** @brief VirtualHandle's name.
    **
    ** Thanks to this, you can get this VirtualHandle only with his name.
    */
    const std::string m_name;


    /** @brief Spoiler used to show and hide paramters */
    Spoiler * m_spoiler;


    /** @brief Mdi where we will shown Images. */
    static Mdi * m_view;


    /** @brief HandleParamters used to show and hide the SubMdiWindowsImage which show the process' result. */
    std::shared_ptr<HandleParameters> m_viewParameters;

    /** @brief CheckBox used to show and hide the SubMdiWindowsImage which show the process' result. */
    CheckBox * m_visibleCheckBox;

    /** @brief SubMdiWindowsImage which show the process' result. */
    SubMdiWindowsImage * m_windows;
};

#endif // VIRTUALHANDLE_H
