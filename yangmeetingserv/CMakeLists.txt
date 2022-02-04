cmake_minimum_required(VERSION 2.8)
project(yangmeetingserv)

add_definitions(-D__STDC_FORMAT_MACROS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -ffunction-sections -fdata-sections")
set(HOME_BASE "../")

# 头文件目录
#include_directories(${HOME_BASE}/src/yangsrt/include)
#include_directories(${HOME_BASE}/src/yangsql/include)
include_directories(./lib)
include_directories(./src)

link_directories("../lib")

# 发现目录下的源文件
aux_source_directory(./src/yangdataserver DIR_SRCS)
aux_source_directory(./src/yanghttp DIR_SRCS)
aux_source_directory(./src/yangsrt/src DIR_SRCS)
aux_source_directory(./src/yangsql/src DIR_SRCS)
aux_source_directory(./src/ DIR_SRCS)


include(utils.cmake)
# 排除不参与编译的文件


add_executable(yangmeetingserv ${DIR_SRCS})

target_link_libraries(yangmeetingserv libst.a libpthread.so libmysqlclient.so)
