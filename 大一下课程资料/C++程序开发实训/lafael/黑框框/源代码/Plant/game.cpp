#include "game.h"
using namespace std;
game::game()
{
}

void game::userIN()
{
    user;
    ifstream ifs("E:/visual stidue/programer/Plant/user.txt", ios::out);
    ofstream ofs("temp.txt", ios::out); // 创建一个临时文件
    if (!ofs.is_open() || !ifs.is_open())
    {
        cout << "无法打开文件" << endl;
    }
    int max = 0;
    ifs >> max;
    ofs << max << "\n";
    string empt_1;
    string empt_2;
    for (int i = 0; i < max - 1; i++)
    {
        getline(ifs,empt_1,'\n');
        getline(ifs, empt_2, '\n');
        user[i][0] = empt_1;
        user[i][1] = empt_2;
        ofs << empt_1;
        ofs << empt_2;
    }
    cout << "输入 1 以登入游戏,反之输入 0 进行注册" << endl;
    int empt = 2;
    cin >> empt;
    if (empt == 0)
    {
        cout << "那么,请依次输入账号名称和密码" << endl;
        cin >> empt_1;
        cin >> empt_2;
        ofs << empt_1;
        ofs << empt_2;
        cout << "创建成功，可以进入游戏了" << endl;
        system("pause");
        work();
    }
    else
    {
        cout << "那么,请依次输入账号名称和密码" << endl;
        cin >> empt_1;
        cin >> empt_2;
        for (int i = 0; i < max; i++)
        {
            if (user[i][0] == empt_1 && user[i][1] == empt_2)
            {
                cout << "登入成功，可以进入游戏了" << endl;
                system("pause");
                work();
                break;
            }
        }
        cout << "登入失败，请重新输入" << endl;
        
    }
    ofs.close();
    ifs.close();
    remove("E:/visual stidue/programer/Plant/autocreate.txt");
    rename("temp.txt", "E:/visual stidue/programer/Plant/autocreate.txt");
}

void game::work()
{
    char mode;
    cout << "欢迎进入拼图游戏" << endl;
    cout << "你可以选择关卡模式或挑战模式" << endl;
    cout << "1.关卡模式" << endl;
    cout << "2.挑战模式" << endl;
    cin >> mode;
    if (mode == '1')
    {
        Base.work();
    }
    else if (mode == '2')
    {
        Hard.work();
    }
    else if(mode=='3')
    {
        Storage.work();
    }
    else
    {
        cout << "错误的输入" << endl;
    }
} 
// 开始游戏

game::~game() {} // 析构