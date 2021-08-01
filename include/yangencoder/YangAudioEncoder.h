#ifndef ___YangAudioEncoderPipe__
#define ___YangAudioEncoderPipe__
#include "yangutil/yangtype.h"
#include "yangutil/buffer/YangAudioBuffer.h"
#include "yangutil/buffer/YangAudioEncoderBuffer.h"
#include "yangutil/sys/YangIni.h"
#include "yangutil/sys/YangThread.h"
#include "YangEncoder.h"

class YangAudioEncoder//:public YangThread
{
public:
	YangAudioEncoder();
	virtual ~YangAudioEncoder(void);
    virtual void init(YangAudioParam *pap)=0;
    virtual int encoder(int puid,unsigned char *p_buf,int bufLen,YangEncoderCallback* pcallback)=0;
    void stop();
    int m_uid;

protected:
    void setAudioPara(YangAudioParam *pap);
	int m_isInit;
	YangAudioParam m_yap;
};

#endif
