#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QObject>

#include "sourceparameters.h"

class QProgressBar;


/** @brief QProgressBar used as SourceParameters.
**  @note This SourceParameters isn't a SourceParameters in which the user can modify the value.
*/
class ProgressBar : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    /** @brief Type for ProgressBar's value */
    typedef int Value;

    /** @brief Build a Progressbar SourceParameters.
    **  @param const QString & label = QString() : Label
    **  @todo add the maximum, the minimum and the default value into the constructor.
    */
    ProgressBar(const QString & label = QString());

    virtual ~ProgressBar();


    /** @brief Add an Progressbar's suscriber. The suscribers' value will be changed when the Progressbar's
        value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        Progressbar.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters. */
    virtual void hideParameters(void);


    /** @brief Set the maximum value.
    **  @param int max : new maximum value.
    */
    virtual void setMaximum(int max);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);

public slots:
    /** @brief Set the new ProgressBar's value.
    **  @param int number : new value. */
    virtual void setValue(int number);

    /** @brief Add to the ProgressBar's value a number.
    **  @param int number : number added to the ProgressBar's value.
    */
    virtual void addValue(int number);
signals:
    /** @brief Emitted when the ProgressBar's value changed.
    **  @warning Do not use it, use HandleParameters::setActionOnChangeValue() instead.
    **  @param int : new value.
    */
    void m_changeValue(int); //do not use it
private slots :
    /** @brief Call when the value is changed, update all suscribers with the new value.
    **  @param int : new value.
    */
    void changeValue(int);
private :
    /** @brief Internal gui element */
    QProgressBar * m_progressbar;
};

#endif // PROGRESSBAR_H
