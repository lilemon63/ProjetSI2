#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include <QObject>

#include "sourceparameters.h"

class QFrame;
class QLineEdit;
class QProgressBar;

/** @brief QLineEdit used as SourceParameters.
**
**  @note Close a spoiler when we have the focus on a QLineEdit will emit a finishEditing(),
**  we will consider the value was changed.
*/
class InputText : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    /** @brief Helper.
    **
    **  An Helper is a gui element with help user to enter a value.
    */
    enum Helper{
        /** No Helper used. */
        None,
        /** A button will be used to open a Folder selector pop-up. */
        Directory,
        /** A button will be used to open a file selector pop-up. */
        SaveFile,
        /** A button will be used to open an existant file selector pop-up. */
        OpenFile};


    /** @brief Type for InputText's value. */
    typedef QString Value;

    /** @brief Build an InputText SourceParameters.
    **  @param const QString & label = QString() : Label.
    **  @param const QString &defaultValue = QString() : default value.
    **  @param Helper= None : Helper used.
    */
    explicit InputText(const QString & label = QString(),
                       const QString &defaultValue = QString(),
                       Helper= None);

    virtual ~InputText(){}


    /** @brief Add an InputText's suscriber. The suscribers' value will be changed when the InputText's
        value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        InputText.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters */
    virtual void hideParameters(void);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);
private slots :
    /** @brief Open the current Helper pop-up */
    void openPopUp(void);

    /** @brief Called when the value is changed, update all suscribers with the new value. */
    void valueChanged(void);
private :
    /** @brief Internal gui element */
    QLineEdit * m_inputText;


    /** @brief Internal QFrame where we will show the InputsTexts. */
    QFrame * m_frame;


    /** @brief Used Helper */
    Helper m_helper;
};

#endif // INPUTTEXT_H
