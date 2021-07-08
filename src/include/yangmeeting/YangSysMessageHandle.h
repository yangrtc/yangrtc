
#ifndef INCLUDE_YANGMEETING_YANGSYSMESSAGEHANDLE_H_
#define INCLUDE_YANGMEETING_YANGSYSMESSAGEHANDLE_H_
#include <yangutil/sys/YangSysMessageI.h>
#include <vector>
#include <mutex>
#include "yangutil/sys/YangThread.h"
#include "yangmeetingtype.h"
#include "YangMeetingHandle.h"
using namespace std;
class YangSysMessageHandle :public YangThread{
public:
	YangSysMessageHandle();
	virtual ~YangSysMessageHandle();
	YangMeetingContext *m_ini;
	YangReceiveMessageI *m_receive;
	YangMeetingHandle* m_videoMeeting;
	void putMessage(YangSysMessageI *handle,YangSysMessageType pst,int puid,int handleState,int optType);
    int m_isStart;
    int m_loop;
    void stop();

protected:
   void run();
   void startLoop();
   void stopLoop();
private:
   vector<YangSysMessage*> m_sysMessages;
   void handleMessage(YangSysMessage *pms);
   mutex m_lock;
};

#endif /* INCLUDE_YANGMEETING_YANGSYSMESSAGEHANDLE_H_ */
