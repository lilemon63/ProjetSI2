#ifndef TOVIDEO_H
#define TOVIDEO_H

#include<QTimer>
#include "../virtualhandle.h"
#include <QObject>
#include "../Parameters/handleprogressbar.h"

class ToVideo : public QObject, public VirtualHandle
{
    Q_OBJECT

private:
    const std::string m_path;
    QTimer m_timer;
    bool prise;
    CvVideoWriter *writer;
    enum{FrameRate,Duree,Progress,Prise,Max};
    ProgressBar * progress;
    int max;
public slots:
    void incrementeTemps();
public:
    ToVideo(const std::string &path, const QString & affName,const std::string &name);
    ImageDataPtr startHandle(const ImageDataPtr src1, const ImageDataPtr);
    void fin();
    void init(const ImageDataPtr);
};

#endif // TOVIDEO_H
