#ifndef INPUTSTEXTS_H
#define INPUTSTEXTS_H

#include <QObject>
#include <QLineEdit>
#include <QFrame>
#include <QStringList>
#include <map>
#include "sourceparameters.h"

class InputsTexts : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    enum Helper{None, Directory, SaveFile, OpenFile};

    explicit InputsTexts(const QString & label = QString(), unsigned int number = 2, const QStringList &defaultValue = QStringList());
    virtual void showParameters(QWidget * parent);
    virtual void hideParameters(void);
    virtual void addSuscriber(HandleParameters * target);
    virtual ~InputsTexts();
    virtual void changeValue( const QString & newValue, int id );

private slots :
    void valueChanged(void);
private :
    QLineEdit ** m_inputText;
    QFrame * m_frame;
    QStringList m_values;
    std::map<QLineEdit *, int> m_ids;
};

#endif // INPUTSTEXTS_H
