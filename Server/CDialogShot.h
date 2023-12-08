#pragma once
#include "resource.h"

// CDialogShot dialog

class CDialogShot : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogShot)

public:
	CDialogShot(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogShot();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nBackspin = 3000;
	int m_nBallDirection = 3;
	int m_nBallIncidence = 15;
	int m_nBallSpeed = 43;
	int m_nSideSpin = -300;
	int m_nHeadSpeed = 35;
	afx_msg void OnBnClickedOk();
	float m_fAttackAngle = 10;
	float m_fDynamicLoft = 10;
	float m_fClubPath = 0;
	float m_fFaceAngle = 0;
	float m_fSwingPlane = 75;
	float m_fSwingDirection = 0;
	float m_fLowPoint = -1;
	float m_fImpactHeight = 0;
	float m_fImpactOffset = 0;
	float m_fClubLie = 0;
	float m_fClubClosureRate = 0;
	float m_fClubFAxis = 0;
	float m_fToeHeelDiff = 0;
};
