#include <iostream>
#include "Maze.h"
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

