//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef YANGHTTP_YANGHTTP_H_
#define YANGHTTP_YANGHTTP_H_
#include "yangsql/include/YangConf.h"
class YangHttp {
public:
	YangHttp();
	virtual ~YangHttp();
	void handle();
	void cycle();
	static void* run(void *arg);
	YangConf *m_conf;
};

#endif /* YANGHTTP_YANGHTTP_H_ */
