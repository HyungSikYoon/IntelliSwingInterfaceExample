#pragma once

#ifdef ZSENSORINTERFACEDLL_EXPORTS
#define ZSENSOR_API __declspec( dllexport )
#else
#define ZSENSOR_API __declspec( dllimport )
#endif


namespace ZSensor
{
#define Z_INPUT 
#define Z_OUTPUT

	enum ZRETURN_CODE
	{
		Z_ERROR = -1,
		Z_NOK = 0,
		Z_OK = 1,
	};


	struct InitializeMsg
	{
		InitializeMsg() : client(Client_TYPE::GDR)	{ }
		enum Client_TYPE
		{
			GDR = 0,
			NextGDR = 1,
			Vision = 2,
			Ohter = 3,
		};

		Client_TYPE client;
	};

	struct ReleaseMsg
	{
		ReleaseMsg()
		{
			nId = 0;
		}
		int nId;
	};

	struct ReturnMsg
	{
		ReturnMsg() : isOK(false), errorCode(0){errorDesc[0] = 0;}
		bool isOK;
		int errorCode;
		char errorDesc[30];
	};
	enum GroundAttr_TYPE
	{
		FAIRWAY = 0,	//  : Fairway
		ROUGH = 1,	//  : Rough
		BUNKER = 2,	//  : Bunker
		TEE = 3,	//  : Tee
		GREEN = 4,	//  : Green
	};

	enum ClubInformation_TYPE
	{
		NonPutting = 0,
		Putting = 1,
		Wood = 100,
		W1 = 101,
		W2 = 102,
		W3 = 103,
		W4 = 104,
		W5 = 105,
		Iron = 200,
		I3 = 203,
		I4 = 204,
		I5 = 205,
		I6 = 206,
		I7 = 207,
		I8 = 208,
		I9 = 209,
		Wedge = 300,
		PW = 310,
		SW = 320,
		Hybrid = 400,
	};
	struct StartMsg
	{
		StartMsg() : clubInformation(ClubInformation_TYPE::NonPutting), goundAttribution(GroundAttr_TYPE::FAIRWAY) {};

		ClubInformation_TYPE clubInformation;
		GroundAttr_TYPE		goundAttribution;
	};

	struct ShotImageRequest
	{
		ShotImageRequest() : shotId(0) {}
		int shotId;
	};

	struct ImageData
	{
		struct Image
		{
			unsigned long long timeStamp;
			unsigned char* pByteBuffer;
			int nBufferSize;
		};
		int width;
		int height;
		int channel;
		int data_type;
		int image_type;
		float fps;	// frame per second
		int nImageArrayCount;
		Image* pImageBuffer;
	};

	struct DeviceInfo
	{
		char	deviceVer[30];
		char	fpgaVer[30];
		char	softwareVer[30];
		char	serialNumber[30];
		char	sensorName[30];
		int	handType; //{0 : right-hand, 1 : left_hand}
	};

	struct DiviceStatus
	{
		ReturnMsg systemState;
		float deviceTemperature;
	};

	struct Point3f
	{
		float x, y, z;
	};
	struct Ready
	{
		Point3f			position; //mm, sensor coordinate
		bool			isTee;
		GroundAttr_TYPE		goundAttribution;
	};

	struct NotReady
	{
		enum NotReadyCause
		{
			NotDefined = 0,
			OutBound = 1,
			BallNotFound = 2,
			MultiBall = 3,
		};
		NotReadyCause notReadyCause;
	};

	struct ShortTriggered
	{
		int shotId;
		unsigned long long timestamp ;
	};

	struct BallFlightInfo
	{
		int shotId;
		float ballSpeed;	// m/s
		float Incidence;	// degree
		float direction;	// degree
		float backSpin;	// rpm
		float sideSpin;	// rpm
	};

	struct ClubPathInfo
	{
		struct Path
		{
			float GAClubPath;//degree        클럽패스 각도(Out to In,  Straight, In to Out)
		};

		struct ImpactPoint
		{
			float GAClubImpactPoint_Hor;//수평성분의 임팩트포인트(음수값이 Heel방향, 양수값이 Toe방향)
			float GAClubImpactPoint_Ver;//수직성분의 임팩트포인트(음수값이 Bottom방향, 양수값이 Top방향)
		};
		int shotId;
		float headSpeed;	// m/s
		Path path;
		float faceAngle;	// degree
		float attackAngle;	// degree
		ImpactPoint impactPoint;
	};

	class iSensorRunnginEventHandler
	{
	public:
		virtual void OnReady(IN Ready &ready) = 0;
		virtual void OnNotReady(IN NotReady &notReady) = 0;
		virtual void OnShortTriggered(IN ShortTriggered &shotTriggered) = 0;
		virtual void OnBallFlightInfo(IN BallFlightInfo &ballFlightInfo) = 0;
		virtual void OnClubPathInfo(IN ClubPathInfo &clubInfo) = 0;
	};

	class ZSENSOR_API IIntelliSwingProtocolAdapter
	{
		iSensorRunnginEventHandler* m_pClientEventHandler;
		bool m_bEnableLog;
		int m_nPort;
		const char* m_szServerIpAddress;
	public:
		IIntelliSwingProtocolAdapter(iSensorRunnginEventHandler* pEventHandler, bool bEnableLog = false);
		int Connect(Z_INPUT const char* szIpAddress, Z_INPUT const int port);
		int Disconnect();
		// Common
		int Initialize(Z_INPUT const InitializeMsg& initializeMsg, Z_OUTPUT ReturnMsg& returnMsg);
		int Release(Z_INPUT const ReleaseMsg& releaseMsg, Z_OUTPUT ReturnMsg& returnMsg);
		int Reboot(Z_OUTPUT ReturnMsg& returnMsg);

		// Sensor
		int Start(Z_INPUT const StartMsg startMsg);
		int Stop(Z_OUTPUT ReturnMsg& returnMsg);
		int GetClubImage(Z_INPUT const ShotImageRequest imageRequest, Z_OUTPUT ImageData& imageData);
		int GetBallImage(Z_INPUT const ShotImageRequest, Z_OUTPUT ImageData& imageData);

		// Service
		int GetDeviceInfo(Z_OUTPUT DeviceInfo& deviceInfo);
		int GetDeviceStatus(Z_OUTPUT DiviceStatus& deviceStatus);
		/*int GetLog(LogRequest, OUT (LogMessage);
		int GetStatistics(StatisticsRequest, OUT (SensorStatistics);
		int RunSiteCalibration(SiteCalibrationRequest, OUT (SiteCalibrationResult);
		int UpdateFirmware(UpdateFirmwareRequest, OUT (UpdateFirmwareResult);
		int GetImage(CameraImageRequest, OUT (ImageData);*/
	};

}