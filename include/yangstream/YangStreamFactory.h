
#ifndef YANGSTREAM_INCLUDE_YANGSTREAMFACTORY_H_
#define YANGSTREAM_INCLUDE_YANGSTREAMFACTORY_H_
#include "YangStreamBase.h"
//#include "YangPlay.h"
//#include "YangPush.h"
class YangStreamFactory {
public:
	YangStreamFactory();
	virtual ~YangStreamFactory();
	YangStreamBase *createStreamBase(int transType,int puid);
	//YangPlay* createPlayRtmp(int puid);
	//YangPlay* createPlaySrt(int puid);
	//YangPush* createPushRtmp(int puid);
	//YangPush* createPushSrt(int puid);
};

#endif /* YANGSTREAM_INCLUDE_YANGSTREAMFACTORY_H_ */
