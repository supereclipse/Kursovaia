#pragma once
#include "pch.h"
#include "ConnectFourBoard.h"

class ConnectFourPlayer
{
protected:
	ConnectFourBoard* board;
	CellType cellType;
	CString name;
public:
	ConnectFourPlayer();
	virtual ~ConnectFourPlayer();
	void SetupPlayer(CString name, CellType cellType);
	void SetBoard(ConnectFourBoard* board);
	virtual bool MakeMove(unsigned int col) = 0;
	CString GetName();
	virtual bool IsHuman() = 0;
};

