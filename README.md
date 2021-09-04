# yangrtc

#### 介绍
Yang Real-Time Communication，专业级的行业视音频应用的SDK。   
yangmeeting 视频会议  
yangrecord 高清录播直播系统    
yangvrscreen 虚拟和桌面的录制直播  

yangrtc功能：  
1、视频编码 8bit:x264、x265、vaapi、nvenc等，二期增加AV1和多种硬件编码。  
2、视频编码 10bit:x265、vaapi、nvenc等。  
3、视频解码：ffmpeg和yangh264decoder。    
4、VR:基于抠图实现虚拟视频的互动和录制、直播等。  
5、8bit和10bit网络播放器：yangplayer  
6、音频：Opus、Aac、Speex、Mp3等音频编解码。    
7、音频：AEC、AGC、ANS及声音合成等处理。    
8、传输：rtmp、srt，二期增加webrtc（自己实现，不使用谷歌lib库）和GB28181。   
9、直播：rtmp、srt、webrtc、HLS、HTTP-FLV。  
10、8bit录制：h264、h265的mp4和flv。    
11、10bit录制：h265的mp4  
12、实现了屏幕共享与控制。  
13、实现了声音和图像多种处理。  
14、专业摄像头的云台控制与多镜头导播切换。   
15、64位编程，不支持32位。  
yangrtc 可支持视频会议、高清录播直播等多种视音频应用。  
可用于远程教育、远程医疗、指挥调度、安防监控、影视录播、协同办公、直播互动等多种行业应用。  
第三方类库为动态调用，编译时不依赖第三方类库包。  

编译环境：  
1、在ubuntu18.04和ubuntu20.04，内核5.4和5.8用Qt和eclipse编译。  
2、Win10下Qt，X64编译，第三方组件用vs2019和mingw64编译。  


yang_config.ini配置参数https://github.com/yangrtc/yangrtc/wiki/config_file  
