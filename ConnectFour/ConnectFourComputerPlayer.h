#pragma once
#include "pch.h"
#include "ConnectFourBoard.h"
#include "ConnectFourPlayer.h"

class ConnectFourComputerPlayer : public ConnectFourPlayer
{
public:
	ConnectFourComputerPlayer();
	virtual ~ConnectFourComputerPlayer();
	virtual bool MakeMove(unsigned int col);
	virtual bool IsHuman();
};

