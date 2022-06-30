// ClientDlg.h : header file
//

#pragma once

#define TIMER_ID_READ_FROM_SERVER 1000
#include <ZSensorInteface/inc/IIntelliSwingProtocolAdapter.h>

// CClientDlg dialog
class CClientDlg : public CDialog, public ZSensor::iSensorRunnginEventHandler
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
private :
	ZSensor::IIntelliSwingProtocolAdapter *m_pIntelliSwingProtocolAdapter;
	CWinThread*     m_pEventThread;

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGetDeviceInfo();
	afx_msg void OnBnClickedButtonInitialize();
	afx_msg void OnBnClickedButtonRelease();
	afx_msg void OnBnClickedButtonReboot();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonGetClubImg();
	afx_msg void OnBnClickedButtonGetBallImg();
	afx_msg void OnBnClickedButtonDeviceStatus();
	afx_msg void OnBnClickedButtonGetLog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	virtual void OnReady(ZSensor::Ready &ready);
	virtual void OnNotReady(ZSensor::NotReady &notReady);
	virtual void OnShortTriggered(ZSensor::ShortTriggered &shotTriggered);
	virtual void OnBallFlightInfo(ZSensor::BallFlightInfo &ballFlightInfo);
	virtual void OnClubPathInfo(ZSensor::ClubPathInfo &clubInfo);

	void StartSensor();
	void StopSensor();
};
