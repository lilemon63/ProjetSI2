#include "handletools.h"

HandleTools::HandleTools()
    :   video("./test.avi" , "ToVideo", "ToVideo"),
        tofiles(".", 0,"ToFiles", "ToFiles"),
        noHandle("Rien", "NOHANDLE"),
        rotation(15, "Rotation", "Rotation"),
        grayscale("grayscale", "grayscale"),
        threshold("threshold", "threshold"),
        countPixel("CountPixel", "CountPixel"),
        editChannel("EditChannel", "EditChannel")
{
}
