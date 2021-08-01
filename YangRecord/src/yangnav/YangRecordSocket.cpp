#include "YangRecordSocket.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <string.h>
#include <string>

using namespace std;
YangRecUDP::YangRecUDP(void)
{
    m_isStart=0;
    m_isConvert=0;
	p1=NULL;
}


YangRecUDP::~YangRecUDP(void)
{
}
void YangRecUDP::stop(){
m_isConvert=0;
}

void YangRecUDP::run(){
    m_isStart=1;
    udpListen();
    m_isStart=0;

}

void YangRecUDP::udpListen(){

 int sock_fd=socket(AF_INET,SOCK_DGRAM,0);
 
 sockaddr_in addr_serv;
 memset(&addr_serv, 0, sizeof(sockaddr_in));

 addr_serv.sin_addr.s_addr=htonl(INADDR_ANY);
 addr_serv.sin_family=AF_INET;
 addr_serv.sin_port=htons(6000);
 if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0) {
	 perror("bind error:");
	 exit(1);
 }
 
 struct sockaddr_in addr_client;
 int len=sizeof(addr_serv);
 char recvBuf[128];
 char sendBuf[128];
 memset(recvBuf,0,128);
 memset(sendBuf,0,128);
 //string s("this is a test!");
// s.copy(sendBuf,s.length(),0);
m_isConvert=1;
 while(m_isConvert)
 {
	recvfrom(sock_fd,recvBuf,128,0,(sockaddr*)&addr_client,(socklen_t *)&len);

	if(p1) proc(recvBuf,len);


 }
 close(sock_fd);

}


void YangRecUDP::proc(char *b,int p_len){

	if(b[0]==0x01){
		if(b[1]==0x68&&b[2]==0x33){
		//printf("\n lubo...%x,%x,%x,%x",b[0],b[1],b[2],b[3]);
			switch(b[3]){			
				case 0x04:
                //record start
                    p1->execCommand(3);
					break;
				case 0x05:
                //close
                    p1->execCommand(0);
					break;
				case 0x06:
                //hd start
                    p1->execCommand(2);
					break;
				case 0x07:
                //pg start
                    p1->execCommand(1);
					break;
				case 0x09:
                //exit
                    p1->execCommand(9);
					break;
			}
		}else if(p_len==9){
			string cs(b);


            if(cs=="08090801") p1->changeVideo(1);
			//if(cs.find("08090806")>-1) p1->changeS(5);
            if(cs=="08090803") p1->changeVideo(2);
			//if(cs.find("08090805")>-1) p1->changeS(4);
            if(cs=="08090802") p1->changeVideo(3);
			//if(cs.find("08090804")>-1) p1->changeS(6);
			//if(cs.find("08090807")>-1) p1->changeS(7);
		}
	}
		/**switch(b[1]){
		case 0x01:
			p1->changeS(1);
			break;
		case 0x02:
			p1->changeS(2);
			break;
		case 0x03:
			p1->changeS(3);
			break;
		}
	
	}else if(b[0]==0x01&&b[1]==0x68&&b[2]==0x33){
		switch(b[3]){
			
			case 0x04:
				p1->startStop(1);
				break;
			case 0x05:
				p1->startStop(0);
				break;
		}**/
	
	//else{
		//p1->proc(b,sockConn,sa,llen);
	//}
}



YangUdpUtil::YangUdpUtil(void)
{
	sockSrv=0;
}


YangUdpUtil::~YangUdpUtil(void)
{
	 close(sockSrv);
}
void YangUdpUtil::init(const char *ip,int port){

	addrClient1.sin_family=AF_INET;
	addrClient1.sin_port=htons(port);
	addrClient1.sin_addr.s_addr=inet_addr(ip);
	//addrClient1.sin_addr.S_un.S_addr=inet_addr("218.198.88.123");
	//addrClient1.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//218.198.88.123
	sockSrv=socket(AF_INET,SOCK_DGRAM,0);
}
int YangUdpUtil::sendUdp(char* data,int len){
	
	return sendto(sockSrv,data,len+1,0,(sockaddr*)&addrClient1,sizeof(sockaddr)); 
}
