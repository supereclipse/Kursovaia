#include "pch.h"
#include "ConnectFourPlayer.h"

ConnectFourPlayer::ConnectFourPlayer()
{
}

ConnectFourPlayer::~ConnectFourPlayer()
{
}

void ConnectFourPlayer::SetupPlayer(CString name, CellType cellType)
{
	this->name = name;
	this->cellType = cellType;
}

void ConnectFourPlayer::SetBoard(ConnectFourBoard* board)
{
	this->board = board;
}

CString ConnectFourPlayer::GetName()
{
	return this->name;
}