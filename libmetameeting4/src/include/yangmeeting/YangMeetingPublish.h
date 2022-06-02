//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef MeetingPubBase_H
#define MeetingPubBase_H
#include <yangmeeting/YangMeetingCapture.h>
#include <yangmeeting/YangMeetingEncoder.h>
#include <yangmeeting/YangMeetingNet.h>
#include <yangmeeting/yangmeetingtype.h>
#include "yangutil/buffer/YangAudioEncoderBuffer.h"
#include "yangutil/buffer/YangAudioBuffer.h"
#include "yangutil/sys/YangIni.h"
#include "yangutil/buffer/YangVideoEncoderBuffer.h"
#include "yangutil/buffer/YangVideoBuffer.h"
class YangMeetingPublish:public YangSendRequestCallback
{
    public:
        YangMeetingPublish(YangMeetingContext *pcontext);
        virtual ~YangMeetingPublish();

    void sendRequest(int32_t puid, uint32_t ssrc, YangRequestType req);
    void startPubVideo();
    void startPubAudio();
	void initAudioEncoding(YangMeetingNet *prr);
	void initVideoEncoding(YangMeetingNet *prr);
	void startAudioCapture(YangPreProcess *pp);
	void startVideoCapture();
	void setNetList(YangMeetingNet *prr);
	void initVideoMeeting();
	void startAudioEncoding();
	void startVideoEncoding();
	void startAudioCaptureState();
	void startVideoCaptureState();
	void stopAudioCaptureState();
	void stopVideoCaptureState();
	void setNetBuffer(YangMeetingNet *prr);
	YangVideoBuffer * getPreVideoBuffer();
	void stopAll();
	void setAec(YangRtcAec *paec);
	void setInAudioBuffer(vector<YangAudioPlayBuffer*> *pbuf);
	void change(int32_t st);
#if Yang_HaveVr
	void addVr();
	void delVr();
#endif
	void sendKeyframe();
    protected:

    private:
	YangMeetingContext *m_context;
	YangMeetingEncoder *m_encoder;
	YangMeetingCapture *m_capture;
	 int32_t isStartAudioCapture,isStartVideoCapture;
	 int32_t isStartAudioEncoder,isStartVideoEncoder;
	void stopAudioState();
	void stopVideoState();
	void initCapture();
};

#endif //
