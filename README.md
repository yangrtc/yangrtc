## Yangrtc Overview
Yang Real-Time Communication，专业级的行业视音频应用的SDK。   
yangrtc是一个自主研发的支持Webrtc/Srt/Rtmp的rtc架构，包含多种视音频编解码和处理等。  

支持视频会议、高清录播直播、直播互动等多种视音频应用。  
 可用于远程教育、远程医疗、指挥调度、安防监控、影视录播、协同办公、直播互动等多种行业应用。  
webrtc支持为自主研发，非谷歌lib,兼容webrtc协议 ,可与谷歌Lib和浏览器互通  
支持Linux/Windows操作系统
  
### 目录功能  
yangmeeting 视频会议  
yangrecord 高清录播直播系统    
yangvrscreen 虚拟和桌面的录制和推流(webrtc/rtmp)  
yangplayer 网路播放器(wetrtc/rtmp)  
YangMeetingServer 视频会议服务端程序  

### yangrtc功能

 1、视频编码 8bit:x264、x265、vaapi、nvenc等，二期增加AV1和多种硬件编码。  
 2、视频编码 10bit:x265、vaapi、nvenc等。  
 3、视频解码：ffmpeg和yangh264decoder。  
 4、VR:基于抠图实现虚拟视频的互动和录制、直播等。  
 5、8bit和10bit网络播放器：yangplayer  
 6、音频：Opus、Aac、Speex、Mp3等音频编解码。  
 7、音频：AEC、AGC、ANS及声音合成等处理。  
 8、传输：webrtc、rtmp、srt，webrtc为自己实现，没使用谷歌lib库。  
 9、直播：rtmp、srt、webrtc、HLS、HTTP-FLV。  
 10、8bit录制：h264、h265的mp4和flv。  
 11、10bit录制：h265的mp4  
 12、实现了屏幕共享与控制。  
 13、实现了声音和图像多种处理。  
 14、专业摄像头的云台控制与多镜头导播切换。  
 15、64位编程，不支持32位。   
  
  
### yangrtc3.0规划：  
1、传输加密改为国密加密，修改srtp支持国密。    
2、实现10位、16位全链路打通，从采集、编码、传输、解码、播放这些环节全部支持10位。  

