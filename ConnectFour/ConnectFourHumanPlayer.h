#pragma once
#include "pch.h"
#include "ConnectFourBoard.h"
#include "ConnectFourPlayer.h"

class ConnectFourHumanPlayer : public ConnectFourPlayer
{
public:
	ConnectFourHumanPlayer();
	virtual ~ConnectFourHumanPlayer();
	virtual bool MakeMove(unsigned int col);
	virtual bool IsHuman();
};