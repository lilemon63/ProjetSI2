#ifndef MDI_H
#define MDI_H

#include <QMdiArea>

class Mdi : public QMdiArea
{
    Q_OBJECT
public:
    explicit Mdi(QWidget *parent = 0);
    
protected :
    void resizeEvent(QResizeEvent *resizeEvent);
signals:
    void onResize(void);
public slots:
    
};

#endif // MDI_H
