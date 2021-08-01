QT       += core gui
QT +=network
QT +=core xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


unix{
    HOME_BASE=../
    INCLUDEPATH += $$HOME_BASE/include
    CONFIG(debug, debug|release) {
        LIBS += -L$$HOME_BASE/bin/lib_debug
        DESTDIR += $$HOME_BASE/bin/app_debug
    }else{
        LIBS += -L$$HOME_BASE/bin/lib_release
        DESTDIR += $$HOME_BASE/bin/app_release
    }
 LIBS += -lYangRecordLib -lYangAVLib  -lpthread -lasound -ldl
}
win32{
    DEFINES += __WIN32__
    DEFINES +=_AMD64_
    HOME_BASE=..\
    INCLUDEPATH += $$HOME_BASE\include
    CONFIG(debug, debug|release) {
        LIBS += -L$$HOME_BASE/bin/lib_win_debug
        DESTDIR += $$HOME_BASE/bin/app_debug
    }else{
        LIBS += -L$$HOME_BASE/bin/lib_win_release
        DESTDIR += $$HOME_BASE/bin/app_debug
    }

    LIBS +=  -lYangRecordLib -lYangAVLib -lws2_32 -lwinmm -ldmoguids -lole32 -lStrmiids
}



# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    recordmainwindow.cpp \
    src/video/yangrecordthread.cpp \
    src/video/yangrecordvideowin.cpp \
    src/video/yangrecordwin.cpp \
    src/yangnav/YangCameraCommand.cpp \
    src/yangnav/YangRecordSocket.cpp \
    src/yangnav/YangTraceListen.cpp \
    src/yangplayer/YangPlayWidget.cpp \
    src/yangwinutil/yangdesktip.cpp \
    src/yangwinutil/yanghttputil.cpp \
    src/yangwinutil/yanglinkbutton.cpp \
    src/yangwinutil/yangrecordcontext.cpp

HEADERS += \
    recordmainwindow.h \
    src/video/yangrecordthread.h \
    src/video/yangrecordvideowin.h \
    src/video/yangrecordwin.h \
    src/video/yangvideotype.h \
    src/yangnav/YangCameraCommand.h \
    src/yangnav/YangRecordI.h \
    src/yangnav/YangRecordSocket.h \
    src/yangnav/YangTraceListen.h \
    src/yangplayer/YangPlayWidget.h \
     src/yangwinutil/YangWinIni.h \
    src/yangwinutil/yangdesktip.h \
    src/yangwinutil/yanghttputil.h \
    src/yangwinutil/yanglinkbutton.h \
    src/yangwinutil/yangqInterfaces.h \
    src/yangwinutil/yangrecordcontext.h

FORMS += \
    recordmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
