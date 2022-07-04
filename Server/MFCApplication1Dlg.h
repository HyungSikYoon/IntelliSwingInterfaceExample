
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
	int m_nShotID = 0;

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedButtonSendReady();
	afx_msg void OnBnClickedButtonSendNotReady();
	afx_msg void OnBnClickedButtonSendTriggered();
	afx_msg void OnBnClickedButtonSendBallInfo();
	afx_msg void OnBnClickedButtonSendClubInfo();
	afx_msg void OnBnClickedButtonSendEnd();
	afx_msg void OnBnClickedButtonSendShot();
	afx_msg void OnDestroy();

	CButton m_ctrlButtonStart;
	CButton m_ctrlButtonStop;
	CButton m_ctrlButtonReady;
	CButton m_ctrlButtonNotReady;
	CButton m_ctrlButtonTriggered;
	CButton m_ctrlButtonBallFlight;
	CButton m_ctrlButtonClubPath;
	CButton m_ctrlButtonSendEnd;
	CButton m_ctrlButtonSendShot;


	void OnBeginServerToClient();
	void OnEndServerToClient();

	CButton m_ctrlCheckIsOnTee;
	CComboBox m_ctrlComboGroundType;
	afx_msg void OnSelchangeComboGround();
};
