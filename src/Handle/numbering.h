#ifndef NUMBERING_H
#define NUMBERING_H

#include <QString>
#include <functional>
#include <vector>
#include <memory>

class Numbering
{
public:
    Numbering( std::initializer_list<std::function<QString (unsigned int)> > generators );

    Numbering(void);

    Numbering(Numbering &);

    void clone( const Numbering & );

    virtual ~Numbering();

    static void setDefaultNumbering( std::initializer_list<std::function<QString (unsigned int)> > generators );


    static QString G_alphabet(unsigned int);
    static QString G_alphabetMaj(unsigned int);
    static QString G_number(unsigned int);
    static QString G_romanNumeral(unsigned int);
    static QString G_none(unsigned int);

    const QString & text(void);

private :
    Numbering(const Numbering &) = delete;
    const Numbering & operator=(const Numbering &) = delete;

    typedef std::vector<std::function<QString (unsigned int)> > ShadowConfig;

    std::shared_ptr<ShadowConfig> m_config;

    static ShadowConfig m_defaultConfig;
    QString m_text;
    unsigned int m_depth;
    unsigned int m_number;



};

#endif // NUMBERING_H
