#ifndef MAP_H
#define MAP_H

#include "choice.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

class map
{
public:
    map();
    ~map();
    virtual void work(int);//int对应地图---base

    void show();//具体玩法---all

    void mapread(int);//读取文件内原始数据---base

    void auto_map(int*);//自动生成地图---hard

    void showuse();//打印用户的作图(当前关卡)---打印

    void showall();//打印全部地图（1张），未来可增加模式为全览（4张）---打印
    
    choice& re_choice();//返回拼图---返回

    char* re_map();//返回地图---返回

    int* re_solution();//返回解法---返回

    void delemap();//初始化noticemap的函数---初始化

    void delework();//初始化workmap的函数---初始化

    void delenow();//初始化nowmap的函数---初始化

    void putnotice(int);//为左上角的信号灯赋值---赋值

    void revise_now(int, int, int);//通过x，y两个坐标和拼图信息对nowMap赋值---赋值
    
    void putsolution(int, int);//放入解---赋值

    bool check_xy(int, int, int);//对x，y坐标检查---检查

    bool check_choice(int);//检查是否拼图越界---检查

    bool check_map();//检查是否完成---检查


    void help();//给出提示

    void record(int,int,int);//记录历史

    void reset();//复现历史
private:
    choice choice;

    char workMap[6 * 6];//六副关卡图，右下角

    int nowMap[6 * 6];//做题图，左下角

    int choice_map[6 * 6];//记录位点的图

    char notice_map[6 * 6];//记录可放入拼图的信号的图，右上

    int solution[7];//解的数组

    vector <int> choiceHistory;//解的历史，回溯

    vector<int> postHistory;//位点的历史，回溯

    vector<vector<int>> pastMap;//过去的点位
};
#endif