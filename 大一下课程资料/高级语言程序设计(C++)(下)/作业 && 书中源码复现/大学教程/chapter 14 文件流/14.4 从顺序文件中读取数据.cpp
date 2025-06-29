#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void outputLine( int, const string &, double );

int main ()
{

    ifstream inClientFile( "client.txt", ios::in);

    if ( !inClientFile )
    {
        cerr << "File can not be opened " << endl;
        exit( EXIT_FAILURE );
    }

    int account;
    double balance;
    string name;

    cout << left << setw( 10 ) << "Account" << setw( 13 )
    << "Name" << "Balance " << fixed << showpoint;
    //showpoint 可以展示小数点，默认六位有效数字，可以搭配setprecision使用

    while ( inClientFile >> account >> name >> balance )
        outputLine ( account, name, balance );
}

void outputLine( int account, const string &name, double balance )
{
    cout << left << setw(10) << account << setw(13) << name
        << setw(7) << setprecision(2) << right << balance << endl;
}