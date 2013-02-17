#ifndef HANDLEPARAMETERS_H
#define HANDLEPARAMETERS_H

#include <QVariant>
#include <memory>
#include <iostream>
#include <functional>

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
    void changeSources(SourceParameters * source);

    /** */
    void setActionOnChangeValue(std::function<void(QVariant, HandleParameters *)> fct);

    template<typename T>
    void setValue(const T & value)
    {
        if( m_lambda )
            m_lambda( QVariant(value) , this);
        else
            QVariant::setValue(value);
    }

    /** /!\ Call it only in lambda giving in setActionOnChangeValue() */
    void acceptChanges(QVariant value);
    
private :
    /** @brief HandleParameters' Source */
    SourceParameters * m_source;

    /** @brief copy is forbidden */
    HandleParameters(const HandleParameters &) : QVariant(0) {};

    /** @brief copy is forbidden */
    const HandleParameters & operator=(const HandleParameters &){ return *this; };

    std::function<void(QVariant, HandleParameters *)> m_lambda;
    
};

#endif // HANDLEPARAMETERS_H
