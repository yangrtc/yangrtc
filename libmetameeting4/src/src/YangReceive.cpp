//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangmeeting/YangReceive.h>
#include <yangmeeting/YangMeetingMessageI.h>
#include <yangutil/yang_unistd.h>
#include <yangutil/sys/YangLog.h>
#include <yangutil/sys/YangMath.h>
#include <yangstream/YangStreamType.h>
#include <yangavutil/video/YangNalu.h>

void g_meetingrecv_receiveAudio(void* user,YangFrame *audioFrame){
	if(user==NULL) return;
	YangReceive* rtcHandle=(YangReceive*)user;
	rtcHandle->receiveAudio(audioFrame);
}
void g_meetingrecv_receiveVideo(void* user,YangFrame *videoFrame){
	if(user==NULL) return;
	YangReceive* rtcHandle=(YangReceive*)user;
	rtcHandle->receiveVideo(videoFrame);
}

void g_meetingrecv_receiveMsg(void* user,YangFrame *msgFrame){
	if(user==NULL) return;
	YangReceive* rtcHandle=(YangReceive*)user;
}
int32_t g_meetingrecv_sendRtcMessage(void* user,int puid,YangRtcMessageType mess){
	if(user==NULL) return 1;
	YangReceive* rtcHandle=(YangReceive*)user;
	//if(rtcHandle->m_recv->sendRtcMessage) rtcHandle->m_recv->sendRtcMessage(rtcHandle->m_recv->context,mess);
	return Yang_Ok;
}
YangReceive::YangReceive(YangMeetingContext *pcontext) {
	m_context = pcontext;
	m_context->streams.setDecoderMediaConfigCallback(this);
	isReceiveConvert = 0;
	isReceived = 0;
	m_isStart = 0;
	m_out_videoBuffer = NULL;
	m_out_audioBuffer = NULL;
	isReceived = 0;
	isReceiveConvert = 0;
	m_headLen = pcontext->avinfo.audio.audioDecoderType == 0 ? 2 : 1;
	m_cache = NULL;

	m_context->sendRtcMessage.context=this;
	m_context->sendRtcMessage.sendRtcMessage=g_meetingrecv_sendRtcMessage;
}

YangReceive::~YangReceive() {

	if (isReceiveConvert) {
		stop();
		while (m_isStart) {
			yang_usleep(1000);
		}
	}
	disConnectAll();
//	for (uint32_t i = 0; i < m_players.size(); i++) {
	//	if (m_players.at(i)) {
//			delete m_players.at(i);
	//		m_players.at(i) = NULL;
	//	}
	//}
	m_players.clear();
	yang_delete(m_cache);
	m_context = NULL;
	m_out_audioBuffer = NULL;
	m_out_videoBuffer = NULL;
}

void YangReceive::receiveAudio(YangFrame *audioFrame) {
	//audioFrame->payload += m_headLen;
	//audioFrame->nb -= m_headLen;
	//m_out_audioBuffer->putPlayAudio(audioFrame);

	m_out_audioBuffer->putPlayAudio(audioFrame);

}
void YangReceive::receiveVideo(YangFrame *videoFrame) {
    if(videoFrame==NULL||videoFrame->payload==NULL) return;
     m_out_videoBuffer->putEVideo(videoFrame);
}

void YangReceive::setMediaConfig(int32_t puid, YangAudioParam *audio,
		YangVideoParam *video) {

	//if (m_context)	m_context->remoteAudio[puid] = audio;
	//if (m_context)	m_context->remoteVideo[puid] = video;
	//yang_post_message(YangM_Sys_NofityMediaParam, puid, NULL);
}

int32_t YangReceive::connectServer(int32_t puid) {
	if (getPlayer(puid)) {
		return getPlayer(puid)->connectServer(getPlayer(puid)->context);
	}
	return 1;
}

int32_t YangReceive::playAudio(int32_t puid) {
	addPlay(puid);
	getPlayer(puid)->context->audioStream = 1;
	if (getPlayer(puid)->isconnected(getPlayer(puid)->context))
		return Yang_Ok;
	int32_t ret = getPlayer(puid)->connectServer(getPlayer(puid)->context);
	if (ret)
		return ret;
	getPlayer(puid)->context->streamInit = 1;
	return ret;
}

int32_t YangReceive::playVideo(int32_t puid) {
	addPlay(puid);
	getPlayer(puid)->context->videoStream = 1;
	if (getPlayer(puid)->isconnected(getPlayer(puid)->context))
		return Yang_Ok;
	int32_t ret = getPlayer(puid)->connectServer(getPlayer(puid)->context);
	if (ret)
		return ret;
	getPlayer(puid)->context->streamInit = 1;
	return ret;
}

int32_t YangReceive::unPlayAudio(int32_t puid) {
	int32_t index = getPlayIndex(puid);
	if (index > -1) {
		YangStreamHandle *sh = m_players.at(index);
		if (sh) {
			sh->context->audioStream = 0;
			removePlay(puid);
		}
		sh = NULL;

	}
	return Yang_Ok;
}

int32_t YangReceive::unPlayVideo(int32_t puid) {
	int32_t index = getPlayIndex(puid);
	if (index > -1) {
		YangStreamHandle *sh = m_players.at(index);
		if (sh) {
			sh->context->videoStream = 0;
			removePlay(puid);
		}
		sh = NULL;
	}
	return Yang_Ok;
}

void YangReceive::disConnectAll() {
	for (size_t i = 0; i < m_players.size(); i++) {
		YangStreamHandle *sh = m_players.at(i);
		sh->disConnectServer(sh->context);
		yang_destroy_stream(sh);
		yang_free(sh);
	}
	m_players.clear();
}

void YangReceive::disConnect(int32_t puid) {
	for (size_t i = 0; i < m_players.size(); i++) {
		if (m_players.at(i)->context->uid == puid) {
			YangStreamHandle *sh = m_players.at(i);
			sh->disConnectServer(sh->context);
			yang_destroy_stream(sh);
			yang_free(sh);
			m_players.erase(m_players.begin() + i);
			return;
		}
	}
}
void YangReceive::removePlay(int32_t puid) {
//	int ind=-1;
//	if(m_context) ind=m_context->streams.getIndex(puid);
//	if(ind>-1){
//		yang_delete(m_context->streams.m_playBuffers->at(ind));
//		m_context->streams.m_playBuffers->erase(m_context->streams.m_playBuffers->begin()+ind);
//	}

	for (int32_t index = 0; index < (int) m_players.size(); index++) {
		if (m_players.at(index)->context->uid == puid) {
			YangStreamHandle* sh=m_players.at(index);
			if (sh->context->audioStream
					|| sh->context->videoStream)
				return;
			sh->context->streamInit = 0;
			sh->disConnectServer(sh->context);
			yang_destroy_stream(sh);
			yang_free(m_players.at(index));
			m_players.erase(m_players.begin() + index);
			return;
		}

	}
}
int32_t YangReceive::getPlayIndex(int32_t puid) {
	for (int32_t i = 0; i < (int) m_players.size(); i++) {
		if (m_players.at(i)->context->uid == puid)
			return i;
	}
	return -1;
}

YangStreamHandle* YangReceive::getPlayer(int32_t puid) {
	for (size_t i = 0; i < m_players.size(); i++) {
		if (m_players.at(i)->context->uid == puid)
			return m_players.at(i);
	}
	return NULL;
}
void YangReceive::setOutAudioBuffer(YangAudioEncoderBuffer *pbuf) {
	m_out_audioBuffer = pbuf;
}
void YangReceive::setOutVideoBuffer(YangVideoDecoderBuffer *pbuf) {
	m_out_videoBuffer = pbuf;
}
void YangReceive::stop() {
	isReceiveConvert = 0;
}

void YangReceive::run() {
	m_isStart = 1;
	startLoop();
	m_isStart = 0;
}
void YangReceive::setReceiveBytes(int32_t pbytes) {

}
int32_t YangReceive::reconnect() {
	int32_t ret = Yang_Ok;
	int32_t retCode = Yang_Ok;
	for (size_t i = 0; i < m_players.size(); i++) {
		if (m_players.at(i)->getConnectState(m_players.at(i)->context)) {
			retCode = m_players.at(i)->reconnect(m_players.at(i)->context);
			if (retCode)
				ret = retCode;
		}

	}
	return ret;
}
void YangReceive::addPlay(int32_t puid) {
	if (getPlayIndex(puid) == -1) {
		//YangStreamFactory sf;
		int32_t ret = 0;
		YangStreamConfig streamConf;
		memset(&streamConf,0,sizeof(YangStreamConfig));
		streamConf.streamOptType = Yang_Stream_Play;
		strcpy(streamConf.app , "live");
		streamConf.uid = puid;

		//strcpy(streamConf. , "127.0.0.1");
		streamConf.localPort = 10000+yang_random()%15000;	//8100;

		char s[128] = { 0 };

		//m_players.push_back(sf.createStreamHandle(m_context->avinfo.sys.transType, puid,m_context));
		if (m_context->avinfo.sys.transType == Yang_Rtmp) {
			sprintf(s, "user%d", puid);
			strcpy(streamConf.remoteIp ,m_context->avinfo.sys.rtmpServerIP);
			streamConf.remotePort = m_context->avinfo.sys.rtmpPort;
		} else if (m_context->avinfo.sys.transType == Yang_Srt) {
			sprintf(s, "%d.%d", m_context->meeting.meetingId, puid);
			strcpy(streamConf.remoteIp , m_context->avinfo.sys.srtServerIP);
			streamConf.remotePort = m_context->avinfo.sys.srtPort;
		} else if (m_context->avinfo.sys.transType == Yang_Webrtc) {
			sprintf(s, "user%d", puid);
			strcpy(streamConf.remoteIp ,m_context->avinfo.sys.rtcServerIP);
			streamConf.remotePort = m_context->avinfo.sys.rtcPort;
			m_headLen = 0;
		}

		strcpy(streamConf.stream , s);


		streamConf.recvCallback.context=this;
		streamConf.recvCallback.receiveAudio=g_meetingrecv_receiveAudio;
		streamConf.recvCallback.receiveVideo=g_meetingrecv_receiveVideo;
		streamConf.recvCallback.receiveMsg=g_meetingrecv_receiveMsg;

		YangStreamHandle* sh=(YangStreamHandle*)calloc(sizeof(YangStreamHandle),1);
		yang_create_streamHandle(sh,&streamConf,&m_context->avinfo);

		m_players.push_back(sh);
//		if(m_context&&m_context->streams.getIndex(puid)==-1){
//			m_context->streams.m_playBuffers->push_back(new YangSynBuffer());
//			m_context->streams.m_playBuffers->back()->m_uid=puid;
//		}
		if (ret) {
			yang_error("player connect error");
		}

	}
}

void YangReceive::startLoop() {

	yang_reindex(m_out_audioBuffer);
	yang_reindex(m_out_videoBuffer);
	int32_t receiveBytes = 0;
	int32_t bufLen = 0;
	int32_t retCode = Yang_Ok;
	isReceiveConvert = 1;
	isReceived = 1;
	int32_t tuid = 0;
	while (isReceiveConvert == 1) {
		if (m_players.size() == 0) {
			yang_usleep(10000);
			continue;
		}
		/**	if(retCode){
		 retCode=reconnect();
		 if(!isReceiveConvert) break;
		 if(retCode) sleep(3);
		 continue;
		 }**/
		receiveBytes = 0;
		for (uint32_t i = 0; i < m_players.size(); i++) {
			if (!m_players.at(i)->context->streamInit)
				continue;
			bufLen = 0;
			tuid = m_players.at(i)->context->uid;
			retCode = m_players.at(i)->receiveData(m_players.at(i)->context,&bufLen);
			if (retCode && !m_players.at(i)->isconnected(m_players.at(i)->context)) {
				if (i < m_players.size() && m_players.at(i)->context->uid == tuid) {
					m_players.at(i)->context->streamInit = 0;
					m_players.at(i)->disConnectServer(m_players.at(i)->context);
					yang_post_message(YangM_Sys_PlayMediaServerError,
							m_players.at(i)->context->uid, NULL);
				}
			}
			//printf("r%d",bufLen);
			receiveBytes += bufLen;
		}
		//if (retCode) {
		//	yang_error("Receive Data Error:%d", retCode);
		//	break;
		//}
		if (receiveBytes == 0)
			yang_usleep(1000);
	}	            		//end while
	//yang_debug("\n***********stop data receive......***************************\n");

	isReceived = 0;
}
