// CardInterface.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <winspool.h>
#include <vector>
using namespace std;

#include "Global.h"
#include "CardInterface.h"
#include "Printer.h"

CPrinter *printer = NULL;            //默认打印机
vector<string> printerList;   //当前可用打印机列表

int InitPrinterList()
{
	bool bStatus = false;
	PRINTER_INFO_2 * InfoPrint=NULL;
	PRINTER_INFO_2 * InfoBase;
	PRINTER_INFO_2 * InfoMemory;
	DWORD Receive, Nbre;
	DWORD Need;
	int i,j=0, base = 0;
	TCHAR erreur[128];
	static char	PrinterName[512] = " ";
	static char PrinterID[512] = " ";
	CIomem Discussion;
	char* cde;
	
	//TODO moved free space
	//freeSpace();

	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 2, (LPBYTE) InfoPrint,0, &Receive, &Nbre);
	Need = Receive;
	//memory allocation
	InfoMemory = InfoBase = InfoPrint = (PRINTER_INFO_2 * ) GlobalAlloc(GPTR, Need);
	i = EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 2, (LPBYTE) InfoPrint, Need, &Receive, &Nbre);
	if (i)  {
		for(i=0; i < (int) Nbre; i++)  {
			if (strncmp(InfoPrint->pDriverName, EVOLIS_DRIVER, 6) == 0) {
				Discussion.SetPrinterName(InfoPrint->pPrinterName);
				Discussion.SetTout(1000);
				if(Discussion.OpenEvoPrinter()) {
					cde = "\x1bRtp\x0d";
					Discussion.SetCde(cde);
					if (Discussion.WRPrinter()) {	
						strcpy(PrinterID,Discussion.GetLastAnswer());
						printerList.push_back(InfoPrint->pPrinterName);
						if (strncmp(&InfoPrint->pDriverName[7], PrinterID, 6) == 0 && !bStatus) {
							InfoBase=InfoPrint;
							base=j;
							bStatus=true;
						}
						j++;
					}
					Discussion.CloseEvoPrinter();
					Discussion.SetTout(30000);
				}					
			}		
			InfoPrint++;
		}
		if(!i || !j) {
			strcpy(erreur,"No printer available");
		}
		else {
			strcpy(PrinterName,InfoBase->pPrinterName);
			if (strncmp(&InfoBase->pDriverName[7],"Dualys",6)==0 || strncmp(&InfoBase->pDriverName[7],"Pebble",6)==0) {				
				//we don't support any other printer now
				printer = new CPrinter();
				printer->SetDriverName(InfoBase->pDriverName);
				printer->SetPrinterName(PrinterName);
			}
		}
	}
	//free memory
	GlobalFree(InfoMemory);
	return (bStatus);
}

int Card_Init()
{
	if(InitPrinterList())
	{
		return SUCCESS;
	}
	return NO_PRINTER;
}

int Card_GetPrinterCount()
{
	return printerList.size();
}

void Card_GetPrinters(OUT char **printers,IN int size)
{
	for(int i=0;i<size;i++)
	{
		char* printer = printers[i];
		strcpy(printer,printerList[i].c_str());
	}
}

int Card_ExecuteCommand(IN const char* command, OUT char* answer)
{
	CHECK_PRINTER();
	string sAnswer;
	printer->SendCommand(command, 60000,sAnswer);
	if(answer){
		strcpy(answer,sAnswer.c_str());
	}
	return SUCCESS;
}

int Card_ReadTrack(IN int trackNo, OUT char* trackInfo)
{
	CHECK_PRINTER();
	int ret = SUCCESS;
	string readTrackInfo;

	if (!printer->ReadTrack(trackNo,readTrackInfo)) 
	{
		ret = printer->AnalyzeAnswer();
	}
	if(trackInfo)
	{
		strcpy(trackInfo,readTrackInfo.c_str());
	}
	return ret;
}

int Card_WriteTrack(IN int trackNo,IN char *trackInfo)
{
	CHECK_PRINTER();
	int ret = SUCCESS;
	string writeTrackInfo;

	writeTrackInfo.append(trackInfo);
	if (printer->WriteTrack(trackNo,writeTrackInfo)) {
	}
	else {
		ret = printer->AnalyzeAnswer();
	}
	return ret;
}

void Card_GetLastError(OUT char *message)
{
	if(message)
	{
		if(printer)
		    strcpy(message,printer->GetErrorMessage().c_str());
		else
			strcpy(message,"没有可用的打印机");
	}
}

int Card_EjectCard(OUT char* answer)
{
	CHECK_PRINTER();
	string sAnswer;
	printer->SendCommand("Se", 30000,sAnswer);
	if(answer){
		strcpy(answer,sAnswer.c_str());
	}
	return SUCCESS;	
}

int Card_SetCoercivity(IN char coercivity)
{
	CHECK_PRINTER();
	printer->SetCoercivity(coercivity);
	return SUCCESS;	
}

int Card_Print(IN char* expiredDate, IN int parValue)
{
	CHECK_PRINTER();
	int ret = SUCCESS;
	if (!printer->Print(expiredDate,parValue)) 
	{
		ret = printer->AnalyzeAnswer();
	}
	return ret;
}

int Card_PrintPassword(IN char* password)
{
	CHECK_PRINTER();
	int ret = SUCCESS;
	if (!printer->PrintPassword(password)) 
	{
		ret = printer->AnalyzeAnswer();
	}
	return ret;
}