//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef YANGHTTP_YANGSERVERLETMANAGER_H_
#define YANGHTTP_YANGSERVERLETMANAGER_H_
#include "../yangsql/include/YangUserManager.h"
#include <map>
class YangServerletManager {
public:
	YangServerletManager();
	virtual ~YangServerletManager();
	string handle(char* p);

	YangUserManager ym;


	void split(const string s,vector<string>* sv,const char flag );
	void split1(const string s,map<string,string>* sv,const char flag );
};

#endif /* YANGHTTP_YANGSERVERLETMANAGER_H_ */
