
// ConnectFour.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif
#include "pch.h"
#include "resource.h"		// основные символы


// CConnectFourApp:
// Сведения о реализации этого класса: ConnectFour.cpp
//

class CConnectFourApp : public CWinApp
{
public:
	CConnectFourApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CConnectFourApp theApp;
