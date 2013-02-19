#ifndef MDI_H
#define MDI_H

#include <set>
#include <QMdiArea>

class MainWindow;
class SubMdiWindows;

class Mdi : public QMdiArea
{
    Q_OBJECT
public:
    explicit Mdi(QWidget *parent = 0);
    void addSubWindow(QWidget *widget, Qt::WindowFlags flags = 0);
    void setMainWindow(MainWindow * );
    void reductAllExcept( const std::set<SubMdiWindows *> &);
protected :
    void resizeEvent(QResizeEvent *resizeEvent);
signals:
    void onResize(void);
public slots:

private :
    MainWindow * m_mainWindow;
};

#endif // MDI_H
