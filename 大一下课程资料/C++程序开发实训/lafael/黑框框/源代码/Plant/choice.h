#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;
#ifndef CHOICE_H
#define CHOICE_H
class choice
{
public:
    choice();//创建文件
    ~choice();
    void openchoice();//展示拼图
    void in_false(int);//写入错误信息
    void in_true(int);//写入正确信息
    bool* get_choice();//拿到已选
private:
    char puzzle[6][78];//拼图
    bool choiced[7];//记录已选
    int width[7];//记录宽度

};//选择拼图的类
#endif

