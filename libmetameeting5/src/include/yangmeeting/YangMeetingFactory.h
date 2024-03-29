﻿//
// Copyright (c) 2019-2022 yanggaofeng
//

#ifndef YANGVIDEOMEETING_INCLUDE_YANGUTILFACTORY_H_
#define YANGVIDEOMEETING_INCLUDE_YANGUTILFACTORY_H_
#include <yangmeeting/yangmeetingtype.h>
#include "YangMeetingHandle.h"
#include "yangutil/sys/YangSysMessageHandle.h"

class YangMeetingFactory{
public:
	YangMeetingFactory();
	//void createIni(const char* p_filename,YangMeetingContext *pcontext);
	YangMeetingHandle* createMeetingHandle(YangMeetingContext *pcontext);
	YangMeetingHandle* getMeetingHandle(YangSysMessageHandle *phandle);
	YangSysMessageHandle* createSysMessageHandle(YangMeetingContext *pcontext,YangReceiveMessageI* prec);
};




#endif /* YANGVIDEOMEETING_INCLUDE_YANGUTILFACTORY_H_ */
