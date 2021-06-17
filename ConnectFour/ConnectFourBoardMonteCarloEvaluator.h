#pragma once
#include "pch.h"
#include "ConnectFourBoard.h"

class ConnectFourBoardMonteCarloEvaluator
{
private:
	ConnectFourBoard* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int xpos;
	CellType startCellType;
public:
	ConnectFourBoardMonteCarloEvaluator(ConnectFourBoard* board, int numIterations, CellType startCellType, unsigned int xpos);
	~ConnectFourBoardMonteCarloEvaluator();
	void EvaluatedBoard();
	void Evaluate();
	int GetVictories() { return numVictories; }
	int GetLosses() { return numLosses; }
	int GetDraws() { return numDraws; }
	unsigned int GetXPos() { return xpos; }
};