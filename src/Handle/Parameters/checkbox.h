#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QMap>
#include <QString>
#include <QObject>
#include <QVariant>
#include <QStringList>

#include "sourceparameters.h"

class QFrame;
class QCheckBox;


/** @brief QCheckBox set used as SourceParameters. */
class CheckBox : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    /** @brief Type for CheckBox' value */
    typedef QMap<QString, QVariant> Value;


    /** @brief Build a CheckBox SourceParameters.
    **  @param const QString & label : Label
    **  @param const QStringList & boxes : label for each QCheckBox, determine the number of QCheckBox to print.
    **  @param const QStringList & defaultChecked = QStringList() : QCheckBox's label which is selected
        by default.
    */
    CheckBox(const QString & label, const QStringList & boxes,
             const QStringList & defaultChecked = QStringList() );

    virtual ~CheckBox(){}

    /** @brief Add a CheckBox' suscriber. The suscribers' value will be changed when the CheckBox
        's value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        CheckBox.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Change the CheckBox's value for one QCheckBox.
    **  @brief const QString & txt : QCheckBox' label.
    **  @brief bool  value : if we want to check it or not. */
    virtual void changeValue(const QString & txt, bool  value);


    /** @brief Hide the parameters */
    virtual void hideParameters(void);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);
private slots :


    /** @brief Emitted when the CheckBox' value is changed ie when we check or uncheck a QCheckBox. */
    void changeValue(bool);
private :

    /** @brief QCheckBox used and shown. */
    QList<QCheckBox *> m_checkboxs;


    /** @brief Internal QFrame where we will show the QCheckBox. */
    QFrame * m_frame;


    /** @brief CheckBox' value.
    **
    **  For each QCheckBox we match the QCheckBox's Label and its value (checked or unchecked).
    */
    Value m_values;
};

#endif // CHECKBOX_H
