#include "pch.h"

ConnectFourBoard::ConnectFourBoard()
{
	cells = new CellType * [7];
	for (unsigned int i = 0; i < 7; i++)
		cells[i] = new CellType[8];
	for (unsigned int i = 0; i < 7; i++)
		for (unsigned int j = 0; j < 8; j++)
			cells[i][j] = CellType_Empty;
}

ConnectFourBoard::ConnectFourBoard(ConnectFourBoard* board)
{
	cells = new CellType * [7];
	for (unsigned int i = 0; i < 7; i++)
		cells[i] = new CellType[8];
	for (unsigned int i = 0; i < 7; i++)
		for (unsigned int j = 0; j < 8; j++)
			cells[i][j] = board->cells[i][j];
}

ConnectFourBoard::~ConnectFourBoard()
{
	for (unsigned int i = 0; i < 7; i++)
		delete[]cells[i];
	delete[]cells;
}

void ConnectFourBoard::SetCell(unsigned int xpos, unsigned int ypos, CellType ct)
{
	cells[ypos][xpos] = ct;
	this->lastY = ypos;
	this->lastX = xpos;
}

bool ConnectFourBoard::CheckLegal(unsigned int xpos)
{
	for (unsigned int i = 0; i < 8; i++)
	{
		if ((xpos < 0) || (xpos > 7) || (CheckLegalY(xpos) < 0))
			return false;
		return (cells[i][xpos] == CellType_Empty);
	}
}

unsigned int ConnectFourBoard::CheckLegalY(unsigned int xpos)
{
	unsigned int count = -1;
	for (unsigned int i = 0; i < 7; i++)
	{
		if (cells[i][xpos] == CellType_Empty)
			count++;
	}
	return count;
}

bool ConnectFourBoard::IsRowMade(unsigned int row)
{
	int numR = 0, numY = 0;
	for (unsigned int i = 0; i < 8; i++)
	{
		if ((0 <= this->lastX) && (this->lastX < 8) && (0 <= this->lastY) && (this->lastY < 7))
		{
			if (cells[this->lastY][i] == cells[this->lastY][i + 1])
			{
				if (cells[this->lastY][i] == CellType_2)
					numY++;
				if (cells[this->lastY][i] == CellType_1)
					numR++;
			}
			if ((cells[this->lastY][i + 1] == cells[this->lastY][this->lastX]) && ((numY == 3) || (numR == 3)))
			{
				if (cells[this->lastY][i] == CellType_2)
					numY++;
				if (cells[this->lastY][i] == CellType_1)
					numR++;
			}
		}
	}

	if ((numR == 4) || (numY == 4))
	{
		bVictory = true;
		return true;
	}

	return false;
}

bool ConnectFourBoard::IsColumnMade(unsigned int col)
{
	int numR = 0, numY = 0;
	unsigned int x = this->lastX;
	unsigned int y = this->lastY;

	for (unsigned int i = 0; i < 4; i++)
	{
		if ((0 <= x) && (x < 8) && (0 <= y) && (y < 7))
		{
			if (cells[y][x] == CellType_2)
				numY++;
			if (cells[y][x] == CellType_1)
				numR++;
			y++;
		}
	}

	if ((numR == 4) || (numY == 4))
	{
		bVictory = true;
		return true;
	}

	return false;
}

bool ConnectFourBoard::IsDiagMade()
{
	int numR = 0, numY = 0;
	unsigned int x = this->lastX;
	unsigned int y = this->lastY;

	while ((0 < x) && (y < 6))
	{
		x--;
		y++;
	}

	for (unsigned int i = 0; i < 8; i++)
	{
		if ((0 <= x) && (x < 8) && (0 <= y) && (y < 7))
		{
			if ((cells[y][x] == CellType_2) && (cells[y][x] == cells[this->lastY][this->lastX]))
				numY++;
			if ((cells[y][x] == CellType_1) && (cells[y][x] == cells[this->lastY][this->lastX]))
				numR++;
			x++;
			y--;
		}
	}

	if ((numR == 4) || (numY == 4))
	{
		bVictory = true;
		return true;
	}

	numR = numY = 0;
	x = this->lastX;
	y = this->lastY;

	while ((x < 7) && (y < 6))
	{
		x++;
		y++;
	}

	for (unsigned int i = 0; i < 8; i++)
	{
		if ((0 <= x) && (x < 8) && (0 <= y) && (y < 7))
		{
			if ((cells[y][x] == CellType_2) && (cells[y][x] == cells[this->lastY][this->lastX]))
				numY++;
			if ((cells[y][x] == CellType_1) && (cells[y][x] == cells[this->lastY][this->lastX]))
				numR++;
			x--;
			y--;
		}
	}

	if ((numR == 4) || (numY == 4))
	{
		bVictory = true;
		return true;
	}

	return false;
}

bool ConnectFourBoard::IsBoardFull()
{
	int numR = 0, numY = 0;
	for (unsigned int i = 0; i < 7; i++)
	{
		for (unsigned int j = 0; j < 8; j++)
		{
			if (cells[i][j] == CellType_2)
				numY++;
			if (cells[i][j] == CellType_1)
				numR++;
		}
	}

	if ((numR + numY) == 70)
		return true;

	return false;
}

bool ConnectFourBoard::CheckEndCondition()
{
	for (unsigned int i = 0; i < 7; i++)
	{
		if (IsRowMade(i))
			return true;
	}
	for (unsigned int j = 0; j < 8; j++)
	{
		if (IsColumnMade(j))
			return true;
	}
	if (IsDiagMade() || IsBoardFull())
		return true;

	return false;
}

bool ConnectFourBoard::IsVictory()
{
	return bVictory;
}

CellType ConnectFourBoard::GetCell(unsigned int xpos, unsigned int ypos)
{
	return cells[ypos][xpos];
}

void ConnectFourBoard::ClearBoard()
{
	for (unsigned int i = 0; i < 7; i++)
		for (unsigned int j = 0; j < 8; j++)
			cells[i][j] = CellType_Empty;
}