######################################################################
# Automatically generated by qmake (2.01a) Sun Mar 27 15:56:29 2016
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
              client \
              pc2rGUI \
              qtworkingdir/build-pc2rGUI-Desktop_Qt_5_6_0_GCC_64bit-Debug
INCLUDEPATH += . \
               client \
               pc2rGUI \
               qtworkingdir/build-pc2rGUI-Desktop_Qt_5_6_0_GCC_64bit-Debug

# Input
HEADERS += client/client.h \
           client/repr.h \
           client/session.h \
           client/tools.h \
           pc2rGUI/gui.h
FORMS += pc2rGUI/gui.ui
SOURCES += client/client.cpp \
           client/commands.cpp \
           client/repr.cpp \
           client/session.cpp \
           client/tools.cpp \
           pc2rGUI/gui.cpp \
           pc2rGUI/main.cpp
