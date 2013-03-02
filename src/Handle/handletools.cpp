#include "handletools.h"

HandleTools::HandleTools()
    : rotation(15, "Rotation", "Rotation"),
      tofiles(".", 0,"ToFiles", "ToFiles"),
      v("./test.avi" , "ToVideo", "ToVideo"),
      noHandle("Rien", "NOHANDLE")
{
}
