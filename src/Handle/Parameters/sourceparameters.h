#ifndef SOURCEPARAMETERS_H
#define SOURCEPARAMETERS_H

#include <set>
#include <QString>

class QLabel;
class QWidget;
class HandleParameters;

/** @brief Virtual class for HandleParameter's source.
**
**  A "source" is a gui element which change the HandleParamter's values when it's modified.
*/
class SourceParameters
{
public:
    /** @brief Create a SourceParameters
    **  @param QString * label = QString() : label
    */
    SourceParameters(const QString & label = QString() );

    SourceParameters( const SourceParameters & ) = delete;
    SourceParameters & operator=( const SourceParameters & ) = delete;

    virtual ~SourceParameters(){}


    /** @brief Add a SourceParamters' suscriber. The suscribers' value will be changed when the SourceParamters
        ' value is changes.
    **  @param HandleParameters * target : HandleParameters were the value will be changed by the
        SourceParamters.
    */
    virtual void addSuscriber(HandleParameters * target);


    /** @brief Hide the parameters */
    virtual void hideParameters(void);


    /** @brief Remove a SourceParamters' suscriber. A suscribers' value will be changed on events.
    **  @param HandleParameters * target : HandleParameters which we remove from the suscribers.
    */
    virtual void removeSuscriber(HandleParameters * target);


    /** @brief Show the parameters on the parameters'area.
    **  @param QWidget * parent : widget where the parameters' will shown.
    */
    virtual void showParameters(QWidget * parent) = 0;

protected :
    /** @brief Type to store the suscribers. */
    typedef std::set<HandleParameters *> M_ListSuscriber;


    /** @brief Shown the QWidget given in the parent.
    **  @param QWidget * parent : parent.
    **  @param QWidget * : QWidget given.
    */
    void setParentLayout(QWidget * parent, QWidget *);


    /** @brief SourceParamters' label */
    QString m_label;


    /** @brief SourceParamters' label */
    QLabel * m_labelView;


    /** @brief SourceParamters' suscribers' list. */
    M_ListSuscriber m_suscribers;
};

#endif // SOURCEPARAMETERS_H
