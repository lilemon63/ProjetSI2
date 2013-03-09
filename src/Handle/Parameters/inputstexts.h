#ifndef INPUTSTEXTS_H
#define INPUTSTEXTS_H

#include <map>
#include <QObject>
#include <QStringList>

#include "sourceparameters.h"

class QFrame;
class QLineEdit;

class InputsTexts : public QObject, public SourceParameters
{
    Q_OBJECT
public:
    enum Helper{None, Directory, SaveFile, OpenFile};

    explicit InputsTexts(const QString & label = QString(), unsigned int number = 2,
                         const QStringList &defaultValue = QStringList());
    virtual ~InputsTexts();

    virtual void addSuscriber(HandleParameters * target);
    virtual void changeValue( const QString & newValue, int id );
    virtual void hideParameters(void);
    virtual void showParameters(QWidget * parent);

private slots :
    void valueChanged(void);
private :
    std::map<QLineEdit *, int> m_ids;
    QLineEdit ** m_inputText;
    QFrame * m_frame;
    QStringList m_values;
};

#endif // INPUTSTEXTS_H
