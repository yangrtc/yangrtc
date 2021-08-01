
#ifndef YANGSTREAM_INCLUDE_YANGAUDIOSTREAMDATA_H_
#define YANGSTREAM_INCLUDE_YANGAUDIOSTREAMDATA_H_
#include "yangutil/yangtype.h"
#include "stdint.h"
class YangAudioStreamData {
public:
	YangAudioStreamData();
	virtual ~YangAudioStreamData();
	void getAudioData(unsigned char* p,int plen,int *dataLen);
	void init(int sample,int channel,YangAudioEncDecType audioType);
	unsigned char* getAudioData();
	long long getRtmpTimestamp();
	long long getTsTimestamp();
private:
	unsigned char* m_audioBufs;
	unsigned char* m_audioBuffer;
	int m_audioHeaderLen;

	long long atime ;
	double atime1;
	double perSt ;
};

#endif /* YANGSTREAM_INCLUDE_YANGAUDIOSTREAMDATA_H_ */
