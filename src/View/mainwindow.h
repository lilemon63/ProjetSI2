#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "../Handle/videoextractor.h"
#include "../Handle/videoview.h"
#include "submdiwindowsimage.h"
#include "submdiwindowsresults.h"

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
    SubMdiWindowsImage * m_subImage;
    SubMdiWindowsImage * m_subImageSource1;
    SubMdiWindowsImage * m_subImageSource2;
    SubMdiWindowsResults * m_subResults;
    Mode m_areaMode;
public slots :
    virtual void setImage(const ImageDataPtr result, const ImageDataPtr src1 , const ImageDataPtr src2);
    void changeMdiMode(int index);
    void onCloseMainSubWindows(void);
    void resizeMdi(void);
    void quitDefaultMode(void);
    void showHideDockParameters(void);
    void showHideDockStreamControl(void);
    void enterInDefaultMode(void);
    void enterInTabulationMode(void);
    void enterInFreeMode(void);
    void fullscreen(void);
    void saveDataFileName(void);
    void windowStateChanged(Qt::WindowStates,Qt::WindowStates);
    void attachDetach(void);
};

#endif // MAINWINDOW_H
