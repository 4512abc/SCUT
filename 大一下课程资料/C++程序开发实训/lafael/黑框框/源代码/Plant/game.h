#ifndef GAME_H
#define GAME_H
#include "base.h"
#include "hard.h"
#include "storage.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

class game
{
public:
    game();

    ~game();

    void work();
    //开始游戏
    void userIN();
    //用户登入
private:
    base Base;
    hard Hard;
    storage Storage;
    std::vector<std::vector<string>> user;
};
#endif
