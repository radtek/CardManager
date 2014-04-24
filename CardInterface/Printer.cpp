// Printer.cpp: implementation of the CPrinter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Printer.h"
#include <winspool.h>
#include "Global.h"

#define	MAX_STR		1028



//////////////////////////////////////////////////////////////////////
// Constructor/Destructor
//////////////////////////////////////////////////////////////////////

CPrinter::CPrinter():detailAnswer("")
{
	//initialisation of answer map
	printerErrors["OK"] = OK_PRINTER;
	printerErrors["ERROR"] = ERR_PRINTER;
	printerErrors["ERROR CDE"] = ERR_CDE;
	printerErrors["ERROR PARAMETRES"] = ERR_PAR;
	printerErrors["NEED CLEANING"] = ERR_NEED_CLEAN;
	printerErrors["ERROR TIME OUT"] = ERR_TIME;
	printerErrors["ERROR HOPPER"] = ERR_MECA_HOPPER;
	printerErrors["HOPPER FULL"] = ERR_HOPPER_FULL;
	printerErrors["HOPPER DOOR"] = ERR_HOPPER_DOOR;
	printerErrors["ERROR HEAD"] = ERR_PRINT_HEAD;
	printerErrors["COVER OPEN"] = ERR_COVER;
	printerErrors["FEEDER EMPTY"] = ERR_FEEDER;
	printerErrors["CARD JAM"] = ERR_CARD_JAM;
	printerErrors["ERROR RIBBON"] = ERR_RIBBON;
	printerErrors["OPT NOT AVAILABLE"] = ERR_OPTION;
	printerErrors["ERROR MAGN CHECKSUM"] = ERR_CHECK_M;
	printerErrors["ERROR MAGN DATA"] = ERR_DATA_M;
	printerErrors["ERROR MAGN"] = ERR_WRITE_M;
	printerErrors["ERROR UNKNOW"] = ERR_UNKNOW;

	coercivity = COERCIVITY_HIGH;
}

CPrinter::~CPrinter()
{
	detailAnswer.clear();
	printerErrors.clear();	
}

void CPrinter::SendCommand(const char* command, long timeout, string &answer)
{
	if (OpenEvoPrinter()) {	
		SetTout(timeout);
		SetCommand(command);
		if(WRPrinter()) {
		  answer.append(GetLastAnswer());	
		}
		else {
			answer.append("Fail to execute command");
		}
		
		CloseEvoPrinter();
	}
}

bool CPrinter::DoAction(const char* command, long timeout, bool bPrev)
{
	bool bStatus = true;

	SetTout(timeout);
	SetCommand(command);
	if(!WRPrinterOK(bPrev)) {
		bStatus = false;
	}
	return(bStatus);
}

void CPrinter::SetCommand(const char* command)
{
	int len = strlen(command);
	char *cde = new char[len+3];
	memset(cde,0x00,len+3);
	//add Start Character and Stop Character
	sprintf(cde,"\x1B%s\x0D",command);
	SetCde(cde);
	delete [] cde;
}

int CPrinter::AnalyzeAnswer() 
{
	int ret = SUCCESS;
	detailAnswer.clear();
	LPSTR lpBuffer = GetLastAnswerError();

	map<string,int>::iterator i;
	i = printerErrors.find(lpBuffer);
		
	if ( i != printerErrors.end( ) ) {
		detailAnswer.append(lpBuffer);
		ret = i->second;
	}
	else {
		detailAnswer.append(GetLastAnswer());
		ret = ERR_UNKNOW;
	}
	return ret;
}

string CPrinter::GetErrorMessage()
{
	return detailAnswer;
}

void CPrinter::GetCoercivityCommand(char* command)
{
	if(command){
		if(this->coercivity == 'l' || this->coercivity == 'h'){
			sprintf(command,"Pmc;%c",coercivity);
		}
	}
}

void CPrinter::SetCoercivity(char value)
{
	coercivity = value;
}

bool CPrinter::WriteTrack(int trackNo, string &trackInfo)
{
	bool bStatus = true;
	string message;
	char command[20];
	memset(command,0,sizeof(command));

	if (OpenEvoPrinter()) {
		bStatus = DoAction("Pem;2",2000,bStatus);
		bStatus = DoAction("Ss",2000,bStatus);
		GetCoercivityCommand(command);
		bStatus = DoAction(command,2000,bStatus);

		SetTout(30000);
		memset(command,0,sizeof(command));
		sprintf(command,"Dm;%d;%s",trackNo,trackInfo.c_str());
		
		SetCommand(command);
		if(!WRPrinterOK(bStatus)) {
			bStatus = false;
		}

		if (bStatus) {	
			SetCommand("Smw");
			if (!WRPrinterOK(bStatus)) {
				bStatus = false;
			}
		}
	
		bStatus = DoAction("Pem;0",2000,bStatus);

		CloseEvoPrinter();
	}
	return (bStatus);
}

bool CPrinter::ReadTrack(int trackNo, string &trackInfo)
{
	bool bStatus = true;
	string message;

	char command[20];
	memset(command,0,sizeof(command));
	if (OpenEvoPrinter()) {
		bStatus = DoAction("Pem;2",2000,bStatus);
		sprintf(command,"%s%d","Smr;",trackNo);
		bStatus = DoAction(command,6000,bStatus);
		
		if (!WRPrinterOK(bStatus)) {
			bStatus = false;
		}
		if(bStatus)
		{
			memset(command,0,sizeof(command));
			sprintf(command,"%s%d","Rmb;",trackNo);
			SetCommand(command);
			if (!WRPrinter(bStatus)) {
				bStatus = false;
			}
			trackInfo.append(GetLastAnswer());
		}
		bStatus = DoAction("Pem;0",2000,bStatus);

		CloseEvoPrinter();
	}
	return (bStatus);
}

char * CPrinter::GetDriverName()
{
	return(DriverName);
}

void CPrinter::SetDriverName(char * newDriverName)
{
	strcpy(DriverName,newDriverName);
}

bool CPrinter::Print(char* expiredDate, int parValue)
{
	bool bStatus = true;
	string message;

	char command[100];
	memset(command,0,sizeof(command));
	if (OpenEvoPrinter()) {       
        bStatus = DoAction("Wcb;k",15000,bStatus);  //clear bitmap
		bStatus = DoAction("Pwb;k",15000,bStatus);  //select monochrome bitmap
		bStatus = DoAction("Pwj;l",15000,bStatus);  //justify text to left
		sprintf(command,"Wt;%d;%d;%d;%d;%s",290,581,1,36,expiredDate);
		bStatus = DoAction(command,15000,bStatus); 
		memset(command,0,sizeof(command));
		sprintf(command,"Wt;%d;%d;%d;%d;%d",790,581,1,36,parValue);
		bStatus = DoAction(command,15000,bStatus); 
		bStatus = DoAction("Sp;k",15000,bStatus);
		CloseEvoPrinter();
	}
	return (bStatus);
}

bool CPrinter::PrintPassword(char* password)
{
	bool bStatus = true;
	string message;

	char command[100];
	memset(command,0,sizeof(command));
	if (OpenEvoPrinter()) {       
        bStatus = DoAction("Wcb;k",15000,bStatus);
		bStatus = DoAction("Pwb;k",15000,bStatus);
		bStatus = DoAction("Pwj;l",15000,bStatus);
		sprintf(command,"Wt;%d;%d;%d;%d;%s",200,200,1,36,password);  //TODOµ÷ÕûpasswordÎ»ÖÃ
		bStatus = DoAction(command,15000,bStatus); 
		bStatus = DoAction("Sp;k",15000,bStatus);
		CloseEvoPrinter();
	}
	return (bStatus);
}