#ifndef __yangmeetingtype1__
#define __yangmeetingtype1__
#include <yangmeeting/YangMeetingMessageI.h>
#include "yangutil/yangtype.h"
//#include "sys/YangLog.h"
//#include "yangutil/yangInterfaces.h"
#include "yangutil/buffer/YangVideoBuffer.h"
#include <vector>

struct YangUser {
        int userId;
	char userName[30];
	char loginName[30];
	int myId;
	int roomAdmin;
	int micFlag;
	int camFlag;
};
struct YangMeeting {
	int meetingId;
	char meetingName[35];
	int departId;
	int meetingTime = 0;
	int roomAdmin = 0;
};

struct YangZbhdParam{
	int meetingId;
	char app[20];
};


struct YangMeetingContext {
	YangAudioParam audio;
	YangVideoParam video;
	YangSysParam sys;
	YangZbhdParam hd;
	YangVideoEncParam enc;
	std::vector<int> audiouids;
	std::vector<int> videouids;
	//std::vector<int> playvideouids;
	//std::vector<int> playaudiouids;
	YangUser user;
	YangMeeting meeting;
	std::vector<YangVideoBuffer*> *videoBuffers;
	YangReceiveMessageI *receive;
	char bgFilename[128];
};

#endif
