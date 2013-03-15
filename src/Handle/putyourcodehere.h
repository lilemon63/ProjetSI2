#ifndef PUTYOURCODEHERE_H
#define PUTYOURCODEHERE_H

#include "virtualhandle.h"


/** @brief Put your code here
    @see ModelHandle */
class PutYourCodeHere : VirtualHandle
{
    /** @brief We use enum to identify the HandleParameters in the HandleParameters' list. */
   enum PARAM_ID{ COLOR, INPUT, CHECK,
         /** @brief This value is used to determinate the HandleParameters' list's size.
         **  @warning Put "MAX" at the end and to not forgent an HandleParameters and do not add other values.
         */
         MAX }; // Parameter's identifiant
public:
   /** @brief Initialize your VirtualHandle
    **
    **  Example :
    **  @code
    **  PutYourCodeHere::PutYourCodeHere()
    **     : VirtualHandle("PutYourCodeHere","PutYourCodeHere") //set the handle's name and the printed name
    **  {
    **      m_listParameters.resize(MAX);
    **      // add a ColorSelection into the parameters
    **      m_listParameters[COLOR] = HandleParameters::build_colorselection("Nothing");
    **      // add an InputText into the parameters
    **      m_listParameters[INPUT] = HandleParameters::build_inputtext("Nothing", "Bonjour");
    **
    **      m_dependancies.reserve(2); //for optimization, 2 is the number of used VirtualHandle in your code.
    **      //add the VirtualHandle named "Rotation" in the dependancies
    **      m_dependancies.push_back( VirtualHandle::getHandleForDependancies("Rotation") );
    **      //add the VirtualHandle named "Rotation" in the dependancies
    **      m_dependancies.push_back( VirtualHandle::getHandleForDependancies("ToVideo") );
    **  }
    **  @endcode
    **  The dependancies list is used to print the VirtualHandle's parameters in the parameters's view. If you
    **  don't want to print the VirtualHandle's parameters, do not add it in the dependancies.
    */
    PutYourCodeHere();

protected :
    /** @brief Handle one or two IplImage
    **
    **  You can put what you want in this.
    **
    **
    **  Example :
    **  @code
    **  ImageDataPtr PutYourCodeHere::startHandle(ImageDataPtr source, ImageDataPtr source1)
    **  {
    **      ImageDataPtr result = executeHandle("Rotation", source, source1); //rotate the image
    **
    **      return executeHandle("ToVideo", result, nullptr); //save the image in a video
    **  }
    **  @endcode
    **  @warning Do not forget to return a result, else an exception may be thrown.
    **  @param ImageDataPtr src1  : first image
    **  @param ImageDataPtr src2 : second image, nullptr if unused
    **  @return ImageDataPtr : handle's result.
    */
    virtual ImageDataPtr startHandle(ImageDataPtr src1, ImageDataPtr src2);
};

#endif // PUTYOURCODEHERE_H
