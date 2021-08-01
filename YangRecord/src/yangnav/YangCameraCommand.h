
#ifndef INCLUDE_YANGTRACE_YANGCAMERACOMMAND_H_
#define INCLUDE_YANGTRACE_YANGCAMERACOMMAND_H_
#include <string>
#include <string.h>
#include "YangRecordSocket.h"

using namespace std;
#define AUTO  "Auto"
#define Image_Ip 8002
//停止跟踪
#define MANUAL  "Manual"
//老师半景
#define HALFTRACK  "HalfTrack"
//老师近景
#define MIDDLETRACK  "MiddleTrack"
//老师全景
#define FULLTRACK  "FullTrack"
//查询跟踪状态
#define SWITCHER_ON  "Switcher_on"
//停止学生跟踪
#define CAM2MANUAL  "Cam2Manual"
//启动学生跟踪
#define CAM2AUTO  "Cam2Auto"

//调用预置位
#define PRECALL  "PreCall"
//设置预置位
#define PRESET  "Preset"
//上转
#define STANDARDUP  "StandardUp"
//下转
#define STANDARDDOWN  "StandardDown"
//左转
#define STANDARDLEFT  "StandardLeft"
//右转
#define STANDARDRIGHT  "StandardRight"
//上下左右停止
#define PANTILTSTOP  "PanTiltStop"
//拉远
#define ZOOMWIDE  "ZoomWide"
//拉近
#define ZOOMTELE  "ZoomTele"
//拉近拉远停止
#define ZOOMSTOP  "ZoomStop"

#define Camera_speed 10
class YangCameraCommand{
public:
	YangCameraCommand();
	virtual ~YangCameraCommand();
	void init(const char *pip);
	void changeFoci(int type);
	void stopChangeFoci();
	void stopChangeDirect();
	void changeDirect(int direct);
    void startAutoTrack();
    void stopAutoTrack();
	void switchCamByCommand(int dd);
    void sendMsg(char *command);
	int isZz;
    int m_curCamId, m_cameraSpeed;
	string m_ip;
    YangUdpUtil udp;

};

#endif /* INCLUDE_YANGTRACE_YANGCAMERACOMMAND_H_ */
