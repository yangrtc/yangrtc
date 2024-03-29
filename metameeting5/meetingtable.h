﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef MEETINGTABLE_H
#define MEETINGTABLE_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QList>
#include "src/yangwinutil/yanghttputil.h"
#include "src/login/yangmeetings.h"
#include "src/login/yangUserInfo.h"
#include "src/yangwinutil/yangqInterfaces.h"
#include "src/yangwinutil/yangvideocontext.h"
namespace Ui {
class MeetingTable;
}

class MeetingTable : public QDialog,public YangLinkButtonI
{
    Q_OBJECT

public:
    explicit MeetingTable(YangVideoContext* pcontext,QWidget *parent = nullptr);
    ~MeetingTable();
    void initTable();
    void setIndex(int pindex);
signals:
    void IntoMeetingEvent();

private:
    Ui::MeetingTable *ui;
    QTableWidget *m_table;
    QVBoxLayout *m_vb;
    QList<YangMeetingInfo*> meetings;


    int32_t m_selIndex=0;

private slots:
   //void intoMeeting();
  // void tableView_clicked(const QModelIndex &index);
   // void selectMeeting();
public:
    YangHttpUtil *m_http;

    //YangMeetings m_meetings;
    YangMeetingInfoHandle *m_meetinghandle;
    YangVideoContext* m_context;

};

#endif // MEETINGTABLE_H
