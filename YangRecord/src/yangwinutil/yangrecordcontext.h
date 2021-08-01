#ifndef YangVideoContext_H
#define YangVideoContext_H

#include "../video/yangrecordthread.h"
#include "../../recordmainwindow.h"
class YangRecordVideoContext
{
public:
    YangRecordVideoContext();

    static RecordMainWindow *mainWin;
    static YangRecordThread *yangThread;
};

#endif // YANGCONTEXT_H
