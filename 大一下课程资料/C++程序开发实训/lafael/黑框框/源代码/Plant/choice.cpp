#include "choice.h"
#include<iostream>
#include<fstream>
using namespace std;
choice::choice() // 为程序入值
{
    ifstream ifs;
    ifs.open("E:/visual stidue/programer/Plant/solve.txt", ios::in);
    if (ifs.is_open())
    {
        for (int i = 0; i < 6; i++)
        {
            ifs.getline(puzzle[i], 78); // 读取每行，确保不超出数组的范围
        }
        ifs.close();
    }
    else
    {
        cout << "文件读取失败" << endl;
    }
    for (int i = 0; i < 7; i++)
        choiced[i] = true;
    width[0] = 11;
    width[1] = 10;
    width[2] = 10;
    width[3] = 9;
    width[4] = 9;
    width[5] = 8;
    width[6] = 6; // 设置字符数，输出时能决定哪些不输
}
choice::~choice() {}
void choice::openchoice()
{
    for (int i = 0; i < 6; i++)
    {
        int sum = 0;
        for (int k = 0; k < 7; k++) // 共七块拼图
        {
            if (choiced[k] == false)
            {
                sum += width[k];
            } // 跳过，++
            else
            {
                for (int j = 0; j < width[k]; j++)
                { // 使用 '\0' 标志行末尾
                    cout << puzzle[i][j + sum];
                } // 输出
                sum += width[k];
            }
        }
        cout << endl;
    }
}
void choice::in_false(int a)
{
    choiced[a - 1] = false;
}
void choice::in_true(int a)
{
    choiced[a] = true;
}
bool* choice::get_choice()
{
    return choiced;
}
