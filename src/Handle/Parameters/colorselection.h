#ifndef COLORSELECTION_H
#define COLORSELECTION_H

#include <QColor>

#include "sourceparameters.h"

class QPushButton;


/** @brief Button which open a color selection pop-up used as SourceParameters. */
class ColorSelection : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    /** @brief Type for ColorSelection's value. */
    typedef QColor Value;

    /** @brief Build a ColorSelection SourceParameters.
    **  @param const QString & label : Label
    **  @param const QColor& = QColor(255,0,0) : default value.
    */
    ColorSelection(const QString & label, const QColor& = QColor(255,0,0) );

    virtual ~ColorSelection(){}


    /** @brief Add a ColorSelection' suscriber. The suscribers' value will be changed when the ColorSelection
        's value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        ColorSelection.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters */
    virtual void hideParameters(void);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent);
private slots :

    /** @brief Open the color selection pop-up. */
    void openPopUp(void);
private :

    /** @brief ColorSelection's value. */
    QColor m_color;

    /** @brief Button used to open the color selection pop-up. */
    QPushButton * m_button;
};

#endif // COLORSELECTION_H
