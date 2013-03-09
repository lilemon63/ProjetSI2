#include "putyourcodehere.h"
#include "Parameters/handleparameters.h"

PutYourCodeHere::PutYourCodeHere()
    : VirtualHandle("PutYourCodeHere","PutYourCodeHere") //handle's name
{
    m_listParameters.resize(MAX);

    m_listParameters[COLOR] = HandleParameters::build_colorselection("Nothing");
    m_listParameters[INPUT] = HandleParameters::build_inputtext("Nothing", "Bonjour");
    m_listParameters[CHECK] = HandleParameters::build_checkbox("Nothing", QStringList({"ee","gg"}) );

    m_dependancies.reserve(2);
    m_dependancies.push_back( VirtualHandle::getHandleForDependancies("Rotation") ); //add dependancies
    m_dependancies.push_back( VirtualHandle::getHandleForDependancies("ToVideo") );
}

// your handle
ImageDataPtr PutYourCodeHere::startHandle(ImageDataPtr source, const ImageDataPtr source1)
{
    //put your code here !
    ImageDataPtr result = executeHandle("Rotation", source, source1);

    return executeHandle("ToVideo", result, nullptr);
}
