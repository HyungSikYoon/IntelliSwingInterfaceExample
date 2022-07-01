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
};
