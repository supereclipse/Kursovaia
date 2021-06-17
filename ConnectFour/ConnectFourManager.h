#pragma once
#include "pch.h"
#include "ConnectFourBoard.h"
#include "ConnectFourPlayer.h"

class ConnectFourManager
{
private:
	ConnectFourBoard* board;
	ConnectFourPlayer* player1;
	ConnectFourPlayer* player2;
	ConnectFourPlayer* currentPlayer;
	bool bGameFinished = false;
public:
	ConnectFourManager();
	virtual ~ConnectFourManager();
	bool Init();
	void ShowBoard();
	void MakeMove(unsigned int col);
	bool IsGameFinished();
};