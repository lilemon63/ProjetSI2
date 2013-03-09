#include<QtScript>

#include "editchannel.h"

EditChannel::EditChannel(const QString & affName, const std::string & name)
    : VirtualHandle(affName, name)
{
    m_listParameters.resize(MAX);
    m_listParameters[SCRIPT_R] = HandleParameters::build_inputtext("R", "R");
    m_listParameters[SCRIPT_G] = HandleParameters::build_inputtext("G", "G");
    m_listParameters[SCRIPT_B] = HandleParameters::build_inputtext("B", "B");
}

ImageDataPtr EditChannel::startHandle(ImageDataPtr src1, const ImageDataPtr)
{
    QScriptEngine engine;
    QString OriginalQueries[3] = { m_listParameters[SCRIPT_R]->toString(),
                                 m_listParameters[SCRIPT_G]->toString(),
                                 m_listParameters[SCRIPT_B]->toString() };

    auto lambda = [&OriginalQueries, &engine](unsigned char & r,
                                            unsigned char & b,
                                            unsigned char & g)
    {
        QString gr = QString::number(0.33*b + 0.56*g + 0.11*r);
        QString red = QString::number(r);
        QString green = QString::number(g);
        QString blue = QString::number(b);
        QString queries[3] = OriginalQueries;
        for( QString & query : queries )
        {
            query.replace("Gr",  gr);        query.replace("B", blue );
            query.replace("G", green );          query.replace("R", red );
        }
        if( engine.canEvaluate(queries[0]) )
            r = engine.evaluate(queries[0]).toInteger();
        if( engine.canEvaluate(queries[1]) )
            g = engine.evaluate(queries[1]).toInteger();
        if( engine.canEvaluate(queries[2]) )
            b = engine.evaluate(queries[2]).toInteger();
    };

    src1->forEachPixel( lambda );

    return src1;
}
