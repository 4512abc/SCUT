#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "map.h"
using namespace std;
#ifndef HARD_H
#define HARD_H
class hard :public map//系统和自主
{
public:
    hard();
    ~hard();
    virtual void work();//工作安排
    void autocreate();//自动生成地图---赋值
    bool recheck(int[],int);//检查是否重复---检查
    void autochoice(int*, int);//选择合适的区域放置拼图---随机
    int checkchoice(int*, int, int);//二分寻找最优位置---检查
    bool endcheck(char*);//最终检查是否合法---检查
    void mark(char*);//随机生成符号
    void custom(char*);//自定义地图
    void sto_auto();//存储当前地图到autocreate文件
    void sto_cust();//存储当前地图到custom文件
private:
    vector<vector<int>> number;//记录随机地点
};
#endif
