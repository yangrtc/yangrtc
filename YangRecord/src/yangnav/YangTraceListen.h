#ifndef __________YangTraceListen___
#define __________YangTraceListen___
#include "YangRecordI.h"
#include "yangutil/sys/YangThread.h"

class YangTraceListen:public YangThread
{
public:
	YangTraceListen(void);
	~YangTraceListen(void);
	YangRecordI *p1;

	void udpListen();
    void proc(char *b,int plen);


    int m_isStart;
    void stop();
protected:
    void run();
    int m_isConvert;
};
#endif
