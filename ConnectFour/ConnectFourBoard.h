#pragma once
#include "pch.h"
#include "CellType.h"

class ConnectFourBoard
{
private:
	CellType** cells;
	bool bVictory = false;
	bool IsRowMade(unsigned int row);
	bool IsColumnMade(unsigned int col);
	bool IsDiagMade();
	bool IsBoardFull();
	unsigned int lastY;
	unsigned int lastX;
public:
	ConnectFourBoard();
	ConnectFourBoard(ConnectFourBoard* board);
	virtual ~ConnectFourBoard();
	void SetCell(unsigned int xpos, unsigned int ypos, CellType ct);
	bool CheckLegal(unsigned int xpos);
	unsigned int CheckLegalY(unsigned int xpos);
	bool CheckEndCondition();
	bool IsVictory();
	unsigned int GetlastY() { return lastY; }
	CellType GetCell(unsigned int xpos, unsigned int ypos);
	void ClearBoard();
};