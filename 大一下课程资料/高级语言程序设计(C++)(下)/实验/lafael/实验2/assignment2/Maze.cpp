/****************************************************
*   Functions to solve mazes.                       *
*                                                   *
*   Datafile must still contain size as first data. *
*                                                   *
*   Four functions are only stubs.                  * 
****************************************************/

#include <iostream>
#include <fstream>
#include "Maze.h"
using namespace std;

//	The following enumerated type indicates directions within the maze

enum Direction {DOWN, LEFT, UP, RIGHT};

//	This struct is used for locations within the maze

struct Position
{
	int H, V;
};

//	The maze itself is indicated by # for the walls
//	All other locations in the maze can be any other character
//	Global variables defining the maze to be solved

char maze[17*17];
int mazeWidth, mazeHeight;
int posi[17*17];
int i=0;
//	These functions provide access to the maze
//	as well as provide manipulation of direction
//	of motion and maze location
//	See implementation for details

void FindEntrance(int&);
bool AtExit(int);
void ReportPosition(int);
void WheresRight(int,Direction,int&);
bool Wall(int);
void TurnRight(Direction&);
void MoveForward(int&,Direction);
void WheresAhead(int,Direction,int&);
void TurnLeft(Direction&);

//	This function loads the maze from the specified file
//	returning the maze and its dimensions
//	The height of the maze is not actually used anywhere but here

bool LoadMaze(const char fname[])
{
	ifstream ifs(fname);
	
	if (ifs.good())
	{
		ifs >> mazeWidth >> mazeHeight;
		for (int i=0;i<mazeHeight;i++)
			for (int j=0;j<mazeWidth;j++)
				ifs >> maze[i*mazeWidth+j];
		ifs.close();
		return true;
	}
	else
	{
		cerr << "File not found." << endl;
		return false;
	}
}

//	This function solves the maze using the 'hand on left wall'
//	rule, printing the maze position as it proceeds

void SolveMaze()
{	
	int pos, other;
	Direction heading;
	
	FindEntrance(pos);
	heading = DOWN;
	while (!AtExit(pos))
	{
		posi[i]=pos;
		i++;
		if(i>=289)
		{
			cout<<"array too small\n";
			abort();
		}
		WheresRight(pos,heading,other);
		if (!Wall(other))
		{
			TurnRight(heading);
			MoveForward(pos,heading);
		}
		else
		{
			WheresAhead(pos,heading,other);
			if (!Wall(other))
				MoveForward(pos,heading);
			else
				TurnLeft(heading);
		}
	}
	posi[i]=pos;
	i++;
	if(i>=400)
	{
		cout<<"array too small\n";
		abort();
	}
	int counter=0;
	for(int j=0;j<i;j++)
	{
		if(posi[j]<0)
			continue;
		cout << "Current position: (" << posi[j]/mazeWidth << ',' << posi[j]%mazeWidth << ')' << endl;
		counter++;
	}
	cout<<"total steps:"<<counter<<endl;
	cout << "Maze solved" << endl;
}

//	This function scans the maze array for the first non-wall item
//	It assumes that the entrance is in the top row of the maze array
	
void FindEntrance(int& pos)
{
	pos= 0;	
	while (Wall(pos)) pos++;
}

//	This function returns true if the maze position is the exit
//	identified by being in the last row of the array

bool AtExit(int pos)
{
	return (pos >= (mazeHeight-1)*mazeWidth);
}

//	This function displays the position in the maze
//	At this time it specifies row and column of the array

/*void ReportPosition(int pos)
{
	cout << "Current position: (" << pos/mazeWidth << ',' << pos%mazeWidth << ')' << endl;
}*/

//	This function takes a maze position and a heading and determines
//	the position to the right of this position

void WheresRight(int pos, Direction heading, int& right)
{
	right=pos;
	switch (heading) 
	{
	case DOWN:
		{
			right--;
			break;
		}
	case LEFT:
		{
			right-=mazeWidth;
			break;
		}
	case UP:
		{
			right++;
			break;
		}
	case RIGHT:
		{
			right+=mazeWidth;
		}
	}

}

//	This function returns true if maze position is wall

bool Wall(int pos)
{
	return (maze[pos] == '#');
}

//	This function changes heading by turning right
//	Take current heading and adjust so that direction is to the right

void TurnRight(Direction& heading)
{
	//to be finished.
}

//	This function changes position in the maze by determining
//	the next position in the current direction

void MoveForward(int& pos, Direction heading)
{
	//to be finished.
}

//	This function determines the position in the direction
//	currently heading

void WheresAhead(int pos, Direction heading, int& ahead)
{
	//to be finished.
}

//	This function changes heading by turning left

void TurnLeft(Direction& heading)
{
	//to be finished.
}
