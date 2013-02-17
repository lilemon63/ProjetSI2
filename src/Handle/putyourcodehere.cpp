#include "putyourcodehere.h"
#include "Parameters/slider.h"
#include "Parameters/dial.h"


PutYourCodeHere::PutYourCodeHere()
    : VirtualHandle("PutYourCodeHere") //handle's name
{
    m_listParameters.resize(1);
    m_listParameters[0] = std::shared_ptr<HandleParameters>(new HandleParameters() );
    m_listParameters[0]->changeSources( std::shared_ptr<SourceParameters>(new Slider("Nothing") ) );

   // m_listParameters[1] = std::shared_ptr<HandleParameters>(new HandleParameters() );
   // m_listParameters[1]->changeSources( std::shared_ptr<SourceParameters>(new Dial("Rotation") ) );
}

// your handle
ImageDataPtr PutYourCodeHere::startHandle(ImageDataPtr source, const ImageDataPtr source1)
{
    executeHandle("ToFiles", source, source1);
    //put your code here !
    return source;
}
