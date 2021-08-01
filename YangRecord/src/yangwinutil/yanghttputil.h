#ifndef YANGHTTPUTIL_H
#define YANGHTTPUTIL_H
#include <QNetworkAccessManager>
#include <QWidget>
#include "yangrecliving/YangLivingType.h"
#include "yangqInterfaces.h"
class YangHttpUtil:public QWidget
{
public:
    YangHttpUtil(YangRecordContext *pini);
     ~YangHttpUtil();
    QString m_url,m_ip;
    int m_port;
    void init(YangRecordContext *pini);
   // void setBase(YangHttpBase *phb);
public:
   // int getHttp(QString qs);
    int getPost(QString module,QString param,YangHttpI *phb);
public slots:
void finished(QNetworkReply *reply);
private:
   // QNetworkAccessManager* m_net;
   // YangHttpBase *m_hb;
};

#endif // YANGHTTPUTIL_H
