#include "yangrecordthread.h"
#include <QDebug>
#include <QMapIterator>
//#include "../yangutil/yangmeetingtype.h"
YangRecordThread::YangRecordThread()
{
    // m_ys=nullptr;
    m_isLoop=0;
    m_video=nullptr;
    m_videoBuffer=nullptr;
  //  delState=0;
    m_bgColor={0,0,0};
    m_textColor={0,0,255};

    m_videoPlayNum=5;
    m_sid=1;
    showType=1;
    this->m_videoWindow=NULL;
    m_isStart=0;
}

YangRecordThread::~YangRecordThread(){
    // m_ys=nullptr;
    // m_vb=NULL;
      m_video=nullptr;
      m_videoBuffer=nullptr;
  //  m_vb=NULL;

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
   // m_ini=pini;
    m_para=pini;


    m_videoPlayNum=pini->video.videoPlayCacheNum;
}
void YangRecordThread::closeAll(){
    //clearRender();
}


void YangRecordThread::render(){


        if(m_videoBuffer){
            long long timestamp=0;
                unsigned char* t_vb=m_videoBuffer->getVideoIn(&timestamp);
                if(showType){
                    if(t_vb&&m_video){
                        m_video->PlayOneFrame(t_vb,m_videoBuffer->m_width,m_videoBuffer->m_height);
                    }
                }else{
                    if(m_videoWindow->m_width==0)     m_videoWindow->initVideo(m_videoBuffer->m_width,m_videoBuffer->m_height,YangI420);
                    m_videoWindow->render(t_vb);
                }
                    t_vb=NULL;

        }



}

void YangRecordThread::run(){
    // init();

    m_isLoop=1;
    m_isStart=1;
    // int interval=1000*1000/50;
    if(!showType){
        if(m_videoWindow==NULL){
            YangWinPlayFactroy pf;
            m_videoWindow=pf.createWinPlay();
            m_videoWindow->init((void*)m_win1->winId());
            m_videoWindow->initBg(m_win1->width(),m_win1->height());
        }
    }
    while(m_isLoop){
      //  if(delState>1){
         //   msleep(1);
         //   if(delState==3) delState=2;
            //  qDebug()<<"-----------------------thread is running delState==--"<<delState;
          //  continue;
       // }
        QThread::msleep(20);
        // qDebug()<<"----------------------------------------thread is running==--";
        render();
    }
    m_isStart=0;
   // closeAll();
}
