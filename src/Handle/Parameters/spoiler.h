#ifndef SPOILER_H
#define SPOILER_H

#include <QObject>
#include <list>
#include "handleparameters.h"
#include "../virtualhandle.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "sourceparameters.h"
#include <string>
#include <QFrame>

class Numbering;

/**
* @class Spoiler
* Used to spoil an handler
*/
class Spoiler : public QWidget
{
    Q_OBJECT
public:
    /**
* @brief Constructor
*/
    Spoiler();

    /**
    * @brief Used to hide all HandlerParameters of a Virtual Handle
    */
    void hideAll();

    virtual void showParameters(QWidget * parent);

    virtual void hideParameters(void);

    virtual ~Spoiler(){}

    void setParam(const VirtualHandle::ListParameters & listParameters, std::shared_ptr<HandleParameters> viewParam,
                  const VirtualHandle::ListDependancies & dependancies,const QString & name, QWidget * parent,
                  Numbering & num);
    /**
    * @brief Used to show again all HandlerParameters of a Virtual handle
    * @param parent : Widget on which they'll be show
    */
    void showAll();

    void changeAffName( const QString & affname, Numbering & num);

    QWidget * widget(void);
public slots:
    void whenClicked();
private:
    QFrame *m_frame;
    QPushButton *m_button,*m_button_icon;
    QHBoxLayout *m_layout;
    QFrame * m_title;

    bool m_hiden = true;
};

#endif // SPOILER_H
