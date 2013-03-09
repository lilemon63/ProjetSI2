#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Handle/imagedata.h"

class VideoExtractor;
class SubMdiWindowsImage;
class SubMdiWindowsResults;

namespace Ui {
class MainWindow;
}

//TODO : séparer en sous-classes
//TODO saveDataFileName
class MainWindow : public QMainWindow //final
{
    Q_OBJECT 
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow( const MainWindow & ) = delete;
    MainWindow & operator=( const MainWindow & ) = delete;
public slots :
    void activeHandle(void);
    void attachDetach(void);
    void changeMdiMode(int index);
    void enterInDefaultMode(void);
    void enterInFreeMode(void);
    void enterInTabulationMode(void);
    void fullscreen(void);
    void nextFrame(void);
    void onCloseMainSubWindows(void);
    void playPause(void);
    void previousFrame(void);
    void quitDefaultMode(void);
    void resizeMdi(void);
    void saveDataFileName(void);
    void setImage(const ImageDataPtr result, const ImageDataPtr src1 , const ImageDataPtr src2);
    void showHideDockParameters(void);
    void showHideDockStreamControl(void);
    void sliderMoved(int);
    void windowStateChanged(Qt::WindowStates,Qt::WindowStates);
private slots:
    void on_actionPlein_cran_triggered();

private:
    enum Mode{Default, Tabulation, Free};
    void updateSeek(void);
private :
    Mode m_areaMode;
    VideoExtractor * m_extractor;
    bool m_isHandleActived;
    bool m_isPlay;
    SubMdiWindowsImage * m_subImage;
    SubMdiWindowsImage * m_subImageSource1;
    SubMdiWindowsImage * m_subImageSource2;
    SubMdiWindowsResults * m_subResults;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
