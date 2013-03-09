#ifndef ZIDIALOG_H
#define ZIDIALOG_H

#include <QDialog>

class ZIDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ZIDialog(QWidget *parent = 0);
    ZIDialog( const & ZIDialog ) = delete;
    ZIDialog & operator=( const & ZIDialog ) = delete;
    virtual ~ZIDialog(void){}
private :
    void closeEvent(QCloseEvent *closeEvent);
signals:
    void onClose(void);
};

#endif // ZIDIALOG_H
