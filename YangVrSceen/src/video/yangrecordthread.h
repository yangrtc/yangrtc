#ifndef YANGTHREAD_H
#define YANGTHREAD_H
#include <QThread>
#include <QVector>

#include "YangPlayWidget.h"
//#include "../yangutil/yangmeetingtype.h"
#include "yangrecliving/YangLivingType.h"
#include "yangplayer/YangWinPlayFactroy.h"
#include "yangutil/buffer/YangVideoBuffer.h"
#include "src/video/yangrecordvideowin.h"
/**struct YangRecordThreadWin{
    YangVideoBuffer *videoBuffer;
    YangWinPlay *videoWindow; 
    void* winId;
    char videoName[15];
    long long timestamp;
};

#define Yang_Record_VideoCount 3
**/
class YangRecordThread : public QThread
{
public:
    YangRecordThread();
    virtual ~YangRecordThread();
    //QWidget *m_ys;
    int m_isLoop;
    void initPara(YangRecordContext *par);
    YangPlayWidget *m_video;
    YangWinPlay *m_videoWindow;
    YangRecordVideoWin *m_win1;
    YangVideoBuffer *m_videoBuffer;
   // void clearRender();
    //YangYuvType m_captureFormat;
   // int m_is16bit;
    int m_sid;
    void stopAll();
    int showType;
    // int delState;
private:
    void render();
    void closeAll();

    //void initPlaySdl(YangRecordThreadWin *pwin);
    int m_isStart;
    YangColor m_bgColor;
    YangColor m_textColor;
    int m_videoPlayNum;
    YangRecordContext *m_para;
  //  unsigned char  *m_vb;

private:
    virtual void run();
};

#endif // YANGTHREAD_H
