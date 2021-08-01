#include "recordmainwindow.h"

#include <QApplication>
#include "src/video/yangrecordthread.h"
#include "yangutil/sys/YangSysMessageHandle.h"
#include "yangrecliving/YangRecordUtilFactory.h"
#include "src/yangnav/YangRecordSocket.h"
#include "src/yangnav/YangTraceListen.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RecordMainWindow w;
    YangRecordUtilFactory rf;
    YangSysMessageHandle* recMessage=rf.createVrRecMessageHandle(w.m_ini);
   // recMessageinitHandle(w.m_ini);
    w.m_recMessage=recMessage;
    YangRecordThread videoThread;


    w.m_rec=rf.getVrHandle(recMessage);
    w.m_rec->setVideoCount(w.m_ini->sys.cameraCount);
    w.m_rec->initAll();

    w.initVideoThread(&videoThread);
    YangTraceListen recSocket;
    recSocket.p1=&w;
    recSocket.start();

    videoThread.start();
    recMessage->start();
    w.show();
    return a.exec();
}
