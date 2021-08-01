#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QHBoxLayout>
#include "yangrecliving/YangLivingHandle.h"
#include "src/video/yangrecordthread.h"
//#include "src/video/yangrecordwin.h"
#include "src/video/yangrecordvideowin.h"
#include "src/video/YangPlayWidget.h"
#include "yangrecliving/YangRecMessageI.h"
#include "yangutil/sys/YangSysMessageHandle.h"
QT_BEGIN_NAMESPACE
namespace Ui { class RecordMainWindow; }
QT_END_NAMESPACE

class RecordMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    RecordMainWindow(QWidget *parent = nullptr);
    ~RecordMainWindow();
    YangSysMessageHandle* m_recMessage;
    YangLivingHandle *m_rec;
    YangRecordContext *m_ini;
    YangRecordThread* m_rt;
    int m_showType;

    YangPlayWidget *m_win0;
    YangRecordVideoWin *m_win1;
    QHBoxLayout *m_hb0;
public:
     void initVideoThread(YangRecordThread *prt);
    void closeEvent( QCloseEvent * event );
private slots:
    void on_m_b_rec_clicked();
    void on_m_b_pause_clicked();

    void on_m_zb_clicked();
    void m_onTimeout();
    void on_m_res_clicked();
    void on_m_c_vr_clicked();
    void on_m_c_screen_clicked();

private:
    void init(YangRecordContext *para);
    Ui::RecordMainWindow *ui;
    void initPreview();
    int initFileName();
    void closeAll();

private:
    int m_isStartRec,m_isStartPause;
    int m_isVr;
    QTimer *m_timer;
    int m_recTimeLen;

};
#endif // MAINWINDOW_H
