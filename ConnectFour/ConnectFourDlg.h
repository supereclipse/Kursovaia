// ConnectFourDlg.h: файл заголовка
//
#pragma once
#include "pch.h"
#include "ConnectFourBoard.h"
#include "ConnectFourPlayer.h"
#include "ConnectFourComputerPlayer.h"
#include "ConnectFourHumanPlayer.h"
#include "CConnectFourField.h"
class CConnectFourField;

// Диалоговое окно CConnectFourDlg
class CConnectFourDlg : public CDialogEx
{
// Создание
public:
	CConnectFourDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECTFOUR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	CConnectFourField Field;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void CreateBoard();
	void CreatePlayer1(CString name, int type);
	void CreatePlayer2(CString name, int type);

	ConnectFourBoard* GetBoard();
	ConnectFourPlayer* GetCurrentPlayer();

private:
	ConnectFourBoard* board;
	ConnectFourPlayer* player1;
	ConnectFourPlayer* player2;
	ConnectFourPlayer* currentPlayer;
	bool bGameInProgress = false;

	void Cleanup();
	void UpdateName();
public:
	afx_msg void OnDestroy();
	void SetGameInProgress(bool InProgress);
	CButton mStartStopButton;
	CString strPlayerTurn;

	void TogglePlayer();
};
