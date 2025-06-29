#include "hard.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;
hard::hard()
{ // 1 2--0 1--2
    number = {
        {0, 1, 2, 6, 7, 8, 12, 13, 14},
        {0, 1, 2, 3, 6, 7, 8, 9, 12, 13, 14, 15, 18, 19, 20, 21},
        {0, 1, 2, 3, 6, 7, 8, 9, 12, 13, 14, 15, 18, 19, 20, 21},
        {0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28},
        {0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35} };
}
// l,r
// int mid(l+r)/2
// if a[mid]>x l=mid+1

hard::~hard() {} 
// 析构

void hard::work()
// 结果都会导入一张难度地图
{
    cout << "欢迎进入挑战模式" << endl;
    cout << "请选择子模式" << endl;
    int a = 0;
    cout << "1.系统模式：由系统出题" << endl;
    cout << "2.创作模式：用户自定义地图" << endl;
    cin >> a;
    if (a == 1)
    {
        cout << "接下来系统将生成随机地图" << endl;
        autocreate();
        delenow();
        //初始化

        //show();
        sto_auto();
    }

    else if(a==2)
    {
        cout << "接下来你将自定义地图" << endl;
        cout << "请输入A（1或3），%（4），O（0或2），X（0）以表示你的地图" << endl;
        cout << "共计要输入36位" << endl;
        custom(re_map());
        show();
    }

    else
    {
        cout << "输入错误" << endl;
    }

}
void hard::autocreate() 
// 获得随机数，得到x，y坐标，写入地图
{
    int pos4 = 0;
    int autopost[5] = {}; 
    // 随机到了那副拼图

    int autoposi[8] = {}; 
    // 记录哪副没有被随机,方便check

    int onerand = 0;
    for (;;)
    {
        pos4 = rand() % 36 + 1;
        //核心位点4

        for (int i = 1; i <= 4; i++)
        {
            for (;;)
            {
                onerand = rand() % 7 + 1;
                if (recheck(autopost, onerand))
                break;
            }
            autopost[i] = onerand; // 1~7
            autoposi[autopost[i]]++;
        }
        // 得到一个不重复的数组

        autochoice(autopost, pos4); 
        // 对以上四个解得到结果

        for (int i = 1; i <= 7; i++)
        {
            if (autoposi[i] != 1)
            {
                int erand = rand() % (number[i - 1].size());
                putsolution(erand, i - 1); 
                // 得到随机数
            }
        }

        auto_map(re_solution());

        if (endcheck(re_map()))
        {
            mark(re_map());
            break;
        }
        else
        {
            for (int i = 1; i <= 7; i++)
            {
                autoposi[i] = 0;
            }
            delework();
        }
    }
} // 先得到随机的要合成“4”的拼图和位置，然后随机剩余的，最后根据随机的记录生成work。
void hard::autochoice(int* autopost, int pos4)
{           
    // 以pos4作为能覆盖区域的最大值，最小值选择

    for (int i = 1; i <= 4; i++) 
        // 判断choice是否覆盖
    {
        int findmax = checkchoice(number[autopost[i] - 1].data(), number[autopost[i] - 1].size() - 1, pos4);
        // 拿到最大位置对应的索引

        int findmin = 0; 
        // 得到最小位置

        int erand = 0;   
        // 最后的随机

        switch (autopost[i])
        {
        case 7:
        case 6:
            erand = pos4;
            putsolution(erand, autopost[i] - 1); // 7，6在number中的上下限为1
            break;
        case 5:
        case 4: 
            // 重构得到最小位置

            findmin = findmax - 6;
            if (findmin < 0)
                findmin = 0; 
            // 移动到指定位置（左上角

            erand = rand() % (findmax - findmin) + findmin;
            putsolution(number[autopost[i]-1][erand], autopost[i] - 1);
            break;

        case 3:
        case 2:
            findmin = findmax - 4; 
            // 移动到指定位置（左上角

            if (findmin < 0)
                findmin = 0;

            erand = rand() % (findmax - findmin) + findmin;
            putsolution(number[autopost[i] - 1][erand], autopost[i] - 1);

            break;
        case 1: 
            // 重构得到最小位置

            findmin = findmax - 4;
            if (findmin < 0)
                findmin = 0; 
            // 移动到指定位置（左上角

            erand = rand() % (findmax - findmin) + findmin;
            putsolution(number[autopost[i] - 1][erand], autopost[i] - 1);
            break;
        }
    }
}
int hard::checkchoice(int* a, int end, int c) 
// 得到位置“4”的地点
{                                             
    // 二分查找
    int str = 0;
    int empt = 0;
    for (; str <= end;)
    {
        int min = (str + end) / 2;
        if (a[min] <= c)
        {
            str = min + 1;
            empt = min;
        }
        else
            end = min - 1;
    }
    return empt;
}
bool hard::recheck(int* post,int n)
{

    for (int i = 1; i <= 4; i++)
    {
        if (post[i]==n)
        {
            return false;
        }
    }
    return true;

}
bool hard::endcheck(char* work)
{
    int count = 0;
    //检查是否有4

    for (int i = 0; i < 36; i++)
    {
        if (work[i] > '4')
            return false;
        else if (work[i] == '4')
            count++;
    }

    if (count != 1)
        return false;
    else
        return true;
}
void hard::mark(char* a)
{
    for (int i = 0; i < 36; i++)
    {
        switch (a[i])
        {
        case '0':
        case '2':
            a[i] = 'O';
            break;
        case '1':
        case '3':
            a[i] = 'A';
            break;
        case '4':
            a[i] = '%';
            break;
        }
    }
}
void hard::custom(char* work)
{
    for (int i = 0; i < 36; i++)
    {
        cin >> work[i];
    }
    cout << "输入完毕" << endl;
    cout << "现在你可以进行游戏了" << endl;
}
void hard::sto_auto()
{
    ifstream ifs("E:/visual stidue/programer/Plant/autocreate.txt", ios::out);
    ofstream ofs("temp.txt", ios::out); // 创建一个临时文件
    if (!ofs.is_open()||!ifs.is_open())
    {
        cout << "无法打开文件" << endl;
    }
    int max = 0;
    ifs >> max;
    max++;
    ofs << max<<"\n";
    char empt;
    int num = 0;
    for (int i = 0; i <max-1; i++)
    {
        for (int j = 0; j < 36; j++)
        {
            ifs >> empt;
            ofs << empt;
        }
        for (int j = 0; j < 7; j++)
        {
            ofs << " ";
            ifs >> num;
            ofs << num;
        }
        ofs << "\n";
    }
    char* work = re_map();
    for (int i = 0; i < 36; i++)
    {
        ofs << work[i];
    }
    int *solutions = re_solution();
    for (int i = 0; i < 7; i++)
    {
        ofs << " ";
        ofs << solutions[i]<<" ";
    }
    ofs << "\n";
    // 要写入的新数据
    // 关闭文件
    ofs.close();
    ifs.close();
    remove("E:/visual stidue/programer/Plant/autocreate.txt");
    rename("temp.txt", "E:/visual stidue/programer/Plant/autocreate.txt");
}