// CardInterfaceTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <assert.h>
#include "../CardInterface/CardInterface.h"

void GetPrinters()
{
	int printerCount = Card_GetPrinterCount();
	if(printerCount>0)
	{
		char** printers = new char*[printerCount];
		for (int i = 0; i < printerCount; ++i)
		{
			printers[i] = new char[100];
			memset(printers[i],0x00,100);
		}

		Card_GetPrinters(printers,printerCount);

		for (int i = 0; i < printerCount; ++i)
        {
          cout << printers[i] << endl;
		  delete[] printers[i];
		}
		delete [] printers;
	} 
}

void ReadAndWriteTrack(int trackNo)
{
	int ret = 0;
	char error[1024] = {0};
	char writeTrack[20];
	char readTrack[20];
	memset(writeTrack,0,sizeof(writeTrack));
	memset(readTrack,0,sizeof(readTrack));
	strcpy(writeTrack,"12345678");
	ret = Card_WriteTrack(trackNo,writeTrack);
	if(ret)
	{
		memset(error,0,sizeof(error));
		Card_GetLastError(error);
		cout<<"Write Track Error: "<<error<<endl;
	}
	assert(ret==0);

	ret = Card_ReadTrack(trackNo,readTrack);
	if(ret)
	{
		memset(error,0,sizeof(error));
		Card_GetLastError(error);
		cout<<"Rrite Track Error: "<<error<<endl;
	}
	assert(ret==0);
	assert(strcmp(writeTrack,readTrack)==0);
}

void Print()
{
	char expiredDate[11] = "2022-01-21";
	int parValue = 1000;
	int ret = Card_Print(expiredDate,parValue);
	assert(ret==0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	ret = Card_Init();
	std::cout<<"Card_Init:"<<ret<<endl;
	//GetPrinters();

	//ReadAndWriteTrack(1);
	Print();

	return 0;
}

