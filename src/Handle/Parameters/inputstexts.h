#ifndef INPUTSTEXTS_H
#define INPUTSTEXTS_H

#include <map>
#include <QObject>
#include <QStringList>

#include "sourceparameters.h"

class QFrame;
class QLineEdit;


/** @brief Many QLineEdit used as SourceParameters. */
class InputsTexts : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    /** @brief Type for InputsTexts' value. */
    typedef QStringList Value;


    /** @brief Build an InputsTexts SourceParameters.
    **  @param const QString & label : Label
    **  @param unsigned int number = 2 : number of QLineEdit used.
    **  @param const QStringList &defaultValue = QStringList() : Default value.
    */
    explicit InputsTexts(const QString & label = QString(), unsigned int number = 2,
                         const QStringList &defaultValue = QStringList());

    virtual ~InputsTexts();


    /** @brief Add a InputsTexts' suscriber. The suscribers' value will be changed when the InputsTexts'
        value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        InputsTexts.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Change the value for one of the QLineEdit used.
    **  @param const QString & newValue : new value.
    **  @param int id : QLineEdit's number. 0 for the first, N - 1 for the QLineEdit N.
    */
    virtual void changeValue( const QString & newValue, int id );


    /** @brief Hide the parameters */
    virtual void hideParameters(void);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);

private slots :

    /** @brief Call when the value is changed, update all suscribers with the new value. */
    void valueChanged(void);
private :

    /** @brief Match all QLineEdit with an identifiant, 0 for the first, N-1 for the QLineEdit N */
    std::map<QLineEdit *, int> m_ids;


    /** @brief All used QLineEdit. */
    QLineEdit ** m_inputText;


    /** @brief Internal QFrame where we will show the InputsTexts. */
    QFrame * m_frame;


    /** @brief InputsTexts' value. */
    QStringList m_values;
};

#endif // INPUTSTEXTS_H
