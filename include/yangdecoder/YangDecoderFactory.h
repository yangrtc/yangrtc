/*
 * YangDecoderFactory.h
 *
 *  Created on: 2020年9月3日
 *      Author: yang
 */

#ifndef YANGDECODER_INCLUDE_YANGDECODERFACTORY_H_
#define YANGDECODER_INCLUDE_YANGDECODERFACTORY_H_
#include "yangdecoder/YangAudioDecoder.h"
#include "yangdecoder/YangVideoDecoder.h"

class YangDecoderFactory {
public:
	YangDecoderFactory();
	virtual ~YangDecoderFactory();

	YangAudioDecoder* createAudioDecoder(YangAudioEncDecType paet,YangAudioParam *pini);
	YangAudioDecoder* createAudioDecoder(YangAudioParam *pini);
	YangVideoDecoder* createVideoDecoder(YangVideoEncDecType paet,YangVideoParam *pini);
	YangVideoDecoder* createFfmpegVideoDecoder(YangVideoEncDecType paet,YangVideoParam *pini);
	YangVideoDecoder* createVideoDecoder(YangVideoParam *pini);
};

#endif /* YANGDECODER_INCLUDE_YANGDECODERFACTORY_H_ */
