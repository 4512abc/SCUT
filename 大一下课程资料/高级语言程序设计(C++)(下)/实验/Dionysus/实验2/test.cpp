#include <iostream>
#include "Maze.h"
#include "maze.cpp"
using namespace std;

int main()
{	
	char fname[64];
	
	cout << "Maze File: ";
	cin >> fname;
	if (LoadMaze(fname))
		SolveMaze();
	return 0;
}
