
// ConnectFourDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ConnectFour.h"
#include "ConnectFourDlg.h"
#include "afxdialogex.h"
#include "CStartupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CConnectFourDlg



CConnectFourDlg::CConnectFourDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONNECTFOUR_DIALOG, pParent)
	, strPlayerTurn(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	board = nullptr;
	player1 = nullptr;
	player2 = nullptr;
	currentPlayer = nullptr;
}

void CConnectFourDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONNECTFOURFIELD, Field);
	DDX_Control(pDX, IDC_BUTTON1, mStartStopButton);
	DDX_Text(pDX, IDC_STATIC1, strPlayerTurn);
}

BEGIN_MESSAGE_MAP(CConnectFourDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CConnectFourDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Обработчики сообщений CConnectFourDlg

BOOL CConnectFourDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	Field.SetGameParent(this);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CConnectFourDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CConnectFourDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CConnectFourDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CConnectFourDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (bGameInProgress)
	{
		Cleanup();
		this->SetGameInProgress(false);
		this->Invalidate();
	}
	else
	{
		CStartupDlg sdlg;
		sdlg.SetDlgParent(this);
		int nRes = sdlg.DoModal();

		if (nRes == IDOK)
		{
			currentPlayer = player1;
			this->SetGameInProgress(true);
			this->UpdateName();
			this->Invalidate();
		}
	}
}

void CConnectFourDlg::CreateBoard()
{
	this->board = new ConnectFourBoard();
}
void CConnectFourDlg::CreatePlayer1(CString name, int type)
{
	if (type == 0)
		this->player1 = new ConnectFourHumanPlayer();
	else
		this->player1 = new ConnectFourComputerPlayer();

	player1->SetupPlayer(name, CellType_1);
	player1->SetBoard(this->board);
}
void CConnectFourDlg::CreatePlayer2(CString name, int type)
{
	if (type == 0)
		this->player2 = new ConnectFourHumanPlayer();
	else
		this->player2 = new ConnectFourComputerPlayer();

	player2->SetupPlayer(name, CellType_2);
	player2->SetBoard(this->board);
}

ConnectFourBoard* CConnectFourDlg::GetBoard()
{
	return board;
}
ConnectFourPlayer* CConnectFourDlg::GetCurrentPlayer()
{
	return currentPlayer;
}

void CConnectFourDlg::Cleanup()
{
	if (player1 != nullptr)
	{
		delete player1;
		player1 = nullptr;
	}
	if (player2 != nullptr)
	{
		delete player2;
		player2 = nullptr;
	}
	if (board != nullptr)
	{
		delete board;
		board = nullptr;
	}
	currentPlayer = nullptr;
}

void CConnectFourDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: добавьте свой код обработчика сообщений
	Cleanup();
}

void CConnectFourDlg::SetGameInProgress(bool InProgress)
{
	this->bGameInProgress = InProgress;
	this->Field.SetGameInProgress(InProgress);
	if (InProgress)
	{
		mStartStopButton.SetWindowTextW(L"Остановить");
	}
	else
	{
		mStartStopButton.SetWindowTextW(L"Запустить");
		Cleanup();
	}
}

void CConnectFourDlg::UpdateName()
{
	CString str;
	str.Format(L"Ход игрока: %s", currentPlayer->GetName());
	strPlayerTurn = str;
	UpdateData(FALSE);
}

void CConnectFourDlg::TogglePlayer()
{
	if (currentPlayer != player1)
		currentPlayer = player1;
	else
		currentPlayer = player2;

	UpdateName();
}