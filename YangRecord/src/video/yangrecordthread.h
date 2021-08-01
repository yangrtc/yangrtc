#ifndef YANGTHREAD_H
#define YANGTHREAD_H
#include <QThread>
#include <QVector>

#include "yangrecordvideowin.h"
//#include "../yangutil/yangmeetingtype.h"
#include "yangrecliving/YangLivingType.h"
#include "yangplayer/YangWinPlayFactroy.h"
#include "yangutil/buffer/YangVideoBuffer.h"
struct YangRecordThreadWin{
    YangVideoBuffer *videoBuffer;
    YangPlayWidget *videoWindow;
   // void* winId;

    long long timestamp;
    int width;
    int height;
};

#define Yang_Record_VideoCount 3

class YangRecordThread : public QThread
{
public:
    YangRecordThread();
    virtual ~YangRecordThread();
    //QWidget *m_ys;
    int m_isLoop;
    void initPara(YangRecordContext *par);
    YangRecordThreadWin m_videos[Yang_Record_VideoCount+1];
    void clearRender();
    YangYuvType m_captureFormat;
    int m_is16bit;
    int m_sid;
    void stopAll();
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
    unsigned char  *m_vb;

private:
    virtual void run();
};

#endif // YANGTHREAD_H
