#include "pch.h"
#include "ConnectFourManager.h"
#include "ConnectFourHumanPlayer.h"
#include "ConnectFourComputerPlayer.h"

ConnectFourManager::ConnectFourManager()
{
}

ConnectFourManager::~ConnectFourManager()
{
	delete this->player2;
	delete this->player1;
	delete this->board;
}

bool ConnectFourManager::Init()
{
	return true;
}

void ConnectFourManager::ShowBoard()
{

}

void ConnectFourManager::MakeMove(unsigned int col)
{
	ShowBoard();
	while (!currentPlayer->MakeMove(0))
	{
		cout << "������������ ���, ���������� ��� ���" << endl;
		ShowBoard();
	}
	if (this->board->CheckEndCondition())
	{
		if (this->board->IsVictory())
			cout << "����� " << currentPlayer->GetName() << " �������!" << endl;
		else
			cout << "�����!" << endl;
		this->bGameFinished = true;
		ShowBoard();
		return;
	}
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool ConnectFourManager::IsGameFinished()
{
	return bGameFinished;
}