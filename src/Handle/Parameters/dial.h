#ifndef DIAL_H
#define DIAL_H

#include <QObject>

#include "sourceparameters.h"

class QDial;
class QFrame;
class QLabel;
class QLineEdit;

/** @brief QDial used as SourceParameters. */
class Dial : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    /** @brief Helper.
    **
    **  An Helper is a gui element with help user to enter a value.
    */
    enum Helper  {
        /** @brief No Helper used */
        None,
        /** @brief Print the current value */
        PrintValue,
        /** @brief The user can edit the value in an input text */
        EnterValue};

    /** @brief Type for Dial's value. */
    typedef int Value;

    /** @brief Build a Dial SourceParameters.
    **  @param const QString & label : Label
    **  @param const int defaultAngle = 0 : default value.
    **  @param int min = 0 : minimal value.
    **  @param int max = 360 : maximal value.
    **  @param Helper = EnterValue : Helper used.
    */
    Dial(const QString & label, int defaultAngle = 0, int min = 0, int max = 360, Helper = EnterValue);


    virtual ~Dial(){}

    /** @brief Add a Dial's suscriber. The suscribers' value will be changed when the Dial
        's value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        ComboBox.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters */
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

    /**  @brief Internal gui element */
    QDial * m_dial;

    /**  @brief Input text used as Helper::EnterText */
    QLineEdit * m_inputText;

    /** @brief Internal QFrame where we will show the Dial. */
    QFrame * m_frame;

    /**  @brief Label used as Helper::PrintText */
    QLabel * m_label;
};

#endif // DIAL_H
