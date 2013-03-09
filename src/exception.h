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

#define EPC this, __FILE__, __LINE__ , PRETTY
#define EP (void*)0,__FILE__, __LINE__ , PRETTY

#define EXCEPTIONS_ARGS_CST const std::string  & msg, \
                            const std::string  & MsgError, \
                            const std::string & ClassName, \
                            const std::string & MethodName, \
                            const void * const ptr = nullptr, \
                            const std::string & FileName = "", \
                            const unsigned int line = 0, \
                            const std::string & pretty = ""

#define EXCEPTIONS_ARGS_CST_IMPL const std::string  & msg, \
                                const std::string  & MsgError, \
                                const std::string & ClassName, \
                                const std::string & MethodName, \
                                const void * const ptr, \
                                const std::string & FileName, \
                                const unsigned int line, \
                                const std::string & pretty

#define EXCEPTIONS_ARGS const std::string & ClassName, \
                        const std::string & MethodName, \
                        const T * const ptr = nullptr, \
                        const std::string & FileName = "", \
                        const unsigned int line = 0, \
                        const std::string & pretty = ""
#define EXCEPTIONS_ARGS_IMPL                    const std::string & ClassName, \
                                                const std::string & MethodName, \
                                                const T * const ptr, \
                                                const std::string & FileName, \
                                                const unsigned int line, \
                                                const std::string & pretty
#define EXCEPTIONS_VALUES ClassName, MethodName, ptr, FileName, line, pretty

/** @brief Exception class which give maximum information about the error, build it with buildException.<br/>
        We use few MACRO :<br/>
        - EXCEPTIONS_ARGS_CST : which is the paramters of the constructor <br/>
        - EXCEPTIONS_ARGS_CST_IMPL : which is the paramters of the constructor in implementation <br/>
        - EXCEPTIONS_ARGS : which is the parameters for static method except the errors messages <br/>
        - EXCEPTIONS_ARGS_IMPL which is the parameters for static method except the errors messages in implemetation <br/>
        - EXCEPTIONS_VALUES : you can use it when calling a method into a method which use EXCEPTION_ARGS* in its declaration, for exemple :<br>
template<typename T> <br/>
const std::string Exception::buildErrorMessage(const std::string  & MsgError, <br/>
                                    EXCEPTIONS_ARGS_IMPL) <br/>
{<br/>
    std::stringstream flux;<br/>
    flux << "Error : " << MsgError << "\n";<br/>
    buildEndOfErrorText(flux, EXCEPTIONS_VALUES);<br/>
    return flux.str();<br/>
}
@author Neckara for Last Dungeon */
class Exception : public std::runtime_error
{
public:
    /** @brief Build an Exception, use the macro EP (ExceptionsParams) for the three lastest parameters
        or EPC (ExceptionsParamsClass)  for the four lastest if you are in an instacied class.<br/>
        Maybie some MACRO for the parameters can help programmers
        @param const std::string  & MsgError : error message
        @param const std::string & ClassName : name of the class which throw the exception
        @param const std::string & MethodName : name of the method which throw the exception
        @param const T * const ptr : instance which throw the exception
        @param const std::string & FileName : name of the file where we throw the exception
        @param const unsigned int line : line where we throw the exception
        @param const std::string & pretty : only for GNU, pretty name of the method which throw the exception
        @return Exception : exception created */
    template<typename T>
    static Exception buildException( const std::string  & MsgError, EXCEPTIONS_ARGS  );
    virtual ~Exception() throw() =default;

    const std::string & getMessage(void) const{return MsgError; }
    const std::string & getClass(void) const{return ClassName; }
    const std::string & getMethod(void) const{return MethodName; }
    const std::string & getFile(void) const{return FileName; }
    const void * getInstance(void) const{return ptr;}
    const char * getTypeInfoName(void) const{return typeid(ptr).name(); }
    unsigned int getLine(void) const { return line; }

    /** @brief Return true if __PRETTY_FUNCTION__ is available, return true only for GNU
        @return bool : return true only for GNU else return false. */
    bool isPrettyAvailable(void)
    {
#if defined(__GNUC__) || defined(__GNUG__)
        return true;
#endif
        return false;
    }

    const std::string & getPrettyFonction(){ return pretty; }
private :

    const std::string MsgError;
    const std::string ClassName;
    const std::string MethodName;
    const std::string FileName;
    const unsigned int line;
    const void * const ptr;
    const std::string pretty;
protected :

    /** @brief Build an Exception
        @param const std::string  & msg : error message
        @param const std::string  & MsgError : original error message
        @param const std::string & ClassName : name of the class which throw the exception
        @param const std::string & MethodName : name of the method which throw the exception
        @param const std::string & FileName : name of the file where we throw the exception
        @param const unsigned int line : line where we throw the exception
        @param const T * const ptr : instance which throw the exception
        @param const std::string & pretty : only for GNU, pretty name of the method which throw the exception */
    Exception( EXCEPTIONS_ARGS_CST );

    /** @brief Create the end of the error message
        @param std::stringstream & flux : stream where the error message will write
        @param const std::string & ClassName : name of the class which throw the exception
        @param const std::string & MethodName : name of the method which throw the exception
        @param const T * const ptr : instance which throw the exception
        @param const std::string & FileName : name of the file where we throw the exception
        @param const unsigned int line : line where we throw the exception
        @param const std::string & pretty : only for GNU, pretty name of the method which throw the exception */
    template<typename T>
    static void buildEndOfErrorText(std::stringstream & flux,
                           EXCEPTIONS_ARGS);


    /** @brief Build the error message text
        @param const std::string  & MsgError : error message
        @param const std::string & ClassName : name of the class which throw the exception
        @param const std::string & MethodName : name of the method which throw the exception
        @param const T * const ptr : instance which throw the exception
        @param const std::string & FileName : name of the file where we throw the exception
        @param const unsigned int line : line where we throw the exception
        @param const std::string & pretty : only for GNU, pretty name of the method which throw the exception */
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

#endif // ERROR_H
