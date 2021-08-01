#ifndef YANGSWIN_H
#define YANGSWIN_H

#include <QWidget>
class YangRecordVideoWin : public QWidget
{
    Q_OBJECT
public:
    explicit YangRecordVideoWin(QWidget *parent = nullptr);
     ~YangRecordVideoWin();
public:
    QPaintEngine* paintEngine()const;
    int sid;

private:

private:


//signals:

};

#endif // YANGSWIN_H
