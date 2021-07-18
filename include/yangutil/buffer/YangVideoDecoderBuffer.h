#ifndef __YangVideoDecoderBuffer__
#define __YangVideoDecoderBuffer__
#include <string.h>
struct YangVideoDBufferHeader{
	int uid;
	int length;
	long long timestamp;
	int frametype;
};

#include "YangBuffer.h"
class YangVideoDecoderBuffer:public YangBuffer
{
public:
	YangVideoDecoderBuffer();
	~YangVideoDecoderBuffer(void);

	void putEVideo(int pind,unsigned char *p,int bufLen, long long timestamp,int frametype);
	void getEVideo(int *pind,unsigned char *p, int *bufLen, long long *timestamp,int *frametype);
private:
	int m_headerLen;
	YangVideoDBufferHeader *m_in,*m_out;
	void initHeader();

};
#endif
