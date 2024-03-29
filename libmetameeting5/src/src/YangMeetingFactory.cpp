﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#include "YangMeetingHandleImpl.h"
#include <yangmeeting/yangmeetingtype.h>
#include <yangmeeting/YangMeetingFactory.h>
#include "yangutil/sys/YangIni.h"
#include "YangMeetingMessageHandle.h"



YangMeetingFactory::YangMeetingFactory() {

}
YangSysMessageHandle* YangMeetingFactory::createSysMessageHandle(YangMeetingContext *pcontext,YangReceiveMessageI* prec){
	return new YangMeetingMessageHandle(pcontext,prec);
}
YangMeetingHandle* YangMeetingFactory::createMeetingHandle(YangMeetingContext *pcontext){
	return new YangMeetingHandleImpl(pcontext);
}

YangMeetingHandle* YangMeetingFactory::getMeetingHandle(YangSysMessageHandle *phandle){
	return ((YangMeetingMessageHandle*)phandle)->m_videoMeeting;
}
/**
void YangMeetingFactory::createIni(const char* p_filename,YangMeetingContext *pcontext){
	YangMeetingConfigIni yi;
	yi.init(p_filename);
	//pcontext->m_log=new YangLog();
	yi.initAudio(&pcontext->avinfo.audio);
	yi.initVideo(&pcontext->avinfo.video);
	yi.initSys(&pcontext->avinfo.sys);
	yi.initHd(&pcontext->hd);
	yi.initEnc(&pcontext->avinfo.enc);
	yi.initRtc(&pcontext->rtc);
	//yi.initCamera(&pcontext->camera);
	//pcontext->hasVr=yi.readIntValue("sys","hasVr",0);
	memset(pcontext->bgFilename, 0, sizeof(pcontext->bgFilename));
	yi.readStringValue("sys", "bgFilename", pcontext->bgFilename, "/home/yang/bmp/jpg/03.jpeg");
	//pcontext->isMulterCamera=0;
	//pcontext->context=new YangMeetingContext1();


}
**/

