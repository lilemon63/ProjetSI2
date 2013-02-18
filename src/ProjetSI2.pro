Qt += system

QMAKE_CXXFLAGS += -std=c++0x
CXXFLAGS="-std=c++11"

SOURCES += \
    main.cpp \
    Handle/virtualhandle.cpp \
    Handle/modelhandle.cpp \
    Handle/videoview.cpp \
    Handle/videoextractor.cpp \
    Handle/videoreader.cpp \
    Handle/imagedata.cpp \
    View/mainwindow.cpp \
    exception.cpp \
    Handle/putyourcodehere.cpp \
    Handle/Reader/folderreader.cpp \
    Handle/parseexception.cpp \
    Handle/BasicHandle/rotation.cpp \
    Handle/Parameters/handleparameters.cpp \
    Handle/Parameters/sourceparameters.cpp \
    Handle/Parameters/slider.cpp \
    Handle/Parameters/checkbox.cpp \
    Handle/Parameters/combobox.cpp \
    Handle/Parameters/dial.cpp \
    Handle/Parameters/radiobutton.cpp \
    Handle/Parameters/spinbox.cpp \
    Handle/handletools.cpp \
    Handle/BasicHandle/tovideo.cpp \
    Handle/BasicHandle/tofiles.cpp \
    View/graphicsview.cpp \
    Handle/Parameters/colorselection.cpp \
    View/submdiwindows.cpp \
    Handle/Parameters/inputtext.cpp \
    View/mdi.cpp

HEADERS += \
    Handle/Handle.h \
    Handle/virtualhandle.h \
    Handle/modelhandle.h \
    Handle/videoview.h \
    Handle/videoextractor.h \
    Handle/videoreader.h \
    Handle/imagedata.h \
    View/mainwindow.h \
    exception.h \
    Handle/putyourcodehere.h \
    Handle/Reader/folderreader.h \
    Handle/parseexception.h \
    Handle/BasicHandle/rotation.h \
    Handle/Parameters/handleparameters.h \
    Handle/Parameters/sourceparameters.h \
    Handle/Parameters/slider.h \
    Handle/Parameters/checkbox.h \
    Handle/Parameters/combobox.h \
    Handle/Parameters/dial.h \
    Handle/Parameters/radiobutton.h \
    Handle/Parameters/spinbox.h \
    Handle/handletools.h \
    Handle/BasicHandle/tovideo.h \
    Handle/BasicHandle/tofiles.h \
    View/graphicsview.h \
    Handle/Parameters/colorselection.h \
    View/submdiwindows.h \
    Handle/Parameters/inputtext.h \
    View/mdi.h

LIBS += -lopencv_core \
        -lopencv_video \
        -lopencv_legacy \
        -lopencv_imgproc \
        -lopencv_highgui

OTHER_FILES += \
    README.md

FORMS += \
    View/mainwindow.ui
