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
    enum Mode{Default, Tabulation, Free};

    Ui::MainWindow *ui;
    VideoExtractor * m_extractor;
    SubMdiWindows * m_subImage;
    SubMdiWindows * m_subImageSource1;
    SubMdiWindows * m_subImageSource2;
    Mode m_areaMode;
public slots :
    virtual void setImage(const ImageDataPtr result, const ImageDataPtr src1 , const ImageDataPtr src2);
    void changeMdiMode(int index);
    void onCloseMainSubWindows(void);
    void resizeMdi(void);
};

#endif // MAINWINDOW_H
