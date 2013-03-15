#ifndef SLIDDER_H
#define SLIDDER_H

#include <QObject>

#include "sourceparameters.h"

class QFrame;
class QLabel;
class QString;
class QSlider;
class QLineEdit;

/** @brief QSlider used as SourceParameters */
class Slider : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    /** @brief Helper.
    **
    **  An Helper is a gui element with help user to enter a value.
    */
    enum Helper {
        /** @brief No Helper used */
        None,
        /** @brief Print the current value */
        PrintValue,
        /** @brief The user can edit the value in an input text */
        EnterValue};


    /** @brief Build a Slider SourceParameters.
    **  @param const QString & label = QString() : Label.
    **  @param int defaultValue = 0 : default value.
    **  @param int min = 0 : minimal value.
    **  @param int max = 100 : maximal value.
    **  @param Helper helper = EnterValue : Helper to use.
    */
    Slider( const QString & label = QString(), int defaultValue = 0, int min = 0, int max = 100,
            Helper helper = EnterValue);

    virtual ~Slider();


    /** @brief Add a Slider's suscriber. The suscribers' value will be changed when the Slider's
        value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        Slider.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters. */
    virtual void hideParameters(void);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);

private slots :

    /** @brief Called when the user enter a new value thanks to the Helper::EnterValue.
    **
    **  Read the value and call changeValue(int).
    */
    void changeValue(void);

    /** @brief Update all suscribers with the new value.
    **  @param int : new value.
    */
    void changeValue(int);
private :
    /** @brief Internal QFrame where we will show the RadioButton. */
    QFrame * m_frame;


    /**  @brief Input text used as Helper::EnterText */
    QLineEdit * m_inputText;


    /** @brief Internal QFrame where we will show the Dial. */
    QLabel * m_label;

    /** @brief Internal gui element */
    QSlider * m_slider;
};

#endif // SLIDDER_H
