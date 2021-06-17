#include "pch.h"
#include "ConnectFourBoardMonteCarloEvaluator.h"
#include "ConnectFourRandomPlayer.h"

ConnectFourBoardMonteCarloEvaluator::ConnectFourBoardMonteCarloEvaluator(ConnectFourBoard* board, int numIterations, CellType startCellType, unsigned int xpos)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numVictories = 0;
	this->numLosses = 0;
	this->xpos = xpos;
	this->startCellType = startCellType;
}

ConnectFourBoardMonteCarloEvaluator::~ConnectFourBoardMonteCarloEvaluator()
{

}

void ConnectFourBoardMonteCarloEvaluator::EvaluatedBoard()
{
	ConnectFourBoard* b = new ConnectFourBoard(this->board);
	ConnectFourRandomPlayer* player1 = new ConnectFourRandomPlayer();
	ConnectFourRandomPlayer* player2 = new ConnectFourRandomPlayer();
	ConnectFourRandomPlayer* currentPlayer;
	bool bGameFinished = false;

	player1->SetupPlayer(L"Random1", CellType_1);
	player2->SetupPlayer(L"Random2", CellType_2);
	player1->SetBoard(b);
	player2->SetBoard(b);
	currentPlayer = (this->startCellType == CellType_1) ? player1 : player2;

	if (b->CheckEndCondition())
	{
		if (b->IsVictory())
			if (currentPlayer == player1)
				numLosses++;
			else
				numVictories++;
		else
			numDraws++;
		bGameFinished = true;
		delete b;
		delete player1;
		delete player2;
		return;
	}

	while (!bGameFinished)
	{
		while (!currentPlayer->MakeMove(0));

		if (b->CheckEndCondition())
		{
			if (b->IsVictory())
				if (currentPlayer == player1)
					numVictories++;
				else
					numLosses++;
			else
				numDraws++;
			bGameFinished = true;
		}
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
	delete b;
	delete player1;
	delete player2;
}

void ConnectFourBoardMonteCarloEvaluator::Evaluate()
{
	for (int i = 0; i < numGames; i++)
		EvaluatedBoard();
}