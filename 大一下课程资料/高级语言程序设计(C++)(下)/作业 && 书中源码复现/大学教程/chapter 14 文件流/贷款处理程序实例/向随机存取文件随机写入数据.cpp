#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


#ifndef CLIENTData_H
#define CLIENTData_H

class ClientData
{
public:
    ClientData( int = 0, const string & = "", 
        const string & = "", double = 0.0 );

    void setAccountNumber ( int );
    int getAccountNumber () const;

    void setLastName( const string & );
    string getLastName() const ;

    void setFirstName( const string & );
    string getFirstName() const;

    void setBalance( double );
    double getBalance() const;
private:
    int accountNumber;
    double Balance;
    //此处用char数组，固定住输入的大小
    char lastName[15];
    char firstName[10];
    
};
#endif

ClientData::ClientData(int accountNumberValue, const string &lastName,
            const string &firstName, double balanceValue)
        : accountNumber(accountNumberValue),Balance(balanceValue)
    //此处不用初始化列表初始化姓名，因为要进行大小的限制
    //若accountNumber 和 balance 也需要限制，那同理，运用函数
    {
        setLastName(lastName);
        setFirstName(firstName);
    }
int ClientData::getAccountNumber() const
{
    return accountNumber;
}
void ClientData::setAccountNumber( int AN)
{
    accountNumber = AN;
}
string ClientData::getLastName() const
{
    return lastName;
}
string ClientData::getFirstName() const
{
    return firstName;
}
double ClientData::getBalance() const
{
    return Balance;
}
void ClientData::setLastName( const string &firstnamestring)
{
    int length = sizeof(firstnamestring);
    length = ( length < 10 ? length : 9 );
    firstnamestring.copy( firstName, length );
    firstName[ length ] = '\0';
}
void ClientData::setFirstName( const string &lastNameString )
{
    int length = sizeof(lastNameString);
    length = ( length < 15 ? length : 14);
    lastNameString.copy( lastName, length );//对象与长度
    lastName[ length ] = '\0';
}
void ClientData::setBalance( double balancevalue)
{
    Balance = balancevalue;
}

int main()
{
    //创建接受输入的参数
    int accountNumber;
    string lastName;
    string firstName;
    double balance;

    //创建ofstream流对象
    fstream outCredit ( "credit.dat", ios::in | ios::out | ios::binary );
    //常规判断文件是否能打开
    if ( !outCredit )
    {
        cerr << "File can not be opened ";
        exit(EXIT_FAILURE);
    }

    //先判断账户序列是否在范围
    cout << "Enter account number ( 1 ~ 100 , 0 to end input )\n?";

    ClientData client ;
    cin >> accountNumber;

    //在范围内则继续输入其他参数
    while ( accountNumber > 0 && accountNumber <= 100 )
    {
        cout << "Enter lastname, firstname, balance \n?";
        cin >> lastName >> firstName >> balance;
    
    client.setAccountNumber(accountNumber);
    client.setBalance(balance);
    client.setFirstName(firstName);
    client.setLastName(lastName);

    //利用输出到文件流的seekp函数，定位输出到的定位指针
    //下面参数是账户序列乘以每个账户所需要的大小，故可以定位到该处
    outCredit.seekp( ( client.getAccountNumber() - 1) * sizeof(ClientData) );
    
    //完成定位后开始写入，调用ofstream的write函数
    /*第一个参数是需要写入的字符串，假设client是const char *类型，
        就直接传入client，否则要传入client的引用，再进行强制类型转换
    */
    outCredit.write( reinterpret_cast< const char* >(&client), 
                     sizeof( ClientData ) );
    
    cout << "Enter account number\n?";
    cin >> accountNumber;
    }

}