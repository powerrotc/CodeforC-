#pragma once


#pragma warning(push)
#pragma warning(disable:4146)

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
#pragma warning(pop)

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class CConnectionMSSQL
{
public:

	CConnectionMSSQL();
	~CConnectionMSSQL();

	bool ConnectionDB(string dbstrName);
	void ClosedDB();

	_ConnectionPtr GetConnectionPtr();
	_RecordsetPtr GetRecordsetPtr();

	_RecordsetPtr ExecuteSQL(string str);


private:
	_ConnectionPtr pCon;
	_RecordsetPtr  pRS;

};

