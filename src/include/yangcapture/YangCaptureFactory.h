/*
 * YangCaptureImpl.h
 *
 *  Created on: 2020年8月30日
 *      Author: yang
 */

#ifndef INCLUDE_YANGCAPTURE_YANGCAPTUREFACTORY_H_
#define INCLUDE_YANGCAPTURE_YANGCAPTUREFACTORY_H_
#include <yangcapture/YangMultiVideoCapture.h>
#include "YangAudioCapture.h"
#include "YangScreenCapture.h"
//#include "../include/YangLivingVideoCapture.h"
class YangCaptureFactory {
public:
	YangCaptureFactory();
	virtual ~YangCaptureFactory();
	YangAudioCapture *createAudioCapture(YangAudioParam *pini);
	YangAudioCapture *createRecordAudioCapture(YangAudioParam *pini);
	YangMultiVideoCapture *createVideoCapture(YangVideoParam *pini);
	YangMultiVideoCapture *createRecordVideoCapture(YangVideoParam *pini);
	YangScreenCapture *createScreenCapture(int capType);
};

#endif /* INCLUDE_YANGCAPTURE_YANGCAPTUREFACTORY_H_ */
