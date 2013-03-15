#ifndef ZIDIALOG_H
#define ZIDIALOG_H

#include <QDialog>


/** @brief Dialog shown to ask to the user parameters about a new created ZI. */
class ZIDialog : public QDialog
{
    Q_OBJECT
public:
    /** @brief Build a ZIDialog.
    **  @param QWidget *parent = 0 : ZIDialog's parent.
    */
    explicit ZIDialog(QWidget *parent = 0);

    ZIDialog( const ZIDialog & ) = delete;
    ZIDialog & operator=( const ZIDialog &) = delete;
    virtual ~ZIDialog(void){}
private :
    /** @brief Process close event.
    **  @param QCloseEvent *closeEvent : close event.
    */
    void closeEvent(QCloseEvent *closeEvent);
signals:
    /** @brief Emitted when closed. */
    void onClose(void);
};

#endif // ZIDIALOG_H
