#ifndef SPOILER_H
#define SPOILER_H

#include <QWidget>

#include "../virtualhandle.h"

class QLabel;
class QFrame;
class Numbering;
class QPushButton;
class QHBoxLayout;
class HandleParameters;
class SourceParameters;

/**
* @class Spoiler
* Used to spoil an handler
*/
class Spoiler : public QWidget //final
{
    Q_OBJECT
public:
    /**
* @brief Constructor
*/
    Spoiler();
    Spoiler( const Spoiler & ) = delete;
    Spoiler & operator=( const Spoiler & ) = delete;

    void changeAffName( const QString & affname, Numbering & num);
    /**
    * @brief Used to hide all HandlerParameters of a Virtual Handle
    */
    void hideAll();

    virtual void hideParameters(void);

    void setParam(const VirtualHandle::ListParameters & listParameters, std::shared_ptr<HandleParameters> viewParam,
                  const VirtualHandle::ListDependancies & dependancies,const QString & name, QWidget * parent,
                  Numbering & num);
    /**
    * @brief Used to show again all HandlerParameters of a Virtual handle
    * @param parent : Widget on which they'll be show
    */
    void showAll();
    virtual void showParameters(QWidget * parent);

    QWidget * widget(void);
public slots:
    void whenClicked();
private:
    QPushButton *m_button,*m_button_icon;
    QFrame *m_frame;
    bool m_hiden = true;
    QHBoxLayout *m_layout;
    QFrame * m_title;
};

#endif // SPOILER_H
