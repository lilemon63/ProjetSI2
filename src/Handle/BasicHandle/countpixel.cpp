#include "countpixel.h"
#include "../Parameters/inputtext.h"

CountPixel::CountPixel(const QString & affName, const std::string & name)
    : VirtualHandle(affName, name)
{
    m_listParameters.resize(MAX);
    m_listParameters[SCRIPT] = HandleParameters::build_inputtext("Condition");
    m_listParameters[NAME] = HandleParameters::build_inputtext("Resultat name");
}

ImageDataPtr CountPixel::startHandle(ImageDataPtr src1, const ImageDataPtr)
{
    QScriptEngine engine;
    QString query = m_listParameters[SCRIPT]->toString();

    unsigned long long int total = 0;

    //debut

    query.replace("Gr","45");
    query.replace("B", "4");
    query.replace("G", "3");
    query.replace("R", "5");
    if( ! engine.canEvaluate(query) )
        std::cerr << "can't evaluate" << std::endl;
    QScriptValue value = engine.evaluate(query);

    total += value.toBool();

    //fin

    //TODO

    return src1;
}
