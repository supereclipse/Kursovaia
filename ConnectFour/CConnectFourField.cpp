// CConnectFourField.cpp: файл реализации
//

#include "pch.h"

#define CONNECTFOURFIELD_CLASSNAME L"ConnectFourField"
#define FIELDNUMBRERSSPACE 20
#define TIMER_ID 101

// CConnectFourField

IMPLEMENT_DYNAMIC(CConnectFourField, CWnd)

CConnectFourField::CConnectFourField()
{

	FieldSizeX = 8;
	FieldSizeY = 7;
	gameParent = nullptr;
	this->RegisterClass();
	nSelectedX = -1;
	nSelectedY = -1;
}

CConnectFourField::~CConnectFourField()
{
}


BEGIN_MESSAGE_MAP(CConnectFourField, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// Обработчики сообщений CConnectFourField




bool CConnectFourField::RegisterClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, CONNECTFOURFIELD_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = CONNECTFOURFIELD_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}


void CConnectFourField::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CWnd::OnPaint() для сообщений рисования

	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return;

	CRect rect;
	GetClientRect(&rect);



	CPen ourPen;
	HGDIOBJ oldPen;
	ourPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(ourPen);

	oldPen = dc.SelectObject(ourPen);

	int hPartSize = (rect.right - FIELDNUMBRERSSPACE) / FieldSizeX;
	int vPartSize = (rect.bottom - FIELDNUMBRERSSPACE) / FieldSizeY;

	this->HighlightSelection(dc);

	for (int i = 0; i < FieldSizeX + 1; i++)
	{
		dc.MoveTo(FIELDNUMBRERSSPACE + i * hPartSize, FIELDNUMBRERSSPACE);
		dc.LineTo(FIELDNUMBRERSSPACE + i * hPartSize, rect.bottom);
	}

	for (int i = 0; i < FieldSizeY + 1; i++)
	{
		dc.MoveTo(FIELDNUMBRERSSPACE,  i * vPartSize + FIELDNUMBRERSSPACE);
		dc.LineTo(rect.right, i * vPartSize + FIELDNUMBRERSSPACE);
	}

	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkMode(TRANSPARENT);

	for (int i = 0; i < FieldSizeX; i++)
	{
		CString str;
		str.Format(L"%d", i);
		dc.TextOutW(FIELDNUMBRERSSPACE / 2 + hPartSize / 2 + i * hPartSize, 0, str);
	}


	for (int x = 0; x < FieldSizeX; x++)
		for (int y = 0; y < FieldSizeY; y++)
		{
			if (this->gameParent->GetBoard()->GetCell(x, y) == CellType_1)
				this->Draw1(dc, this->GetRectFromField(x, y));
			if (this->gameParent->GetBoard()->GetCell(x, y) == CellType_2)
				this->Draw2(dc, this->GetRectFromField(x, y));
		}


	dc.SelectObject(oldPen);
	ourPen.DeleteObject();

}

void CConnectFourField::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if ((bGameInProgress) && (this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;

		int x, y;
		this->GetFieldPosition(point, x, y);

		if (this->gameParent->GetCurrentPlayer()->MakeMove(x) == true)
		{
			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				this->gameParent->TogglePlayer();
			}
		}
		this->Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


bool CConnectFourField::CheckEndCondition()
{
	if (this->gameParent->GetBoard()->CheckEndCondition())
	{
		if (this->gameParent->GetBoard()->IsVictory())
		{
			CString str;
			str.Format(L"Игрок %s победил!", this->gameParent->GetCurrentPlayer()->GetName());
			AfxMessageBox(str);
		}
		else
		{
			AfxMessageBox(L"Ничья!");
		}
		
		return true;
	}

	return false;
}


void CConnectFourField::GetFieldPosition(CPoint point, int& xpos, int& ypos)
{
	// TODO: Добавьте сюда код реализации.
	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return;

	CRect rect;
	GetClientRect(&rect);
	int hPartSize = (rect.right - FIELDNUMBRERSSPACE) / FieldSizeX;
	int vPartSize = (rect.bottom - FIELDNUMBRERSSPACE) / FieldSizeY;
	for (int i = 0; i < FieldSizeX; i++)
	{
		if ((point.x > FIELDNUMBRERSSPACE + i * hPartSize) && (point.x < FIELDNUMBRERSSPACE + (i + 1) * hPartSize))
			xpos = i;
	}
	for (int i = 0; i < FieldSizeY; i++)
	{
		if ((point.y > FIELDNUMBRERSSPACE + i * vPartSize) && (point.y < FIELDNUMBRERSSPACE + (i + 1) * vPartSize))
			ypos = i;
	}
}


void CConnectFourField::OnDestroy()
{
	CWnd::OnDestroy();
	// TODO: добавьте свой код обработчика сообщений
}

CRect CConnectFourField::GetRectFromField(int x, int y)
{
	// TODO: Добавьте сюда код реализации.
	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return CRect(0, 0, 0, 0);

	CRect rect;
	CRect rectWnd;
	GetClientRect(&rectWnd);
	int hPartSize = (rectWnd.right - FIELDNUMBRERSSPACE) / FieldSizeX;
	int vPartSize = (rectWnd.bottom - FIELDNUMBRERSSPACE) / FieldSizeY;

	rect.left = FIELDNUMBRERSSPACE + x * hPartSize + 1;
	rect.top = FIELDNUMBRERSSPACE + y * vPartSize + 1;
	rect.right = FIELDNUMBRERSSPACE + ((x + 1) * hPartSize) - 1;
	rect.bottom = FIELDNUMBRERSSPACE + ((y + 1) * vPartSize) - 1;

	return rect;
}


void CConnectFourField::Draw1(CPaintDC& dc, CRect rect)
{
	// TODO: Добавьте сюда код реализации.
	CPen pen;
	pen.CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(65, 65, 65));
	HGDIOBJ oldbrush = dc.SelectObject(brush);

	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);

	dc.SelectObject(oldPen);
	pen.DeleteObject();
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
}


void CConnectFourField::Draw2(CPaintDC& dc, CRect rect)
{
	// TODO: Добавьте сюда код реализации.
	CPen pen;
	pen.CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(222, 222, 222));
	HGDIOBJ oldbrush = dc.SelectObject(brush);

	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);

	dc.SelectObject(oldPen);
	pen.DeleteObject();
	dc.SelectObject(oldbrush);
	brush.DeleteObject();

}


void CConnectFourField::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	int x, y;

	GetFieldPosition(point, x, y);
	if ((nSelectedX != x) || (nSelectedY != y))
	{
		nSelectedX = x;
		nSelectedY = y;
		this->Invalidate();
	}

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = this->m_hWnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;

	TrackMouseEvent(&tme);

	CWnd::OnMouseMove(nFlags, point);
}


void CConnectFourField::HighlightSelection(CPaintDC& dc)
{
	// TODO: Добавьте сюда код реализации.
	if ((nSelectedX < 0) || (nSelectedY < 0))
		return;
	CRect rect = GetRectFromField(nSelectedX, nSelectedY);
	CBrush brush;
	brush.CreateSolidBrush(RGB(125, 249, 255));
	HGDIOBJ oldbrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
}


void CConnectFourField::OnMouseLeave()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	nSelectedX = -1;
	nSelectedY = -1;
	this->Invalidate();

	CWnd::OnMouseLeave();
}

void CConnectFourField::SetGameParent(CConnectFourDlg* p)
{
	this->gameParent = p;
}

void CConnectFourField::SetGameInProgress(bool InProgress)
{
	if (bGameInProgress != InProgress)
	{
		this->bGameInProgress = InProgress;
		this->gameParent->SetGameInProgress(InProgress);
		if (InProgress)
			SetTimer(TIMER_ID, 1000, NULL);
		else
			KillTimer(TIMER_ID);
	}
}

void CConnectFourField::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if ((bGameInProgress) && (!this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;

		if (this->gameParent->GetCurrentPlayer()->MakeMove(0) == true)
		{
			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				this->gameParent->TogglePlayer();
			}
		}
		this->Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}
