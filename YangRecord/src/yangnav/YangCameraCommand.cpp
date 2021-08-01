
#include "YangCameraCommand.h"

YangCameraCommand::YangCameraCommand() {
	m_curCamId = 1;
	m_cameraSpeed = 15;
	isZz = 1;



}

YangCameraCommand::~YangCameraCommand() {

}

void YangCameraCommand::init(const char *ip1) {
	udp.init(ip1, 8005);
}


/**
 * 根据指令切换摄像头
 * @param command 指令
 * */
void YangCameraCommand::switchCamByCommand(int camNo) {

	//if(command.equals("student_up"))
	//	camNo = "2";
	//else
	//camNo="1";
	/**			break;
	 case "student_down":
	 camNo = "1";
	 break;
	 case "student_sanup":
	 camNo = "1";
	 break;
	 case "student_sandown":
	 camNo = "1";
	 break;
	 default:
	 camNo = "1";
	 }**/
    if (camNo != m_curCamId) {
		/*				gotoCamera(camNo);*/
		m_curCamId = camNo;
		//sd.main.mainView.showLocalCamera();
	}
}

/**
 * 向矩阵程序发送命令
 * @param ip 接受命令的IP
 * @param port 接受命令的借口
 * @param command 命令内容
 * */
void YangCameraCommand::sendMsg(char *command) {
	//memset(comm,0,1024);

	udp.sendUdp(command, strlen(command));

}

/**
 * 启动跟踪
 * */
void YangCameraCommand::startAutoTrack() {
    sendMsg("Auto|END");
}

/**
 * 停止跟踪
 * */
void YangCameraCommand::stopAutoTrack() {
    sendMsg("Manual|END");
}

/**
 * 转动摄像头的方向, 上0, 下1, 左2, 右3
 * @param direct 方向
 * */
void YangCameraCommand::changeDirect(int direct) {
	isZz = 0;
	//CString command("");
	char command[1024] = { 0 };
	switch (direct) {
	case 0:
		//sprintf(command,"%d|%s|%d|END",currCamNo,STANDARDUP,camSpeed);
		sprintf(command, "%s|%d|%d|END", STANDARDUP, m_curCamId, m_cameraSpeed);

		break;
	case 1:
		//sprintf(command,"%d|%s|%d|END",currCamNo,STANDARDDOWN,camSpeed);
		sprintf(command, "%s|%d|%d|END", STANDARDDOWN, m_curCamId, m_cameraSpeed);
		//command = STANDARDDOWN + "|" + currCamNo + "|" + camSpeed + "|END";
		break;
	case 2:
		//sprintf(command,"%d|%s|%d|END",currCamNo,STANDARDLEFT,camSpeed);
		sprintf(command, "%s|%d|%d|END", STANDARDLEFT, m_curCamId, m_cameraSpeed);
		//command = STANDARDLEFT + "|" + currCamNo + "|" + camSpeed + "|END";
		break;
	case 3:
		//sprintf(command,"%d|%s|%d|END",currCamNo,STANDARDRIGHT,camSpeed);
		sprintf(command, "%s|%d|%d|END", STANDARDRIGHT, m_curCamId, m_cameraSpeed);
		//command = STANDARDRIGHT + "|" + currCamNo + "|" + camSpeed + "|END";
		break;
	}
    sendMsg(command);
}

/**
 * 停止云台转动[上下左右方向的转动]
 * */
void YangCameraCommand::stopChangeDirect() {
	char command[1024] = { 0 };
	sprintf(command, "%s|%d|1|END", PANTILTSTOP, m_curCamId);
	//String command= PANTILTSTOP + "|" + currCamNo + "|END";
    sendMsg(command);
}

/**
 * 调焦距, 0+, 1-
 * @param type 调焦的类型, 增大还是缩小
 * */
void YangCameraCommand::changeFoci(int type) {
	isZz = 1;
	char command[1024] = { 0 };
	if (type == 0) {
		//sprintf(command,"%d|%s|%d|END",currCamNo,ZOOMTELE,camSpeed);
		sprintf(command, "%s|%d|%d|END", ZOOMTELE, m_curCamId, m_cameraSpeed);
		//command = ZOOMTELE + "|" + currCamNo + "|" + camSpeed + "|END";
	} else {
		//sprintf(command,"%d|%s|%d|END",currCamNo,ZOOMWIDE,camSpeed);
		sprintf(command, "%s|%d|%d|END", ZOOMWIDE, m_curCamId, m_cameraSpeed);
		//command = ZOOMWIDE + "|" + currCamNo + "|" + camSpeed + "|END";
	}
    sendMsg(command);
}

/**
 * 停止焦距控制
 * */
void YangCameraCommand::stopChangeFoci() {
	char command[1024] = { 0 };			//= ZOOMSTOP + "|" + currCamNo + "|END";
	//sprintf(command,"%d|%s|END",currCamNo,ZOOMSTOP);
	sprintf(command, "%s|%d|1|END", ZOOMSTOP, m_curCamId);
    sendMsg(command);
}
