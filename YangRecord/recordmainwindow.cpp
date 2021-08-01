#include "recordmainwindow.h"
#include "ui_recordmainwindow.h"
#include "yangrecliving/YangRecordUtilFactory.h"
#include "yangrecliving/YangRecMessageI.h"
#include "src/yangwinutil/yangrecordcontext.h"
#include "yangutil/sys/YangLog.h"
#include "yangutil/sys/YangFileUtil.h"
#include <QMessageBox>
RecordMainWindow::RecordMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RecordMainWindow)
{

    ui->setupUi(this);
    YangRecordUtilFactory yuf;
    m_ini=new YangRecordContext();
    memset(m_ini, 0, sizeof(YangRecordContext));
    yuf.createIni("yang_config_record.ini",m_ini);
    yang_setLogLevle(m_ini->sys.logLevel);
    yang_setLogFile(m_ini->sys.hasLogFile);
    init(m_ini);

    m_rec=nullptr;
    ui->m_r_model1->setChecked(1);
    m_synrec=0;
    m_isStartRec=0,m_isStartPause=0;
    m_isStartZb=0,m_isStartPg=0;
    YangRecordVideoContext::mainWin=this;
    m_recMessage=nullptr;

    m_timer=new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(m_onTimeout()));

    m_recTimeLen=0;
    m_isAutoNav=0;select_id=1;
    m_cameraHandle.init("127.0.0.1");
}

RecordMainWindow::~RecordMainWindow()
{
    destroyAll();
    // YANG_DELETE(m_ini);
}

void RecordMainWindow::destroyAll(){
    if(m_rec){
        qDebug()<<"..............close event....";
        if(m_isStartRec){
            m_rec->stopRecordLiving();
            m_timer->stop();
            m_isStartRec=!m_isStartRec;
        }
        m_rt->stopAll();
        //m_rt->quit();
        m_rec=nullptr;
        m_recMessage->m_loop=0;

        while(m_recMessage->m_isStart){
            QThread::msleep(1);
        }
        m_recMessage->deleteAll();
        YANG_DELETE(m_recMessage);

        YangRecordVideoContext::mainWin=NULL;
        YangRecordVideoContext::yangThread=NULL;
        delete ui;
        //YANG_DELETE(m_rec);

        YANG_DELETE(m_ini);
        m_rt=NULL;
        m_recMessage=nullptr;
        yang_closeLogFile();
    }
}

void RecordMainWindow::initVideoThread(YangRecordThread *prt){
    m_rt=prt;
    m_rt->initPara(m_ini);
    YangRecordVideoContext::yangThread=m_rt;
    initPreview();
}
void RecordMainWindow::initPreview(){

    m_win1=new YangRecordVideoWin();
    m_win2=new YangRecordVideoWin();
    m_win3=new YangRecordVideoWin();
    m_win0=new YangRecordVideoWin();

    m_win1->sid=1;
    m_win2->sid=2;
    m_win3->sid=3;
    m_hb0=new QHBoxLayout();
    m_hb1=new QHBoxLayout();
    m_hb2=new QHBoxLayout();
    m_hb3=new QHBoxLayout();
    ui->vdMain->setLayout(m_hb0);
    ui->vd1->setLayout(m_hb1);
    ui->vd2->setLayout(m_hb2);
    ui->vd3->setLayout(m_hb3);

    m_hb0->addWidget(m_win0);
    m_hb1->addWidget(m_win1);
    m_hb2->addWidget(m_win2);
    m_hb3->addWidget(m_win3);

    m_hb0->setMargin(0);
    m_hb0->setSpacing(0);
    m_hb1->setMargin(0);
    m_hb1->setSpacing(0);
    m_hb2->setMargin(0);
    m_hb2->setSpacing(0);
    m_hb3->setMargin(0);
    m_hb3->setSpacing(0);
    m_rt->m_videos[0].videoWindow=m_win0;
    m_rt->m_videos[1].videoWindow=m_win1;
    m_rt->m_videos[2].videoWindow=m_win2;
    m_rt->m_videos[3].videoWindow=m_win3;
    for(int j=0;j<4;j++) {
        m_rt->m_videos[j].width=m_ini->video.width;//->initVideo(,m_ini->video.height,YangI420);
        m_rt->m_videos[j].height=m_ini->video.height;
    }
    /**
   // m_rt->m_videos[0].winId=(void*)m_win0->winId();
   // m_rt->m_videos[1].winId=(void*)m_win1->winId();
  //  m_rt->m_videos[2].winId=(void*)m_win2->winId();
   // m_rt->m_videos[3].winId=(void*)m_win3->winId();

    m_rt->m_videos[0].width=m_win0->width();
    m_rt->m_videos[1].width=m_win1->width();
    m_rt->m_videos[2].width=m_win2->width();
    m_rt->m_videos[3].width=m_win3->width();

    m_rt->m_videos[0].height=m_win0->height();
    m_rt->m_videos[1].height=m_win1->height();
    m_rt->m_videos[2].height=m_win2->height();
    m_rt->m_videos[3].height=m_win3->height();**/
    //   sprintf( m_rt->m_videos[0].videoName,"老师");
    //   sprintf( m_rt->m_videos[1].videoName,"学生");
    //   sprintf( m_rt->m_videos[2].videoName,"白板");
    std::vector<YangVideoBuffer*> *vbs=m_rec->getPreVideoBuffer();

    for(unsigned int i=0;i<vbs->size();i++){
        m_rt->m_videos[i+1].videoBuffer=vbs->at(i);

        // qDebug()<<"...........preview videoBuffer..."<<i;
    }
    vbs=NULL;
    m_rt->m_videos[0].videoBuffer=nullptr;
    ui->vd1->setStyleSheet("border-color:red;");
    // m_rt->start();
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
    sprintf(m_ini->filenames, "recs%d", st);

    return Yang_Ok;
}
void RecordMainWindow::init(YangRecordContext *para) {
    para->record.livingModel = 1;
    para->record.recordModel = 1;
    para->record.mode=1;
    para->createFile=1;
    //  para->createRtmp=1;

}
void RecordMainWindow::selectBox(int pind){
    // qDebug()<<"select box pind==="<<pind;
    m_rt->m_sid=pind;
    if(pind==1){
        ui->vd1->setStyleSheet("border-color:red;");
        ui->vd2->setStyleSheet("border-color:white;");
        ui->vd3->setStyleSheet("border-color:white;");
    }else if(pind==2){
        ui->vd1->setStyleSheet("border-color:white;");
        ui->vd2->setStyleSheet("border-color:red;");
        ui->vd3->setStyleSheet("border-color:white;");
    }else if(pind==3){
        ui->vd1->setStyleSheet("border-color:white;");
        ui->vd2->setStyleSheet("border-color:white;");
        ui->vd3->setStyleSheet("border-color:red;");
    }
    m_rec->change(pind);
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
        selectBox(1);
        int ret=initFileName();
        if(ret) {
            static QMessageBox messageBox(QMessageBox::NoIcon,"",ret==1?"视频保存目录没有写权限！":"创建视频保存目录失败！",QMessageBox::Ok,NULL);
            messageBox.show();
            return;
        }
        ui->m_b_rec->setText("停止");
        yang_post_message(YangM_Rec_Start,0,NULL);
        // m_rec->startRecordLiving();
        m_timer->start(1000);
        m_isStartRec=!m_isStartRec;
        m_recTimeLen=0;
    }else{
        ui->m_b_rec->setText("录制");
        yang_post_message(YangM_Rec_Stop,0,NULL);
        // m_rec->stopRecordLiving();
        m_timer->stop();
        m_isStartRec=!m_isStartRec;
    }

}

void RecordMainWindow::on_m_r_model1_clicked()
{
    if(m_rec) m_rec->setRecordModule(1);

    if(m_ini->record.recordModel==1&&m_synrec){
        if(m_rec) m_rec->setRecordModule(4);
    }
}

void RecordMainWindow::on_m_r_model2_clicked()
{
    if(m_rec) m_rec->setRecordModule(2);
}

void RecordMainWindow::on_m_r_model3_clicked()
{
    if(m_rec) m_rec->setRecordModule(3);
}

void RecordMainWindow::on_m_b_pause_clicked()
{
    if(!m_isStartPause){
        ui->m_b_rec->setText("继续");
        m_rec->pause();
        m_isStartPause=!m_isStartPause;
        m_timer->stop();

    }else{
        ui->m_b_rec->setText("暂停");
        m_rec->resume();
        m_isStartPause=!m_isStartPause;
        m_timer->start();
    }
}

void RecordMainWindow::on_m_zb_clicked()
{
    m_ini->createRtmp=ui->m_zb->checkState()==Qt::Checked?1:0;

    //if(m_rec) m_rec->startFilmLiving();
    qDebug()<<"rtmp............."<<m_ini->createRtmp;
}

void RecordMainWindow::on_m_res_clicked()
{
    m_synrec=ui->m_res->checkState()==Qt::Checked?1:0;
    if(m_ini->record.recordModel==1){
        if(m_synrec)
            m_rec->setRecordModule(4);
        else
            m_rec->setRecordModule(1);
    }
}

void RecordMainWindow::on_m_b_zb_clicked()
{
    if(!m_isStartZb){
        ui->m_b_zb->setText("停止直播");
        yang_post_message(YangM_Rec_Film_Start,0,NULL);
        //if(m_rec) m_rec->startFilmLiving();
        m_isStartZb=!m_isStartZb;


    }else{
        ui->m_b_zb->setText("开始直播");
        yang_post_message(YangM_Rec_Film_Stop,0,NULL);
        // if(m_rec) m_rec->stopFilmLiving();
        m_isStartZb=!m_isStartZb;

    }

}

void RecordMainWindow::on_m_b_pg_clicked()
{

    if(!m_isStartPg){
        ui->m_b_pg->setText("停止评估");
        yang_post_message(YangM_Rec_Pg_Start,0,NULL);
        // if(m_rec) m_rec->startMultiLiving();
        m_isStartPg=!m_isStartPg;


    }else{
        ui->m_b_pg->setText("开始评估");
        yang_post_message(YangM_Rec_Pg_Start,0,NULL);
        // if(m_rec) m_rec->stopMultiLiving();
        m_isStartPg=!m_isStartPg;

    }
}
void RecordMainWindow::changeVideo(int st){
    selectBox(st);
    //if(m_rec) m_rec->change(st);
}
void RecordMainWindow::execCommand(int st){
    if(st==0){

    }else if(st==1){

    }else if(st==2){

    }else if(st==3){

    }
}
void RecordMainWindow::proc( char *b,int llen){
    string cs(b,llen);


    if(cs=="08090801") changeVideo(1);
    //if(cs.find("08090806")>-1) p1->changeS(5);
    if(cs=="08090803") changeVideo(2);
    //if(cs.find("08090805")>-1) p1->changeS(4);
    if(cs=="08090802") changeVideo(3);
}


void RecordMainWindow::on_m_b_autonav_clicked()
{
    m_isAutoNav=!m_isAutoNav;
    //MessageBox(m_cameraHandle.ip);
    if(m_isAutoNav)
    {


        m_cameraHandle.startAutoTrack();
    }
    else{

        m_cameraHandle.stopAutoTrack();
    }
}

void RecordMainWindow::on_m_r_teacher_clicked()
{
    select_id=1;
    m_cameraHandle.m_curCamId=1;
}

void RecordMainWindow::on_m_r_student_clicked()
{
    select_id=2;
    m_cameraHandle.m_curCamId=2;
}


void RecordMainWindow::on_m_b_up_pressed()
{
    m_cameraHandle.changeDirect(0);
}

void RecordMainWindow::on_m_b_down_pressed()
{
    m_cameraHandle.changeDirect(1);
}

void RecordMainWindow::on_m_b_left_pressed()
{
    m_cameraHandle.changeDirect(2);
}

void RecordMainWindow::on_m_b_right_pressed()
{
    m_cameraHandle.changeDirect(3);
}

void RecordMainWindow::on_m_b_zoomIn_pressed()
{
    m_cameraHandle.changeFoci(1);
}

void RecordMainWindow::on_m_b_zoomOut_pressed()
{
    m_cameraHandle.changeFoci(0);
}

void RecordMainWindow::on_m_b_up_released()
{
    m_cameraHandle.stopChangeDirect();
}

void RecordMainWindow::on_m_b_down_released()
{
    m_cameraHandle.stopChangeDirect();
}

void RecordMainWindow::on_m_b_left_released()
{
    m_cameraHandle.stopChangeDirect();
}

void RecordMainWindow::on_m_b_right_released()
{
    m_cameraHandle.stopChangeDirect();
}

void RecordMainWindow::on_m_b_zoomIn_released()
{
    m_cameraHandle.stopChangeFoci();
}

void RecordMainWindow::on_m_b_zoomOut_released()
{
    m_cameraHandle.stopChangeFoci();
}
