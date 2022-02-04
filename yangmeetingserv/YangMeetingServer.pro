TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# Copyright (c) 2019-2022 yanggaofeng

    HOME_BASE=../

    INCLUDEPATH += ./src
    INCLUDEPATH += ./lib
    LIBS += -L$$HOME_BASE/yangmeetingserv/lib
    LIBS += -lst  -lpthread -lmysqlclient
  CONFIG(debug, debug|release) {
        DESTDIR += $$HOME_BASE/bin/server_debug
    }else{

        DESTDIR += $$HOME_BASE/bin/server_release
    }
SOURCES += \
    src/yangdataserver/YangDataChannelServer.cpp \
    src/yangdataserver/YangMapMeeting.cpp \
    src/yangdataserver/YangMessageData.cpp \
    src/yangdataserver/YangServerMeeting.cpp \
    src/yangdataserver/YangStThread.cpp \
    src/yangdataserver/YangThread.cpp \
    src/yangdataserver/YangUserDataHandle.cpp \
    src/yanghttp/YangHttp.cpp \
    src/yanghttp/YangServerletManager.cpp \
    src/yanghttp/httpserver.cpp \
    src/yangmeetingserv.cpp \
    src/yangsql/src/YangConf.cpp \
    src/yangsql/src/YangConnectionPool.cpp \
    src/yangsql/src/YangMysqlBase.cpp \
    src/yangsql/src/YangUserManager.cpp \
    src/yangsrt/src/YangTsBuffer.cpp \
    src/yangsrt/src/YangTsMuxer.cpp \
    src/yangsrt/src/YangTsPacket.cpp \
    src/yangsrt/src/YangTsdemux.cpp \
    src/yangsrt/src/YangTsdemuxer.cpp \
    src/yangsrt/src/common.cpp \
    src/yangsrt/src/crc.cpp \
    src/yangsrt/src/srt_data.cpp

HEADERS += \
    src/yangdataserver/YangCommandId.h \
    src/yangdataserver/YangCommon.h \
    src/yangdataserver/YangDataChannelServer.h \
    src/yangdataserver/YangMapMeeting.h \
    src/yangdataserver/YangMessageData.h \
    src/yangdataserver/YangServerMeeting.h \
    src/yangdataserver/YangStThread.h \
    src/yangdataserver/YangThread.h \
    src/yangdataserver/YangUserContext.h \
    src/yangdataserver/YangUserDataHandle.h \
    src/yanghttp/YangHttp.h \
    src/yanghttp/YangServerletManager.h \
    src/yanghttp/httpserver.h \
    src/yangsql/include/YangConf.h \
    src/yangsql/include/YangConnectionPool.h \
    src/yangsql/include/YangMysqlBase.h \
    src/yangsql/include/YangUserManager.h \
    src/yangsrt/include/YangTsBuffer.h \
    src/yangsrt/include/YangTsMuxer.h \
    src/yangsrt/include/YangTsPacket.h \
    src/yangsrt/include/YangTsPid.h \
    src/yangsrt/include/YangTsdemux.h \
    src/yangsrt/include/YangTsdemuxer.h \
    src/yangsrt/include/common.h \
    src/yangsrt/include/crc.h \
    src/yangsrt/include/srt_data.hpp
