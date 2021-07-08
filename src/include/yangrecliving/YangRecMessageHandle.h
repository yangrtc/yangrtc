
#ifndef INCLUDE_YANGMEETING_YangRecMessageHandle_H_
#define INCLUDE_YANGMEETING_YangRecMessageHandle_H_
#include "YangRecMessageI.h"
#include <vector>
#include <mutex>
#include "yangutil/sys/YangThread.h"
#include "YangLivingType.h"
#include "YangVrHandle.h"
using namespace std;
class YangRecMessageHandle :public YangThread{
public:
	YangRecMessageHandle();
	virtual ~YangRecMessageHandle();


	YangVrHandle* m_videoRec;
	void putMessage(YangRecMessageType pst,int optType);
	void initHandle(YangRecordContext* pini);
	void deleteRechandle();
    int m_isStart;
    int m_loop;
    void stop();

protected:
   void run();
   void startLoop();
   void stopLoop();
private:
   YangRecordContext *m_ini;
   vector<YangRecMessageType> m_sysMessages;
   void handleMessage(YangRecMessageType mss);
   mutex m_lock;
};

#endif /* INCLUDE_YANGMEETING_YangRecMessageHandle_H_ */
