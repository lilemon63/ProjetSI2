#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "../Handle/videoextractor.h"
#include "../Handle/videoview.h"
#include "submdiwindows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    VideoExtractor * m_extractor;
    SubMdiWindows * m_subImage;
    QMdiArea::ViewMode m_areaMode;
public slots :
    virtual void setImage(const ImageDataPtr result, const ImageDataPtr src1 , const ImageDataPtr src2);
    void changeMdiMode(void);
    void onCloseMainSubWindows(void);
};

#endif // MAINWINDOW_H
