#ifndef INCLUDE_YANGUTIL_SYS_YANGSYSMESSAGEI_H_
#define INCLUDE_YANGUTIL_SYS_YANGSYSMESSAGEI_H_
enum YangSysMessageType {
	YangM_Sys_Shutdown,
	YangM_Sys_ConnectServer,
	YangM_Sys_DisconnectServer,
	YangM_Sys_ConnectServerInterrupt,

	YangM_Sys_PushMediaServerConnect,
	YangM_Sys_PlayMediaServerConnect,
	YangM_Sys_PushMediaServerError,
	YangM_Sys_PlayMediaServerError,

	YangM_Sys_Login,
	YangM_Sys_Logout,
	YangM_Sys_GetMeetinginfo,
	YangM_Sys_Setvr,
	YangM_Sys_UnSetvr,
	YangM_Sys_Pubaudio,
	YangM_Sys_Pubvideo,
	YangM_Sys_UnPubaudio,
	YangM_Sys_UnPubvideo,
	YangM_Sys_Playaudio,
	YangM_Sys_Playvideo,
	YangM_Sys_UnPlayaudio,
	YangM_Sys_UnPlayvideo
};
class YangSysMessageI {
public:
	YangSysMessageI();
	virtual ~YangSysMessageI();
	virtual void success()=0;
	virtual void failure(int errcode)=0;
};
struct YangSysMessage {
	int uid;
	YangSysMessageType messageId;
	int handleState;
	YangSysMessageI *handle;
};
class YangReceiveMessageI {
public:
	YangReceiveMessageI() {
	};
	virtual ~YangReceiveMessageI() {
	};
	virtual void receiveError(int pet)=0;
	virtual void receiveMessage(char *pstr)=0;
	virtual void receiveSysMessage(YangSysMessage *psm, int phandleRet)=0;
};
void yang_post_message(YangSysMessageType st, int uid,YangSysMessageI *mhandle);
void yang_post_message1(YangSysMessageType st, int uid, int handleState,YangSysMessageI *mhandle);
#endif /* INCLUDE_YANGUTIL_SYS_YANGSYSMESSAGEI_H_ */
