#include <iostream>
#include <fstream>
#include "game.h"
using namespace std;
int main()
{
    srand(time(0));
    game game;
    game.work();
    system("pause");
}