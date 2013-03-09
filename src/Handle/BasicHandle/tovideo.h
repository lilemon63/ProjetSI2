#ifndef TOVIDEO_H
#define TOVIDEO_H

#include<QTime>

#include "../virtualhandle.h"
#include "../Parameters/inputtext.h"
#include "../Parameters/progressbar.h"

class ToVideo : public VirtualHandle
{
private:
    enum{FrameRate, Duree, PathV, Progress, Prise, Max};
public:
    ToVideo(const std::string &path, const QString & affName,const std::string &name);
    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr);
private :
    void onEnding();
    void init(const ImageDataPtr);
    void saveFrame( ImageDataPtr );

    CheckBox * m_checkBox;
    bool m_isActif;
    ProgressBar * m_progress;
    QTime m_timer;
    CvVideoWriter * m_writer;
};

#endif // TOVIDEO_H
