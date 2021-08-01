#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTimer>
#include "yangrecliving/YangVrHandle.h"
#include "src/video/yangrecordthread.h"
#include "src/video/yangrecordwin.h"
#include "src/video/yangrecordvideowin.h"
#include "src/yangnav/YangRecordI.h"
#include "yangutil/sys/YangSysMessageHandle.h"
#include "src/yangnav/YangCameraCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RecordMainWindow; }
QT_END_NAMESPACE

class RecordMainWindow : public QMainWindow,public YangRecordI
{
    Q_OBJECT

public:
    RecordMainWindow(QWidget *parent = nullptr);
    ~RecordMainWindow();

    YangVrHandle *m_rec;
    YangRecordContext *m_ini;
    YangRecordThread *m_rt;
    YangSysMessageHandle *m_recMessage;


    YangRecordVideoWin *m_win1,*m_win2,*m_win3,*m_win0;
    QHBoxLayout *m_hb1,*m_hb2,*m_hb3,*m_hb0;
public:
    void changeVideo(int st);
    void execCommand(int st);
    void proc( char *b,int llen);
    void initVideoThread(YangRecordThread *prt);
public:
    void selectBox(int pind);
private slots:
    void on_m_b_rec_clicked();
    void on_m_r_model1_clicked();
    void on_m_r_model2_clicked();
    void on_m_r_model3_clicked();
    void on_m_b_pause_clicked();
    void on_m_zb_clicked();
    void m_onTimeout();
    void on_m_res_clicked();
    void on_m_b_zb_clicked();
    void on_m_b_pg_clicked();

    void on_m_b_autonav_clicked();

    void on_m_r_teacher_clicked();

    void on_m_r_student_clicked();



    void on_m_b_up_pressed();

    void on_m_b_down_pressed();

    void on_m_b_left_pressed();

    void on_m_b_right_pressed();

    void on_m_b_zoomIn_pressed();

    void on_m_b_zoomOut_pressed();

    void on_m_b_up_released();

    void on_m_b_down_released();

    void on_m_b_left_released();

    void on_m_b_right_released();

    void on_m_b_zoomIn_released();

    void on_m_b_zoomOut_released();

private:
    YangCameraCommand m_cameraHandle;
    void init(YangRecordContext *para);
    Ui::RecordMainWindow *ui;
    void initPreview();
    int initFileName();
    void destroyAll();

private:
    int m_isAutoNav,select_id;
    int m_isStartRec,m_isStartPause;
    int m_isStartZb,m_isStartPg;
    QTimer *m_timer;
    int m_recTimeLen;
    int m_synrec;

};
#endif // MAINWINDOW_H
