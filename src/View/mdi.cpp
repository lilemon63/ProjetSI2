#include "mdi.h"
#include<iostream>

Mdi::Mdi(QWidget *parent) :
    QMdiArea(parent)
{
}

void Mdi::resizeEvent(QResizeEvent *resizeEvent)
{
    QMdiArea::resizeEvent(resizeEvent);
    emit onResize();
}
