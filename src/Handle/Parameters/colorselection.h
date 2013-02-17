#ifndef COLORSELECTION_H
#define COLORSELECTION_H

#include <QPushButton>
#include <QPalette>

#include "sourceparameters.h"

class ColorSelection : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    ColorSelection(const QString & label, const QColor& = QColor(255,0,0));
    virtual void showParameters(QWidget * parent);
    virtual void hideParameters(void);
    virtual void addSuscriber(HandleParameters * target);
private slots :
    void openPopUp(void);
private :
    QPushButton * m_button;
    QColor m_color;
};

#endif // COLORSELECTION_H
