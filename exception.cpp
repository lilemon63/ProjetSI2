#include "exception.h"

Exception::Exception( EXCEPTIONS_ARGS_CST_IMPL )
        : std::runtime_error(msg),
          MsgError(MsgError),
          ClassName(ClassName),
          MethodName(MethodName),
          FileName(FileName),
          line(line),
          ptr(ptr),
          pretty(pretty)
{
}
