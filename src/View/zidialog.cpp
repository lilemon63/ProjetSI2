#include "zidialog.h"
#include <QCloseEvent>

ZIDialog::ZIDialog(QWidget *parent) :
    QDialog(parent)
{
}

void ZIDialog::closeEvent(QCloseEvent *closeEvent)
{
    emit onClose();
    closeEvent->accept();
}
