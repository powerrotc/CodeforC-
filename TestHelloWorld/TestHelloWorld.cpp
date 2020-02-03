// TestHelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "CConnectionMSSQL.h"


void processTableOfDB(CConnectionMSSQL* dbPtr, string strTableName);


int main()
{

    CConnectionMSSQL* dbConnect = new CConnectionMSSQL;

    string dbName = "test";

    if (dbConnect->ConnectionDB(dbName))
    {
        string strSQL = "SELECT * FROM test";

        processTableOfDB(dbConnect, strSQL);
    }

    delete dbConnect;
}

void processTableOfDB(CConnectionMSSQL * dbPtr, string strTableName)
{
    dbPtr->ExecuteSQL(strTableName);

    _RecordsetPtr pRs = dbPtr->GetRecordsetPtr();




    if (pRs != NULL)
    {

        _variant_t    vtColumn;
        _variant_t    vtNull;

        vtNull.ChangeType(VT_NULL);




        TCHAR    strDisp[MAX_PATH + 1];
        short    i;
        long    nRow = pRs->Fields->Count;    // Getting a field's count 

        // write field name 
        for (i = 0; i < nRow; i++)
        {
            // Acquire field name 
            vtColumn = pRs->Fields->GetItem(i)->Name;

            vtColumn.ChangeType(VT_BSTR);
            lstrcpyn(strDisp, (_bstr_t)vtColumn, MAX_PATH);

            if (i == nRow - 1) {
                printf("%s\n", strDisp);
            }
            else {
                printf("%s,", strDisp);
            }
        }

        pRs->MoveFirst();

        // write field value 
        if (!pRs->EndOfFile)
        {
            while (!pRs->EndOfFile)
            {
                for (i = 0; i < nRow; i++)
                {
                    vtColumn = pRs->GetCollect(i);

                    // if data is null then use "" 
                    if (vtColumn == vtNull) {
                        vtColumn = _variant_t("");
                    }
                    else {
                        vtColumn.ChangeType(VT_BSTR);
                    }
                    lstrcpyn(strDisp, (_bstr_t)vtColumn, MAX_PATH);

                    if (i == nRow - 1) {
                        printf("%s\n", (LPCSTR)strDisp);
                    }
                    else {
                        printf("%s,", (LPCSTR)strDisp);
                    }
                }

                pRs->MoveNext();
            }
        }

        dbPtr->ClosedDB();
    }

}


/*
#include "stdafx.h"
#include "stdio.h"
#include "io.h"

// ADO DLL 임포트
#import "C:\Program files\Common Files\System\Ado\msado15.dll" no_namespace rename("EOF", "ADOEOF")

int main()
{
    HRESULT    hr;

    // COM 라이브러리 초기화
    CoInitialize(NULL);

    try {

        _ConnectionPtr    pConn;
        _RecordsetPtr    pRs;

        hr = pConn.CreateInstance(__uuidof(Connection));
        hr = pRs.CreateInstance(__uuidof(Recordset));

        pConn->CursorLocation = adUseClient;

        // MySQL ODBC 접속 문자열
        _bstr_t strConn("DRIVER={MySQL ODBC 3.51 Driver};SERVER = localhost;DATABASE = hong;UID = hong; PWD = hong;");

        // 데이터베이스 접속
        hr = pConn->Open(strConn, "", "", adConnectUnspecified);

        // 레코드셋 설정
        hr = pRs->Open("select * from animal", pConn.GetInterfacePtr(), adOpenForwardOnly, adLockReadOnly, adCmdText);


        _variant_t    vtColumn;
        _variant_t    vtNull;

        vtNull.ChangeType(VT_NULL);

        TCHAR    strDisp[MAX_PATH + 1];
        short    i;
        long    nRow = pRs->Fields->Count;    // 레코드수 취득

        // 필드명 표시
        for (i = 0; i < nRow; i++)
        {
            // 필드명 취득
            vtColumn = pRs->Fields->GetItem(i)->Name;

            vtColumn.ChangeType(VT_BSTR);
            lstrcpyn(strDisp, (_bstr_t)vtColumn, MAX_PATH);

            if (i == nRow - 1) {
                TRACE("%s\n", strDisp);
            }
            else {
                TRACE("%s,", strDisp);
            }
        }

        pRs->MoveFirst();

        // 필드값 표시
        if (!pRs->ADOEOF)
        {
            while (!pRs->ADOEOF)
            {
                for (i = 0; i < nRow; i++)
                {
                    vtColumn = pRs->GetCollect(i);

                    // 데이터가 NULL이면 ""을 대입
                    if (vtColumn == vtNull) {
                        vtColumn = _variant_t("");
                    }
                    else {
                        vtColumn.ChangeType(VT_BSTR);
                    }
                    lstrcpyn(strDisp, (_bstr_t)vtColumn, MAX_PATH);

                    if (i == nRow - 1) {
                        TRACE("%s\n", (LPCSTR)strDisp);
                    }
                    else {
                        TRACE("%s,", (LPCSTR)strDisp);
                    }
                }

                pRs->MoveNext();
            }
        }

        hr = pRs->Close();


    }
    catch (_com_error & e) {
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
        printf("Error:%s\n", (LPCSTR)bstrDescription);
    }
}

*/