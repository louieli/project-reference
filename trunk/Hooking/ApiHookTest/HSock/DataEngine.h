/*****************************************************************************
Filename: 	DataEngine.h
Copyright(C) XXXXXXXXXXXXX

Created:	2004-07-09
Author:     jyan
Abstract:	
            从特定格式的文件读取配置
            格式如下：
            SysDllName|SysApiName|YourDllName|YourApiName
            
Modified History:	
        Who             When                Modify
*****************************************************************************/

#ifndef _DATA_ENGINE_H
#define _DATA_ENGINE_H

#include "string"
#include "vector"
using namespace std;

struct data_info
{
	string des_module;
	string des_fun;
	string mine_module;
	string mine_fun;
};

class CDataEngine
{
public:
	CDataEngine();
	virtual ~CDataEngine();

	void parser(const char* pfile);
	int  get_size();

	data_info* get_info(int nindex);

private:
	void parserline(string& str_line);
	vector<data_info> m_info;
};

#endif