#ifndef MDI_H
#define MDI_H

#include <set>
#include <QMdiArea>

class MainWindow;
class SubMdiWindows;


/** @brief QMdiArea which contains SubMdiWindows.
**  @warning do not inherit of it.
*/
class Mdi : public QMdiArea //final
{
    Q_OBJECT
public:
    /** @brief Build and initialize a Mdi.
    **  @param QWidget *parent = 0 : Mdi's parent.
    */
    explicit Mdi(QWidget *parent = 0);

    Mdi(const Mdi &) = delete;
    Mdi & operator=(const Mdi &) = delete;


    /** @brief Add a QWidget into the Mdi.
    **
    **  If the QWidget given is also a SubMdiWindows, we will execute some connects.
    **  @param QWidget *widget : widget to add.
    **  @param Qt::WindowFlags flags = 0 : widget's flag.
    */
    void addSubWindow(QWidget *widget, Qt::WindowFlags flags = 0);


    /** @brief Reduct all SubMdiWindows except the specified one.
    **
    **  Used for exemple by MainWindows to enter in the Default mode, it reduce all SubMdiWindows except
    **  the 4 mains.
    **  @param const std::set<SubMdiWindows *> & : specified SubMdiWindows.
    */
    void reductAllExcept( const std::set<SubMdiWindows *> &);


    /** @brief Set the MainWindows to use.
    **  @param MainWindow * : used MainWindows.
    */
    void setMainWindow(MainWindow * );

signals:
    /** @brief emit when the Mdi is resized.
    **
    **  If we are in default mode, the SubMdiWindows will be resized and we didn't go out the default
        mode.
    */
    void onResize(void);

protected :
    /** @brief Called when there is a resize event.
    **
    **  emit the onResize() signal.
    **  @param QResizeEvent *resizeEvent : resize event.
    */
    void resizeEvent(QResizeEvent *resizeEvent);

private :
    /** @brief Used MainWindows. */
    MainWindow * m_mainWindow;
};

#endif // MDI_H
