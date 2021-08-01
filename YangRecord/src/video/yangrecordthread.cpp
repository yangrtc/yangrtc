#include "yangrecordthread.h"
#include <QDebug>
#include <QMapIterator>
//#include "../yangutil/yangmeetingtype.h"
YangRecordThread::YangRecordThread()
{
    // m_ys=nullptr;
    m_isLoop=0;
    //  delState=0;
    m_bgColor={0,0,0};
    m_textColor={0,0,255};
    m_captureFormat=YangI420;
    m_is16bit=1;
    m_videoPlayNum=5;
    m_sid=1;
    m_vb=NULL;
    m_isStart=0;
}

YangRecordThread::~YangRecordThread(){
    // m_ys=nullptr;
    // m_vb=NULL;
    m_vb=NULL;

    stopAll();
}
void YangRecordThread::stopAll(){
    if(m_isLoop){
        m_isLoop=0;
        while (m_isStart) {
            QThread::msleep(1);
        }
    }
    closeAll();
}
void YangRecordThread::initPara(YangRecordContext *pini){
    m_para=pini;
    for(int i=0;i<Yang_Record_VideoCount+1;i++){
        memset(&m_videos[i],0,sizeof(YangRecordThreadWin));
    }
    if(pini->video.videoCaptureFormat==YangYv12){
        m_captureFormat=YangYv12;
        m_is16bit=0;
    }
    if(pini->video.videoDecoderType==1) {
        m_captureFormat=YangI420;
        // qDebug()<<"*****************YangYv12*************add video uid==";
    }
    m_videoPlayNum=pini->video.videoPlayCacheNum;
}
void YangRecordThread::closeAll(){
    clearRender();
}

void YangRecordThread::clearRender(){
    int i=0;
    for(i=0;i<Yang_Record_VideoCount+1;i++){
        YangRecordThreadWin *ys=&m_videos[i];
        if(ys&&ys->videoWindow){
            ys->videoBuffer=NULL;
            ys->videoWindow=NULL;
           }
        ys=NULL;

    }

}


void YangRecordThread::render(){
    for(int i=0;i<Yang_Record_VideoCount+1;i++){
        YangRecordThreadWin *ys=&m_videos[i];
        if(ys->videoBuffer){
            if(ys->videoBuffer->m_size>0)  {
                unsigned char* vdata=ys->videoBuffer->getVideoIn(&ys->timestamp);
                ys->videoWindow->PlayOneFrame(vdata,ys->width,ys->height);
                if(m_sid==i) m_videos[0].videoWindow->PlayOneFrame(vdata,ys->width,ys->height);
                if(ys->videoBuffer&&ys->videoBuffer->m_size>m_videoPlayNum) ys->videoBuffer->resetIndex();
                vdata=NULL;
            }
        }
        ys=NULL;
    }//end for
}

void YangRecordThread::run(){
    m_isLoop=1;
    m_isStart=1;
    // int interval=1000*1000/50;
    while(m_isLoop){
        QThread::msleep(20);
        render();
    }
    m_isStart=0;
    // closeAll();
}
