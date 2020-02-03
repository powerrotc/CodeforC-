#include "CConnectionMSSQL.h"
#include <stdio.h>
#include <string.h>


//#pragma warning(push)
//#pragma warning(disable:4146)
//
//#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")
//#pragma warning(pop)




CConnectionMSSQL::CConnectionMSSQL() 
{
	 pCon = NULL;
	 pRS = NULL;

}
CConnectionMSSQL::~CConnectionMSSQL()
{
    pCon = NULL;
    pRS = NULL;
}

bool CConnectionMSSQL::ConnectionDB(string dbstrName)
{
    if (!dbstrName.size())
        return false;

    char str[255];
    char strtemp[255];

    strcpy_s(str, "driver={SQL Server;server=127.0.0.1;");
    strcat_s(str, "uid=super;pwd=Winnipeg1;database=");

    strcpy_s(strtemp, dbstrName.c_str());

    strcat_s(str, strtemp);
    strcat_s(str, ";");

  
    //strcat_s(str, "uid=super;pwd=Winnipeg1;database=temp;");

    try
    {
        CoInitialize(NULL);
        pCon.CreateInstance(__uuidof(Connection));

        pCon->Open(str, "", "", 0);
        //pRS = pCon->Execute("SELECT * FROM test", NULL, adOptionUnspecified);
    }

    catch (_com_error & e)
    {
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
        printf("Error:%s\n", (LPCSTR)bstrDescription);
    }

    return true;
}
void CConnectionMSSQL::ClosedDB()
{
    pRS->Close();
    pCon->Close();

    pRS = NULL;
    pCon = NULL;
    CoUninitialize();
}


_RecordsetPtr CConnectionMSSQL::GetRecordsetPtr()
{
    return pRS;
}

_ConnectionPtr CConnectionMSSQL::GetConnectionPtr()
{
    return pCon;
}

_RecordsetPtr CConnectionMSSQL::ExecuteSQL(string strTableName)
{
    char tableName[255]; 
    strcpy_s(tableName, strTableName.c_str());

    try 
    {
        pRS = pCon->Execute((_bstr_t)tableName, NULL, adOptionUnspecified);
    }
    catch (_com_error & e)
    {
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
        printf("Error:%s\n", (LPCSTR)bstrDescription);
    }


    return pRS;
}
