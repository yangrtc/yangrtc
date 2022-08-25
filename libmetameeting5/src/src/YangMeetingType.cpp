//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangmeeting/yangmeetingtype.h>

#include <yangutil/sys/YangIni.h>
#include <yangutil/sys/YangLog.h>
YangMeetingContext::YangMeetingContext() {
	//videoBuffers=NULL;
	receive = NULL;
}
YangMeetingContext::~YangMeetingContext() {
	//videoBuffers=NULL;
	receive = NULL;
//	  for(std::map<int, YangAudioParam*>::iterator it = remoteAudio.begin(); it != remoteAudio.end(); ++it) {
	//        	yang_delete(it->second);
	//    }
	if (remoteAudio.size() > 0)
		remoteAudio.clear();

	// for(std::map<int, YangVideoParam*>::iterator it = remoteVideo.begin(); it != remoteVideo.end(); ++it) {
	// 	        	yang_delete(it->second);
	//	    }
	if (remoteVideo.size() > 0)
		remoteVideo.clear();

}

void YangMeetingContext::initExt(void *filename) {
    YangIni *ini = (YangIni*) filename;


	memset(&hd, 0, sizeof(YangZbhdParam));

    hd.meetingId=ini->readIntValue(ini->filename,(const char*)"hd",(const char*) "meetingId", 1001);
	memset(hd.app, 0, sizeof(hd.app));
    ini->readStringValue(ini->filename,(const char*)"hd", (const char*)"app", hd.app, (const char*)"live");
#if Yang_Enable_Vr
	memset(bgFilename, 0, sizeof(bgFilename));
	yi.readStringValue("sys", "bgFilename", bgFilename, "/home/yang/bmp/jpg/03.jpeg");
#endif

	memset(&user,0,sizeof(YangUser));
	memset(&meeting,0,sizeof(YangMeeting));


}
