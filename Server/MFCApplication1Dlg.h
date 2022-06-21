
// MFCApplication1Dlg.h : header file
//

#pragma once

#include "ZIntelliSwingServer.h"

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private :
	ZIntelliSwingServer *m_pServer = nullptr;

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();

	CButton m_ctrlButtonStart;
	CButton m_ctrlButtonStop;
	CButton m_ctrlButtonReady;
	CButton m_ctrlButtonNotReady;
	CButton m_ctrlButtonTriggered;
	CButton m_ctrlButtonBallFlight;
	CButton m_ctrlButtonClubPath;
	CButton m_ctrlButtonSendEnd;

	afx_msg void OnDestroy();

	void OnBeginServerToClient();

	void OnEndServerToClient();
	afx_msg void OnBnClickedButtonSendEnd();
};
