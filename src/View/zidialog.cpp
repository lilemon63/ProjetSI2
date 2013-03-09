#include <QCloseEvent>

#include "zidialog.h"

ZIDialog::ZIDialog(QWidget *parent) :
    QDialog(parent)
{
}

void ZIDialog::closeEvent(QCloseEvent *closeEvent)
{
    emit onClose();
    closeEvent->accept();
}
