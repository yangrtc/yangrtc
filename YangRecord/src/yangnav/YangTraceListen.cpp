#include "YangTraceListen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
//#define SOCKADDR_IN
#define socklen_t int
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#ifdef _WIN32

#else
#define closesocket(s)	close(s)
#endif
using namespace std;
YangTraceListen::YangTraceListen(void)
{
    m_isConvert=0;
    m_isStart=0;
}


YangTraceListen::~YangTraceListen(void)
{
}

void YangTraceListen::stop(){
    m_isConvert=0;
}

void YangTraceListen::run(){
    m_isStart=1;
    udpListen();
    m_isStart=0;
}
void YangTraceListen::udpListen(){
	
 #ifdef _WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);
#endif
    int sockfd;

    struct sockaddr_in l_addr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("UDP socket create error!");
        exit(1);
    }
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 300*1000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv,
            sizeof(struct timeval));
    l_addr.sin_family = AF_INET;
    l_addr.sin_port = htons(8006);
    l_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*) &l_addr, sizeof(l_addr)) < 0) {
        printf("Udp server bind error");
        exit(1);
    }
    char buffer[1024] = { 0 };
    m_isConvert=1;
    while (m_isConvert) {
        struct sockaddr_in src;
        socklen_t src_len = sizeof(src);
        memset(&src, 0, sizeof(src));
        memset(buffer, 0, 1024);
        if( recvfrom(sockfd, buffer, 128, 0, (sockaddr*) &src, &src_len)>0){

            printf("%s\n",buffer);
         //   if(strlen(buffer) < 8)         continue;
                    proc(buffer,src_len);


        }
    }

    closesocket(sockfd);

}

void YangTraceListen::proc(char *b,int plen){
		/**if(b[0]==0x01){
		switch(b[1]){
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
	
	}else{
		p1->proc(b,sockConn,sa,llen);
	}**/
   std::string cs=b;

	//MessageBox(hwd,cs,cs,MB_OK);
    if(cs=="08090801"||cs=="08090806") p1->changeVideo(1);
    if(cs=="08090803"||cs=="08090805") p1->changeVideo(2);
    if(cs=="08090802"||cs=="08090804") p1->changeVideo(3);
    //if(cs=="08090804") p1->changeS(6);
    //if(cs=="08090807") p1->changeS(7);
    /**if(cs=="08090801"||cs=="08090806") p1->changeS(1);
    if(cs=="08090803") p1->changeS(2);
    if(cs=="08090805") p1->changeS(4);
    if(cs=="08090802"||cs=="08090804") p1->changeS(3);**/


    //if(cs=="")){p1->changeS(1);
}
