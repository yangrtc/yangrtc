#include "recordmainwindow.h"
#include "ui_recordmainwindow.h"
#include "yangrecliving/YangRecordUtilFactory.h"
#include "yangrecliving/YangLivingType.h"
#include <QDebug>
#include "yangutil/sys/YangLog.h"
#include "yangutil/sys/YangFileUtil.h"
#include <QMessageBox>
//#include "yangrecliving/YangLivingMessageHandle.h"
RecordMainWindow::RecordMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RecordMainWindow)
{

    ui->setupUi(this);
    YangRecordUtilFactory yuf;
    m_ini=new YangRecordContext();
    memset(m_ini, 0, sizeof(YangRecordContext));
    yuf.createIni("yang_config.ini",m_ini);
    yang_setLogLevle(m_ini->sys.logLevel);
    yang_setLogFile(m_ini->sys.hasLogFile);
    init(m_ini);
    m_ini->audio.usingMono=0;
    m_ini->audio.audioEncoderType=0;
    m_ini->audio.sample=44100;
    m_ini->audio.channel=2;
    m_showType=1;

    m_isStartRec=0,m_isStartPause=0;

    m_win0=NULL;
    m_win1=NULL;

    m_timer=new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(m_onTimeout()));
    m_isVr=0;
    m_rec=NULL;
    m_recTimeLen=0;
    m_recMessage=NULL;


    ui->m_res->setCheckState(Qt::Checked);


    m_hb0=new QHBoxLayout();


    ui->vdMain->setLayout(m_hb0);
    if(m_showType){
        m_win0=new YangPlayWidget(this);
        m_hb0->addWidget(m_win0);
    }else{
        m_win1=new YangRecordVideoWin(this);
        m_hb0->addWidget(m_win1);
    }


    m_hb0->setMargin(0);
    m_hb0->setSpacing(0);

}

RecordMainWindow::~RecordMainWindow()
{
    closeAll();
    // YANG_DELETE(m_ini);(pr
}
void RecordMainWindow::closeEvent( QCloseEvent * event ){
    qDebug()<<"Windows is exiting..................";
    closeAll();
    exit(0);
}
void RecordMainWindow::initVideoThread(YangRecordThread *prt){
    m_rt=prt;
    m_rt->initPara(m_ini);
    m_rt->showType=m_showType;
    initPreview();
}
void RecordMainWindow::closeAll(){
    if(m_isStartRec){
        m_rec->stopRecord();
        m_timer->stop();
        m_isStartRec=!m_isStartRec;
    }
    if(m_rec){
        if(m_isStartRec){
            m_rec->stopRecord();
            m_timer->stop();
            m_isStartRec=!m_isStartRec;
        }
        m_rt->stopAll();
        m_rec=nullptr;
        m_recMessage->m_loop=0;
        while(m_recMessage->m_isStart){
            QThread::msleep(1);
        }
        m_recMessage->deleteAll();
        YANG_DELETE(m_recMessage);
        m_rt=NULL;
        m_recMessage=nullptr;
        yang_closeLogFile();
        YANG_DELETE(m_ini);
        delete ui;
    }
}

void RecordMainWindow::initPreview(){



    m_rt->m_video=m_win0;
    m_rt->m_win1=m_win1;

    m_rt->m_videoBuffer=m_rec->getPrebuffer();




}

int RecordMainWindow::initFileName(){
    YangFileUtil fu;
    int ret=fu.hasPath(m_ini->record.filePath);
    if(ret){
        if(ret==1) {
            qDebug()<<"not exists path="<<m_ini->record.filePath;
            if(fu.createPath(m_ini->record.filePath)==-1){
                return 2;
            }
        }
        if(ret==2) return 1;
    }


    memset(m_ini->filename,0,sizeof(m_ini->filename));
    memset(m_ini->filenames,0,sizeof(m_ini->filenames));
    srand(time(0));
    int st = rand();
    sprintf(m_ini->filename, "rec0%d.mp4", st);
    sprintf(m_ini->filenames, "rec1%d", st);
    return 0;

}
void RecordMainWindow::init(YangRecordContext *para) {
    para->audio.usingMono=0;
    para->audio.audioEncoderType=0;
    para->record.livingModel = 1;
    para->record.recordModel = 1;
    para->record.mode=1;
    para->createFile=1;
    para->createRtmp=0;

}

void RecordMainWindow::m_onTimeout(){
    m_recTimeLen++;
    int ss=m_recTimeLen>59?m_recTimeLen%60:m_recTimeLen;
    ui->m_sec->setText(ss>9?QString::number(ss):"0"+QString::number(ss));
    if(ss==0||m_recTimeLen==1){
        int hh=m_recTimeLen/3600;
        int mm=m_recTimeLen/60;
        mm=mm>59?mm%60:mm;
        ui->m_hh->setText(hh>9?QString::number(hh):"0"+QString::number(hh));
        ui->m_min->setText(mm>9?QString::number(mm):"0"+QString::number(mm));
    }


}

void RecordMainWindow::on_m_b_rec_clicked()
{
    if(!m_isStartRec){
        int ret=initFileName();
        if(ret) {
            static QMessageBox messageBox(QMessageBox::NoIcon,"",ret==1?"视频保存目录没有写权限！":"创建视频保存目录失败！",QMessageBox::Ok,NULL);
                messageBox.show();
            return;
        }
        ui->m_b_rec->setText("停止");
       // m_rec->recordFile();
        yang_post_message(YangM_Rec_Start,0,NULL);
        m_timer->start(1000);
        m_isStartRec=!m_isStartRec;
        m_recTimeLen=0;
    }else{
        ui->m_b_rec->setText("开始");
       // m_rec->stopRecord();
        yang_post_message(YangM_Rec_Stop,0,NULL);
        m_timer->stop();
        m_isStartRec=!m_isStartRec;
    }

}


void RecordMainWindow::on_m_b_pause_clicked()
{
    if(!m_isStartPause){
        ui->m_b_rec->setText("继续");
        m_rec->pauseRecord();
        m_isStartPause=!m_isStartPause;
        m_timer->stop();

    }else{
        ui->m_b_rec->setText("暂停");
        m_rec->resumeRecord();
        m_isStartPause=!m_isStartPause;
        m_timer->start();
    }
}

void RecordMainWindow::on_m_zb_clicked()
{
    m_ini->createRtmp=ui->m_zb->checkState()==Qt::Checked?1:0;
    qDebug()<<"rtmp............."<<m_ini->createRtmp;
}

void RecordMainWindow::on_m_res_clicked()
{
    m_ini->createFile=ui->m_res->checkState()==Qt::Checked?1:0;
}

void RecordMainWindow::on_m_c_vr_clicked()
{
    m_isVr=ui->m_c_vr->checkState()==Qt::Checked?1:0;
    if(m_isVr){
        //if(m_rec) m_rec->startVr(m_ini->bgFilename);
        yang_post_message(YangM_Rec_Setvr,0,NULL);
    }else{
        //if(m_rec) m_rec->stopVr();
        yang_post_message(YangM_Rec_UnSetvr,0,NULL);
    }
}

void RecordMainWindow::on_m_c_screen_clicked()
{

}
