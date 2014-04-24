
// CardManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CardManager.h"
#include "CardManagerDlg.h"
#include "afxdialogex.h"
#include "../CardInterface/CardInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCardManagerDlg �Ի���




CCardManagerDlg::CCardManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCardManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCardManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, &CCardManagerDlg::OnBnClickedButtonExecute)
ON_BN_CLICKED(IDC_BUTTON_EXECUTE, &CCardManagerDlg::OnExecuteCommand)
ON_BN_CLICKED(IDC_BUTTON_READ_TRACK, &CCardManagerDlg::OnReadTracks)
ON_BN_CLICKED(IDC_BUTTON_WRITE_TRACK, &CCardManagerDlg::OnWriteTracks)
ON_BN_CLICKED(IDC_BUTTON_EJECTION, &CCardManagerDlg::OnEjectCard)
ON_BN_CLICKED(IDC_RADIO_LOW, &CCardManagerDlg::OnCheckLow)
ON_BN_CLICKED(IDC_RADIO_HIGH, &CCardManagerDlg::OnCheckHigh)
ON_BN_CLICKED(IDC_BUTTON_PRINT, &CCardManagerDlg::OnPrintCard)
ON_BN_CLICKED(IDC_BUTTON_RESET, &CCardManagerDlg::OnResetNumber)
END_MESSAGE_MAP()


// CCardManagerDlg ��Ϣ�������

BOOL CCardManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//change the frame size manually
	SetWindowPos(NULL,0,0,400,320,SWP_NOMOVE);

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//����ĳ�ʼ������
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_HIGH);        //Coercivity Ĭ��ѡ��High
	radio->SetCheck(1);

	if(Card_Init())
	{
		AfxMessageBox(_T("��ʼ����ӡ��ʧ��"),MB_OK|MB_ICONWARNING   );
	} else 
	{
		ShowPrinters();
	}	

	Card_SetCoercivity('h');
	((CEdit*)GetDlgItem(IDC_EDIT_NUMBER))->SetWindowTextA("1");
	((CEdit*)GetDlgItem(IDC_EDIT_PRINTED_NUMBER))->SetWindowTextA("0");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCardManagerDlg::ShowPrinters()
{
	int printerCount = Card_GetPrinterCount();
	if(printerCount>0)
	{
		CComboBox* printerSelect=(CComboBox*)GetDlgItem(IDC_COMBO_PRINTERS); 
		char** printers = new char*[printerCount];
		for (int i = 0; i < printerCount; ++i)
		{
			printers[i] = new char[100];
			memset(printers[i],0x00,100);
		}

		Card_GetPrinters(printers,printerCount);

		for (int i = 0; i < printerCount; ++i)
        {
          printerSelect->AddString(printers[i]);
		  delete[] printers[i];
		}
		delete [] printers;

		printerSelect->SetCurSel(0);
	} 
}

void CCardManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCardManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCardManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCardManagerDlg::OnExecuteCommand()
{
	//�����������Ƭ��ӡ��ִ��
	CEdit* commandEdit=(CEdit*)GetDlgItem(IDC_EDIT_COMMAND); 
	CEdit* answerEdit=(CEdit*)GetDlgItem(IDC_EDIT_RESPONSE);
	char command[200];
	char answer[200];
	memset(command,0x00,sizeof(command));
	memset(answer,0x00,sizeof(answer));
	commandEdit->GetWindowTextA(command,100);
	Card_ExecuteCommand(command,answer);
	answerEdit->SetWindowTextA(answer);
}


void CCardManagerDlg::OnReadTracks()
{
	char trackInfo[20];
	char error[100];
	memset(trackInfo,0,sizeof(trackInfo));
	memset(error,0,sizeof(error));
	if(IsDlgButtonChecked(IDC_TRACK2_CHECK)){
		if(Card_ReadTrack(2,trackInfo)){
			Card_GetLastError(error);
			((CEdit*)GetDlgItem(IDC_TRACK2_READ))->SetWindowTextA(error);
		} else {
			((CEdit*)GetDlgItem(IDC_TRACK2_READ))->SetWindowTextA(trackInfo);
		}
	}
}


void CCardManagerDlg::OnWriteTracks()
{	
	char trackInfo[20];
	char error[100];
	memset(trackInfo,0,sizeof(trackInfo));
	memset(error,0,sizeof(error));
	
	((CEdit*)GetDlgItem(IDC_TRACK2_WRITE))->GetWindowTextA(trackInfo,25);

	if(IsDlgButtonChecked(IDC_TRACK2_CHECK)){
		if(Card_WriteTrack(2,trackInfo)){
			Card_GetLastError(error);
			((CEdit*)GetDlgItem(IDC_TRACK2_READ))->SetWindowTextA(error);
		} else {
			((CEdit*)GetDlgItem(IDC_TRACK2_READ))->SetWindowTextA("OK");
		}
	}
}


void CCardManagerDlg::OnEjectCard()
{
	char error[100];
	memset(error,0,sizeof(error));
	if(Card_EjectCard(NULL))
	{
	    Card_GetLastError(error);
		AfxMessageBox(_T(error),MB_OK|MB_ICONWARNING   );
	}
}


void CCardManagerDlg::OnCheckLow()
{
	char error[100];
	memset(error,0,sizeof(error));
	if(Card_SetCoercivity('l'))
	{
		Card_GetLastError(error);
		AfxMessageBox(_T(error),MB_OK|MB_ICONWARNING   );
	}
}


void CCardManagerDlg::OnCheckHigh()
{
	char error[100];
	memset(error,0,sizeof(error));
	if(Card_SetCoercivity('h'))
	{
		Card_GetLastError(error);
		AfxMessageBox(_T(error),MB_OK|MB_ICONWARNING   );
	}
}

void CCardManagerDlg::OnOK()
{
	if(GetDlgItem(IDC_EDIT_EXPIRED_DATE)==GetFocus() || GetDlgItem(IDC_EDIT_PAR_VALUE)==GetFocus())
	{
		OnPrintCard();
		return;
	}
}


void CCardManagerDlg::OnPrintCard()
{
	CEdit* expiredDateEdit=(CEdit*)GetDlgItem(IDC_EDIT_EXPIRED_DATE);
	CEdit* parValueEdit=(CEdit*)GetDlgItem(IDC_EDIT_PAR_VALUE);
	CEdit* numberEdit=(CEdit*)GetDlgItem(IDC_EDIT_NUMBER);
			
	char expiredDate[200];
	char parValue[10];
	char number[10];
	char error[100];
	int total;
	memset(error,0x00,sizeof(error));
	memset(expiredDate,0x00,sizeof(expiredDate));
	memset(parValue,0x00,sizeof(parValue));
	memset(number,0x00,sizeof(number));

	expiredDateEdit->GetWindowTextA(expiredDate,200);
	parValueEdit->GetWindowTextA(parValue,10);
	numberEdit->GetWindowTextA(number,10);

	if(strlen(number)==0)
	{
		//no card number, we use the default value 1
		total = 1;
	} else 
	{
		total = atoi(number);
	}

	if(total==0)
	{
		//the input number is not correct
		AfxMessageBox(_T("��������ȷ�Ŀ�Ƭ������ֵ����Ϊ����"),MB_OK|MB_ICONWARNING   );
		return;
	} else if(total>200)
	{
		AfxMessageBox(_T("��Ƭ��������С��200"),MB_OK|MB_ICONWARNING   );
		return;
	}

	if(total>1)
	{
		char info[200];
		memset(info,0x00,sizeof(info));
		sprintf(info,"ȷ��Ҫ��ӡ %d �ſ�Ƭ��",total);
		if(AfxMessageBox(_T(info),MB_OKCANCEL|MB_ICONQUESTION)==IDCANCEL)
		{
			return;
		}
	}

	int i;
	for(i=0;i<total;i++)
	{
		if(Card_Print(expiredDate,atol(parValue)))
		{
			Card_GetLastError(error);
			AfxMessageBox(_T(error),MB_OK|MB_ICONWARNING   );
			break;
		}
	}
	CEdit* printedEdit=(CEdit*)GetDlgItem(IDC_EDIT_PRINTED_NUMBER);
	char printedNumber[10];
	memset(printedNumber,0x00,sizeof(printedNumber));
	printedEdit->GetWindowTextA(printedNumber,10);
	
	int tmp = atoi(printedNumber)+i;
	memset(printedNumber,0x00,sizeof(printedNumber));
	sprintf(printedNumber,"%d",tmp);
	printedEdit->SetWindowTextA(printedNumber);
}


void CCardManagerDlg::OnResetNumber()
{
	((CEdit*)GetDlgItem(IDC_EDIT_PRINTED_NUMBER))->SetWindowTextA("0");
}
