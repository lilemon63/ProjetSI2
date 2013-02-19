#ifndef SLIDDER_H
#define SLIDDER_H

#include<QSlider>
#include <QObject>
#include <QString>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include "sourceparameters.h"

/** @brief Slidder used as SourceParameters */
class Slider : public QObject, public SourceParameters
{
public:
    enum Helper {None, PrintValue, EnterValue};
    Q_OBJECT;
public :
    Slider( const QString & label = QString(), int defaultValue = 0, int min = 0, int max = 100,
            Helper helper = EnterValue);

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual void addSuscriber(HandleParameters * target);

    virtual ~Slider();
private :
    QSlider * m_slider;
    QFrame * m_frame;
    QLabel * m_label;
    QLineEdit * m_inputText;
private slots :
    void changeValue(int);
    void changeValue(void);
};

#endif // SLIDDER_H
