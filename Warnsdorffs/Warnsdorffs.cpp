// Warnsdorffs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Knight.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <Windows.h>



using namespace std;


int main()
{
	Knight k = Knight(3, 3);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	vector<vector<int>> ev = k.evaluate();

	for (int i = 0; i < ev.size(); i++) {
		for (int j = 0; j < ev.at(i).size(); j++) {
			SetConsoleTextAttribute(hConsole, 8 + ev.at(i).at(j) / 10);
			cout << setw(4) << ev.at(i).at(j) << "  ";
		}
		cout << endl << endl;
	}

	system("pause");
    return 0;
}

