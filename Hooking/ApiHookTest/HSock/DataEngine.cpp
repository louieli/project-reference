#include "stdafx.h"
#include "dataengine.h"

CDataEngine::CDataEngine()
{
}

CDataEngine::~CDataEngine()
{
}

void CDataEngine::parser(const char* pfile)
{
	m_info.empty();
	
	if(!pfile)
		return;

	FILE* pf = fopen(pfile, "rb");
	if(!pf)
		return;

	string str_line;
	char   c(0);
	while(!feof(pf))
	{
		if(fread(&c, 1, 1, pf) != 1)
			break;

		if(c == '\r' || c == '\n')
		{
			if(str_line.length() == 0)
				continue;

			parserline(str_line);
			str_line = "";
		}
		else
		{
			str_line += c;
		}
	}

	if(str_line.length() > 0)
		parserline(str_line);
}

void CDataEngine::parserline(string& str_line)
{
	data_info info;
	string* str_act = &info.des_module;
	
	int  nflag = 0;
	char c(0);
	for(int i = 0; i < str_line.length(); i++)
	{
		c = str_line[i];
		if(i == 0 && c == ';')
		{
			break;
		}
		if(c == '|')
		{
			switch(nflag)
			{
			case 0:
				str_act = &info.des_fun;
				break;
			case 1:
				str_act = &info.mine_module;
				break;
			case 2:
				str_act = &info.mine_fun;
				break;
			}
			nflag++;
		}
		else if(c != ' ')
		{
			*str_act += c;
		}
	}

	if(info.des_fun.length() > 0 &&
	   info.des_module.length() > 0 &&
	   info.mine_fun.length() > 0 &&
	   info.mine_module.length() > 0)
	{
		m_info.push_back(info);
	}
}

int CDataEngine::get_size()
{
	return m_info.size();
}

data_info* CDataEngine::get_info(int nindex)
{
	if(m_info.size() < nindex+1)
		return NULL;

	return &m_info[nindex];
}
