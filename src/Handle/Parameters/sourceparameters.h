#ifndef SOURCEPARAMETERS_H
#define SOURCEPARAMETERS_H

#include<QWidget>
#include <set>
#include <QLabel>

class HandleParameters;

/** @brief Virtual class for HandleParameters' source */
class SourceParameters
{
public:
    /** @brief Create a SourceParameters
        @param QString * label = QString() : label */
    SourceParameters(QString label = QString() );

    /** @brief Add a SourceParamters' suscriber. The suscribers' value will be changed on events.
        @param HandleParameters * target : HandleParameters were the value will be changed by this SourceParameters */
    virtual void addSuscriber(HandleParameters * target);

    /** @brief remove a SourceParamters' suscriber. The suscribers' value will be changed on events.
        @param HandleParameters * target : HandleParameters were the value will be changed by this SourceParameters */
    virtual void removeSuscriber(HandleParameters * target);

    /** @brief Show the parameters on the parameters'area
        @param QWidget * parent : parent widget */
    virtual void showParameters(QWidget * parent) = 0;

    /** @brief Hide the parameters */
    virtual void hideParameters(void);

    virtual ~SourceParameters(){}

protected :
    typedef std::set<HandleParameters *> M_ListSuscriber;
    M_ListSuscriber m_suscribers;

    void setParentLayout(QWidget * parent, QWidget *);

    QString m_label;

    QLabel * m_labelView;
};

#endif // SOURCEPARAMETERS_H
