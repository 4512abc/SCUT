#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
    //ofstream constructor opens file
    //文件输出流的构造函数打开文件
    ofstream outClientFile( "clients.txt", ios::out );

    //exit program if unable to create file
    //如果不能正常创建文件，结束程序
    if ( !outClientFile ) // 重载的！运算符
    {
        cerr << "File could not be opened " << endl;
        exit( EXIT_FAILURE );
    }

    cout << "Enter the account, name, and balance." << endl
        << "Enter end-of-file to end input.\n?";
        //提示用户输入什么可以结束输入
        //然而根据循环条件
    int account;
    string name;
    double balance;

    while ( cin >> account >> name >> balance )
    {
        cout << "? ";
        outClientFile << account << ' ' << name << ' ' << balance << endl;
    }
}