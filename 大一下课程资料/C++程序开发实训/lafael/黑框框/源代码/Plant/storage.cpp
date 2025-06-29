#include "storage.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;
storage::storage() {}
storage::~storage() {}
void storage::work()
{
    cout << "欢迎进入存档模式" << endl;
    cout << "请选择存档模式" << endl;
    int a = 0;
    cout << "1.系统存档：由系统出题" << endl;
    cout << "2.创作存档：用户自定义地图" << endl;
    cin >> a;
    if (a == 1)
        ;
    // map.auto_map();
}