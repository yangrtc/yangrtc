#ifndef __YangVideoEncoderHandle__
#define __YangVideoEncoderHandle__
#include "YangVideoEncoder.h"
#include "stdint.h"

#include <vector>

#include "yangutil/buffer/YangVideoEncoderBuffer.h"
#include "yangutil/buffer/YangVideoBuffer.h"
#include "yangutil/sys/YangIni.h"
#include "yangutil/sys/YangThread.h"

using namespace std;
class YangVideoEncoderHandle:public YangThread,public YangEncoderCallback
{
public:
	YangVideoEncoderHandle(YangVideoParam *pini,YangVideoEncParam *enc);
	~YangVideoEncoderHandle(void);

private:
	int m_isInit;

public:
	int m_isStart;
	void init();
	void stop();
	void setOutVideoBuffer(YangVideoEncoderBuffer * pvl);
	void setInVideoBuffer(YangVideoBuffer *pvl);
	//void setRoomState(int pst);
	void setVideoMetaData(YangVideoMeta *pvmd);
	void onVideoData(unsigned char* p,int plen,long long timestamp,int pframetype,int puid);
	void onAudioData(unsigned char* p,int plen,int puid);
protected:
	void run();
	void stopLoop();
	void startLoop();
	void saveFile(char *fileName, unsigned char *pBuffer, long BufferLen);

private:
	YangVideoBuffer *m_in_videoBuffer;
	YangVideoEncoderBuffer *m_out_videoBuffer;
	YangVideoMeta *m_vmd;
	int m_isConvert;
	YangVideoParam *m_para;
	YangVideoEncParam *m_enc;

};
#endif
