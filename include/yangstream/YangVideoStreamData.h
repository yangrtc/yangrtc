#ifndef YANGSTREAM_INCLUDE_YANGVIDEOSTREAMDATA_H_
#define YANGSTREAM_INCLUDE_YANGVIDEOSTREAMDATA_H_
#include "yangutil/yangtype.h"
#include "stdint.h"
class YangVideoStreamData {
public:
	YangVideoStreamData();
	virtual ~YangVideoStreamData();
	void getVideoData(unsigned char* p,int plen,int *dataLen,long long videoTimestamp,int frametype,YangVideoEncDecType videoType=Yang_VED_264);
	void getVideoMeta(unsigned char* p,int plen,int *dataLen,YangVideoEncDecType videoType=Yang_VED_264);
	unsigned char* getVideoData();
	long long getRtmpTimestamp();
	long long getTsTimestamp();
protected:
	void init();
	void initEncType(YangVideoEncDecType videoType,int frametype);
private:
	unsigned char* m_videoBufs;

	unsigned char* m_videoBuffer;

	char* yang_put_be32(char *output, unsigned int nVal);

	long long videoTimestamp , baseTimestamp;
	long long curVideotimestamp = 0;
	int preTimestamp = 0;

};

#endif /* YANGSTREAM_INCLUDE_YANGVIDEOSTREAMDATA_H_ */
