#ifndef MDI_H
#define MDI_H

#include <set>
#include <QMdiArea>

class MainWindow;
class SubMdiWindows;

class Mdi : public QMdiArea //final
{
    Q_OBJECT
public:
    explicit Mdi(QWidget *parent = 0);
    Mdi(const Mdi &) = delete;
    Mdi & operator=(const Mdi &) = delete;

    void addSubWindow(QWidget *widget, Qt::WindowFlags flags = 0);
    void reductAllExcept( const std::set<SubMdiWindows *> &);
    void setMainWindow(MainWindow * );
signals:
    void onResize(void);
protected :
    void resizeEvent(QResizeEvent *resizeEvent);
private :
    MainWindow * m_mainWindow;
};

#endif // MDI_H
