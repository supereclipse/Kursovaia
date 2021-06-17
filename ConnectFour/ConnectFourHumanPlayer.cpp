#include "pch.h"
#include "ConnectFourHumanPlayer.h"

ConnectFourHumanPlayer::ConnectFourHumanPlayer()
{
}

ConnectFourHumanPlayer::~ConnectFourHumanPlayer()
{
}


bool ConnectFourHumanPlayer::MakeMove(unsigned int col)
{
	
	if (this->board->CheckLegal(col))
	{
		this->board->SetCell(col, this->board->CheckLegalY(col), this->cellType);
		return true;
	}

	return false;
}

bool ConnectFourHumanPlayer::IsHuman()
{
	return true;
}