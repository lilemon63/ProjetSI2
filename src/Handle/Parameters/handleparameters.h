#ifndef HANDLEPARAMETERS_H
#define HANDLEPARAMETERS_H

#include <QColor>
#include <memory>
#include <QVariant>
#include <functional>

#include "inputtext.h"

class SourceParameters;

/** @brief Parameters for VirtualHandle
**
**  @warning Do not inherint of it.
**  @todo create the method build_inputstexts().
**  @todo create the method build_progressBar().
*/
class HandleParameters final : public QVariant
{
public:
    /** @brief Create an HandleParameters*/
    explicit HandleParameters(void);

    HandleParameters( const HandleParameters & ) = delete;
    HandleParameters & operator=( const HandleParameters & ) = delete;
    ~HandleParameters(void);

    /** @brief In the function executed when the value change, accept the new value.
    **  @warning Call it only in the function you set thanks to setActionOnChangeValue().
    **  @warning If you don't call this method, the value will not be updated.
    **  @param QVariant value : new value.
    */
    void acceptChanges(QVariant value);

    /**  @brief Return an HandleParameters in which the SourceParameters is a CheckBox.
    **  @param const QString & label : Label
    **  @param const QStringList & boxes : label for each QCheckBox, determine the number of QCheckBox to print.
    **  @param const QStringList & defaultChecked = QStringList() : QCheckBox's label which is selected
        by default.
    **  @todo add the last parameters.
    */
    static std::shared_ptr<HandleParameters> build_checkbox(const QString & label,
                                                            const QStringList & boxes = QStringList() );


    /**  @brief Return an HandleParameters in which the SourceParameters is a ColorSelection.
    **  @param const QString & label : Label
    **  @param const QColor& = QColor(255,0,0) : default value.
    */
    static std::shared_ptr<HandleParameters> build_colorselection(const QString & label,
                                                                  const QColor& = QColor(255,0,0));


    /** @brief Return an HandleParameters in which the SourceParameters is a ComboBox.
    **  @param const QString & label : Label
    **  @param const QStringList & choices = QStringList() : value which the user can choose.
    **  @param const QString & defaultValue = QString() : default value
    */
    static std::shared_ptr<HandleParameters> build_comboBox(const QString & label,
                                                            const QStringList & choices = QStringList(),
                                                            const QString & defaultValue = QString() );


    /** @brief Return an HandleParameters in which the SourceParameters is a ComboBox.
    **  @param const QString & label : Label
    **  @param const int defaultAngle = 0 : default value.
    **  @param int min = 0 : minimal value.
    **  @param int max = 360 : maximal value.
    **  @param Helper = EnterValue : Helper used.
    **  @todo Add the last parameters
    */
    static std::shared_ptr<HandleParameters> build_dial(const QString & label, int defaultAngle = 0);


    /** @brief Return an HandleParameters in which the SourceParameters is an InputText.
    **  @param const QString & label = QString() : Label.
    **  @param const QString &defaultValue = QString() : default value.
    **  @param Helper= None : Helper used.
    */
    static std::shared_ptr<HandleParameters> build_inputtext(const QString & label = QString(),
                                                             const QString &defaultValue = QString(),
                                                             InputText::Helper helper = InputText::None);


    /** @brief Return an HandleParameters in which the SourceParameters is a RadioButton.
    **  @param const QString & label : Label.
    **  @param const QStringList & boxes : list of all possible value/options.
    **  @param const QString & defaultValue = "" : the default value.
    */
    static std::shared_ptr<HandleParameters> build_radiobutton(const QString & label,
                                                               const QStringList & boxes = QStringList() );


    /** @brief Return an HandleParameters in which the SourceParameters is a Slider.
    **  @param const QString & label = QString() : Label.
    **  @param int defaultValue = 0 : default value.
    **  @param int min = 0 : minimal value.
    **  @param int max = 100 : maximal value.
    **  @param Helper helper = EnterValue : Helper to use.
    **  @todo add the Helper to the values.
    */
    static std::shared_ptr<HandleParameters> build_slider( const QString & label, int defaultValue = 0,
                                                           int min = 0, int max = 100);


    /** @brief Return an HandleParameters in which the SourceParameters is a SpinBox.
    **  @param const QString & label = QString() : Label.
    **  @param int defaultValue = 0 : default value.
    **  @param int min = 0 : minimal value.
    **  @param int max = 100 : maximal value.
    **  @todo add the other parameters.
    */
    static std::shared_ptr<HandleParameters> build_spinbox(const QString & label = QString() );

    /** @brief Change the current SourceParameters.
    **
    **  If you want to remove the last SourceParameters without add a new SourceParameters, give nullptr in
        arguments.
    **  @param SourceParameters * m_source : new SourceParameters or nullptr.
    */
    void changeSources(SourceParameters * source);


    /** @brief Hide the SourceParameters.  */
    void hideParameters(void);


    /** @brief Change the function called when the HandleParameters' value change.
    **  @param std::function<void(QVariant, HandleParameters *)> fct : new called function.
    */
    void setActionOnChangeValue(std::function<void(QVariant, HandleParameters *)> fct);


    /** @brief Change the HandleParameters' value.
    **
    **  Called by SourceParameters when the value change, update the HandeParameters or call the function
    **  specified by setActionOnChangeValue().
    **  @param const T & value : new value.
    */
    template<typename T>
    void setValue(const T & value);

    /** @brief Show the SourceParameters
    **  @param QWidget * parent : Widget where the SourceParameters will be shown.
    */
    void showParameters(QWidget * parent);

private :
    /** @brief function called when the HandleParameters' value change */
    std::function<void(QVariant, HandleParameters *)> m_lambda;

    /** @brief HandleParameters' SourceParameters. */
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
