#include "parseexception.h"

ParseException::ParseException(EXCEPTIONS_ARGS_CST_IMPL)
    :Exception(msg, MsgError , EXCEPTIONS_VALUES)
{
}
