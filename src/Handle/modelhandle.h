#ifndef MODELHANDLE_H
#define MODELHANDLE_H

//you must include this header
#include "Handle.h"

/** @brief model for create a new VirtualHandle. */
class ModelHandle : public VirtualHandle //all handle must herit from VirtualHandle
{
public:
    /** @brief Create a new ModelHandle
    **
    ** A ModelHandle is an VirtualHandle test which explain how write his own handle class.
    */
    ModelHandle(void);
protected :
    /** @brief Process one or two IplImage
    **
    **  An ModelHandle's startHandle() will call startHandle one more time.
    **  @param ImageDataPtr src1  : first image
    **  @param ImageDataPtr src2 : second image, nullptr if unused
    **  @return ImageDataPtr : handle's result.
    */
    virtual ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr src2);

    /** @brief For exemple */
    int tour;
};

#endif // MODELHANDLE_H
