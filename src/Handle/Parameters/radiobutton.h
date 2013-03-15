#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QObject>

#include "sourceparameters.h"

class QFrame;
class QRadioButton;
class QButtonGroup;


/** @brief Group of QRadioButton used as SourceParameters.
**  @note The user can select only one option/QradioButton.
*/
class RadioButton : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    /** @brief Type for RadioButton's value */
    typedef QString Value;

    /** @brief Build a RadioButton SourceParameters.
    **  @param const QString & label : Label.
    **  @param const QStringList & boxes : list of all possible value/options.
    **  @param const QString & defaultValue = "" : the default value.
    */
    RadioButton(const QString & label, const QStringList & boxes, const QString & defaultValue = QString() );


    virtual ~RadioButton(){}

    /** @brief Add a RadioButton's suscriber. The suscribers' value will be changed when the RadioButton's
        value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        RadioButton.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters. */
    virtual void hideParameters(void);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);
private slots :

    /** @brief Called when the value is changed, update all suscribers with the new value. */
    void changeValue(void);
private :
    /** @brief Internal QFrame where we will show the RadioButton. */
    QFrame * m_frame;

    /** @brief Group used to contain the QRadioButton and have only one possible user choice. */
    QButtonGroup * m_group;

    /** @brief List of all used QRadioButton */
    QList<QRadioButton *> m_radiobuttons;
};

#endif // RADIOBUTTON_H
