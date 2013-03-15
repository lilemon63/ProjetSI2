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

/** @brief VirtualHandle's parameters' Spoiler
**
** Used to hide and show VirtualHandle's parameters when the user click on it.
** @warning Do not inherint of it.
*/
class Spoiler : public QWidget //final
{
    Q_OBJECT
public:
    /** @brief Build and initialize a new Spoiler. */
    Spoiler();

    Spoiler( const Spoiler & ) = delete;
    Spoiler & operator=( const Spoiler & ) = delete;


    /** @brief Change the shown name.
    **
    **  Concat the Numbering's text and the VirtualHandle's shown name.
    **  @param const QString & affname : VirtualHandle's name to show.
    **  @param Numbering & num : Numbering to use.
    */
    void changeAffName( const QString & affname, Numbering & num);


    /** @brief Hide the spoiler. */
    void hideAll();


    /** @brief Hide the spoiler content but doesn't hide the spoiler */
    virtual void hideParameters(void);


    /** @brief Set the parameters into the spoiler.
    **
    **  @param const VirtualHandle::ListParameters & listParameters : VirtualHandle's parameters.
    **  @param std::shared_ptr<HandleParameters> viewParam : VirtualHandle's checkbox for the "Vue active"
        ( VirtualHandle::m_viewParameters ).
    **  @param const VirtualHandle::ListDependancies & dependancies : VirtualHandle's dependancies.
    **  @param const QString & name : VirtualHandle's shown name.
    **  @param QWidget * parent : QWidget in which the spoiler will be shown.
    **  @param Numbering & num : VirtualHandle's Numbering.
    */
    void setParam(const VirtualHandle::ListParameters & listParameters,
                  std::shared_ptr<HandleParameters> viewParam,
                  const VirtualHandle::ListDependancies & dependancies,
                  const QString & name, QWidget * parent,
                  Numbering & num);


    /** @brief Show the spoiler. */
    void showAll();


    /** @brief Show the spoiler content.
    **  @param parent : QWidget on which the spoiler will be shown.
    */
    virtual void showParameters(QWidget * parent);


    /** @brief Widget in which we will shown the Spoiler content. */
    QWidget * widget(void);

public slots:
    /** @brief Called when the user click on the spoiler.
    **
    **  Hide the spoiler content or show it according if the content spoiler is show or hide.
    */
    void whenClicked();
private:
    /** @brief Spoiler's button, show the Numbering text and the VirtualHandle shown name.
    **
    **  When clicked, call whenClicked().
    */
    QPushButton *m_button;


    /** @brief Spoiler's button, show an icon.
    **
    **  When clicked, call whenClicked().
    */
    QPushButton *m_button_icon;

    /** @brief QFrame where the spoiler content will be shown */
    QFrame *m_frame;


    /** @brief If the spoiler content is visible or not.
    **  @todo we can replace it by m_frame->isVisible(). */
    bool m_hiden = true;


    /** @brief Frame for the spoiler's header.
    **
    **   Contain m_button and m_button_icon.
    */
    QFrame * m_title;
};

#endif // SPOILER_H
