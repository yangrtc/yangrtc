
#ifndef YANGSTREAM_INCLUDE_YANGSTREAMBASE_H_
#define YANGSTREAM_INCLUDE_YANGSTREAMBASE_H_
#include <stdint.h>
struct YangStreamConf{
	char server[50];
	char app[20];
	char stream[20];
	char url[60];
	int port;
	int streamOptType;
};

class YangReceiveCallback{
public:
	YangReceiveCallback(){};
	virtual ~YangReceiveCallback(){};
	virtual void receiveAudio(int puid,unsigned char* p,int plen)=0;
	virtual void receiveVideo(int puid,unsigned char* p,int plen,long long ptimestamp,int keyframe)=0;
};
class YangStreamBase {
public:
	YangStreamBase(int puid);
	virtual ~YangStreamBase();
	void init(int streamOptType,char *server, char *app, char *streamName,int pport);
	int connectServer();
	int disConnectServer();
	virtual int reconnect()=0;
	virtual int receiveData(int *plen)=0;
	virtual int publishVideoData(uint8_t *srcVideoSource, int plen,	long long videoTimestamp, int frameType)=0;
	virtual int publishAudioData(uint8_t *buf, int plen, long long audioTimestamp,int audioType)=0;
	virtual int getConnectState()=0;
	virtual int getIsconnected()=0;
	void setReceiveCallback(YangReceiveCallback *pdata);


	int m_streamInit;
	int m_uid;
	int m_audioStream;
	int m_videoStream;

protected:
	virtual int connectMediaServer()=0;
	virtual int disConnectMediaServer()=0;
	YangStreamConf m_conf;
	YangReceiveCallback *m_data;
	int m_netState;
};

#endif /* YANGSTREAM_INCLUDE_YANGSTREAMBASE_H_ */
