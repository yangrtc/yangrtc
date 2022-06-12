//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef SRC_YANGDATACHANNEL_INCLUDE_YANGMESSAGETCPI_H_
#define SRC_YANGDATACHANNEL_INCLUDE_YANGMESSAGETCPI_H_
#include <stdint.h>

class YangMessageHandleI{
public:
	YangMessageHandleI(){}
	virtual ~YangMessageHandleI(){}
	virtual void decodeMessage(uint8_t* p,int32_t plen)=0;
};



#endif /* SRC_YANGDATACHANNEL_INCLUDE_YANGMESSAGETCPI_H_ */
