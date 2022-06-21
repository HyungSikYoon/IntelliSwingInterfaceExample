
// ClientDlg.h : header file
//

#pragma once
#include <grpcpp/grpcpp.h>
#include "../ProtoBuf/IntelliSwingInterface.grpc.pb.h"


// CClientDlg dialog
class CClientDlg : public CDialogEx
{
// Construction
public:
	CClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private :
	std::unique_ptr<IntelliSwing::IntelliSwingProtocol::Stub> m_uptrStub;

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInitialize();
	afx_msg void OnBnClickedButtonRelease();
	afx_msg void OnBnClickedButtonReboot();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonGetClubImg();
	afx_msg void OnBnClickedButtonGetBallImg();
	afx_msg void OnBnClickedButtonGetDeviceInfo();
	afx_msg void OnBnClickedButtonDeviceStatus();
	afx_msg void OnBnClickedButtonGetLog();
};
