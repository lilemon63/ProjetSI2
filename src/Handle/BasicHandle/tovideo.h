#ifndef TOVIDEO_H
#define TOVIDEO_H

#include<QTime>
#include "../virtualhandle.h"
#include <QObject>
#include "../Parameters/progressbar.h"

class ToVideo : public QObject, public VirtualHandle
{
    Q_OBJECT

private:
    const std::string m_path;
    QTime m_timer;
    CvVideoWriter * m_writer;
    enum{FrameRate, Duree, Progress, Prise, Max};
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
