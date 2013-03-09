#ifndef SLIDDER_H
#define SLIDDER_H

#include <QObject>

#include "sourceparameters.h"

class QFrame;
class QLabel;
class QString;
class QSlider;
class QLineEdit;

/** @brief Slidder used as SourceParameters */
class Slider : public QObject, public SourceParameters
{
    Q_OBJECT;
public:
    enum Helper {None, PrintValue, EnterValue};

    Slider( const QString & label = QString(), int defaultValue = 0, int min = 0, int max = 100,
            Helper helper = EnterValue);
    virtual ~Slider();

    virtual void addSuscriber(HandleParameters * target);
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);

private slots :
    void changeValue(void);
    void changeValue(int);
private :
    QFrame * m_frame;
    QLineEdit * m_inputText;
    QLabel * m_label;
    QSlider * m_slider;
};

#endif // SLIDDER_H
