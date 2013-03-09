#ifndef SOURCEPARAMETERS_H
#define SOURCEPARAMETERS_H

#include <set>
#include <QString>

class QLabel;
class QWidget;
class HandleParameters;

/** @brief Virtual class for HandleParameters' source */
class SourceParameters
{
public:
    /** @brief Create a SourceParameters
        @param QString * label = QString() : label */
    SourceParameters(const QString & label = QString() );

    SourceParameters( const SourceParameters & ) = delete;
    SourceParameters & operator=( const SourceParameters & ) = delete;

    virtual ~SourceParameters(){}

    /** @brief Add a SourceParamters' suscriber. The suscribers' value will be changed on events.
        @param HandleParameters * target : HandleParameters were the value will be changed by this SourceParameters */
    virtual void addSuscriber(HandleParameters * target);

    /** @brief Hide the parameters */
    virtual void hideParameters(void);

    /** @brief remove a SourceParamters' suscriber. The suscribers' value will be changed on events.
        @param HandleParameters * target : HandleParameters were the value will be changed by this SourceParameters */
    virtual void removeSuscriber(HandleParameters * target);

    /** @brief Show the parameters on the parameters'area
        @param QWidget * parent : parent widget */
    virtual void showParameters(QWidget * parent) = 0;

protected :
    typedef std::set<HandleParameters *> M_ListSuscriber;

    void setParentLayout(QWidget * parent, QWidget *);

    QString m_label;

    QLabel * m_labelView;

    M_ListSuscriber m_suscribers;
};

#endif // SOURCEPARAMETERS_H
