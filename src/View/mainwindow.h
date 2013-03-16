#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Handle/imagedata.h"

class VideoExtractor;
class SubMdiWindowsImage;
class SubMdiWindowsResults;

/** @brief Namespace used for Qt's form. */
namespace Ui {
    /** @class MainWindow
    **  @see ::MainWindow
    */
    class MainWindow;
}

/** @brief Program's main windows.
**  @warning Do not inherit of it.
**  @todo Split this big class in many little class.
**  @todo saveDataFileName() to save results thanks to an HandleParameters as the VirtualHandle selection.
**  @see The wiki for more details.
*/
class MainWindow : public QMainWindow //final
{
    Q_OBJECT 
public:
    /** @brief build and initialize a new MainWindow.
    **  @param QWidget *parent = 0 : MainWindow's parent.
    */
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    MainWindow( const MainWindow & ) = delete;
    MainWindow & operator=( const MainWindow & ) = delete;
public slots :
    /** @brief Activate or disable the process. */
    void activeHandle(void);


    /** @brief Attach or detach a SubMdiWindows to/from the Mdi. */
    void attachDetach(void);


    /** @brief Change the Mdi mode according to the selected mode in the combobox.
    **
    **  The mode will change the way to shown the SubMdiWindows.
    **  @see Mode
    **  @see Wiki for more details.
    */
    void changeMdiMode(int index);


    /** @brief Set the default mode for the Mdi.
    **  @see Mode
    **  @see Wiki for more details.
    */
    void enterInDefaultMode(void);


    /** @brief Set the free mode for the Mdi.
    **  @see Mode
    **  @see Wiki for more details.
    */
    void enterInFreeMode(void);


    /** @brief Set the tabulation mode for the Mdi.
    **  @see Mode
    **  @see Wiki for more details.
    */
    void enterInTabulationMode(void);


    /** @brief Enter or go out the MainWindows into fullscrean mode. */
    void fullscreen(void);


    /** @brief Ask the next frame to the VideoExtractor. */
    void nextFrame(void);


    /** @brief When a SubWindows is closed and if we are in default mode, enter into the free mode. */
    void onCloseMainSubWindows(void);


    /** @brief Ask to the VideoExtractor to start or stop the automatic reading. */
    void playPause(void);


    /** @brief Ask the previous frame to the VideoExtractor. */
    void previousFrame(void);


    /** @brief Quit the default mode */
    void quitDefaultMode(void);


    /** @brief When the Mdi is resized, quit the default mode if we are into. */
    void resizeMdi(void);


    /** @brief Save the process extracted result's into a file.
    **  @todo there is nothing into.
    **  @note Use SubMdiWindowsResults::saveIntoFile() instead.
    */
    void saveDataFileName(void);


    /** @brief show the mains images.
    **  @param ImageDataPtr result : result ImageData for all the process.
    **  @param ImageDataPtr src1 : first sources undistorded.
    **  @param ImageDataPtr src1 : second sources undistorded.
    */
    void setImage(ImageDataPtr result, ImageDataPtr src1 , ImageDataPtr src2);


    /** @brief Hide or show the dock for parameters.
    **  @see Wiki for more details.
    */
    void showHideDockParameters(void);


    /** @brief Hide or show the dock for stream control.
    **  @see Wiki for more details.
    */
    void showHideDockStreamControl(void);


    /** @brief Called when the slider is mouved.
    **
    **  Ask to the VideoExtractor the frame which the number is given in parameters.
    **  @param int : frame's number.
    */
    void sliderMoved(int);


    /** @brief Called when a SubMdiWindows' state is changed.
    **
    **  Used to know when we should quit the Default mode.
    **  @param Qt::WindowStates : old state (?)
    **  @param Qt::WindowStates : new state (?)
    **  @todo verify the parameters (old or new ?)
    */
    void windowStateChanged(Qt::WindowStates,Qt::WindowStates);
private:

    /** @brief Mdi mode
    **  @see Wiki for more details
    */
    enum Mode{
        /** @brief Only the 4 main SubMdiWindows will be shown at specifics positions.
        **
        **  When the user resize, move, close or open a windows, enter in Free mode.
        */
        Default,
        /** @brief The SubMdiWindows will be shown as tab as we have in ours internet browse. */
        Tabulation,
        /** @brief */
        Free};

    /** @brief Open a pop-up to change the video stream for one of the two sources.
    **
    **  When the pop-up is closed the source will be updated.
    **  @param int : source number : 1 for the first source, 2 for the second.
    **  @todo We can create the QDialog with the Qt Creator.
    */
    void openChangeSourcesDialog(int);

    /** @brief Enable or disable the seek gui element and update them. */
    void updateSeek(void);

private slots :
    /** @brief Open a pop-up to change the first video stream source. */
    void changeSource1(void);


    /** @brief Open a pop-up to change the second video stream source. */
    void changeSource2(void);
private :

    /** @brief Current Mdi's mode */
    Mode m_areaMode;


    /** @brief Used VideoExtractor */
    VideoExtractor * m_extractor;


    /** @brief If the process is actived or not. */
    bool m_isHandleActived;


    /** @brief If the automatic reading is actived or not. */
    bool m_isPlay;


    /** @brief Shown the process' result ImageData.
    **
    ** One of the 4 main SubMdiWindows. */
    SubMdiWindowsImage * m_subImage;


    /** @brief Shown the fisrt source undistorded.
    **
    ** One of the 4 main SubMdiWindows. */
    SubMdiWindowsImage * m_subImageSource1;


    /** @brief Shown the second source undistorded.
    **
    ** One of the 4 main SubMdiWindows. */
    SubMdiWindowsImage * m_subImageSource2;


    /** @brief Shown the process' result extracted information.
    **
    ** One of the 4 main SubMdiWindows. */
    SubMdiWindowsResults * m_subResults;


    /** @brief Qt form's class */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
