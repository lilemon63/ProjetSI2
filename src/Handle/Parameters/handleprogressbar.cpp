#include "handleprogressbar.h"

HandleProgressBar::HandleProgressBar(ProgressBar *p)
    :HandleParameters(),p(p)
{
}

void HandleProgressBar::setValue(int value)
{
    p->setValue(value);
}
