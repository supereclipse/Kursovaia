#pragma once
// CConnectFourField
#include "pch.h"

class CConnectFourDlg;

class CConnectFourField : public CWnd
{
	DECLARE_DYNAMIC(CConnectFourField)

public:
	CConnectFourField();
	virtual ~CConnectFourField();

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool RegisterClass();
public:
	afx_msg void OnPaint();
private:
	int FieldSizeX;
	int FieldSizeY;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	void GetFieldPosition(CPoint point, int& xpos, int& ypos);
public:
	afx_msg void OnDestroy();
private:
	CRect GetRectFromField(int x, int y);
public:
	void Draw1(CPaintDC& dc, CRect rect);
private:
	void Draw2(CPaintDC& dc, CRect rect);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	int nSelectedX;
	int nSelectedY;
	CConnectFourDlg* gameParent;
	bool bGameInProgress = false;
	void HighlightSelection(CPaintDC& dc);
	bool CheckEndCondition();
public:
	afx_msg void OnMouseLeave();
	void SetGameParent(CConnectFourDlg* p);
	void SetGameInProgress(bool InProgress);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};