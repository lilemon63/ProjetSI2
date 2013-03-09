#ifndef EDITCHANNEL_H
#define EDITCHANNEL_H

#include "../virtualhandle.h"

class EditChannel : public VirtualHandle
{
    enum{SCRIPT_R, SCRIPT_G, SCRIPT_B, MAX};
public:
    EditChannel(const QString & affName = "Untilted", const std::string & = "noname");
protected :
    ImageDataPtr startHandle(ImageDataPtr src1, const ImageDataPtr src2);
};


#endif // EDITCHANNEL_H
