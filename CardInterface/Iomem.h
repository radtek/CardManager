#ifndef IOMEN_H_
#define IOMEN_H_
#include "targetver.h"

class CIomem  
{
public:

	CIomem();
	~CIomem();
	LPSTR	GetLastAnswer();
	LPSTR	GetLastAnswerError();
	void	SetCde(const char* newCde);
	void	SetDwdCde(LPSTR newCde, int size);
	void	SetPrinterName(char *);
	char *	GetPrinterName();
	void	SetTout(DWORD value);
	DWORD	GetTout();


	HANDLE	OpenEvoPrinter();
	BOOL	CloseEvoPrinter();

	BOOL	WritePrinterCde();
	BOOL	ReadPrinterAnswer();
	BOOL	WRPrinter(BOOL bPrev = true);
	BOOL	WRPrinterOK(BOOL bPrev = true);
	BOOL	DownloadOK(BOOL bPrev = true);

private:
	LPSTR	lpstrAnswer;
	LPSTR	lpstrLastError;
	LPSTR	lpstrDwdCde;
	LPSTR	lpstrCde;
	LPSTR	lpstrPrinterName;

	DWORD	dwCdeLen;
	DWORD	dwBytesRead;
	
	HANDLE	hPrinter;	
	
};

#endif // IOMEN_H_
