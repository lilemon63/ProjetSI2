#ifndef HANDLEPARAMETERS_H
#define HANDLEPARAMETERS_H

#include <QVariant>
#include <memory>
#include <iostream>

class SourceParameters;

/** @brief Parameters for VirtualHandle */
class HandleParameters : public QVariant
{
public:
    /** @brief Create an HandleParameters*/
    explicit HandleParameters(void);

    ~HandleParameters(void);


    /** @brief Show the Parameters on the parameters' area
        @param QWidget * parent : parent */
    void showParameters(QWidget * parent);

    /** @brief Hide the Parameters on the parameters' area  */
    void hideParameters(void);


    /** @brief Change the source
        @param SourceParameters * m_source : */
    void changeSources(std::shared_ptr<SourceParameters> source);
    
private :
    /** @brief HandleParameters' Source */
    std::shared_ptr<SourceParameters> m_source;

    /** @brief copy is forbidden */
    HandleParameters(const HandleParameters &) : QVariant(0) {};

    /** @brief copy is forbidden */
    const HandleParameters & operator=(const HandleParameters &){ return *this; };
    
};

#endif // HANDLEPARAMETERS_H
