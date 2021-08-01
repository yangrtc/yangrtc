/*
 * YangAudioEncoderFactory.h
 *
 *  Created on: 2020年9月3日
 *      Author: yang
 */

#ifndef YANGENCODER_INCLUDE_YANGVIDEOENCODERFACTORY_H_
#define YANGENCODER_INCLUDE_YANGVIDEOENCODERFACTORY_H_
#include "yangutil/yangtype.h"
#include "YangVideoEncoder.h"
#include "yangencoder/YangAudioEncoder.h"
#include "YangVideoEncoderMeta.h"

class YangEncoderFactory {
public:
	YangEncoderFactory();
	virtual ~YangEncoderFactory();
	YangAudioEncoder* createAudioEncoder(YangAudioEncDecType paet,YangAudioParam *pini);
	YangAudioEncoder* createAudioEncoder(YangAudioParam *pini);
	YangVideoEncoder* createVideoEncoder(YangVideoEncDecType paet,YangVideoParam *pini);
	YangVideoEncoder* createVideoEncoder(YangVideoParam *pini);
	YangVideoEncoderMeta* createVideoEncoderMeta(YangVideoParam *pini);
};

#endif /* YANGENCODER_INCLUDE_YANGVIDEOENCODERFACTORY_H_ */
