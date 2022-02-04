//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef YANGAPP_YANGPLAYAPP_H_
#define YANGAPP_YANGPLAYAPP_H_
#include <yangmeeting/yangmeetingtype.h>
#include <vector>

#include "yangavutil/audio/YangRtcAec.h"
#include "yangutil/buffer/YangAudioPlayBuffer.h"
#include "yangutil/buffer/YangVideoBuffer.h"
#include "yangutil/sys/YangIni.h"
using namespace std;

class YangMeetingAudioPlay {
public:
	YangMeetingAudioPlay(YangMeetingContext *pcontext);
	virtual ~YangMeetingAudioPlay();
	void initAudioPlay();
	void startAudioPlay();
	void setInAudioList(vector<YangAudioPlayBuffer*> *paudioList);
	void setAec(YangRtcAec *paec);
	int32_t getIsAecInit();

	//void stopAll();
private:
	YangMeetingContext *m_context;
};

#endif /* YANGAPP_YANGPLAYAPP_H_ */
