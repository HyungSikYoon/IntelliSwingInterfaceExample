
// ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include <string>
#include <google/protobuf/util/time_util.h>
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//#ifdef _DEBUG
//#pragma comment(lib, "opencv_world440d.lib")
//#else
//#pragma comment(lib, "opencv_world440.lib")
//#endif

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
class LogHelper
{
	std::string m_msg;
public:
	LogHelper(std::string msg) : m_msg(msg)
	{
		std::cout << m_msg << " S" << std::endl;
	}
	~LogHelper()
	{
		std::cout << m_msg << " E" << std::endl;

	}

};



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TXT_STATUS, m_ctrlTxtShotStatus);
	DDX_Control(pDX, IDC_TXT_SHOTID, m_ctrlTXTShotId);
	DDX_Control(pDX, IDC_TXT_BALL_SPEED, m_ctrlTXTBallSpeed);
	DDX_Control(pDX, IDC_TXT_INCIDENCE, m_ctrlTxtIncidence);
	DDX_Control(pDX, IDC_TXT_DIRECTION, m_ctrlTXTBallDirection);
	DDX_Control(pDX, IDC_TXT_SIDESPIN, m_ctrlTXTSideSpin);
	DDX_Control(pDX, IDC_TXT_BACKSPIN, m_ctrlTXTBackSpin);
	DDX_Control(pDX, IDC_TXT_HEAD_SPEED, m_ctrlTXTHeadSpeed);
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
	ON_BN_CLICKED(IDC_BUTTON_SHOW_DBG_IMG, &CClientDlg::OnBnClickedButtonShowDbgImg)
	ON_BN_CLICKED(IDC_BUTTON_GET_IMAGE, &CClientDlg::OnBnClickedButtonGetImage)
	ON_WM_DESTROY()
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

	// extra initialization 

	std::string target_str = "localhost:50051";

	//std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());
	grpc::ChannelArguments channelArguments;
	channelArguments.SetMaxReceiveMessageSize(GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH * 2);
	channelArguments.SetMaxSendMessageSize(GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH * 2);

	std::shared_ptr<grpc::Channel> channel = grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(), channelArguments);
	if (channel)
	{
		std::cout << "Channel create complete " << target_str << std::endl;
		g_uptrStub = IntelliSwing::IntelliSwingProtocol::NewStub(channel);
		if (g_uptrStub)
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
	LogHelper log(__FUNCTION__);

	grpc::ClientContext context;
	IntelliSwing::InitializeMsg initMsg;
	IntelliSwing::ReturnMsg retMsgPB;
	grpc::Status status = g_uptrStub->Initialize(&context, initMsg, &retMsgPB);
	if (status.ok()) 
	{
		std::cout << "State Return Msg"<< retMsgPB.isok() << std::endl;
		std::cout << "rpc OK" << std::endl;
	}
	else 
	{
		std::cout<<"OnBnClickedButtonInitialize RPC failed" << status.error_code() << ": " << status.error_message()<< std::endl;
	}
}


void CClientDlg::OnBnClickedButtonRelease()
{
	LogHelper log(__FUNCTION__);
	IntelliSwing::ReleaseMsg releaseMsg;
	IntelliSwing::ReturnMsg retMsgPB;
	grpc::ClientContext context;

	grpc::Status status = g_uptrStub->Release(&context, releaseMsg, &retMsgPB);
	if (status.ok())
	{
		std::cout << "State Return Msg" << retMsgPB.isok() << std::endl;
		std::cout << "OnBnClickedButtonRelease OK" << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonRelease RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}
}


void CClientDlg::OnBnClickedButtonReboot()
{
	LogHelper log(__FUNCTION__);
	grpc::ClientContext context;
	IntelliSwing::ReturnMsg retMsgPB;

	//protobuf::em
	grpc::Status status = g_uptrStub->Reboot(&context, google::protobuf::Empty(), &retMsgPB);
	if (status.ok())
	{
		std::cout << "State Return Msg" << retMsgPB.isok() << std::endl;
		std::cout << "OnBnClickedButtonReboot OK" << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonReboot RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}
}


void CClientDlg::StartRunner()
{
	m_pContext  = new grpc::ClientContext();

	IntelliSwing::StartMsg startMsg;
	IntelliSwing::SensorRunningMsg runMsg;
	startMsg.set_clubinformation(IntelliSwing::StartMsg_ClubInformation::StartMsg_ClubInformation_W1);
	m_reader = g_uptrStub->Start(m_pContext, startMsg);
	std::cout << "Send Start Msg " << std::endl;

	if (m_reader)
	{
		IntelliSwing::SensorRunningMsg runMsg;
		
		while (m_reader->Read(&runMsg))
		{
			std::cout << "receiving message " << (int)runMsg.runState_case();
			if (runMsg.has_timestamp())
				std::cout << ", timestamp : " << google::protobuf::util::TimeUtil::ToString(runMsg.timestamp()) << std::endl;
			else
				std::cout << std::endl;


			switch (runMsg.runState_case())
			{

			case IntelliSwing::SensorRunningMsg::kReady:
			{
				std::cout << "IntelliSwing::SensorRunningMsg::kReady " << std::endl;
				m_ctrlTxtShotStatus.SetWindowTextW(_T("Ready"));

			}
			break;

			case IntelliSwing::SensorRunningMsg::kNotReady:
			{
				std::cout << "IntelliSwing::SensorRunningMsg::kReady " << std::endl;
				m_ctrlTxtShotStatus.SetWindowTextW(_T("kNotReady"));

			}
			break;

			case IntelliSwing::SensorRunningMsg::kShotTriggered:
			{
				std::cout << "IntelliSwing::SensorRunningMsg::kShotTriggered " << std::endl;
				m_ctrlTxtShotStatus.SetWindowTextW(_T("kShotTriggered"));

			}
			break;

			case IntelliSwing::SensorRunningMsg::kBallInfo:
			{
				std::cout << "IntelliSwing::SensorRunningMsg::kBallInfo " << std::endl;
				m_ctrlTxtShotStatus.SetWindowTextW(_T("kBallInfo"));

				const IntelliSwing::SensorRunningMsg_BallFlightInfo& ballInfoPB = runMsg.ballinfo();
				m_ctrlTXTShotId.SetWindowTextW(std::to_wstring(ballInfoPB.shotid()).c_str());
				m_ctrlTXTBallSpeed.SetWindowTextW(std::to_wstring(ballInfoPB.ballspeed()).c_str());
				m_ctrlTxtIncidence.SetWindowTextW(std::to_wstring(ballInfoPB.incidence()).c_str());
				m_ctrlTXTBallDirection.SetWindowTextW(std::to_wstring(ballInfoPB.direction()).c_str());
				m_ctrlTXTSideSpin.SetWindowTextW(std::to_wstring(ballInfoPB.sidespin()).c_str());
				m_ctrlTXTBackSpin.SetWindowTextW(std::to_wstring(ballInfoPB.backspin()).c_str());

				std::cout << "   ->shot information :  shotId " << ballInfoPB.shotid() << std::endl;
				std::cout << "   ->shot information :  speed  " << ballInfoPB.ballspeed() << std::endl;;
				std::cout << "   ->shot information :  direction " << ballInfoPB.direction() << ", Incidence " << ballInfoPB.incidence() << std::endl;
				std::cout << "   ->shot information :  backSpin " << ballInfoPB.backspin() << "sideSpin  " << ballInfoPB.sidespin() << std::endl;
			}
			break;

			case IntelliSwing::SensorRunningMsg::kClubInfo:
			{
				std::cout << "IntelliSwing::SensorRunningMsg::kClubInfo ";
				m_ctrlTxtShotStatus.SetWindowTextW(_T("kBallInfo"));

				const IntelliSwing::SensorRunningMsg_ClubPathInfo& clubPathInfoPB = runMsg.clubinfo();
				m_ctrlTXTHeadSpeed.SetWindowTextW(std::to_wstring(clubPathInfoPB.headspeed()).c_str());

				std::cout << "   ->club information :  shotId " << clubPathInfoPB.shotid() << std::endl;
				std::cout << "   ->club information :  headSpeed " << clubPathInfoPB.headspeed() << std::endl;
			}
			break;

			case IntelliSwing::SensorRunningMsg::RUNSTATE_NOT_SET:
			{
				std::cout << "IntelliSwing::SensorRunningMsg::RUNSTATE_NOT_SET " << std::endl;
			}
			break;
			default:
			{

			}
			break;
			}

		}//while (m_reader->Read(&runMsg))
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
}

void CClientDlg::OnBnClickedButtonStart()
{
	LogHelper log(__FUNCTION__);

	if (m_pContext) return;

	m_ctrlTxtShotStatus.SetWindowTextW(_T("-"));
	m_ctrlTXTShotId.SetWindowTextW(_T("-"));
	m_ctrlTXTBallSpeed.SetWindowTextW(_T("-"));
	m_ctrlTxtIncidence.SetWindowTextW(_T("-"));
	m_ctrlTXTBallDirection.SetWindowTextW(_T("-"));
	m_ctrlTXTSideSpin.SetWindowTextW(_T("-"));
	m_ctrlTXTBackSpin.SetWindowTextW(_T("-"));
	m_ctrlTXTHeadSpeed.SetWindowTextW(_T("-"));

	std::thread(&CClientDlg::StartRunner, this).detach();
}

void CClientDlg::OnBnClickedButtonStop()
{
	LogHelper log(__FUNCTION__);
	grpc::ClientContext context;
	IntelliSwing::ReturnMsg retMsgPB;

	//protobuf::em
	grpc::Status status = g_uptrStub->Stop(&context, google::protobuf::Empty(), &retMsgPB);
	if (status.ok())
	{
		std::cout << "State Return Msg" << retMsgPB.isok() << std::endl;
		std::cout << "OnBnClickedButtonStop OK" << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonStop RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}
}


void CClientDlg::OnBnClickedButtonGetClubImg()
{
	LogHelper log(__FUNCTION__);
	grpc::ClientContext context;
	IntelliSwing::ImageData retMsgPB;
	IntelliSwing::ShotImageRequest imageRequest;
	//protobuf::em
	grpc::Status status = g_uptrStub->GetClubImage(&context, imageRequest, &retMsgPB);
	if (status.ok())
	{
		std::cout << "OnBnClickedButtonGetClubImg OK" << std::endl;
		std::cout << "  -> image width " << retMsgPB.width() << std::endl;
		std::cout << "  -> image height " << retMsgPB.height() << std::endl;
		std::cout << "  -> image channel " << retMsgPB.channel() << std::endl;
		std::cout << "  -> image data_type " << retMsgPB.data_type() << std::endl;
		std::cout << "  -> image image_type " << retMsgPB.image_type() << std::endl;
		std::cout << "  -> image fps " << retMsgPB.fps() << std::endl;
		std::cout << "  -> image datas " << retMsgPB.datas_size() << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonStop RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}
}


void CClientDlg::OnBnClickedButtonGetBallImg()
{
	LogHelper log(__FUNCTION__);
	grpc::ClientContext context;
	IntelliSwing::ImageData retMsgPB;
	IntelliSwing::ShotImageRequest imageRequest;
	//protobuf::em
	grpc::Status status = g_uptrStub->GetBallImage(&context, imageRequest, &retMsgPB);
	if (status.ok())
	{
		std::cout << "OnBnClickedButtonGetBallImg OK" << std::endl;

		std::cout << "  -> image width " << retMsgPB.width() << std::endl;
		std::cout << "  -> image height " << retMsgPB.height() << std::endl;
		std::cout << "  -> image channel " << retMsgPB.channel() << std::endl;
		std::cout << "  -> image data_type " << retMsgPB.data_type() << std::endl;
		std::cout << "  -> image image_type " << retMsgPB.image_type() << std::endl;
		std::cout << "  -> image fps " << retMsgPB.fps() << std::endl;
		std::cout << "  -> image datas " << retMsgPB.datas_size() << std::endl;
	}
	else
	{
		std::cout << "OnBnClickedButtonGetBallImg RPC failed" << status.error_code() << ": " << status.error_message() << std::endl;
	}
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
	
	CDialogEx::OnTimer(nIDEvent);
}


void CClientDlg::OnBnClickedButtonShowDbgImg()
{
	// TODO: Add your control notification handler code here
	//::grpc::ClientContext* context, const ::IntelliSwing::DebugImageRequest& request, ::IntelliSwing::DebugImage* response
	grpc::ClientContext context;

	IntelliSwing::DebugImageRequest request;
	IntelliSwing::DebugImage response;
	request.add_channel(0);
	request.add_channel(1);
	request.add_channel(2);
	request.add_channel(3);
	request.set_key("i");
	grpc::Status status = g_uptrStub->GetDebugImage(&context, request, &response);

	if (status.ok())
	{

		size_t imageSize = response.datas().size();
		for (int i = 0; i < imageSize; i++)
		{
			const auto& img = response.datas().at(i);

			size_t width = img.width();
			size_t height = img.height();

			size_t nChannel = img.channel();
			size_t imgType = img.image_type();


			if (nChannel == 1 && imgType == 0 && !img.data().empty())
			{
				std::string winName;
				/*cv::Mat matInc = cv::Mat(cv::Size(width, height), CV_8UC1, (void*)&img.data()[0]).clone();
				winName = "DebugImg" + std::to_string(i);
				cv::imshow(winName, matInc);
				m_vecCamImage.push_back(matInc);*/
			}
		}
	}
}

void CClientDlg::OnBnClickedButtonGetImage()
{
	// TODO: Add your control notification handler code here
	IntelliSwing::CameraImageRequest request;
	IntelliSwing::ImageData response;

	request.set_camid(0);
	request.set_exposure(0);
	request.set_gain(0);
	grpc::ClientContext context;

	grpc::Status status = g_uptrStub->GetImage(&context, request, &response);
	if (status.ok())
	{
		size_t width = response.width();
		size_t height = response.height();

		size_t nChannel = response.channel();
		size_t imgType = response.image_type();

		size_t imageSize = response.datas().size();
		for (int i = 0; i < imageSize; i++)
		{
			const auto &img = response.datas().at(i);

			if (nChannel == 1 && imgType == 0 && !img.data().empty())
			{
				std::string winName;
				/*cv::Mat matInc =  cv::Mat(cv::Size(width, height), CV_8UC1,(void *) &img.data()[0]).clone();
				winName = "CamImg" + std::to_string(i);
				cv::imshow(winName, matInc);
				m_vecCamImage.push_back(matInc);*/
			}
		}
	}
}


void CClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	//cv::destroyAllWindows();
}
