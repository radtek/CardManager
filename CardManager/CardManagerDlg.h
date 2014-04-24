
// CardManagerDlg.h : 头文件
//

#pragma once


// CCardManagerDlg 对话框
class CCardManagerDlg : public CDialogEx
{
// 构造
public:
	CCardManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CARDMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//重载OnOk事件，去掉回车关闭窗口功能
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
