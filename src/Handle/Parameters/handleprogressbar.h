#ifndef HANDLEPROGRESSBAR_H
#define HANDLEPROGRESSBAR_H
#include "handleparameters.h"
#include "progressbar.h"

class HandleProgressBar : public HandleParameters
{
public:
    HandleProgressBar(ProgressBar *p);
    void setValue(int value);
    void setMaximum(int max);

private:
    ProgressBar * p;
};

#endif // HANDLEPROGRESSBAR_H
