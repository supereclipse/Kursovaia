#pragma once
#include "pch.h"
#include "ConnectFourBoard.h"
#include "ConnectFourPlayer.h"

class ConnectFourRandomPlayer : public ConnectFourPlayer
{
public:
	ConnectFourRandomPlayer();
	virtual ~ConnectFourRandomPlayer();
	virtual bool MakeMove(unsigned int col);
	virtual bool IsHuman();
};