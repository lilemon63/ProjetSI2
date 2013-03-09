#ifndef NUMBERING_H
#define NUMBERING_H

#include <vector>
#include <memory>
#include <QString>
#include <functional>

class Numbering final
{
public:
    Numbering(void);
    Numbering( std::initializer_list<std::function<QString (unsigned int)> > generators );
    Numbering(const Numbering &) = delete;
    Numbering(Numbering &);
    Numbering & operator=(const Numbering &) = delete;

    ~Numbering();


    void cloneFrom( const Numbering & );

    static QString G_alphabet(unsigned int);
    static QString G_alphabetMaj(unsigned int);
    static QString G_none(unsigned int);
    static QString G_number(unsigned int);
    static QString G_romanNumeral(unsigned int);

    Numbering & operator--();

    static void setDefaultNumbering( std::initializer_list<std::function<QString (unsigned int)> > generators );

    const QString & text(void) const;
private :
    typedef std::vector<std::function<QString (unsigned int)> > ShadowConfig;

    std::shared_ptr<ShadowConfig> m_config;

    static ShadowConfig m_defaultConfig;

    unsigned int m_depth;
    unsigned int m_number;
    QString m_text;
};

#endif // NUMBERING_H
