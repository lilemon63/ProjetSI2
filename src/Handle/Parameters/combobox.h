#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QObject>

#include "sourceparameters.h"

class QComboBox;


/** @brief QComboBox used as SourceParameters. */
class ComboBox : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    /** @brief Type for ComboBox's value. */
    typedef QString Value;

    /** @brief Build a ComboBox SourceParameters.
    **  @param const QString & label : Label
    **  @param const QStringList & choices : value which the user can choose.
    **  @param const QString & defaultValue = QString() : default value
    */
    ComboBox( const QString & label, const QStringList & choices, const QString & defaultValue = QString() );

    virtual ~ComboBox(){}

    /** @brief Add a ComboBox's suscriber. The suscribers' value will be changed when the ComboBox
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
    /** @brief Update all suscribers with the new value.
    **  @QString newValue : new value.
    */
    void changeValue(QString newValue);
private :

    /** Internal gui object. */
    QComboBox * m_combobox;

};



#endif // COMBOBOX_H

