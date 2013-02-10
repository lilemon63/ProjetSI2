#ifndef SLIDDER_H
#define SLIDDER_H

#include<QSlider>
#include <QObject>

#include "sourceparameters.h"

/** @brief Slidder used as SourceParameters */
class Slider : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public :
    Slider();

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~Slider(){}

private :
    QSlider m_slider;
private slots :
    void changeValue(int);
};

#endif // SLIDDER_H
