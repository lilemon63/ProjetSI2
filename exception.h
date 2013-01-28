#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>
#include<typeinfo>
#include<sstream>

#if defined(__GNUC__) || defined(__GNUG__)
    #define throwExc(X, Y, Z) Exception::throwException( (X), (Y), (Z), __FILE__, __LINE__, this , __PRETTY_FUNCTION__)
#else
    #define throwExc(X, Y, Z) Exception::throwException( (X), (Y), (Z), __FILE__, __LINE__, this , "")
#endif

#if defined(__GNUC__) || defined(__GNUG__)
#define throwExcOutClass(X, Y, Z) Exception::throwException( (X), (Y), (Z), __FILE__, __LINE__, (const void *)nullptr , __PRETTY_FUNCTION__)
#else
    #define throwExcOutClass(X, Y, Z) Exception::throwException( (X), (Y), (Z), __FILE__, __LINE__, (const void *)nullptr , "")
#endif

/** @brief Exception class throw it with throwExc(messageError, className, methodName); */
class Exception : public std::runtime_error
{
public:
    /** @brief Used by the MACCRO throwExc. Throw an Exception
        @param const std::string  & MsgError : error message
        @param const std::string & ClassName : name of the class which throw the exception
        @param const std::string & MethodName : name of the method which throw the exception
        @param const std::string & FileName : name of the file where we throw the exception
        @param const unsigned int line : line where we throw the exception
        @param const T * const ptr : instance which throw the exception
        @param const std::string & pretty : only for GNU, pretty name of the method which throw the exception */
    template<typename T>
    static void throwException(   const std::string  & MsgError,
                                  const std::string & ClassName,
                                  const std::string & MethodName,
                                  const std::string & FileName,
                                  const unsigned int line,
                                  const T * const ptr,
                                  const std::string & pretty);
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

    /** @brief Build an Exception
        @param const std::string  & MsgError : error message
        @param const std::string & ClassName : name of the class which throw the exception
        @param const std::string & MethodName : name of the method which throw the exception
        @param const std::string & FileName : name of the file where we throw the exception
        @param const unsigned int line : line where we throw the exception
        @param const T * const ptr : instance which throw the exception
        @param const std::string & pretty : only for GNU, pretty name of the method which throw the exception */
    Exception(  const std::string  & msg,
                const std::string & MsgError,
                const std::string & ClassName,
                const std::string & MethodName,
                const std::string &FileName,
                const unsigned int line,
                const void *const ptr,
                const std::string & pretty);

    const std::string MsgError;
    const std::string ClassName;
    const std::string MethodName;
    const std::string FileName;
    const unsigned int line;
    const void * const ptr;
    const std::string pretty;
};


template<typename T>
void Exception::throwException(   const std::string  & MsgError,
                              const std::string & ClassName,
                              const std::string & MethodName,
                              const std::string & FileName,
                              const unsigned int line,
                              const T *const ptr,
                              const std::string & pretty)
{
    std::stringstream flux;
    flux << "Error : " << MsgError << "\n"
         << "On " << ClassName
         << "::" << MethodName << " ( " << typeid(ptr).name()
         << " )" << " in ligne " << line << " of file "
         << FileName << " with instance " << ptr;
#if defined(__GNUC__) || defined(__GNUG__)
    flux << "\nComplete methode name :\n" << pretty << "\n";
#endif
    throw Exception(flux.str(), MsgError, ClassName, MethodName, FileName, line, ptr, pretty);
}

#endif // EXCEPTION_H
