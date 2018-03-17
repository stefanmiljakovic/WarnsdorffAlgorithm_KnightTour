#include "stdafx.h"
#include "Knight.h"

#include <algorithm>

const static int MOVE [MOVE_SIZE][PAIR] =
{
	{1, 2}, {2, 1}, {-1, 2}, {-2, 1},
	{-1,-2},{-2,-1},{1,-2}, {2, -1}
};

Knight::Knight(int x, int y)
{
	pos.x = x;
	pos.y = y;

	this->movesMade = 0;
	this->initializeVector();
}

Knight::Knight(std::vector<std::vector<int>> table , Position pos, int moves) {
	this->table = table;
	this->pos = pos;
	this->movesMade = moves;
}

void Knight::initializeVector() {
	table = std::vector<std::vector<int>>(TABLE_SIZE, std::vector<int>(TABLE_SIZE, -1)); // initializes it with -1 default
}

void Knight::makeMove() {
	this->table.at(pos.x).at(pos.y) = ++movesMade;
}

bool Knight::checkConstraints(int i) {
	if (i >= 0 && i < TABLE_SIZE) {
		return true;
	}
	return false;
}


int Knight::checkMoves(int dx, int dy) {
	int mov = 0;

	for (int i = 0; i < MOVE_SIZE; i++) {
		int x = dx + MOVE[i][0];
		int y = dy + MOVE[i][1];

		if (checkConstraints(x) && checkConstraints(y) && table.at(x).at(y) == -1) {
			mov++;
		}
	}

	return mov;
}

void Knight::setMoveOrder() {
	for (int i = 0; i < MOVE_SIZE; i++) {
		int x = pos.x + MOVE[i][0];
		int y = pos.y + MOVE[i][1];

		if (checkConstraints(x) && checkConstraints(y) && table.at(x).at(y) == -1) {
			moveOrder.emplace_back(MoveOrder(checkMoves(x, y), i));
		}
	}

	if(moveOrder.size() > 1)
		std::sort(moveOrder.begin(), moveOrder.end(), [](const MoveOrder& lhs, const MoveOrder& rhs) {

		return lhs.movesPossible < rhs.movesPossible;
	});
}

std::vector<std::vector<int>> Knight::evaluate() {

	this->setMoveOrder();
	this->makeMove();

	if (movesMade == pow(TABLE_SIZE, 2))
		return table;

	if (moveOrder.empty())
		return {}; // return empty vector

	for (int i = 0; i < moveOrder.size(); i++) {
		Knight k = Knight(this->table,
			Position(pos.x + MOVE[moveOrder.at(i).pairID][0], pos.y + MOVE[moveOrder.at(i).pairID][1]),
			movesMade);

		std::vector<std::vector<int>> temp = k.evaluate();

		if (temp.empty())
			continue;

		return temp;
	}
}

Knight::~Knight()
{
}
