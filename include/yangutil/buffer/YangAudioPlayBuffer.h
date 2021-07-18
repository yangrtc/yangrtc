#ifndef ___YangAudioPlayBuffer__
#define ___YangAudioPlayBuffer__
#include <string.h>


#include "YangBuffer.h"
#include "../YangAvsynI.h"
struct YangAudioBufferHeader{
	int length;
	long long timestamp;
};
class YangAudioPlayBuffer:public YangBuffer
{
public:
	YangAudioPlayBuffer(int pBufLen);
	~YangAudioPlayBuffer(void);
	YangAvsynI* m_syn;
	void putAudio(unsigned char *p_buf,long long ptimestamp);
	void getAudio(unsigned char *p_buf,long long *timestamp);
	unsigned char *getAudios(long long *timestamp);
	int getTimestamp(long long *timestamp);
	int playFrame();
	void reset();
private:
	int m_bufLen;
	int m_headerLen;
	YangAudioBufferHeader *m_in,*m_out;
	unsigned char * retChar;
};
#endif
