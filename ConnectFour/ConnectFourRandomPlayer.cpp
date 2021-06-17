#include "pch.h"
#include "ConnectFourRandomPlayer.h"

ConnectFourRandomPlayer::ConnectFourRandomPlayer()
{
}

ConnectFourRandomPlayer::~ConnectFourRandomPlayer()
{
}


bool ConnectFourRandomPlayer::MakeMove(unsigned int c)
{
	unsigned int col;
	col = (unsigned int)(rand() % 8);

	if (this->board->CheckLegal(col))
	{
		this->board->SetCell(col, this->board->CheckLegalY(col), this->cellType);
		return true;
	}

	return false;
}

bool ConnectFourRandomPlayer::IsHuman()
{
	return false;
}