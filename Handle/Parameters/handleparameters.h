#ifndef HANDLEPARAMETERS_H
#define HANDLEPARAMETERS_H

#include <QVariant>
#include <memory>

class SourceParameters;

/** @brief Parameters for VirtualHandle */
class HandleParameters : public QVariant
{
public:
    /** @brief Create an HandleParameters
        @param QVariant defaultValue : parameters' default value */
    explicit HandleParameters(QVariant defaultValue);

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
    
};

#endif // HANDLEPARAMETERS_H
