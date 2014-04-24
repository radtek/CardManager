// Iomem.cpp: implementation of the CIomem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Iomem.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

//Declaration of dll function
extern "C" {
_declspec(dllimport)	HANDLE	FAR PASCAL OpenPebble(char *);
_declspec(dllimport)	BOOL	FAR PASCAL ClosePebble(HANDLE);
_declspec(dllimport)	BOOL	FAR PASCAL ReadPebble(HANDLE, LPSTR, DWORD, LPDWORD);
_declspec(dllimport)	BOOL	FAR PASCAL WritePebble(HANDLE, LPSTR, DWORD);      
_declspec(dllimport)	BOOL	FAR PASCAL GetIomemVersion(LPSTR); 
_declspec(dllimport)	DWORD	WaitBusy;          
_declspec(dllimport)	DWORD	FAR PASCAL GetTimeout(void); 
_declspec(dllimport)	BOOL	FAR PASCAL SetTimeout(DWORD); 
_declspec(dllimport)	BOOL	FAR PASCAL GetStatusEvo(HANDLE hPebble, int *nBytesRead); 
}

//////////////////////////////////////////////////////////////////////
// Constructor/Destructor
//////////////////////////////////////////////////////////////////////

CIomem::CIomem()
{
	//memory allocation for pointer type properties
	lpstrAnswer =  new char[1024];
	lpstrLastError =  new char[1024];

	memset(lpstrAnswer,0x00,1024);
	memset(lpstrLastError,0x00,1024);

	lpstrCde = new char[1024];
	lpstrPrinterName = new char[1024];
	lpstrDwdCde = NULL; 
}

CIomem::~CIomem()
{
	if(lpstrAnswer) {
		delete(lpstrAnswer);
	}
	if(lpstrLastError) {
		delete(lpstrLastError);
	}
	if(lpstrDwdCde) {
		delete(lpstrDwdCde);
	}
	if(lpstrPrinterName) {
		delete(lpstrPrinterName);
	}
	if(lpstrCde) {
		delete(lpstrCde);
	}
}

/// <summary>
/// Read last answer from printer
/// </summary>
/// <returns> a pointer to the string buffer</returns>
LPSTR CIomem::GetLastAnswer()
{
	return(lpstrAnswer);
}
/// <summary>
///  read the answer error returned by the printer
/// </summary>
/// <returns>a pointer to the string buffer</returns>
LPSTR CIomem::GetLastAnswerError()
{
	return(lpstrLastError);
}
/// <summary>
/// To set the escape command to send to the printer
/// </summary>
/// <param name="newCde">escape command</param>
void CIomem::SetCde(const char* newCde)
{
	dwCdeLen = strlen(newCde);
	strcpy(lpstrCde, newCde);	
}
/// <summary>
/// To set the download escape command.
/// </summary>
/// <param name="newCde">downloading escape command</param>
/// <param name="size">size of the buffer that contains escape command.</param>
/// <returns></returns>
void CIomem::SetDwdCde(LPSTR newCde, int size)
{
	dwCdeLen = size;
	lpstrDwdCde = newCde;
}
/// <summary>
/// To set the printer/driver name to open for communication;
/// </summary>
/// <param name="newName">string that contains driver name.</param>
/// <returns></returns>
void CIomem::SetPrinterName(char * newName)
{
	strcpy(lpstrPrinterName,newName);
}
/// <summary>
/// It return the printer name we are using.
/// </summary>
/// <returns>string that contains the information</returns>
char * CIomem::GetPrinterName()
{
	return(lpstrPrinterName);
}
/// <summary>
/// To set the timeout value
/// </summary>
/// <param name="value">value defined in milliseconds</param>
void CIomem::SetTout(DWORD value)
{
	SetTimeout(value);
}
/// <summary>
/// To get the currect timeout value
/// </summary>
/// <returns>Timeout value in milliseconds</returns>
DWORD CIomem::GetTout()
{
	return(GetTimeout());
}
/// <summary>
/// To open and grant access to the local port attached to the printer driver
/// </summary>
/// <returns>Handle on the port</returns>
HANDLE CIomem::OpenEvoPrinter()
{
	hPrinter=OpenPebble(lpstrPrinterName);
	return(hPrinter);
}
/// <summary>
/// To close and free access to the local port.
/// </summary>
/// <returns>True if correct</returns>
/// <returns>False otherwise</returns>
BOOL CIomem::CloseEvoPrinter()
{
	BOOL bClose  = false;
	bClose = ClosePebble(hPrinter);
	return(bClose);
}
/// <summary>
/// To write a short command to the printer.
/// </summary>
/// <returns>True: if it correct</returns>
/// <returns>False otherwise</returns>
BOOL CIomem::WritePrinterCde()
{
	BOOL bWrite = false;

	if(lpstrCde) {
		bWrite = WritePebble(hPrinter,lpstrCde,dwCdeLen);
	}
	return(bWrite);
}
/// <summary>
/// To read answer from the printer
/// </summary>
/// <returns>True: if answer available</returns>
/// <returns>False otherwise</returns>
BOOL CIomem::ReadPrinterAnswer()
{
	BOOL bRead = false;

	bRead = ReadPebble(hPrinter,lpstrAnswer,1024,&(dwBytesRead));
	if(bRead) {
		if (strncmp(lpstrAnswer,"OK",2)) {
			strcpy(lpstrLastError,lpstrAnswer);
		}
	}

	return(bRead);
}
/// <summary>
/// Sequence to synchronize writing and reading.
/// </summary>
/// <returns>True: if writing and readin are correct</returns>
/// <returns>False otherwise</returns>
BOOL CIomem::WRPrinter(BOOL bPrev)
{
	BOOL bWR=false;

	if( bPrev && lpstrCde) {
		bWR = WritePebble(hPrinter,lpstrCde,dwCdeLen);
		dwBytesRead=0;
		if(bWR) {
			bWR = ReadPebble(hPrinter,lpstrAnswer,1024,&(dwBytesRead));
			if (!bWR) {
				strcpy(lpstrAnswer,"Fails to Read on Port, Check connection or printer ready !!!!");
				strcpy(lpstrLastError,lpstrAnswer);
			}
			else {
				if (strncmp(lpstrAnswer,"OK",2)) {
					strcpy(lpstrLastError,lpstrAnswer);
				}
			}
		}
		else  {
			strcpy(lpstrAnswer,"Fails to Write on Port, Check connection or printer ready !!!!");
			strcpy(lpstrLastError,lpstrAnswer);
		}
	}
	return(bWR);
}

/// <summary>
/// Sequence to synchronize writing and reading and checks taht answer is "OK"
/// </summary>
/// <returns>True: if writing and reading are correct and the answer is "OK"</returns>
/// <returns>False otherwise</returns>
BOOL CIomem::WRPrinterOK(BOOL bPrev)
{
	BOOL	bWROK = false;
	int		iPrtstatus=0;

	if( bPrev) {
		if(lpstrCde) {

			GetStatusEvo(hPrinter,&iPrtstatus);
			if ((iPrtstatus & 0xFF) == 0x18) { //READY
				bWROK = WritePebble(hPrinter,lpstrCde,dwCdeLen);
			}
		
			dwBytesRead=0;
			if(bWROK) {
				bWROK = ReadPebble(hPrinter,lpstrAnswer,1024,&(dwBytesRead));
				if(bWROK) {
					if (!strncmp(lpstrAnswer,"OK",2)) {
						bWROK = true;
					}
					else {
						bWROK = false;
						strcpy(lpstrLastError,lpstrAnswer);
					}
				}
			}
		}
	}
	return(bWROK);
}

/// <summary>
/// Sequence to synchronize writing and reading and checks taht answer is "OK"
/// Used for huge escape command especially downloading command
/// </summary>
/// <returns>True: if writing and reading are correct and the answer is "OK"</returns>
/// <returns>False otherwise</returns>
BOOL CIomem::DownloadOK(BOOL bPrev)
{
	BOOL	bWROK = false;
	int		iPrtstatus=0;

	if( bPrev) {
		if(lpstrDwdCde) {
			GetStatusEvo(hPrinter,&iPrtstatus);
			if ((iPrtstatus & 0xFF) == 0x18) { //READY
				bWROK = WritePebble(hPrinter,lpstrDwdCde,dwCdeLen);
			}

			dwBytesRead=0;
			if(bWROK) {
				bWROK = ReadPebble(hPrinter,lpstrAnswer,1024,&(dwBytesRead));
				if (bWROK) {
					if (!strncmp(lpstrAnswer,"OK",2)) {
						bWROK = true;
					}
					else {
						bWROK = false;
						strcpy(lpstrLastError,lpstrAnswer);
					}
				}
			}
		}
	}

	lpstrDwdCde = NULL;
	dwCdeLen = 0;


	return(bWROK);
}
