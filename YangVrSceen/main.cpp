#include "recordmainwindow.h"

#include <QApplication>
#include "src/video/yangrecordthread.h"
#include "yangutil/sys/YangSysMessageHandle.h"
#include "yangrecliving/YangRecordUtilFactory.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RecordMainWindow w;
    YangRecordUtilFactory rf;
     YangSysMessageHandle* livingMessage=rf.createRecMessageHandle(w.m_ini);

    w.m_recMessage=livingMessage;
    YangRecordThread videoThread;

    w.m_rec=rf.getLivingHandle(livingMessage);

    w.m_rec->init();
    w.initVideoThread(&videoThread);
    videoThread.start();
    livingMessage->start();


    w.show();
    return a.exec();
}
