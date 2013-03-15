#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <sstream>
#include <typeinfo>
#include <stdexcept>

#if defined(__GNUC__) || defined(__GNUG__)
    #define PRETTY __PRETTY_FUNCTION__
    #define PRETTY_SHOW(X) (X) << "Complete methode name :\n" << pretty << "\n"
#else
    #define PRETTY ""
    #define PRETTY_SHOW(X) (X) << "Pretty function only available on GNU system\n"
#endif

/** @brief Exception Parameters for Class
**
**  You can use it as lasts arguments to build an exception where you are in an instancied class.
**  @see Exception
*/
#define EPC this, __FILE__, __LINE__ , PRETTY

/** @brief Exception Parameters.
**
**  You can use it as lasts arguments to build an exception where you aren't in an instancied class.
**  @see Exception
*/
#define EP (void*)0,__FILE__, __LINE__ , PRETTY

/** @brief Contructors' arguments for declaration
**  @see Exception
*/
#define EXCEPTIONS_ARGS_CST const std::string  & msg, \
                            const std::string  & MsgError, \
                            const std::string & ClassName, \
                            const std::string & MethodName, \
                            const void * const ptr = nullptr, \
                            const std::string & FileName = "", \
                            const unsigned int line = 0, \
                            const std::string & pretty = ""

/** @brief Contructors' arguments for definition
**  @see Exception
*/
#define EXCEPTIONS_ARGS_CST_IMPL const std::string  & msg, \
                                const std::string  & MsgError, \
                                const std::string & ClassName, \
                                const std::string & MethodName, \
                                const void * const ptr, \
                                const std::string & FileName, \
                                const unsigned int line, \
                                const std::string & pretty

/** @brief Methods' arguments for declaration
**  @see Exception
*/
#define EXCEPTIONS_ARGS const std::string & ClassName, \
                        const std::string & MethodName, \
                        const T * const ptr = nullptr, \
                        const std::string & FileName = "", \
                        const unsigned int line = 0, \
                        const std::string & pretty = ""

/** @brief Methods' arguments for definition
**  @see Exception
*/
#define EXCEPTIONS_ARGS_IMPL                    const std::string & ClassName, \
                                                const std::string & MethodName, \
                                                const T * const ptr, \
                                                const std::string & FileName, \
                                                const unsigned int line, \
                                                const std::string & pretty
/** @brief Used as parameters in an Exceptions' method to call another exception method (see the example)
**  @see Exception
*/
#define EXCEPTIONS_VALUES ClassName, MethodName, ptr, FileName, line, pretty


/** @brief Exception class which give maximum information about the error, build it with buildException().
**
**        @code @endcode
**        We use few macro
**        @list
**        - EXCEPTIONS_ARGS_CST : which is the paramters of the constructor
**        - EXCEPTIONS_ARGS_CST_IMPL : which is the paramters of the constructor in implementation
**        - EXCEPTIONS_ARGS : which is the parameters for static method except the errors messages
**        - EXCEPTIONS_ARGS_IMPL which is the parameters for static method except the errors messages in
          implemetation
**        - EXCEPTIONS_VALUES : you can use it when calling a method into a method which use EXCEPTION_ARGS*
          in its declaration,
**        see the Exception example for more details.
**        @endlist
**        @todo I don't know why but if I remove the tag code and endcode in this description, there is a
          problem.
**        @warning This class isn't easy to understand, do not modify it.
**        @author Neckara for Last Dungeon
*/
class Exception : public std::runtime_error
{
public:
    /** @brief Build an Exception.
    **
    **    Use the macro EP (Exceptions Parameters) for the three lastest parameters
    **    or EPC (Exceptions Parameters Class)  for the four lastest if you are in an instacied class.
    **    Maybie some MACRO for the parameters can help programmers
    **    @param const std::string  & MsgError : error message
    **    @param const std::string & ClassName : name of the class which throw the exception
    **    @param const std::string & MethodName : name of the method which throw the exception
    **    @param const T * const ptr : instance which throw the exception
    **    @param const std::string & FileName : name of the file where we throw the exception
    **    @param const unsigned int line : line where we throw the exception
    **    @param const std::string & pretty : only for GNU, pretty name of the method which throw the
          exception
    **    @return Exception : exception created
    */
    template<typename T>
    static Exception buildException( const std::string  & MsgError, EXCEPTIONS_ARGS  );

    virtual ~Exception() throw() =default;


    /** @brief Return the Exception's error message.
    **  @return const std::string & : Exception's error message.
    */
    const std::string & getMessage(void) const{return MsgError; }


    /** @brief Return the class' name from where the Exception was thrown.
    **  @return const std::string & : class' name from where the Exception was thrown.
    */
    const std::string & getClass(void) const{return ClassName; }


    /** @brief Return the method or the functions' name from where the Exception was thrown.
    **  @return const std::string & : Method or functions' name from where the Exception was thrown.
    */
    const std::string & getMethod(void) const{return MethodName; }


    /** @brief Return the filename's name from where the Exception was thrown.
    **  @return const std::string & : filename's name from where the Exception was thrown.
    */
    const std::string & getFile(void) const{return FileName; }


    /** @brief Return the pointer to the object from where the Exception was thrown.
    **  @return const void * : pointer to the object from where the Exception was thrown or nullptr.
    */
    const void * getInstance(void) const{return ptr;}


    /** @brief Return the class's name from where the Exception was thrown according
        to typeid.
    **  @return const char * : class's name from where the Exception was thrown according
        to typeid.
    */
    const char * getTypeInfoName(void) const{return typeid(ptr).name(); }


    /** @brief Return the line where the Exception was thrown.
    **  @return unsigned int : line where the Exception was thrown.
    */
    unsigned int getLine(void) const { return line; }

    /** @brief Return true if __PRETTY_FUNCTION__ is available, return true only for GNU system.
    **  @return bool : return true only for GNU system else return false.
    */
    bool isPrettyAvailable(void)
    {
#if defined(__GNUC__) || defined(__GNUG__)
        return true;
#endif
        return false;
    }

    /** @brief  Return the method or the function's name from where the Exception was thrown according
    **  to __PRETTY_FUNCTION__.
    **  @param const std::string & : method or function's name from where the Exception was thrown according
    **  to __PRETTY_FUNCTION__.
    */
    const std::string & getPrettyFonction(){ return pretty; }
private :
    /** @brief Exception's error message. */
    const std::string MsgError;

    /** @brief Class' name from where the Exception was thrown. */
    const std::string ClassName;


    /** @brief Method or functions' name from where the Exception was thrown. */
    const std::string MethodName;


    /** @brief Filename's name from where the Exception was thrown. */
    const std::string FileName;


    /** @brief Line where the Exception was thrown. */
    const unsigned int line;


    /** @brief Pointer to the object from where the Exception was thrown or nullptr. */
    const void * const ptr;


    /** @brief const std::string & : Method or function's name from where the Exception was thrown according
    **  to __PRETTY_FUNCTION__.
    */
    const std::string pretty;
protected :

    /**   @brief Build an Exception
    **    @param const std::string  & msg : error message
    **    @param const std::string  & MsgError : original error message
    **    @param const std::string & ClassName : name of the class which throw the exception
    **    @param const std::string & MethodName : name of the method which throw the exception
    **    @param const std::string & FileName : name of the file where we throw the exception
    **    @param const unsigned int line : line where we throw the exception
    **    @param const T * const ptr : instance which throw the exception
    **    @param const std::string & pretty : only for GNU, pretty name of the method which throw the
          exception
    */
    Exception( EXCEPTIONS_ARGS_CST );

    /** @brief Create the end of the error message
    **    @param std::stringstream & flux : stream where the error message will write
    **    @param const std::string & ClassName : name of the class which throw the exception
    **    @param const std::string & MethodName : name of the method which throw the exception
    **    @param const T * const ptr : instance which throw the exception
    **    @param const std::string & FileName : name of the file where we throw the exception
    **    @param const unsigned int line : line where we throw the exception
    **    @param const std::string & pretty : only for GNU, pretty name of the method which throw the
          exception
    */
    template<typename T>
    static void buildEndOfErrorText(std::stringstream & flux,
                           EXCEPTIONS_ARGS);


    /** @brief Build the error message text.
    **  @param const std::string  & MsgError : error message
    **  @param const std::string & ClassName : name of the class which throw the exception
    **  @param const std::string & MethodName : name of the method which throw the exception
    **  @param const T * const ptr : instance which throw the exception
    **  @param const std::string & FileName : name of the file where we throw the exception
    **  @param const unsigned int line : line where we throw the exception
    **  @param const std::string & pretty : only for GNU, pretty name of the method which throw the exception
    */
    template<typename T>
    static const std::string buildErrorMessage(const std::string  & MsgError,
                                        EXCEPTIONS_ARGS);
};


template<typename T>
Exception Exception::buildException(   const std::string  & MsgError,
                              EXCEPTIONS_ARGS_IMPL)
{
    std::string errorMessage = buildErrorMessage(MsgError, EXCEPTIONS_VALUES);
    return Exception(errorMessage, MsgError, EXCEPTIONS_VALUES);
}

template<typename T>
void Exception::buildEndOfErrorText(std::stringstream & flux,
                                    EXCEPTIONS_ARGS_IMPL)
{
    flux  <<  "On " << ClassName
          << "::" << MethodName << " ( " << typeid(ptr).name()
          << " )" << " in ligne " << line << " of file "
          << FileName << " with instance " << ptr << "\n";
    PRETTY_SHOW(flux);
}

template<typename T>
const std::string Exception::buildErrorMessage(const std::string  & MsgError,
                                    EXCEPTIONS_ARGS_IMPL)
{
    std::stringstream flux;
    flux << "Error : " << MsgError << "\n";
    buildEndOfErrorText(flux, EXCEPTIONS_VALUES);
    return flux.str();
}

/** @example Exception
**  @code
**  template<typename T>
**  const std::string Exception::buildErrorMessage(const std::string  & MsgError,
**                                    EXCEPTIONS_ARGS_IMPL)
**  {
**      std::stringstream flux;
**      flux << "Error : " << MsgError << "\n";
**      buildEndOfErrorText(flux, EXCEPTIONS_VALUES);
**      return flux.str();
**  }
**  @endcode
*/

#endif // ERROR_H
