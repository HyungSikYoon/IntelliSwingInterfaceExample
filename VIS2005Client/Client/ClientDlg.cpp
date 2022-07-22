// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#include <plog/Log.h>

#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>


#include <plog/Log.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//const char *g_serverAddress = "100.100.100.200";
//const int g_nPortnumber = 50051;

#pragma comment(lib, "ZSensorInterfaceDll.lib")

// CClientDlg dialog
class LogHelper
{
	const size_t            m_line;
	const char* const       m_func;

public:
	LogHelper(const char* func, size_t line) : m_func(func), m_line(line)
	{
		IF_PLOG_(PLOG_DEFAULT_INSTANCE_ID, plog::warning) (*plog::get<PLOG_DEFAULT_INSTANCE_ID>()) += plog::Record(plog::warning, m_func, m_line, "", "", PLOG_DEFAULT_INSTANCE_ID).ref()<< " --> Start" ;
		
	}
	~LogHelper()
	{
		IF_PLOG_(PLOG_DEFAULT_INSTANCE_ID, plog::warning) (*plog::get<PLOG_DEFAULT_INSTANCE_ID>()) += plog::Record(plog::warning, m_func, m_line, "", "", PLOG_DEFAULT_INSTANCE_ID).ref()<< " <-- End" ;

	}

};


// CClientApp construction
plog::ColorConsoleAppender<plog::TxtFormatter> g_consoleAppender;
//plog::RollingFileAppender<plog::TxtFormatter> rfileAppender;
void InitializeLog(BOOL bWriteFile)
{
	if(bWriteFile)
	{
		CHAR logFileName[60] = {};
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		sprintf_s(logFileName,
			"log%04d%02d%02d_%u%02u%02u.log",
			systemTime.wYear,
			systemTime.wMonth,
			systemTime.wDay,
			systemTime.wHour,
			systemTime.wMinute,
			systemTime.wSecond);


		static plog::RollingFileAppender<plog::TxtFormatter> rfileAppender(logFileName, 100000,10);

		plog::init(plog::debug, &rfileAppender); // Initialize logging to the file.
	    
		plog::get()->addAppender(&g_consoleAppender); // Also add logging to the console.
		LOGW<<"Log Initialized with file "<< logFileName;
	}
	else
	{
		plog::init(plog::debug, &g_consoleAppender); // Initialize logging to the file.
	    
		LOGW<<"Log Initialized";
	}
	
}


#define LOG_BEGIN_END LogHelper helper(__FUNCTION__, __LINE__)


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClientDlg dialog




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
	, m_strIniPath(_T(INIFILENAME))
	, m_nPortNumber(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_config.bAutoConnect = 0;
	m_config.bWriteFile = 0;
	m_config.IpAddressField[0] = 127;
	m_config.IpAddressField[1] = 0;
	m_config.IpAddressField[2] = 0;
	m_config.IpAddressField[3] = 1;

	m_config.nPortNumber = 50051;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_ctrlServerIpAddress);
	DDX_Control(pDX, IDC_CHECK_AUTO_CONNECT, m_ctrlButtonAutoConnect);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPortNumber);
	DDV_MinMaxUInt(pDX, m_nPortNumber, 0, 65535);
	DDX_Control(pDX, IDC_LIST_BALL_INFO, m_ctrlListBallInfo);
	DDX_Control(pDX, IDC_LIST_CLUB_INFO, m_ctrlListClubInfo);
	DDX_Control(pDX, IDC_TXT_STATUS, m_ctrlTxtStatus);
	DDX_Control(pDX, IDC_CHECK_SAVE_SHOT_INFO_TO_CSV, m_ctrlChkCSVWrite);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_GET_DEVICE_INFO, &CClientDlg::OnBnClickedButtonGetDeviceInfo)
	ON_BN_CLICKED(IDC_BUTTON_INITIALIZE, &CClientDlg::OnBnClickedButtonInitialize)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, &CClientDlg::OnBnClickedButtonRelease)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CClientDlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_START, &CClientDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CClientDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_GET_CLUB_IMG, &CClientDlg::OnBnClickedButtonGetClubImg)
	ON_BN_CLICKED(IDC_BUTTON_GET_BALL_IMG, &CClientDlg::OnBnClickedButtonGetBallImg)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_STATUS, &CClientDlg::OnBnClickedButtonDeviceStatus)
	ON_BN_CLICKED(IDC_BUTTON_GET_LOG, &CClientDlg::OnBnClickedButtonGetLog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CClientDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_WORKING_FOLDER, &CClientDlg::OnBnClickedButtonOpenWorkingFolder)
	ON_BN_CLICKED(IDC_CHECK_AUTO_CONNECT, &CClientDlg::OnBnClickedCheckAutoConnect)
	ON_BN_CLICKED(IDC_CHECK_SAVE_SHOT_INFO_TO_CSV, &CClientDlg::OnBnClickedCheckSaveShotInfoToCsv)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	LOG_BEGIN_END;
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// extra initialization here
	CString strExePath;
	GetExePath(strExePath);
	m_strIniPath =strExePath+_T("\\") + _T(INIFILENAME) ;

	ReadINI(m_strIniPath, m_config);

	InitializeLog(m_config.bWriteFile);
	m_ctrlServerIpAddress.SetAddress(m_config.IpAddressField[0],m_config.IpAddressField[1], m_config.IpAddressField[2], m_config.IpAddressField[3]); 

	m_nPortNumber = m_config.nPortNumber;

	LOGW<<"OnInit Dialog";
	LOGW<<"Revision "<<m_pIntelliSwingProtocolAdapter->GetRevision();
	LOGW<<"Updatedate "<<m_pIntelliSwingProtocolAdapter->GetUpdateDate();
	
	
	EnableButtons(FALSE);


	m_pIntelliSwingProtocolAdapter = new ZSensor::IIntelliSwingProtocolAdapter(this);

	if(m_ctrlChkCSVWrite.GetCheck())
	{
		SetCSVPath();
	}

	if(m_config.bAutoConnect)
		m_ctrlButtonAutoConnect.SetCheck(TRUE);

	m_pEventThread = NULL;

	UpdateData(FALSE);

	if(m_config.bAutoConnect)
		ConnectServer();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnDestroy()
{
	__super::OnDestroy();

	if(m_pEventThread != NULL)
	{
		StopSensor();
		WaitForSingleObject(m_pEventThread->m_hThread,2000);
	}
	
	UpdateINI(m_strIniPath, m_config);
	// TODO: Add your message handler code here
	delete m_pIntelliSwingProtocolAdapter;
	m_pIntelliSwingProtocolAdapter = NULL;
}


void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CClientDlg::OnBnClickedButtonInitialize()
{
	// TODO: Add your control notification handler code here

	ZSensor::InitializeMsg initializeMsg;
	ZSensor::ReturnMsg returnMsg;
	if(m_pIntelliSwingProtocolAdapter)
	{
		if(m_pIntelliSwingProtocolAdapter->Initialize(initializeMsg, returnMsg) != ZSensor::Z_OK)
		{
			LOGW<<"return result Error "	<< m_pIntelliSwingProtocolAdapter->GetLastErrorMessage();
		}
		LOGW<<"return result "<<returnMsg.isOK;
	}
}

void CClientDlg::OnBnClickedButtonRelease()
{
	LOG_BEGIN_END;
	ZSensor::ReleaseMsg releaseMsg;
	ZSensor::ReturnMsg returnMsg;
	if(m_pIntelliSwingProtocolAdapter)
	{
		
		m_pIntelliSwingProtocolAdapter->Release(releaseMsg, returnMsg);
		LOGW<<"return result "<<returnMsg.isOK;
	}

}

void CClientDlg::OnBnClickedButtonReboot()
{
	LOG_BEGIN_END;
	ZSensor::ReturnMsg returnMsg;
	if(m_pIntelliSwingProtocolAdapter)
	{
		m_pIntelliSwingProtocolAdapter->Reboot(returnMsg);
		LOGW<<"return result "<<returnMsg.isOK;
	}
}

UINT MyThread(LPVOID lpParam)
{
	CClientDlg* pClass = (CClientDlg*) lpParam;
	pClass->StartSensor();
	return 0L;
}

void CClientDlg::StartSensor()
{

	LOG_BEGIN_END;
	ZSensor::StartMsg startMsg;
	ZSensor::ReturnMsg returnMsg;
	if(m_pIntelliSwingProtocolAdapter)
	{
		
		m_pIntelliSwingProtocolAdapter->Start(startMsg);
		LOGW<<"Sensing End ";
	}

	m_pEventThread = NULL;
}
void CClientDlg::StopSensor()
{
	LOG_BEGIN_END;
	ZSensor::ReturnMsg returnMsg;
	if(m_pIntelliSwingProtocolAdapter)
	{
		m_pIntelliSwingProtocolAdapter->Stop(returnMsg);
		LOGW<<"return result "<<returnMsg.isOK;
	}
}
 

void CClientDlg::OnBnClickedButtonStart()
{
	LOG_BEGIN_END;

	m_pEventThread = AfxBeginThread( MyThread, this);

	if(m_pEventThread == NULL)
		LOGW<<"Fail to create camera thread!!";

}

void CClientDlg::OnBnClickedButtonStop()
{
	LOG_BEGIN_END;
	StopSensor();
}

void CClientDlg::OnBnClickedButtonGetClubImg()
{
	LOG_BEGIN_END;

	ZSensor::ShotImageRequest imageRequest;
	imageRequest.shotId = 100;

	ZSensor::ImageData imageData;
	if(m_pIntelliSwingProtocolAdapter)
	{
		m_pIntelliSwingProtocolAdapter->GetClubImage(imageRequest, imageData);
		
		LOGW<<"return  image count = "<< imageData.nImageArrayCount;
		
		m_pIntelliSwingProtocolAdapter->ClearImageData(imageData);
	}
}

void CClientDlg::OnBnClickedButtonGetBallImg()
{
	LOG_BEGIN_END;

	ZSensor::ShotImageRequest imageRequest;
	imageRequest.shotId = 100;

	ZSensor::ImageData imageData;
	if(m_pIntelliSwingProtocolAdapter)
	{
		m_pIntelliSwingProtocolAdapter->GetBallImage(imageRequest, imageData);
		
		LOGW<<"return  image count = "<< imageData.nImageArrayCount;

		m_pIntelliSwingProtocolAdapter->ClearImageData(imageData);
	}
}

void CClientDlg::OnBnClickedButtonDeviceStatus()
{
	LOG_BEGIN_END;
	ZSensor::DeviceStatus deviceStatus;
	if(m_pIntelliSwingProtocolAdapter)
	{
		m_pIntelliSwingProtocolAdapter->GetDeviceStatus(deviceStatus);
		LOGW<<"return result "<<deviceStatus.systemState.isOK;
	}
}

void CClientDlg::OnBnClickedButtonGetDeviceInfo()
{
	LOG_BEGIN_END;
	ZSensor::DeviceInfo deviceInfo;
	if(m_pIntelliSwingProtocolAdapter)
	{
		m_pIntelliSwingProtocolAdapter->GetDeviceInfo(deviceInfo);
		LOGW<<"return result "<<deviceInfo.deviceVer;
	}
}

void CClientDlg::OnBnClickedButtonGetLog()
{
	LOG_BEGIN_END;
}

void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}

void CClientDlg::OnReady(ZSensor::Ready &ready)
{
	LOG_BEGIN_END;
	m_ctrlTxtStatus.SetWindowTextW(_T("Status : Ready"));
}
void CClientDlg::OnNotReady(ZSensor::NotReady &notReady)
{
	LOG_BEGIN_END;
	CString strStatus;
	strStatus.Format(_T("Status : Not Ready %d"), (int)notReady.notReadyCause);
	m_ctrlTxtStatus.SetWindowTextW(strStatus);
}
void CClientDlg::OnShortTriggered(ZSensor::ShortTriggered &shotTriggered)
{
	LOG_BEGIN_END;
	LOGW<<"ShortTriggered  "<<shotTriggered.shotId<<", timestamp "<<shotTriggered.timestamp;

	CString strStatus;
	strStatus.Format(_T("Status : Shot Triggered %d"), shotTriggered.shotId);

	m_ctrlTxtStatus.SetWindowTextW(strStatus);

	m_ctrlListBallInfo.ResetContent();
	m_ctrlListClubInfo.ResetContent();
}
void CClientDlg::OnBallFlightInfo(ZSensor::BallFlightInfo &ballFlightInfo)
{
	LOG_BEGIN_END;
	LOGW<<"  Shot ID "<<ballFlightInfo.shotId;
	LOGW<<"  Ball Speed "<<ballFlightInfo.ballSpeed<<", incidence "<<ballFlightInfo.Incidence<<", dir : " <<ballFlightInfo.direction;
	LOGW<<"  Ball BS "<<ballFlightInfo.backSpin<<", SS "<<ballFlightInfo.sideSpin;
	m_ctrlTxtStatus.SetWindowTextW(_T("Status : RECV Ball Info"));

	CString shotID;
	CString ballSpeed;
	CString ballDirection;
	CString spinInfo;

	shotID.Format(_T("Shot ID %04d"), ballFlightInfo.shotId);
	ballSpeed.Format(_T("Speed  %.2f"), ballFlightInfo.ballSpeed);
	ballDirection.Format(_T("incidence: %.1f, dir: %.1f"), ballFlightInfo.Incidence, ballFlightInfo.direction);
	spinInfo.Format(_T("SideSpin: %.1f, BackSPin: %.1f"), ballFlightInfo.sideSpin, ballFlightInfo.backSpin);

	m_ctrlListBallInfo.AddString(shotID);
	m_ctrlListBallInfo.AddString(ballSpeed);
	m_ctrlListBallInfo.AddString(ballDirection);
	m_ctrlListBallInfo.AddString(spinInfo);

	if(m_ctrlChkCSVWrite.GetCheck())
	{

		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);

		FILE *fp = _tfopen(m_strCSVPath, _T("at"));
		if(fp)
		{
			fprintf(fp, "%02d-%02d, %u:%02u:%02u,", systemTime.wMonth,systemTime.wDay,systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
			fprintf(fp, "%04d,", ballFlightInfo.shotId);
			fprintf(fp, "%.2f,", ballFlightInfo.ballSpeed);
			fprintf(fp, "%.1f, %.1f, ", ballFlightInfo.Incidence, ballFlightInfo.direction);
			fprintf(fp, "%.1f, %.1f\n", ballFlightInfo.sideSpin, ballFlightInfo.backSpin);
			fclose(fp);
		}
	}
}
void CClientDlg::OnClubPathInfo(ZSensor::ClubPathInfo &clubInfo)
{
	LOG_BEGIN_END;
	LOGW<<"head Speed "<<clubInfo.headSpeed;
	m_ctrlTxtStatus.SetWindowTextW(_T("Status : RECV Club Info"));

	CString shotID;
	CString ballSpeed;

	shotID.Format(_T("Shot ID %04d"), clubInfo.shotId);
	ballSpeed.Format(_T("Speed  %.2f"), clubInfo.headSpeed);

	m_ctrlListClubInfo.AddString(shotID);
	m_ctrlListClubInfo.AddString(ballSpeed);
}

void CClientDlg::ConnectServer()
{
	BYTE address[4];
	m_ctrlServerIpAddress.GetAddress(address[0], address[1], address[2], address[3]);

	m_config.IpAddressField[0] = address[0];
	m_config.IpAddressField[1] = address[1];
	m_config.IpAddressField[2] = address[2];
	m_config.IpAddressField[3] = address[3];

	m_config.nPortNumber = m_nPortNumber;

	for(int i = 0;i < 4; i++)
	{
		if(m_config.IpAddressField[i]< 0 || m_config.IpAddressField[i] > 255)
		{
			CString ipAddress;
			ipAddress.Format(_T("IP Address : %d.%d.%d.%d"), m_config.IpAddressField[0], m_config.IpAddressField[1], m_config.IpAddressField[2], m_config.IpAddressField[3]);
			MessageBox(ipAddress, _T("Connection Error"));
			return;
		}
	}
	if(m_config.nPortNumber < 0 || m_config.nPortNumber > 65535)
	{
		CString ipAddress;
		ipAddress.Format(_T("Port number : %d"), m_config.nPortNumber);
		MessageBox(ipAddress, _T("Connection Error"));
		return;
	}
	char buffer[100];
	sprintf_s(buffer,100, "%d.%d.%d.%d", m_config.IpAddressField[0], m_config.IpAddressField[1], m_config.IpAddressField[2], m_config.IpAddressField[3]);
	if(m_pIntelliSwingProtocolAdapter->Connect(buffer, m_config.nPortNumber))
	{
		EnableButtons(TRUE);
	}
}

void CClientDlg::OnBnClickedButtonConnect()
{
	UpdateData();
	ConnectServer();
}


void CClientDlg::OnBnClickedButtonDisconnect()
{
	m_pIntelliSwingProtocolAdapter->Disconnect();
	EnableButtons(FALSE);
}

void CClientDlg::OnBnClickedButtonOpenWorkingFolder()
{
	CString strFilePath;
	GetExePath(strFilePath);
	ShellExecute(NULL, _T("open"), strFilePath.GetBuffer(), NULL, NULL, SW_SHOWDEFAULT);
}

void CClientDlg::EnableButtons(BOOL bEnable)
{
	std::vector<int> vecControls;

	vecControls.push_back(IDC_BUTTON_INITIALIZE           );
	vecControls.push_back(IDC_BUTTON_RELEASE              );
	vecControls.push_back(IDC_BUTTON_REBOOT               );
	vecControls.push_back(IDC_BUTTON_START                );
	vecControls.push_back(IDC_BUTTON_STOP                 );
	vecControls.push_back(IDC_BUTTON_GET_CLUB_IMG         );
	vecControls.push_back(IDC_BUTTON_GET_BALL_IMG         );
	vecControls.push_back(IDC_BUTTON_GET_DEVICE_INFO      );
	vecControls.push_back(IDC_BUTTON_DEVICE_STATUS        );
	vecControls.push_back(IDC_BUTTON_GET_LOG              );
	vecControls.push_back(IDC_CHECK_SAVE_SHOT_INFO_TO_CSV );
	vecControls.push_back(IDC_CHECK_AUTO_CONNECT          );
	vecControls.push_back(IDC_BUTTON_DISCONNECT           );
	
	for(int i = 0; i < vecControls.size(); i++)
	{
		CWnd* pWind = AfxGetMainWnd()->GetDlgItem(vecControls[i]);
		if(pWind)
		{
			(CButton*)(pWind)->EnableWindow(bEnable);
		}
	}
}



void CClientDlg::SetWorkingDirectory(CString Buffer)
{
	if( !SetCurrentDirectory(Buffer) )
	{
		printf("SetCurrentDirectory failed (%d)\n", GetLastError());
		return;
	}
}

void CClientDlg::UpdateINI(CString iniPath, INIField &out)
{
	CString value;
	value.Format(_T("%d"),  out.bAutoConnect);
	WritePrivateProfileString(_T("APPCONFIG"), _T("bAutoConnect"), value, iniPath );

	value.Format(_T("%d"),  out.bWriteFile);
	WritePrivateProfileString(_T("APPCONFIG"), _T("bWriteFile"), value, iniPath );

	value.Format(_T("%d"),  out.IpAddressField[0]);
	WritePrivateProfileString(_T("APPCONFIG"), _T("IpAddressField_0"), value, iniPath );
	value.Format(_T("%d"),  out.IpAddressField[1]);
	WritePrivateProfileString(_T("APPCONFIG"), _T("IpAddressField_1"), value, iniPath );
	value.Format(_T("%d"),  out.IpAddressField[2]);
	WritePrivateProfileString(_T("APPCONFIG"), _T("IpAddressField_2"), value, iniPath );
	value.Format(_T("%d"),  out.IpAddressField[3]);
	WritePrivateProfileString(_T("APPCONFIG"), _T("IpAddressField_3"), value, iniPath );
	value.Format(_T("%d"),  out.nPortNumber);
	WritePrivateProfileString(_T("APPCONFIG"), _T("nPortNumber"), value, iniPath );
}

void CClientDlg::ReadINI(CString iniPath, INIField &read)
{
	read.bAutoConnect = GetPrivateProfileInt(_T("APPCONFIG"), _T("bAutoConnect"), 0, iniPath );
	read.bWriteFile = GetPrivateProfileInt(_T("APPCONFIG"), _T("bWriteFile"),  0, iniPath );
	read.IpAddressField[0] = GetPrivateProfileInt(_T("APPCONFIG"), _T("IpAddressField_0"), 127, iniPath );
	read.IpAddressField[1] = GetPrivateProfileInt(_T("APPCONFIG"), _T("IpAddressField_1"), 0,iniPath );
	read.IpAddressField[2] = GetPrivateProfileInt(_T("APPCONFIG"), _T("IpAddressField_2"),  0,iniPath );
	read.IpAddressField[3] = GetPrivateProfileInt(_T("APPCONFIG"), _T("IpAddressField_3"),  1, iniPath );
	read.nPortNumber = GetPrivateProfileInt(_T("APPCONFIG"), _T("nPortNumber"), 50051, iniPath );
}
 

CString CClientDlg::GetExePath(CString &strFilePath)

{
    m_criticalExe.Lock();
	{
		static TCHAR pBuf[256] = {0, };
		memset(pBuf, NULL, sizeof(pBuf));
		GetModuleFileName( NULL, pBuf, sizeof( pBuf ) ); //현재 실행 경로를 가져오는 함수
		strFilePath.Format( _T( "%s" ), pBuf );
		strFilePath = strFilePath.Left( strFilePath.ReverseFind( _T( '\\' ) ) );
	}
    m_criticalExe.Unlock();

    return strFilePath;
}
void CClientDlg::OnBnClickedCheckAutoConnect()
{

	if(m_ctrlButtonAutoConnect.GetCheck())
	{
		m_config.bAutoConnect = TRUE;
	}
	else
	{
		m_config.bAutoConnect = FALSE;
	}
}

void CClientDlg::OnBnClickedCheckSaveShotInfoToCsv()
{
	// TODO: Add your control notification handler code here
	if(m_ctrlChkCSVWrite.GetCheck())
	{
		SetCSVPath();
	}
}

void CClientDlg::SetCSVPath()
{
	CString strCSVFIleName;

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);

	strCSVFIleName.Format(_T("DATA_%04d%02d%02d_%u%02u%02u.csv"),
		systemTime.wYear,
		systemTime.wMonth,
		systemTime.wDay,
		systemTime.wHour,
		systemTime.wMinute,
		systemTime.wSecond);
		

	m_strCSVPath = strCSVFIleName;

	FILE *fp = _tfopen(m_strCSVPath, _T("wt"));
	if(fp)
	{
		fprintf(fp, "Date, time, ShotID, ballSpeed, incidence, direction, SideSpin, BackSPin\n"); 
		fclose(fp);
	}
}