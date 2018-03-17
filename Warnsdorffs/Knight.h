#pragma once

#define TABLE_SIZE 8
#define MOVE_SIZE 8

#define PAIR 2

#include <vector>

class Knight
{

private: 
	struct Position {
		int x, y;

		Position() {}
		Position(int i, int j) {
			x = i;
			y = j;
		}
	};
	
	struct MoveOrder {
		int movesPossible; // lower is better
		int pairID;

		MoveOrder(int i, int id) {
			this->movesPossible = i;
			this->pairID = id;
		}
	};

private:

	Position pos;
	std::vector<std::vector<int>> table;
	std::vector<MoveOrder> moveOrder;

	int movesMade;

	void initializeVector();
	void makeMove();

	void setMoveOrder();

	int checkMoves(int, int);
	bool checkConstraints(int);

public:
	Knight(int, int);
	Knight(std::vector<std::vector<int>>, Position, int);
	~Knight();

	std::vector<std::vector<int>> evaluate();
};

