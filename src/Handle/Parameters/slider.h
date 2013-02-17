#ifndef SLIDDER_H
#define SLIDDER_H

#include<QSlider>
#include <QObject>
#include <QString>

#include "sourceparameters.h"

/** @brief Slidder used as SourceParameters */
class Slider : public QObject, public SourceParameters
{
public:
    Q_OBJECT;
public :
    Slider( QString label = QString(), int defaultValue = 0, int min = 0, int max = 100);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~Slider();
private :
    QSlider * m_slider;
private slots :
    void changeValue(int);
};

#endif // SLIDDER_H
