#ifndef COLORSELECTION_H
#define COLORSELECTION_H

#include <QColor>

#include "sourceparameters.h"

class QPushButton;

class ColorSelection : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    ColorSelection(const QString & label, const QColor& = QColor(255,0,0) );
    virtual ~ColorSelection(){}
    virtual void addSuscriber(HandleParameters * target);
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);
private slots :
    void openPopUp(void);
private :
    QColor m_color;
    QPushButton * m_button;
};

#endif // COLORSELECTION_H
