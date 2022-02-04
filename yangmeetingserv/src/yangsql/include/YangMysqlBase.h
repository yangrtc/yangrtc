//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef YANGSQL_INCLUDE_YANGMYSQLBASE_H_
#define YANGSQL_INCLUDE_YANGMYSQLBASE_H_
#include <string>
#include <vector>
#include "mysql/mysql.h"
//#include "YangConf.h"
#include "YangConnectionPool.h"
using namespace std;
class YangMysqlBase {
public:
	YangMysqlBase();
	virtual ~YangMysqlBase();
	void initMysql();
	vector<vector<string>> querySql(char* psql);
	int exeSql(string str);

	//void init();

protected:
	YangPool *m_sql;
	//YangConf *m_conf;

};

#endif /* YANGSQL_INCLUDE_YANGMYSQLBASE_H_ */
