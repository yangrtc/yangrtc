/*
 * YangBaseAllocator.h
 *
 *  Created on: 2020年8月8日
 *      Author: yang
 */

#ifndef YANGUTIL_BUFFER_YANGBUFFER_H_
#define YANGUTIL_BUFFER_YANGBUFFER_H_
#include <mutex>
#include "../yangtype.h"

#define Yang_Reindex(p)  if(p!=NULL) p->resetIndex();
struct YangBufferHeader{
	char headerLength;
	int bodyLength;
	//unsigned char *header;
	//unsigned char *body;
};
class YangBuffer {
public:
	YangBuffer();
	virtual ~YangBuffer();
public:
    int m_index;
	int m_size;
	int m_mediaType;
	//int m_userId;
	int m_uid;
	void resetIndex();
	void putData(int pHeadLen,unsigned char*pheader,int bodyLen,unsigned char* body);
	int getData(unsigned char*pheader,unsigned char* body);
	unsigned char* getData(unsigned char*pheader);
	int getHeaderData(unsigned char*pheader);

protected:
	int m_newIndex;
	int m_curIndex;
	int m_baseHeaderLen;
	YangBufferHeader *m_baseIn;
	YangBufferHeader *m_baseOut;
	int m_alen,m_cache_num;//,m_cache_num_cap;
	unsigned char *m_cache,*m_tmp,*m_tmp1;
	void setSize(int padd);
private:

	std::mutex m_lock;

	//int m_bufHeaderLen;


};

#endif /* YANGUTIL_BUFFER_YANGBUFFER_H_ */
