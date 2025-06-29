#include "Map.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;
map::map() 
// 构造，开自定义数组
{
    postHistory = vector<int>(7,-1);

    for (int j = 0; j < 36; j++)
        workMap[j] = '0'; 
    // 初始化地图

    for (int i = 0; i < 36; i++)
    {
        nowMap[i] = 0;
    } 
    // 初始化做题板

    for (int i = 0; i < 6;i++)
    {
        for (int j = 0; j < 6; j++)
        {
            choice_map[i * 6 + j] = j;
        }
    } 
    // 初始化可放入拼图的信号的图

    for (int i = 0; i < 36; i++)
    {
        notice_map[i] = ' ';
    } 
    // 初始化记录放入拼图的图

    for (int i = 0; i < 7; i++)
    {
        solution[i] = 0;
    }
}; 
// 输入流读取文件

map::~map() 
{
};

void map::work(int n)
{
    cout << "读取文件" << endl;
}

void map::show()
{
    cout << "打印地图" << endl;
    showall();
    //打印地图

    cout << "开始做答吧" << endl;
    //开始循环

    bool tips = true;

    for (; choiceHistory.size() < 7;)
    {
        int num;
        cout << "打印拼图" << endl;
        re_choice().openchoice();
        //每回合的更新地图

        cout << "需要提示吗，是则输入y，否则输入n"<<endl;
        char empt;
        cin >> empt;
        //进行选择

        if (empt == 'y')
        {
            cout << "接下来是提示内容，勿外传" << endl;
            help();
            cout << "提示结束" << endl;
        }
        else
        {
            cout << "那么开始游戏吧" << endl;
        }

        cout << "需要回溯吗，是则输入y，否则输入n" << endl;

        cin >> empt;
        //进行选择

        if (empt == 'y')
        {
            cout << "将回到上一次保存数据的时间点" << endl;
            if (tips = true)
                cout << "若没有保存过数据，回溯将无法进行" << endl;
            reset();
        }
        else
        {
            cout << "那么开始游戏吧" << endl;
        }
        //回溯结束

        cout << "那么,在这次的放置，你要选择哪个拼图？" << endl;
        cin >> num;
        //选择拼图

        if (num > 8 || num < 1) 
            // 越界判断
        {
            cout << "没有这么多的拼图,请按图示控制在1~7内" << endl;
            cout << "请重新输入" << endl;
            cin >> num;
        }
        if (!check_choice(num))
        {
            cout << "该拼图已选，请重新选择" << endl;
            cin >> num;
        }
        re_choice().in_false(num);
        // 删除已选的拼图,num-1

        putnotice(num);            
        // 生成信号

        showall();
        //弹出总页面

        int posx = 0; 
        int posy = 0;    
        // 记录位置

        if (tips == true)
        {
            cout << "注意：请将拼图左上角填入地图块中含*的位置" << endl;
            cout << "地图有36个区块,打出每个区块的坐标即可,例如(1,1)表示第一个区块" << endl;
        }
        cout << "那么，以x y的形式输入你想要的地区吧" << endl;
        cin >> posx >> posy;
        if (!check_xy(posx, posy, num))
        {
            cout << "错误坐标，请重试" << endl;
            cin >> posx >> posy;
        }
        //修正

        record(posx, posy, num);
        //x-1,y-1

        revise_now(posx, posy, num);
        cout << "操作完毕，请看图" << endl;
        //结束

        delemap();
        //清空警示

        showall();
        //显示图片

        if (tips == true)
        {
            cout << "注意：当你认为完成拼图或无法继续时，可以通过输入退出" << endl;
            tips = false;
        }
        cout << "输入y以结束游戏，系统会进入判断。反之输入n，游戏继续，直到七张拼图全部用完" << endl;
        char or_yn;
        cin >> or_yn;
        if (or_yn == 'y')
            break;
    }
    if (check_map())
    {
        cout << "恭喜你，你赢了！" << endl;
    }
    else
    {
        cout << "你输了，再接再厉" << endl;
    }
}

void map::mapread(int n)
{

    ifstream ifs;
    ifs.open("E:/visual stidue/programer/Plant/original.txt", ios::in);
    ifs.seekg(36 * (n - 1), ios_base::beg);
    if (ifs.is_open())
    {
        for (int j = 0; j < 36; j++)
            ifs >> workMap[j]; 
        // 读取每行，确保不超出数组的范围

        ifs.close();
    }
    else
        cout << "文件打开失败" << endl;
    //读取地图
    ifstream sfs;
    sfs.open("E:/visual stidue/programer/Plant/solution.txt", ios::in);
    if (sfs.is_open())
    {
        int empt = 0;
        for (int i = 0; i < 7 * (n - 1); i++)
        {
            sfs >> empt;
        }
        cout << 1;
        for (int j = 0; j < 7; j++)
        {
            ifs >>solution[j];
        }
        sfs.close();
        cout << 1;
    }
    else
        cout << "文件打开失败" << endl;
    //读取解

}

choice& map::re_choice()
{
    return choice;
}

void map::showuse()
{
    for (int i = 0; i < 36; i++)
    {
        if (i == 0)
            cout << "- - - - - - - - -" << endl;
        if (i % 6 == 0)
            cout << "|  ";
        cout << nowMap[i] << " ";
        if (i % 6 == 5)
            cout << " |" << endl;
    }
    cout << "- - - - - - - - -" << endl;
}

void map::delemap()
{
    for (int i = 0; i < 36; i++)
    {
        notice_map[i] = ' ';
    } 
    // 初始化记录放入拼图的图
}

void map::showall()
{
    for (int i = 0; i < 6; i++) // 打印行数
    {
        if (i % 2 == 0)
        {
            cout << "- - - - - - - - - - - - - - - - - - -" << endl;
        }
        else if (i % 2 == 1)
            cout << "- - - - - - - - - - - - - - -  - - -" << endl; // 边框打印
        cout << "| ";
        for (int j = i * 6; j < i * 6 + 6; j++)
            // 打印列数
        {
            cout << notice_map[j] << " " << choice_map[j];
            cout << " | ";
        }
        cout << endl;
        cout << "| ";
        for (int j = i * 6; j < i * 6 + 6; j++) 
            // 打印列数
        {
            cout << nowMap[j] << " " << workMap[j];
            cout << " | ";
        }
        cout << endl;
    }

    cout << "- - - - - - - - - - - - - - -  - - -" << endl;
    // 边框打印
}

void map::putnotice(int a)
{
    switch (a)
    {
    case 7:
    case 6:
        for (int i = 0; i < 36; i++)
            notice_map[i] = '*';
        break;
    case 5:
    case 4:
        for (int i = 0; i < 30; i++)
        {
            if (i % 6 != 5)
                notice_map[i] = '*';
            else
                notice_map[i] = ' ';
        }
        break;
    case 3:
    case 2:
        for (int i = 0; i < 24; i++)
        {
            if (i % 6 < 4)
                notice_map[i] = '*';
            else
                notice_map[i] = ' ';
        }
        break;
    case 1:
        for (int i = 0; i < 18; i++)
        {
            if (i % 6 < 3)
                notice_map[i] = '*';
            else
                notice_map[i] = ' ';
        }
        break;
    }
}

void map::revise_now(int y, int x, int n) 
// 左上角为参考系，赋值要向下衍生
{
    switch (n)
    {
    case 7:
    case 6:
        nowMap[(y - 1) * 6 + (x - 1)]++;
        break;
    case 5:
    case 4:
        nowMap[(y - 1) * 6 + (x - 1)]++;
        nowMap[(y - 1) * 6 + (x)]++;
        nowMap[(y) * 6 + (x - 1)]++;
        nowMap[(y) * 6 + (x)]++;
        break;
    case 3:
    case 2:
        for (int i = 0; i < 3; i++) 
            // 9格有点多，循环吧
        {
            nowMap[(y - 1) * 6 + (x - 1 + i)]++;
            nowMap[(y) * 6 + (x - 1 + i)]++;
            nowMap[(y + 1) * 6 + (x - 1 + i)]++;
        }
        break;
    case 1:
        for (int i = 0; i < 4; i++) 
            // 16格有点多，循环吧
        {
            nowMap[(y - 1) * 6 + (x - 1 + i)]++;
            nowMap[(y) * 6 + (x - 1 + i)]++;
            nowMap[(y + 1) * 6 + (x - 1 + i)]++;
            nowMap[(y + 2) * 6 + (x - 1 + i)]++;
        }
        break;
    }
}

char* map::re_map()
{
    return workMap;
}

bool map::check_xy(int x, int y, int n)
// 判断解
{
    switch (n)
    {

    case 5:
    case 4:
        if (x== 6 || y == 6)
            return false;
        else
            return true;
    case 3:
    case 2:
        if (x > 4 || y > 4)
            return false;
        else
            return true;
    case 1:
        if (x  > 3 || y  > 3)
            return false;
        else
            return true;
    }
    return true;
}

bool map::check_choice(int n)
{
    bool* a = choice.get_choice();
    if (a[n - 1] == false)
        return false;
    return true;
}

bool map::check_map()
{
    for (int i = 0; i < 36; i++)
    {
        switch (workMap[i])
        {
        case 'A':
            if (nowMap[i] != 1 && nowMap[i] != 3)
                return false;
            break;
        case '%':
            if (nowMap[i] != 4)
                return false;
            break;
        case 'O':
            if (nowMap[i] != 2 && nowMap[i] != 0)
                return false;
            break;
        case 'X':
            if (nowMap[i] != 0)
                return false;
            break;
        }
    }

    return true;
}

void map::auto_map(int* solve)
{
    for (int i = 0; i < 7; i++)
    {
        int empt = solve[i];
        // 拿到随机到的结果

        switch (i+1)
        {
        case 7:
        case 6:
            workMap[empt]++;
            break;
        case 5:
        case 4:
            workMap[empt]++;
            workMap[empt + 1]++;
            workMap[empt + 6]++;
            workMap[empt + 7]++;
            break;
        case 3:
        case 2:
            for (int i = 0; i < 3; i++) 
                // 9格有点多，循环吧
            {
                workMap[empt + i]++;
                workMap[empt + 6 + i]++;
                workMap[empt + 12 + i]++;
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) 
                // 16格有点多，循环吧
            {
                workMap[empt + i]++;
                workMap[empt + 6 + i]++;
                workMap[empt + 12 + i]++;
                workMap[empt + 18 + i]++;
            }
            break;
        }
    }
}

void map::putsolution(int a, int n)
{
    solution[n] = a;
}

int* map::re_solution()
{
    return solution;
}

void map::delework()
{
    for (int i = 0; i < 36; i++)
        workMap[i] = '0';
}

void map::delenow()
{
    for (int i = 0; i < 36; i++)
    {
        nowMap[i] = 0;
    }
    // 初始化做题板
}

void map::help()
{
    for (int i = 0; i < 7; i++)
    {
        if (solution[i] != postHistory[i])
        {
            int x = solution[i] / 6 + 1;
            int y = solution[i] % 6 + 1;
            cout << "拼图" << i + 1 << "应被放置到"<<solution[i]<<"第" <<x<<"行，第"<<y<<"列";
            return;
        }

    }
    cout << "全部正确，去交卷吧" << endl;

}

void map::record(int posx,int posy,int n)
{
    cout << "存入数据" << endl;
    choiceHistory.push_back(n - 1);
    pastMap.push_back(vector<int>(36,0));
    for(int i=0;i<36;i++)
    {
        pastMap[pastMap.size()-1][i] = nowMap[i];
    }
    postHistory[n - 1] = (posx - 1) * 6 + (posy - 1);
}

void map::reset()
{
    if (pastMap.size() != 0)
    {
        postHistory[choiceHistory.size()-1] = -1;
        choice.in_true(choiceHistory.size()-1);
        choiceHistory.pop_back();
        for (int i = 0; i < 36; i++)
        {
            nowMap[i] = pastMap[pastMap.size()-1][i];
        }
        pastMap.pop_back();
    }
    showall();
    re_choice().openchoice();
}