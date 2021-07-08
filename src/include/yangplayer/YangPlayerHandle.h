/*
 * YangPlayerHandle.h
 *
 *  Created on: 2021年5月26日
 *      Author: yang
 */

#ifndef INCLUDE_YANGPLAYER_YANGPLAYERHANDLE_H_
#define INCLUDE_YANGPLAYER_YANGPLAYERHANDLE_H_
#include <string>
#include <yangutil/buffer/YangVideoBuffer.h>
class YangPlayerHandle {
public:
	YangPlayerHandle(){};
	virtual ~YangPlayerHandle(){};
	virtual YangVideoBuffer* getVideoBuffer()=0;
	virtual void play(std::string url)=0;
	static YangPlayerHandle* createPlayerHandle();
};

#endif /* INCLUDE_YANGPLAYER_YANGPLAYERHANDLE_H_ */
