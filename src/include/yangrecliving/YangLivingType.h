/*
 * yangrecordtype.h
 *
 *  Created on: 2020年10月12日
 *      Author: yang
 */

#ifndef YANGRECLIVING_INCLUDE_YANGRECORDTYPE_H_
#define YANGRECLIVING_INCLUDE_YANGRECORDTYPE_H_
#include "yangutil/yangtype.h"
struct YangRecordParam{

	char app[20];
	char filePath[128];
	int roomId;
	//int videoCount;
	int hzhType;
	int isMp4;
	int fileTimeLen;
	int livingModel;
	int recordModel;
	int mode;
};
struct YangRecordContext{
	YangAudioParam audio;
	YangVideoParam video;
	YangSysParam sys;
	YangVideoEncParam enc;
	YangRecordParam record;
	//YangCameraParam camera;
	int createFile;
	int createRtmp;

	int createFile3;
	int createRtmp3;
	char filename[50];
	char filenames[50];
	//char filename2[50];
	//char filename3[50];
	char bgFilename[128];
};
enum YangRecodeModuleType{
	Yang_Record_Film=1,
	Yang_Record_Hzh,
	Yang_Record_Res,
	Yang_Record_Both
};


#endif /* YANGRECLIVING_INCLUDE_YANGRECORDTYPE_H_ */
