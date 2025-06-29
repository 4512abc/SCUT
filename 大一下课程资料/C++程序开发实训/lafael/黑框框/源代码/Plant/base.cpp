#include "base.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
base::base() {} // 构造
base::~base() {} // 析构
void base::work()
{
    cout << "欢迎进入关卡模式" << endl;
    cout << "请选择关卡" << endl;
    int n = 0;
    cout << "1.第一关" << endl;
    cout << "2.第二关" << endl;
    cout << "3.第三关" << endl;
    cout << "4.第四关" << endl;
    cout << "5.第五关" << endl;
    cout << "6.第六关" << endl;
    cin >> n;
    mapread(n);
    show();
}