#include "yangvideothread.h"
#include <QDebug>
#include <QMapIterator>
#include "yangmeeting/yangmeetingtype.h"
#include "YangVideoWinHandleH.h"
#include "yangutil/yangtype.h"
YangVideoThread* g_videoThread=NULL;

void yang_clearRender(){
    if(g_videoThread) g_videoThread->clearRender();
}
void yang_add_winvideo(int pwid,YangPlayWidget * pwin){
    if(g_videoThread) g_videoThread->addWin(pwid,pwin);
}
void yang_add_winshowvideo(int pwid,int puid){
    if(g_videoThread) g_videoThread->showWin(pwid,puid);
}
YangVideoThread::YangVideoThread()
{
    m_isLoop=0;
    m_bgColor={0,0,0};
    //m_textColor={0,0,255};
    m_captureFormat=YangYv12;
    m_is16bit=1;
    m_videoPlayNum=5;
    m_isStart=0;
    g_videoThread=this;
    m_meetingHandle=nullptr;
}

YangVideoThread::~YangVideoThread(){
    g_videoThread=nullptr;
    m_meetingHandle=nullptr;


    if(m_isLoop){
        m_isLoop=0;
        while (m_isStart) {
            QThread::msleep(1);
        }
    }
    closeAll();
}

void YangVideoThread::initPara(YangMeetingContext *pini){
    m_ini=pini;
    if(pini->video.videoCaptureFormat==YangI420){
        m_captureFormat=YangI420;
        m_is16bit=0;
    }
    if(pini->video.videoDecHwType==0) {
        m_captureFormat=YangYv12;//YangI420;//YangYv12;
        // qDebug()<<"*****************YangYv12*************add video uid==";
    }
    m_videoPlayNum=pini->video.videoPlayCacheNum;
}

void YangVideoThread::closeAll(){
    clearRender();

}

void YangVideoThread::removePlayvideo(int32_t puid){
    delWd(puid);
}

void YangVideoThread::clearRender(){
    for(int i=0;i<m_showWins.size();i++){
        YangShowWinType *ys1=m_showWins[i];
        if(ys1){
            ys1->synBuffer=nullptr;
            ys1->videoWindow=nullptr;
            delete m_showWins[i];
            m_showWins[i]=nullptr;
        }


        ys1=NULL;
    }
    m_showWins.clear();
}
void YangVideoThread::delWd(int puid){
    qDebug()<<"del.............puid======"<<puid;
    int32_t ind=getShowVidesIndexByuid(puid);
    if(ind>-1){
        YangShowWinType *ys=m_showWins[ind];
        ys->uid=-1;
        ys->synBuffer=nullptr;
        ys->videoBuffer=nullptr;
        ys->isPreview=0;
        ys=NULL;
    }
}

void YangVideoThread::showWin(int pwid,int puid){
    qDebug()<<"add wid===="<<pwid<<"..puid=="<<puid;
    delWd(puid);
    int32_t ind=getShowVidesIndex(pwid);
    if(ind>-1) {

        m_showWins[ind]->synBuffer=nullptr;
        if(m_ini->user.userId==puid){
            m_showWins[ind]->captureFormat=YangI420;//:m_captureFormat
            m_showWins[ind]->videoBuffer=m_meetingHandle->getPreviewVideo();
            m_showWins[ind]->synBuffer=NULL;
            m_showWins[ind]->isPreview=1;

        }else{
            m_showWins[ind]->captureFormat=YangI420;//m_captureFormat;//:m_captureFormat
            m_showWins[ind]->synBuffer=getVideoBuffer(puid);
            m_showWins[ind]->videoBuffer=NULL;
            m_showWins[ind]->isPreview=0;
            //  qDebug()<<"...videbufer====="<< m_showWins[ind]->videoBuffer;
        }
        m_showWins[ind]->uid=puid;

    }

}



void YangVideoThread::addWin(int wid,YangPlayWidget *pwd){
    qDebug()<<"add wid===="<<wid;
    int32_t ind1=getShowVidesIndex(wid);
    if(ind1==-1){
        m_showWins.push_back(new YangShowWinType{0,wid,-1,m_captureFormat,0,NULL,NULL,pwd});

    }

}


YangSynBuffer* YangVideoThread::getVideoBuffer(int puid){
    if(!m_ini||!m_ini->streams.m_playBuffers) return NULL;
    return m_ini->streams.getSynBuffer(puid);
}

int YangVideoThread::getShowVidesIndexByuid(int puid){
    for (int i=0;i<(int)m_showWins.size();i++ ) {
        if(m_showWins[i]->uid==puid) return i;
    }
    return -1;
}

int YangVideoThread::getShowVidesIndex(int wid){

    for (int i=0;i<(int)m_showWins.size();i++ ) {
        if(m_showWins[i]->wid==wid) return i;
    }
    return -1;
}


void YangVideoThread::render(){
    int tsize=m_showWins.size();
    //if(tsize!=2) qDebug()<<"tsize==============="<<tsize;
    for(int i=0;i<tsize;i++){
        YangShowWinType *ys=m_showWins[i];
        if(ys->uid==-1){
            ys->synBuffer=NULL;
            ys->videoBuffer=NULL;
        }else{
            if(ys->isPreview){

                if(ys->videoBuffer==NULL) ys->videoBuffer=m_meetingHandle->getPreviewVideo();

            }else {
                if(ys->synBuffer==NULL)     ys->synBuffer=getVideoBuffer(ys->uid);
            }
        }
           // qDebug()<<"ys->isPreview=="<<ys->isPreview<<"..uid=="<<ys->uid<<"..mysuserid=="<<m_ini->user.userId;
            if(ys->isPreview){
                if(ys->videoBuffer&&ys->videoBuffer->m_size>0){
                    uint8_t* p1=ys->videoBuffer->getVideoRef(&m_frame);
                    if(p1) ys->videoWindow->playVideo(p1,ys->videoBuffer->m_width,ys->videoBuffer->m_height);

                    p1=NULL;
                }
            }else if(ys->synBuffer&&ys->synBuffer->getVideoSize()>0){
                uint8_t* p=ys->synBuffer->getVideoRef(&m_frame);
                if(p) ys->videoWindow->playVideo(p,ys->synBuffer->m_width,ys->synBuffer->m_height);
                // if(ys->videoBuffer->m_size>m_videoPlayNum) ys->videoBuffer->resetIndex();
                p=NULL;
            }

            ys=NULL;
        }//end for
    }


    void YangVideoThread::run(){
        m_isStart=1;
        m_isLoop=1;

        // int32_t interval=1000*1000/50;
        while(m_isLoop){
            QThread::msleep(20);
            render();
        }
        closeAll();
        m_isStart=0;
    }
