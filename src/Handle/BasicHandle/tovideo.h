#ifndef TOVIDEO_H
#define TOVIDEO_H

#include<QTime>
#include "../virtualhandle.h"
#include <QObject>
#include "../Parameters/progressbar.h"
#include "../Parameters/inputtext.h"

class ToVideo : public QObject, public VirtualHandle
{
    Q_OBJECT

private:
    InputText * m_Path;
    QTime m_timer;
    CvVideoWriter * m_writer;
    enum{FrameRate, Duree, Progress, Prise,PathV, Max};
    ProgressBar * m_progress;
    CheckBox * m_checkBox;
    bool m_isActif;
public:
    ToVideo(const std::string &path, const QString & affName,const std::string &name);
    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr);
private :
    void onEnding();
    void init(const ImageDataPtr);
signals :
    void newFrame( ImageDataPtr );
private slots :
    void saveFrame( ImageDataPtr );
};

#endif // TOVIDEO_H
