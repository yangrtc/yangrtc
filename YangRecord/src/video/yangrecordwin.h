#ifndef YangRecordWin_H
#define YangRecordWin_H
#include <QDialog>
#include <QHBoxLayout>
#include "yangrecordvideowin.h"
#include "../yangwinutil/yangqInterfaces.h"
//#include "yangselectuservideo.h"
#include "yangvideotype.h"
class YangRecordWin: public QWidget
{
Q_OBJECT
public:
    YangRecordWin(QWidget *parent = nullptr);
    virtual ~YangRecordWin();

    QHBoxLayout *m_hb;
    YangRecordVideoWin *vwin;
    void init();
protected:
   // void showEvent(QShowEvent *event);
private slots:
    //void onTaskBoxContextMenuHandle();
   // void initContextMenu(const QPoint &pos);
   // void onVideoClick();
private:

   // void addMenu(int pind,QString str,QMenu *pMenu);
};

#endif // YANGVIDEOWIN_H
