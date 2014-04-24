
// CardManagerDlg.h : ͷ�ļ�
//

#pragma once


// CCardManagerDlg �Ի���
class CCardManagerDlg : public CDialogEx
{
// ����
public:
	CCardManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CARDMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//����OnOk�¼���ȥ���س��رմ��ڹ���
	void OnOK();
public:
//	afx_msg void OnBnClickedButtonExecute();
	afx_msg void OnExecuteCommand();
private:
	void ShowPrinters();
public:
	afx_msg void OnReadTracks();
	afx_msg void OnWriteTracks();
	afx_msg void OnEjectCard();
	afx_msg void OnCheckLow();
	afx_msg void OnCheckHigh();
	afx_msg void OnPrintCard();
	afx_msg void OnResetNumber();
};
