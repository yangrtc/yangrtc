#include "yangrecordwin.h"
#include "yangutil/yangtype.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
//#include "../tooltip/RDesktopTip.h"
#include "../yangwinutil/yangrecordcontext.h"
YangRecordWin::YangRecordWin(QWidget *parent):QWidget(parent)
{

    m_hb=new QHBoxLayout();
        m_hb->setMargin(0);
    m_hb->setSpacing(1);
    setLayout(m_hb);
    this->setAutoFillBackground(true);
    //m_selectUser=nullptr;
    vwin=nullptr;


   //this->setWidget(m_centerWdiget);


}

YangRecordWin::~YangRecordWin()
{
    // m_mh=nullptr;
    //m_selectUser=nullptr;
   //  if(1) return;
    YANG_DELETE(vwin);

    YANG_DELETE(m_hb);

}




void YangRecordWin::init(){

}



