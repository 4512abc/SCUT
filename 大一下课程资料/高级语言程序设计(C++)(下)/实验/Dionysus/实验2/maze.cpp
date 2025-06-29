#include <iostream>
#include <fstream>
#include "Maze.h"
using namespace std;

enum Direction {DOWN, LEFT, UP, RIGHT};//枚举类型的Direction，表示了方向，利于后续switch语句的操作


struct Position //用于表明当前位置的结构体
{
    int H, V;
};

// The maze itself is indicated by # for the walls 
// All other locations in the maze can be any other character
// Global variables defining the maze to be solved

int mazeWidth, mazeHeight;//记录长宽
int *posi;//int型指针，记录走过的位置
char *maze;//char型数组
int i = 0;//记录第i步

// These functions provide access to the maze 找到入口
// as well as provide manipulation of direction  
// of motion and maze location
// See implementation for details  

void FindEntrance(int&);
bool AtExit(int);
// void ReportPosition(int); // Unused function, commented out
void WheresRight(int, Direction, int&);
bool Wall(int);
void TurnRight(Direction&);
void MoveForward(int&, Direction);
void WheresAhead(int, Direction, int&);
void TurnLeft(Direction&);

// This function loads the maze from the specified file
// returning the maze and its dimensions
// The height of the maze is not actually used anywhere but here

bool LoadMaze(const char fname[]) //传入一个char数组类型的文件名，载入迷宫
{
    ifstream ifs(fname);//创建ifstream类型的对象，打开文件

    if (ifs.good())//检查文件流是否处于良好状态的方法。如果文件流没有错误，那么 ifs.good() 将返回 true。否则，如果有错误发生，它将返回 false 通常在读入或写入文件之后调用，判断是否出错
                    //文件流为绝对路径格式，不带引号，\分隔
    {
        ifs >> mazeWidth >> mazeHeight; //读取文件第一个、第二个数据，即宽度和高度
        maze = new char[mazeWidth * mazeHeight];//动态创建符合文件长宽的迷宫，利用char指针存储
        posi = new int[mazeWidth * mazeHeight];//动态创建符合位置
        for (int i = 0; i < mazeHeight; i++)
            for (int j = 0; j < mazeWidth; j++)
                ifs >> maze[i * mazeWidth + j];//双循环完成迷宫的初始化
        ifs.close();//关闭文件
        return true;//载入成功
    }
    else
    {
        cerr << "File not found." << endl;
        return false;//没有载入成功
    }
}

// This function solves the maze using the 'hand on left wall'
// rule, printing the maze position as it proceeds

void SolveMaze()//找到迷宫的解
{
    int pos, other;//pos记录当前位置
    Direction heading;//Direction枚举类型的对象heading

    FindEntrance(pos);//找到入口位置
    heading = DOWN;//将heading设置为向下
    while (!AtExit(pos))//找到出口，最底端
    {
        posi[i] = pos;
        i++;//计数器，将第i步的位置pos传到posi数组，便于后续输出迷宫路径
        if (i >= mazeWidth*mazeHeight)//步数大于了迷宫格子数
        {
            cout << "array too small\n";
            abort();//终止程序
        }
        WheresRight(pos, heading, other);//找到右侧
        if (!Wall(other))//如果当前右侧不是墙
        {
            TurnRight(heading);//转向右侧
            MoveForward(pos, heading);//向前走
        }
        else//如果是墙
        {
            WheresAhead(pos, heading, other);//找到前进方向
            if (!Wall(other))
                MoveForward(pos, heading);//向前走
            else//如果还是墙
                TurnLeft(heading);//向左转
        }
    }
    posi[i] = pos;
    i++;//完成步数自增以及位置输入
    if (i >= mazeHeight*mazeWidth)//再进行一次步数判断
    {
        cout << "array too small\n";
        abort();
    }
    int counter = 0;//计步器
    for (int j = 0; j < i; j++)//输出解决路径
    {
        if (posi[j] < 0)
            continue;//跳过不符合的项
        cout << "Current position: (" << posi[j] / mazeWidth << ',' << posi[j] % mazeWidth << ')' << endl;
        counter++;
    }
    cout << "total steps:" << counter << endl;
    cout << "Maze solved" << endl;
    delete maze;
    delete posi;//delete掉动态内存
}

// This function scans the maze array for the first non-wall item
// It assumes that the entrance is in the top row of the maze array

void FindEntrance(int& pos)//找入口
{
    pos = 0;
    while (Wall(pos)) pos++;//遍历，找到非墙的入口为止，记录位置
}

// This function returns true if the maze position is the exit
// identified by being in the last row of the array

bool AtExit(int pos)//判断出口
{
    return (pos >= (mazeHeight - 1) * mazeWidth);//到了最底端
}

// This function takes a maze position and a heading and determines
// the position to the right of this position

void WheresRight(int pos, Direction heading, int& right)//一个当前位置，一个方向，一个记录右侧位置
{
    right = pos;//记录当前位置
    switch (heading)//选择方向
    {
    case DOWN:
        {
            right--;
            break;
        }
    case LEFT:
        {
            right -= mazeWidth;
            break;
        }
    case UP:
        {
            right++;
            break;
        }
    case RIGHT:
        {
            right += mazeWidth;
        }
    }
}

// This function returns true if maze position is wall

bool Wall(int pos)//判断是否为墙
{
    return (maze[pos] == '#');
}

// This function changes heading by turning right
// Take current heading and adjust so that direction is to the right
//转向右侧
void TurnRight(Direction& heading)//方向的引用
{
    heading = static_cast<Direction>((static_cast<int>(heading) + 1) % 4);//转向右侧 down left up right
}

// This function changes position in the maze by determining
// the next position in the current direction

//往前走，记录相应数组的变化，其实此时用二维数组会很方便，不过定义了迷宫宽度也还好
void MoveForward(int& pos, Direction heading)//传入位置的引用
{
    switch (heading)
    {
    case DOWN:
        {
            pos += mazeWidth;
            break; 
        }
    case LEFT:
        {
            pos--;
            break;
        }
    case UP:
        {
            pos -= mazeWidth;
            break;
        }
    case RIGHT:
        {
            pos++;
        }
    }
}

// This function determines the position in the direction
// currently heading

void WheresAhead(int pos, Direction heading, int& ahead)//找到下一步是路还是墙
{
    ahead = pos;//当前位置赋给ahead
    switch (heading)
    {
    case DOWN:
        {
            ahead += mazeWidth;
            break;
        }
    case LEFT:
        {
            ahead--;
            break;
        }
    case UP:
        {
            ahead -= mazeWidth;
            break;
        }
    case RIGHT:
        {
            ahead++;
        }
    }
}

// This function changes heading by turning left

void TurnLeft(Direction& heading)//转向左侧
{
    heading = static_cast<Direction>((static_cast<int>(heading) + 3) % 4);
}