#ifndef ___YangAudioBuffer__
#define ___YangAudioBuffer__
#include <string.h>

#include "YangBuffer.h"
class YangAudioBuffer:public YangBuffer
{
public:
	YangAudioBuffer(int plen,int pcacheNum);
	~YangAudioBuffer(void);
	void putAudio(unsigned char *p_buf);
	int getAudio(unsigned char *p_buf);
	unsigned char *getAudio();
	void reset();

private:
	int m_headerLen,m_in,m_out;
	int m_bufLen;

};
#endif
