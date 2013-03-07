#ifndef ZIDIALOG_H
#define ZIDIALOG_H

#include <QDialog>

class ZIDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ZIDialog(QWidget *parent = 0);
private :
    void closeEvent(QCloseEvent *closeEvent);
signals:
    void onClose(void);
public slots:
    
};

#endif // ZIDIALOG_H
