#include "countpixel.h"
#include "../Parameters/inputtext.h"

CountPixel::CountPixel(const QString & affName, const std::string & name)
    : VirtualHandle(affName, name)
{
    m_listParameters.resize(MAX);
    m_listParameters[SCRIPT] = HandleParameters::build_inputtext("Condition");
    m_listParameters[NAME] = HandleParameters::build_inputtext("Resultat name", "CountPixel");
}

ImageDataPtr CountPixel::startHandle(ImageDataPtr src1, const ImageDataPtr)
{
    QScriptEngine engine;
    QString originalQuery = m_listParameters[SCRIPT]->toString();

    unsigned long long int total = 0;

    auto lambda = [&total, &originalQuery, &engine](unsigned char & r, unsigned char & b, unsigned char & g)
    {
        QString query = originalQuery;
        query.replace("Gr", QString::number(0.33*b + 0.56*g + 0.11*r) );
        query.replace("B", QString::number(b) );
        query.replace("G", QString::number(g) );
        query.replace("R", QString::number(r) );
        if( ! engine.canEvaluate(query) )
            total = -1;
        QScriptValue value = engine.evaluate(query);

        total += value.toBool();
    };
    src1->forEachPixel( lambda);
    /* IplImage * source = src1->getImage();
    for( char * line = source->imageData;
         line < source->imageData + source->imageSize;
         line += source->widthStep)
    {
        for( char * p = line;
             p - line < source->width * source->nChannels;
             p += source->nChannels )
        {
            query.replace("Gr", QString::number(0.33*p[0] + 0.56*p[1] + 0.11*p[2]) );
            query.replace("B", QString::number(p[0]) );
            query.replace("G", QString::number(p[1]) );
            query.replace("R", QString::number(p[2]) );
            if( ! engine.canEvaluate(query) )
                total = -1;
            QScriptValue value = engine.evaluate(query);

            total += value.toBool();
        }
    } */

    src1->addResults( m_listParameters[NAME]->toString(), total);

    return src1;
}
