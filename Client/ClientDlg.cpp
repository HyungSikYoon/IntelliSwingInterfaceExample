
// ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#include <google/protobuf/util/time_util.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg dialog



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INITIALIZE, &CClientDlg::OnBnClickedButtonInitialize)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, &CClientDlg::OnBnClickedButtonRelease)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CClientDlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_START, &CClientDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CClientDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_GET_CLUB_IMG, &CClientDlg::OnBnClickedButtonGetClubImg)
	ON_BN_CLICKED(IDC_BUTTON_GET_BALL_IMG, &CClientDlg::OnBnClickedButtonGetBallImg)
	ON_BN_CLICKED(IDC_BUTTON_GET_DEVICE_INFO, &CClientDlg::OnBnClickedButtonGetDeviceInfo)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_STATUS, &CClientDlg::OnBnClickedButtonDeviceStatus)
	ON_BN_CLICKED(IDC_BUTTON_GET_LOG, &CClientDlg::OnBnClickedButtonGetLog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: Add extra initialization here

	std::string target_str = "localhost:50051";
	std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());
	if (channel)
	{
		std::cout << "Channel create complete " << target_str << std::endl;
		m_uptrStub = IntelliSwing::IntelliSwingProtocol::NewStub(channel);
		if (m_uptrStub)
			std::cout << "channel connected " << target_str << std::endl;
		return TRUE;
	}
	
	std::cout << "Cannot connect server " << target_str << std::endl;
	return TRUE;  // return TRUE  unless you set the focus to a control
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
		CDialogEx::OnSysCommand(nID, lParam);
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
		CDialogEx::OnPaint();
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
	grpc::ClientContext context;
	IntelliSwing::InitializeMsg initMsg;
	IntelliSwing::ReturnMsg retMsg;
	grpc::Status status = m_uptrStub->Initialize(&context, initMsg, &retMsg);
	if (status.ok()) 
	{
		std::cout << "State Return Msg"<< retMsg.isok() << std::endl;
		std::cout << "rpc OK" << std::endl;
	}
	else 
	{
		std::cout<<"OnBnClickedButtonInitialize RPC failed" << status.error_code() << ": " << status.error_message()<< std::endl;
	}
}


void CClientDlg::OnBnClickedButtonRelease()
{
	// TODO: Add your control notification handler code here
	IntelliSwing::ReleaseMsg releaseMsg;
	IntelliSwing::ReturnMsg retMsg;
	grpc::ClientContext context;

	grpc::Status status = m_uptrStub->Release(&context, releaseMsg, &retMsg);
	if (status.ok())
	{
		std::cout << "State Return Msg" << retMsg.isok() << std::endl;
		std::cout << "OnBnClickedButtonRelease OK" << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonRelease RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}
}


void CClientDlg::OnBnClickedButtonReboot()
{
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	m_pContext = new grpc::ClientContext();

	IntelliSwing::StartMsg startMsg;
	IntelliSwing::SensorRunningMsg runMsg;

	startMsg.set_clubinformation(IntelliSwing::StartMsg_ClubInformation::StartMsg_ClubInformation_W1);
	
	m_reader = m_uptrStub->Start(m_pContext, startMsg);
	std::cout << "Send Start Msg "<< std::endl;

	if (m_reader == nullptr)  return;
	SetTimer(TIMER_ID_READ_FROM_SERVER, 100, nullptr);

	/*while (m_reader->Read(&runMsg))
	{
		if(runMsg.has_timestamp())
			std::cout << "receiving message " << google::protobuf::util::TimeUtil::ToString(runMsg.timestamp()) << std::endl;
	}

	grpc::Status status = m_reader->Finish();
	if (status.ok())
	{
		std::cout << "OnBnClickedButtonRelease OK" << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonRelease RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}*/
}


void CClientDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButtonGetClubImg()
{
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButtonGetBallImg()
{
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButtonGetDeviceInfo()
{
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButtonDeviceStatus()
{
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnBnClickedButtonGetLog()
{
	// TODO: Add your control notification handler code here
}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (TIMER_ID_READ_FROM_SERVER)
	{
		KillTimer(TIMER_ID_READ_FROM_SERVER);

		if (m_reader)
		{
			IntelliSwing::SensorRunningMsg runMsg;
			bool bReadSuceed = m_reader->Read(&runMsg);
			if (bReadSuceed)
			{
				SetTimer(TIMER_ID_READ_FROM_SERVER, 100, nullptr);

				std::cout << "receiving message " << (int)runMsg.runState_case();
				if (runMsg.has_timestamp())
					std::cout << ", timestamp : " << google::protobuf::util::TimeUtil::ToString(runMsg.timestamp()) << std::endl;
				else
					std::cout << std::endl;

			}
			else
			{
				grpc::Status status = m_reader->Finish();
				if (status.ok())
				{
					std::cout << "OnBnClickedButtonRelease OK" << std::endl;
				}
				else
				{
					std::cout << "OnBnClickedButtonRelease RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
				}
				delete m_pContext;
				m_pContext = nullptr;
			}

		}
		/*while (m_reader->Read(&runMsg))
	{
		if(runMsg.has_timestamp())
			std::cout << "receiving message " << google::protobuf::util::TimeUtil::ToString(runMsg.timestamp()) << std::endl;
	}

	grpc::Status status = m_reader->Finish();
	if (status.ok())
	{
		std::cout << "OnBnClickedButtonRelease OK" << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonRelease RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}*/
	}
	CDialogEx::OnTimer(nIDEvent);
}
