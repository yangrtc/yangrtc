//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <string.h>
#include "../include/srt_data.hpp"

SRT_DATA_MSG::SRT_DATA_MSG():_msg_type(SRT_MSG_DATA_TYPE)
    ,_len(0)
    ,_data_p(nullptr)
  {

}

SRT_DATA_MSG::SRT_DATA_MSG(unsigned int len):_msg_type(SRT_MSG_DATA_TYPE)
    ,_len(len)
 {
    _data_p = new unsigned char[len];
    memset(_data_p, 0, len);
}

SRT_DATA_MSG::SRT_DATA_MSG(unsigned char* data_p, unsigned int len):_msg_type(SRT_MSG_DATA_TYPE)
    ,_len(len)
    //,_key_path(path)
{
    _data_p = new unsigned char[len];
    memcpy(_data_p, data_p, len);
}

SRT_DATA_MSG::~SRT_DATA_MSG() {
    if (_data_p && (_len > 0)) {
        delete _data_p;
    }
}

unsigned int SRT_DATA_MSG::msg_type() {
    return _msg_type;
}

//std::string SRT_DATA_MSG::get_path() {
//    return _key_path;
//}

unsigned int SRT_DATA_MSG::data_len() {
    return _len;
}

unsigned char* SRT_DATA_MSG::get_data() {
    return _data_p;
}
