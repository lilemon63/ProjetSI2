#include "numbering.h"
#include "../exception.h"
#include <math.h>
#include <iostream>

Numbering::ShadowConfig Numbering::m_defaultConfig = {&Numbering::G_none,
                                                      &Numbering::G_romanNumeral,
                                                      &Numbering::G_alphabetMaj,
                                                      &Numbering::G_number,
                                                      &Numbering::G_alphabet,
                                                      &Numbering::G_number};

QString Numbering::G_alphabet(unsigned int nb)
{
    QString result;
    while( nb != 0 )
    {
        char c = nb % 26;
        nb -= c;
        c += 'a';
        result += c;
    }
    return result;
}

QString Numbering::G_alphabetMaj(unsigned int nb)
{
    QString result;
    while( nb != 0 )
    {
        char c = nb % 26;
        nb -= c;
        c += 'A';
        result += c;
    }
    return result;}

QString Numbering::G_number(unsigned int nb)
{
    return QString::number(nb);
}

QString Numbering::G_romanNumeral(unsigned int nb)
{
    QChar symboles[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    QString result;
    if( nb > 4899)
        throw Exception::buildException("On va jusqu'à 4899 mais il ne faut pas exagérer tout de même! (on ne gère pas les chiffres romains étendus)", "Numbering",
                                        "G_RomanNumeral", EP);
    int i = sizeof(symboles)/sizeof(QChar) - 1;
    unsigned int coef = pow(10, i/2);
    while( nb )
    {
        unsigned int chiffre = nb/coef;
        if( chiffre )
        {
            if(chiffre > 8)
                result += QString((int)10-chiffre, symboles[i]) + symboles[i+2];
            else if(chiffre > 4)
                result += symboles[i+1] + QString(chiffre - 5, symboles[i]);
            else if(chiffre > 3 && symboles[i] != 'M')
            {
                result += symboles[i];
                result += symboles[i+1];
            }
            else
                result += QString((int)chiffre, symboles[i]);
        }
        nb -= coef*chiffre;
        coef /= 10;
        i -= 2;
    }
    return result;
}

QString Numbering::G_none(unsigned int)
{
    return QString();
}

Numbering::Numbering( std::initializer_list<std::function<QString (unsigned int)> > generators )
    : m_config( new ShadowConfig(generators) ),
    m_depth(0),
    m_number(0)
{
}

Numbering::Numbering(void)
    : m_config( new ShadowConfig(m_defaultConfig) ),
      m_depth(0),
      m_number(0)
{

}

Numbering::Numbering(Numbering & other)
    : m_config( other.m_config),
      m_text( other.m_text),
      m_depth( other.m_depth + 1 > m_config->size() ? other.m_depth : other.m_depth + 1),
      m_number(0)
{
    ++other.m_number;
    m_text += (*m_config)[m_depth](other.m_number);
    if( m_text != "" && m_text[m_text.size() - 1] != '.' )
        m_text += ".";
}

Numbering::~Numbering()
{
}

void Numbering::setDefaultNumbering( std::initializer_list<std::function<QString (unsigned int)> > generators )
{
    m_defaultConfig = generators;
}


const QString & Numbering::text(void)
{
    return m_text;
}
