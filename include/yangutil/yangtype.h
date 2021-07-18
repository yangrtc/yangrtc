/*
 * yangtype.h
 *
 *  Created on: 2020年10月14日
 *      Author: yang
 */

#ifndef YANGUTIL_YANGTYPE_H_
#define YANGUTIL_YANGTYPE_H_
#include "YangErrorCode.h"
#include "../Yang_Config.h"
//#include "sys/YangLog.h"
#define YANG_DELETE(a) {if( (a) != NULL ) {delete (a); (a) = NULL;}}
#define YANG_DELETES(a) {if( (a) != NULL ) {delete[] (a); (a) = NULL;}}
#define YANG_FREE(a) {if( (a) != NULL ) {free((a)); (a) = NULL;}}
enum YangYuvType{
    YangYuy2,
	YangI420,
	YangNv12,
    YangYv12,
	YangP010,
	YangP016
};
struct YangRect{
    short x;
    short y;
    short w;
    short h;
};
struct YangColor{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
struct YangH2645Conf {
	int vpsLen;
	int spsLen;
	int ppsLen;
	unsigned char vps[128];
	unsigned char sps[128];
	unsigned char pps[64];
};
struct YangRtmpMeta {
	unsigned char buffer[128];
	int bufLen;
};
struct YangVideoMeta {
	int isInit;
	YangH2645Conf mp4Meta;
	//YangRtmpMeta flvMeta;
	YangRtmpMeta livingMeta;
};

enum YangAudioEncDecType{
	Yang_AED_AAC,
	Yang_AED_MP3,
	Yang_AED_SPEEX,
	Yang_AED_OPUS
};
enum YangVideoEncDecType{
	Yang_VED_264,
	Yang_VED_265,
	Yang_VED_vp9
};
enum YangVideoHwType{
	Yang_Hw_Soft,
	YangV_Hw_Intel,
	YangV_Hw_Nvdia,
	YangV_Hw_Android
};
/**
struct YangEncoderParam {
	int width;
	int height;
	int fps;
	int bitrate;
	int keyint_max;
	int level_idc;
	int profile;
};
**/
struct YangAudioParam{
	int sample;
	int frameSize;
	int bitrate;
	int channel;

	int usingMono;
	int hasAec;
	int echoPath;

	int aecBufferFrames;
	int audioCacheSize;
	int audioCacheNum;
	int audioPlayCacheNum;

	int hasAudioHeader;
	int audioEncoderType;
	int	audioDecoderType;
	int audioPlayType;

	int aIndex;
	int aSubIndex;
};

struct YangVideoParam{
		int width; //= 800
		int height; //= 600
		int outWidth;
		int outHeight;
		int rate; // 512
		int frame; //25
		//int bitcount; // 16
		int bitDepth;

		int videoCacheNum;
		int evideoCacheNum;
		int videoPlayCacheNum;

		int videoCaptureFormat;
		int videoEncoderFormat;
		
		int videoEncoderType;
		int videoDecoderType;
		int videoEncHwType;
		int videoDecHwType;
		int vIndex;
};
struct YangVideoEncParam{
		int preset;
		int level_idc;
		int profile;
		int keyint_max;
		int enc_threads;
		//int fps_num;
};
struct YangSysParam{
		int isMultCamera;
		int transType;
		int usingDataServer;
		int rtmpPort;
		int srtPort;
		int httpPort;
		int dataPort;
		int hasLogFile;
		int logLevel;
		int cameraCount;

		char cameraIndexs[50];
		char rtmpServerIP[20];
		char srtServerIP[20];
		char httpServerIP[20];
		char dataServerIP[20];
};



#endif /* YANGUTIL_YANGTYPE_H_ */
