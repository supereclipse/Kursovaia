#include "pch.h"
#include "ConnectFourComputerPlayer.h"
#include "ConnectFourBoardMonteCarloEvaluator.h"

ConnectFourComputerPlayer::ConnectFourComputerPlayer()
{
}

ConnectFourComputerPlayer::~ConnectFourComputerPlayer()
{
}


bool ConnectFourComputerPlayer::MakeMove(unsigned int col)
{
	vector <ConnectFourBoardMonteCarloEvaluator*> evaluators;
	for(unsigned int i = 0; i < 8; i++)
		if (this->board->CheckLegal(7))
		{
			this->board->SetCell(i, this->board->CheckLegalY(i), this->cellType);
			evaluators.push_back(new ConnectFourBoardMonteCarloEvaluator(this->board, 1000, (this->cellType == CellType_1) ? CellType_2 : CellType_1, i));
			this->board->SetCell(i, this->board->GetlastY(), CellType_Empty);
		}

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		(*evaluator)->Evaluate();

	int biggestVictories = -1;

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		if (this->cellType == CellType_1)
		{
			if ((*evaluator)->GetVictories() > biggestVictories)
				biggestVictories = (*evaluator)->GetVictories();
		}
		else
		{
			if ((*evaluator)->GetLosses() > biggestVictories)
				biggestVictories = (*evaluator)->GetLosses();
		}

	vector<ConnectFourBoardMonteCarloEvaluator*> biggestWinEvaluators;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
	{
		int numVictories;
		if (this->cellType == CellType_1)
			numVictories = (*evaluator)->GetVictories();
		else
			numVictories = (*evaluator)->GetLosses();
		if (numVictories == biggestVictories)
			biggestWinEvaluators.push_back((*evaluator));
	}

	this->board->SetCell(biggestWinEvaluators[0]->GetXPos(), this->board->CheckLegalY(biggestWinEvaluators[0]->GetXPos()), this->cellType);
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		delete (*evaluator);
	evaluators.clear();
	biggestWinEvaluators.clear();
	return true;
}

bool ConnectFourComputerPlayer::IsHuman()
{
	return false;
}