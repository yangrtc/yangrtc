#ifndef __YangRecordI___
#define __YangRecordI___

class YangRecordI{
	public:
		YangRecordI(){};
	virtual	~YangRecordI(){};
	public:
        virtual void changeVideo(int st)=0;
        virtual void execCommand(int st)=0;
        virtual void proc( char *b,int llen)=0;
};
#endif
