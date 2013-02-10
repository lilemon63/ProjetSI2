#include "putyourcodehere.h"
#include "Parameters/slider.h"


PutYourCodeHere::PutYourCodeHere()
    : VirtualHandle("PutYourCodeHere") //handle's name
{
    HandleParameters param;
    param.changeSources( std::shared_ptr<SourceParameters>(new Slider() ) );
    m_listParameters.push_back( param );
}

// your handle
ImageDataPtr PutYourCodeHere::startHandle(const ImageDataPtr source, const ImageDataPtr)
{
    //put your code here !
    return source;
}
