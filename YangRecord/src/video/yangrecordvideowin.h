#ifndef YANGSWIN_H
#define YANGSWIN_H

#include <QWidget>
#include "../yangplayer/YangPlayWidget.h"
class YangRecordVideoWin : public YangPlayWidget
{
    Q_OBJECT
public:
    explicit YangRecordVideoWin(QWidget *parent = nullptr);
     ~YangRecordVideoWin();
public:
    QPaintEngine* paintEngine()const;
    int sid;
signals:
    void clicked();
protected:
 void mousePressEvent(QMouseEvent *);
private:

private:

private slots:
void onVideoClick();
//signals:

};

#endif // YANGSWIN_H
