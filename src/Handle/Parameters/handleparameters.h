#ifndef HANDLEPARAMETERS_H
#define HANDLEPARAMETERS_H

#include <QColor>
#include <memory>
#include <QVariant>
#include <functional>

#include "inputtext.h"

class SourceParameters;

/** @brief Parameters for VirtualHandle */
class HandleParameters final : public QVariant
{
public:
    /** @brief Create an HandleParameters*/
    explicit HandleParameters(void);
    HandleParameters( const HandleParameters & ) = delete;
    HandleParameters & operator=( const HandleParameters & ) = delete;
    ~HandleParameters(void);

    /** /!\ Call it only in lambda giving in setActionOnChangeValue() */
    void acceptChanges(QVariant value);


    static std::shared_ptr<HandleParameters> build_checkbox(const QString & label,
                                                            const QStringList & boxes = QStringList() );
    static std::shared_ptr<HandleParameters> build_colorselection(const QString & label,
                                                                  const QColor& = QColor(255,0,0));
    static std::shared_ptr<HandleParameters> build_comboBox(const QString & label,
                                                            const QStringList & choices = QStringList(),
                                                            const QString & defaultValue = QString() );
    static std::shared_ptr<HandleParameters> build_dial(const QString & label, int defaultAngle = 0);
    static std::shared_ptr<HandleParameters> build_inputtext(const QString & label = QString(),
                                                             const QString &defaultValue = QString(),
                                                             InputText::Helper helper = InputText::None);
    static std::shared_ptr<HandleParameters> build_radiobutton(const QString & label,
                                                               const QStringList & boxes = QStringList() );
    static std::shared_ptr<HandleParameters> build_slider( const QString & label, int defaultValue = 0,
                                                           int min = 0, int max = 100);
    static std::shared_ptr<HandleParameters> build_spinbox(const QString & label = QString() );

    /** @brief Change the source
        @param SourceParameters * m_source : */
    void changeSources(SourceParameters * source);


    /** @brief Hide the Parameters on the parameters' area  */
    void hideParameters(void);


    /** */
    void setActionOnChangeValue(std::function<void(QVariant, HandleParameters *)> fct);

    template<typename T>
    void setValue(const T & value);

    /** @brief Show the Parameters on the parameters' area
        @param QWidget * parent : parent */
    void showParameters(QWidget * parent);

private :

    std::function<void(QVariant, HandleParameters *)> m_lambda;

    /** @brief HandleParameters' Source */
    SourceParameters * m_source;
};



template<typename T>
void HandleParameters::setValue(const T & value)
{
    if( m_lambda )
        m_lambda( QVariant(value) , this);
    else
        QVariant::setValue(value);
}

#endif // HANDLEPARAMETERS_H
