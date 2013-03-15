#ifndef SPINBOX_H
#define SPINBOX_H

#include <QObject>

#include "sourceparameters.h"

class QSpinBox;


/** @brief QSpinBox used as SourceParameters */
class SpinBox : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public:
    /** @brief Type for the SpinBox' value */
    typedef int Value;

    /** @brief Build a SpinBox SourceParameters.
    **  @param const QString & label = QString() : Label.
    **  @param int defaultValue = 0 : default value.
    **  @param int min = 0 : minimal value.
    **  @param int max = 100 : maximal value.
    */
    SpinBox(const QString & label = QString(), int defaultvalue = 0, int min = 0, int max = 100 );

    virtual ~SpinBox(){}


    /** @brief Add a SpinBox's suscriber. The suscribers' value will be changed when the SpinBox's
        value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        SpinBox.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters. */
    virtual void hideParameters(void);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);
private slots :
    /** @brief Update all suscribers with the new value.
    **  @param int : new value.
    */
    void changeValue(int);
private :
    /** @brief Internal gui element */
    QSpinBox * m_spinbox;
};

#endif // SPINBOX_H
