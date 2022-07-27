// ClientDlg.h : header file
//

#pragma once

#define TIMER_ID_READ_FROM_SERVER 1000
#define TIMER_ID_AUTO_STOP 2001
#define TIMER_ID_AUTO_START 2002


#include <ZSensorInteface/inc/IIntelliSwingProtocolAdapter.h>
#include "afxcmn.h"
#include "afxwin.h"
#include "afxmt.h"

#define INIFILENAME "ZSensorDiag.ini"

struct INIField
{
	int bWriteFile;
	int bAutoConnect;
	int IpAddressField[4];
	int nPortNumber;

};

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
	CCriticalSection m_criticalExe;
	INIField m_config;
	CString m_strIniPath;
	CString m_strCSVPath;

	CIPAddressCtrl m_ctrlServerIpAddress;
	CButton m_ctrlButtonAutoConnect;

	UINT m_nPortNumber;
	CListBox m_ctrlListBallInfo;
	CListBox m_ctrlListClubInfo;
	CStatic m_ctrlTxtStatus;
	CButton m_ctrlChkCSVWrite;
	CButton m_ctrlChkAutoStop;


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
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonOpenWorkingFolder();
	afx_msg void OnBnClickedCheckAutoConnect();
	afx_msg void OnBnClickedCheckSaveShotInfoToCsv();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	virtual void OnReady(ZSensor::Ready &ready);
	virtual void OnNotReady(ZSensor::NotReady &notReady);
	virtual void OnShortTriggered(ZSensor::ShortTriggered &shotTriggered);
	virtual void OnBallFlightInfo(ZSensor::BallFlightInfo &ballFlightInfo);
	virtual void OnClubPathInfo(ZSensor::ClubPathInfo &clubInfo);

	void ConnectServer();
	void StartSensor();
	void StopSensor();
	void SetCSVPath();
	void SetWorkingDirectory(CString Buffer);
	void UpdateINI(CString iniPath, INIField &out);
	void ReadINI(CString iniPath, INIField &read);
	void EnableButtons(BOOL bEnable);
	CString GetExePath(CString &strFilePath);


};
