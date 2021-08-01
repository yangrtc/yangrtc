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


yang_config.ini配置参数  
[audio]//音频  
sample=44100  //采样率
channel=2     //声道  
bitrate=128  //码率  
usingMono=0 //是否单声道（视频会议建议单声道）1:单声道 0：双声道  
hasAec=0    //回声消除 1:启用 0:不启用  
echoPath=10 //aec   
aecBufferFrames=8   
audioPlayType=0  
audioEncoderType=0 //音频编码 0:AAc 1:Mp3 2:Speex 3:Opus    
audioDecoderType=0 //音频解码 0:AAc 1:Mp3 2:Speex 3:Opus  
audioCacheNum=100  
audioCacheSize=100  
audioPlayCacheNum=10  
aIndex=1  //声卡声音采集编号  
aSubIndex=0 //linux下，子设备编号  


[video]//视频  
width=640  //摄像头采集width  
height=480  //摄像头采集height  
outWidth=640 //编码输出width  
outHeight=480 //编码输出height  
rate=4096  //码率  
frame=25  //帧数  
bitDepth=8 //位深 8/10/16  
videoEncoderType=0 //0:h264 1:h265  
videoDecoderType=0 //0:h264 1:h265   
videoEncHwType=0   //0:软编 1:硬编  
videoDecHwType=0  //0:软解 1:硬解  
vIndex=0        //摄像头编号  

[sys]  
transType=1 //1:Srt 0:Rtmp 2:webrtc(二期实现)  
hasVr=1 //启动Vr 1:启动 0:不启动  
isMultCamera=1 //1:多个摄像头 0:单个摄像头  
cameraIndexs=0,1,2 //支持多个摄像头，摄像头编号以逗号分割  
cameraCount=3 //摄像头个数,yangrtc理论上支持的摄像头个数没有上限  
bgFilename=/home/jpg/02.jpeg //背景文件，目前支持jpeg  
rtmpPort=1935   //rtmp端口  
httpPort=8090   //http端口  
srtPort=8080    //srt端口  
dataPort=9999   //信令和数据端口  
rtmpServerIP=10.42.0.1  //rtmp服务地址  
srtServerIP=10.42.0.1   //srt服务器地址  
httpServerIP=10.42.0.1   //http服务器地址  
dataServerIP=10.42.0.1    //数据和信令服务器地址  
logLevel=5  //日志级别 fatal/error/debug/info/trace  
hasLogFile=0  //开启日志文件 1:输出到文件 0:输出到console  

[record]  
fileTimeLen=60  //录制视频文件单个文件分钟数，60为录制视文件1小时（60分钟）后生成第二个视频文件  
filePath=/home/recordfile  //保存文件路径  
roomId=1  //教室编号
app=live //直播app名称
  
[hd]//互动参数  
meetingId=1001 //会议编号  
classroomId=1 //教室编号  
app=yangmeeting //服务端app名称   

[enc]  
preset=7  //预设编码参数，参考x264和x265  
enc_threads=4 //编码线程数  
