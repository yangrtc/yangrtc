//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangmeeting/YangPublish.h>
#include <yangutil/yang_unistd.h>

#include <yangmeeting/YangMeetingMessageI.h>
#include <yangstream/YangStreamCapture.h>
#include <yangavutil/video/YangNalu.h>
#include <yangavutil/video/YangMeta.h>
#include <yangutil/sys/YangLog.h>
#include <yangutil/sys/YangMath.h>
#include <yangstream/YangStreamType.h>
#include <stdio.h>

void g_meetingstream_sendData(void* context,YangFrame* msgFrame){
	YangPublish* push=(YangPublish*)context;
	push->publishMsg(msgFrame);
}

void g_meetingstream_receiveMsg(void* user,YangFrame *msgFrame){
	if(user==NULL) return;
	YangPublish* rtcHandle=(YangPublish*)user;
	rtcHandle->receiveMsg(msgFrame);
	//if(rtcHandle->m)
}


YangPublish::YangPublish(YangMeetingContext *pcontext) {
	m_context = pcontext;
	m_context->streams.setSendRequestCallback(this);
	m_in_videoBuffer = NULL;
	m_in_audioBuffer = NULL;
	m_isStart = 0;
	m_isConvert = 0;
	m_vmd = NULL;
	m_audioEncoderType = m_context->avinfo.audio.audioEncoderType;
	m_netState = 1;
	m_isInit = 0;
	isPublished = 0;
	m_isPubVideo = 0, m_isPubAudio = 0;
	m_transType=Yang_Webrtc;
	notifyState=0;

	m_context->channeldataSend.context=this;
	m_context->channeldataSend.sendData=g_meetingstream_sendData;
}

YangPublish::~YangPublish() {
	if (m_isConvert) {
		stop();
		while (m_isStart) {
			yang_usleep(1000);
		}
	}
	m_context = NULL;
	m_in_videoBuffer = NULL;
	m_in_audioBuffer = NULL;
	m_vmd = NULL;
}

void YangPublish::sendRequest(int32_t puid,uint32_t ssrc,YangRequestType req){
	//	YangM_Sys_StartAudioCapture,	YangM_Sys_StartVideoCapture,

	if(req==Yang_Req_Sendkeyframe) yang_post_message(YangM_Sys_SendKeyframe,0,NULL);
	if(req==Yang_Req_Connected) {

		if(m_isPubAudio) yang_post_message(YangM_Sys_StartAudioCapture,0,NULL);
		if(m_isPubVideo) yang_post_message(YangM_Sys_StartVideoCapture,0,NULL);
	}
}
int32_t YangPublish::connectServer(int32_t puid){
    return m_pushs.back()->connectSfuServer();
}
int32_t YangPublish::publishMsg(YangFrame* msgFrame){

    if(m_pushs.size()>0) {
        msgFrame->uid=m_pushs.front()->streamConfig->uid;
        return m_pushs.front()->on_message(msgFrame);
    }
	return 1;
}
int32_t YangPublish::receiveMsg(YangFrame* msgFrame){

	if(m_context->channeldataRecv.receiveData)
        m_context->channeldataRecv.receiveData(m_context->channeldataRecv.context,msgFrame);
	return Yang_Ok;
}
int32_t YangPublish::pubAudioStream(int32_t puid) {
	int32_t ret = Yang_Ok;
	ret = connectMediaServer();
	if (ret)
		return ret;
	m_isPubAudio = 1;
	yang_post_message(YangM_Sys_StartAudioCapture,0,NULL);

	return Yang_Ok;
}
int32_t YangPublish::pubVideoStream(int32_t puid) {
	int32_t ret = Yang_Ok;
	ret = connectMediaServer();
	if (ret)
		return ret;
	m_isPubVideo = 1;
	yang_post_message(YangM_Sys_StartVideoCapture,0,NULL);

	return ret;
}
int32_t YangPublish::unPublishAudioStream(int32_t puid) {
	m_isPubAudio = 0;
	if (!m_isPubVideo)
		disConnectMediaServer();
	return Yang_Ok;
}
int32_t YangPublish::unPublishVideoStream(int32_t puid) {
	m_isPubVideo = 0;
	if (!m_isPubAudio)
		disConnectMediaServer();
	return Yang_Ok;
}

int32_t YangPublish::reconnectMediaServer() {
    return m_pushs.back()->connectSfuServer();

}
int32_t YangPublish::connectMediaServer() {
	if(m_pushs.size()>0) return Yang_Ok;
	int32_t ret = 0;
	YangStreamConfig streamConf;
	memset(&streamConf,0,sizeof(streamConf));

	strcpy(streamConf.app,"live");
	streamConf.streamOptType=Yang_Stream_Publish;

	strcpy(streamConf.remoteIp,m_context->avinfo.sys.rtcServerIP);
	streamConf.remotePort=m_context->avinfo.sys.rtcPort;
	sprintf(streamConf.stream, "user%d", m_context->user.userId);

	streamConf.uid=m_context->user.userId;//0 singleuser 1 multiuser

	streamConf.localPort=10000+yang_random()%15000;;

	streamConf.recvCallback.context=this;
	streamConf.recvCallback.receiveMsg=g_meetingstream_receiveMsg;

	streamConf.rtcCallback.context=this;
	memcpy(&streamConf.rtcCallback,&m_context->rtcCallback,sizeof(YangRtcCallback));
	if (m_pushs.size() == 0) {
        YangPeerConnection2* sh=new YangPeerConnection2(&m_context->avinfo,&streamConf);
        sh->init();
		m_pushs.push_back(sh);

	}



    ret = m_pushs.back()->connectSfuServer();

	if (ret)		return ret;

	yang_reindex(m_in_audioBuffer);
	yang_reindex(m_in_videoBuffer);
	return ret;
}
int32_t YangPublish::disConnectMediaServer() {
	if (m_pushs.size() > 0) {
        yang_delete(m_pushs.back());
		m_pushs.clear();
	}
	return Yang_Ok;
}
void YangPublish::stop() {
	m_isConvert = 0;
}

void YangPublish::run() {
	m_isStart = 1;
	startLoop();
	m_isStart = 0;
}

void YangPublish::setInAudioList(YangAudioEncoderBuffer *pbuf) {
	m_in_audioBuffer = pbuf;
}
void YangPublish::setInVideoList(YangVideoEncoderBuffer *pbuf) {
	m_in_videoBuffer = pbuf;
}
void YangPublish::setInVideoMetaData(YangVideoMeta *pvmd) {
	m_vmd = pvmd;
}

void YangPublish::startLoop() {

	isPublished = 0;
	m_isConvert = 1;
	YangStreamCapture data,metaFrame;
	memset(&data,0,sizeof(YangStreamCapture));
	memset(&metaFrame,0,sizeof(YangStreamCapture));
	yang_create_streamCapture(&data);
	yang_create_streamCapture(&metaFrame);
	YangFrame audioFrame;
	YangFrame videoFrame;
    memset(&audioFrame,0,sizeof(YangFrame));
    memset(&videoFrame,0,sizeof(YangFrame));
	data.initAudio(data.context,m_context->avinfo.sys.transType,m_context->avinfo.audio.sample, m_context->avinfo.audio.channel,
			(YangAudioCodec) m_context->avinfo.audio.audioEncoderType);
	data.initVideo(data.context,m_context->avinfo.sys.transType);
	metaFrame.initVideo(metaFrame.context,m_context->avinfo.sys.transType);
	YangVideoCodec videoType =	(YangVideoCodec) m_context->avinfo.video.videoEncoderType;
	YangVideoMeta* vmd=NULL;
	if(m_context->avinfo.enc.createMeta==0){
		vmd=(YangVideoMeta*)calloc(sizeof( YangVideoMeta),1);
	}
	size_t i = 0;
	int32_t ret = Yang_Ok;
	isPublished = 1;
	notifyState=1;
	YangH264NaluData nalu;
	while (m_isConvert == 1) {

		if ((!m_isPubVideo && !m_isPubAudio) || (m_pushs.size() == 0)) {
			yang_usleep(20000);
			continue;
		}

		if ((m_in_videoBuffer && m_in_videoBuffer->size() == 0)
				&& (m_in_audioBuffer && m_in_audioBuffer->size() == 0)) {
			yang_usleep(2000);
			continue;
		}
        if (m_pushs.size() == 0) {
			yang_usleep(500);
			continue;
		}
        YangPeerConnection2* stream=m_pushs.back();

        if(stream->isConnected()){
			if(notifyState&&m_transType<Yang_Webrtc){
						if(m_context) m_context->streams.sendRequest(0,0,Yang_Req_Connected);
						notifyState=0;
					}

		}else{
			yang_usleep(500);
			continue;
		}
		/**if(ret){
		 ret=reconnectMediaServer();
		 if(!m_isConvert) break;
		 sleep(3);
		 if(!ret){
		 yang_reindex(m_in_audioBuffer);
		 yang_reindex(m_in_videoBuffer);
		 }
		 continue;
		 }**/

		if (m_isPubAudio && m_in_audioBuffer && m_in_audioBuffer->size() > 0) {
			if (m_in_audioBuffer->size() > 100)
				yang_error("encode cache big..%d\n", m_in_audioBuffer->size());

			audioFrame.payload = m_in_audioBuffer->getAudioRef(&audioFrame);
			data.setAudioData(data.context,&audioFrame);
			//printf("ad%d-%d,",audioBufLen,adata.getAudioLen());
			for (i = 0; i < m_pushs.size(); i++) {
                ret = m_pushs.at(i)->on_audio(data.getAudioFrame(data.context));
                if (ret&&!m_pushs.at(i)->isConnected()) {
                    m_pushs.back()->close();
                    yang_post_message(YangM_Sys_PushMediaServerError,m_pushs.back()->streamConfig->uid,NULL);
				}
			}
		}

		if (m_isPubVideo && m_in_videoBuffer
				&& m_in_videoBuffer->size() > 0) {

			videoFrame.payload = m_in_videoBuffer->getEVideoRef(&videoFrame);

			if (videoFrame.frametype == YANG_Frametype_I) {

				if (m_vmd) {
					data.setVideoMeta(data.context,m_vmd->livingMeta.buffer,
							m_vmd->livingMeta.bufLen, videoType);
					//if (ret)	continue;
				} else {
					if (!vmd->isInit) {
						if (videoType == Yang_VED_264) {
							yang_createH264Meta(vmd, &videoFrame);
							yang_getConfig_Flv_H264(&vmd->mp4Meta,
									vmd->livingMeta.buffer,
									&vmd->livingMeta.bufLen);
						} else if (videoType == Yang_VED_265) {
							yang_createH265Meta(vmd, &videoFrame);
							yang_getConfig_Flv_H265(&vmd->mp4Meta,
									vmd->livingMeta.buffer,
									&vmd->livingMeta.bufLen);
						}
					}

					data.setVideoMeta(data.context,vmd->livingMeta.buffer,vmd->livingMeta.bufLen, videoType);


				}
				data.setVideoFrametype(data.context,YANG_Frametype_Spspps);
				data.setMetaTimestamp(data.context,videoFrame.pts);
                ret = stream->on_video(data.getVideoFrame(data.context));



				if (!m_context->avinfo.enc.createMeta) {

					memset(&nalu, 0, sizeof(YangH264NaluData));
					if (videoType == Yang_VED_264)
						yang_parseH264Nalu(&videoFrame, &nalu);
					else
						yang_parseH265Nalu(&videoFrame, &nalu);


					if (nalu.keyframePos > -1) {
						videoFrame.payload += nalu.keyframePos + 4;
						videoFrame.nb -= (nalu.keyframePos + 4);

					} else {
						videoFrame.payload = NULL;
						continue;
					}
				}

			}

			data.setVideoData(data.context,&videoFrame, videoType);
            ret = stream->on_video(data.getVideoFrame(data.context));

            if (ret && !stream->isConnected()) {
                stream->close();
			}

		}

	}			//end
	isPublished = 0;
	yang_destroy_streamCapture(&data);
	yang_destroy_streamCapture(&metaFrame);
}
