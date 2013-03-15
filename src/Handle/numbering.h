#ifndef NUMBERING_H
#define NUMBERING_H

#include <vector>
#include <memory>
#include <QString>
#include <functional>

/** @class ShadowConfig
**  Internal type for Numbering configuration. (into Numbering class)
*/

/** @brief Numbering Provides a numbering system which you can customize thanks to generators.
**
**  When you copy the Numbering, you create an new Numbering "deeper" and the original Number will
    be "incremented". For exemple :
**  @code
**  Numbering x; // I.
**  Numbering x1 = x; // I.1
**  Numbering x2 = x; // I.2
**  Numbering x11 = x1; // I.1.a
**  Numbering x21 = x2; // I.2.a
**  @endcode
**  I, II, III or 1, 2, 3 or a, b, c depend on the "depth".
**
**  a or b or b depend on the parent's "incremented" counter.
**  In our example, x is the x1 and x2's parent, x1 is the x11's parent, x2 is the x21's parent.
**
**  The class is design to be given in parameters of a function which will print the "part" and its sub-part :
**  @code
**  void printPart(Numbering num)
**  {
**          std::cerr << num.text() << std::endl;
**          printSubPart(num);
**  }
**  @endcode
**  @todo we can add a convertion operator(std::string) to act like text()
**  @todo I don't know how to add typdef in the documentation
*/
class Numbering final
{
public:
    /** @brief Build a Numbering with default generators and start the counter from the beginning ("deeper"
      counter and "incremented" counter).
    */
    Numbering(void);


    /** @brief Build a Numbering with generators given in parameters and start the counter from the
        beginning ("deeper" counter and "incremented" counter).
    **  @param std::initializer_list<std::function<QString (unsigned int)> > generators : generators
    */
    Numbering( std::initializer_list<std::function<QString (unsigned int)> > generators );
    Numbering(const Numbering &) = delete;


    /** @brief Build a Numbering from an existing Numbering "N".
    **
    ** The new Numbering will have the same generators than N. The "depth" will be N's "depth" + 1 and the
       N will be "incremented".
    ** @param Numbering & : Numbering N.
    **
    */
    Numbering(Numbering &);

    Numbering & operator=(const Numbering &) = delete;

    ~Numbering();


    /** @brief clone a Numbering into the current Numbering
    **
    ** The current Numbering will have the same "depth" and "incremented" count than the source Numbering
    ** @param const Numbering & : source Numbering
    */
    void cloneFrom( const Numbering & );

    /** @brief alphabet generator, convert a number into letters (1 -> a, 28 -> ab)
    **  @param unsigned int : value
    **  @return QString : result
    */
    static QString G_alphabet(unsigned int);

    /** @brief alphabet generator, convert a number into capital letters (1 -> A, 28 -> AB)
    **  @param unsigned int : value
    **  @return QString : result
    */
    static QString G_alphabetMaj(unsigned int);

    /** @brief return "", used as an "empty" generator
    **  @param unsigned int : value
    **  @return QString : result
    */
    static QString G_none(unsigned int);

    /** @brief number generator, convert a number into a number (1 -> "1", 42 -> "42")
    **  @param unsigned int : value
    **  @return QString : result
    */
    static QString G_number(unsigned int);

    /** @brief ronam numeral generator, convert a number into roman numeral (1 -> "I", 12 -> "XII")
    **
    **  /!\ The value can't exceed 4899.
    **  @param unsigned int : value
    **  @return QString : result
    */
    static QString G_romanNumeral(unsigned int);


    /** @brief "Decremente" a Numbering ie decrement the "incremented" count.
    **  @return Numbering & : this numbering
    */
    Numbering & operator--();


    /** @brief Set the defaults generators to use when they aren't specified in the Numbering's constructor.
    **  @param std::initializer_list<std::function<QString (unsigned int)> > : generators to use
    */
    static void setDefaultNumbering( std::initializer_list<std::function<QString (unsigned int)> > generators );


    /** @brief return the Numbering's text
    **
    **  The nubering text is the concat of all generators result for each "depth" and with the parent's
        "incremented" count as generator's value.
    **  The first generator will used for the first "depth", the second for the second "depth", etc.
    **  @code
    **  Numbering deep0( { &Numbering::G_none, &Numbering::G_romanNumeral } );
    **  deep0.text(); // deep = 0 -> use G_none -> ""
    **  Numbering deep1 = deep0;
    **  deep1.text(); // deep = 1 -> use G_romanNumeral -> "I"
    **  Numbering deep2 = deep1;
    **  deep2.text(); // deep > 1 -> use the last generator : G_romanNumeral -> "I.I"
    **  @endcode
    **  @return const QString & : Numbering's text
    */
    const QString & text(void) const;
private :
    /** @brief Type for internal Numbering's configuration. */
    typedef std::vector<std::function<QString (unsigned int)> > ShadowConfig;

    /** @brief internal Numbering configuration */
    std::shared_ptr<ShadowConfig> m_config;

    /** @brief Default configuration */
    static ShadowConfig m_defaultConfig;

    /** @brief Numbering's depth */
    unsigned int m_depth;

    /** @brief "incremented" counter */
    unsigned int m_number;

    /** @brief Text retourned by text() */
    QString m_text;
};

#endif // NUMBERING_H
