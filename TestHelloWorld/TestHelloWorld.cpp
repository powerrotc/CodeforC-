// TestHelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <string.h>


#pragma warning(push)
#pragma warning(disable:4146)

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
#pragma warning(pop)


int main()
{
	_ConnectionPtr pCon = NULL;
	_RecordsetPtr  pRS = NULL; 
	char str[255]; 

	strcpy_s(str, "driver={SQL Server; server = 127.0.0.1;");
	strcat_s(str, "uid=super;pwd=Winnipeg1; database = temp;");

	CoInitialize(NULL);
	pCon.CreateInstance(__uuidof(Connection));

	pCon->Open(str, "", "", 0);
	pRS = pCon->Execute("SELECT * FROM test", NULL, adOptionUnspecified);

	while (pRS->EndOfFile == FALSE)
	{
		printf("%s\n", (LPCTSTR)(_bstr_t)pRS->GetCollect(L"XXX"));
		pRS->MoveNext();
	}

	pRS->Close();
	pCon->Close();

	pRS = NULL; 
	pCon = NULL; 
	CoUninitialize();


}

