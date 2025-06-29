#include <iostream>
#include <fstream>
#include <iomanip>
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
void outputLine( ostream &, const ClientData & );


int enterChoice();
void createTextFile( fstream& );
void updateRecord( fstream& );
void newRecord( fstream& );
void deleteRecord( fstream& );
int getAccount( const char * const);

enum Choices{ PRINT = 1, UPDATE, NEW, DELETE, END };

int main()
{
    fstream inOutCredit( "credit.dat", ios::in |ios::out | ios::binary )
    ;
    if (!inOutCredit)
    {
        cerr << " File can not be opened ";
        exit (EXIT_FAILURE);
    }

    int choice; //记录用户的选择

    while ( (choice = enterChoice() ) != END)
    {
        switch( choice )
        {
            case PRINT:
                createTextFile( inOutCredit );
                break;
            case UPDATE:
                updateRecord( inOutCredit );
                break;
            case NEW :
                newRecord( inOutCredit );
                break;
            case DELETE :
                deleteRecord( inOutCredit );
                break;
            default:
                cerr << "Incorrect choice " << endl;
                break;
        }

        inOutCredit.clear();//重置inoutcredit对象

    }
}

//让用户能够输入菜单选择项
int enterChoice()
{
    cout << "\nEnter your choice" << endl
        << "1 - 创建新账户列表的文件" << endl
        <<"     called \"print.txt\" for printing" << endl
        << "2 - 更新一个账户" <<endl
        << "3 - 加入一个账户" <<endl
        << "4 - 删除一个账户" << endl
        << "5 - 结束进程\n?" << endl;

        int menuChoice;
        cin >> menuChoice ;
        return menuChoice ;
}

void createTextFile( fstream &readFromFile )
{
    //创建文本文件
    ofstream outPrintFile( "print.txt", ios::out );

    if ( !outPrintFile )
    {
        cerr << "File can not be opened ";
        exit (EXIT_FAILURE);
    }
    //输出表头
    outPrintFile << left << setw(10 )<< "Account"<< setw( 16 )
    << "Last Name" << setw( 11 )<<"First Name" << right
    << setw( 10 )<<"Balance" << endl;

    //将读指针设置到开头
    readFromFile.seekg( 0 );
    //从文件中读取第一条记录
    ClientData client;
    readFromFile.read( reinterpret_cast< char *>(&client), sizeof (ClientData) );

    //将所有的记录文件复制到文本文件
    //调用ifstream函数eof判断是否到文件末尾
    while ( !readFromFile.eof() )
    {
        //将单条记录复制到文本文件
        if ( client.getAccountNumber( ) != 0 )
            outputLine( outPrintFile, client );

        //再读取下一条记录(指针会移动)
        readFromFile.read( reinterpret_cast< char * > (&client), sizeof(ClientData) );

    }
}

void updateRecord( fstream &updateFile )
{
    //获取要更新的账户
    int accountNumber = getAccount( "Enter account to update" );

    //移动指针到正确的记录位置
    updateFile.seekg( (accountNumber - 1) * sizeof(ClientData) );
    //读取该位置第一条记录

    ClientData client;
    updateFile.read( reinterpret_cast < char *>(&client), sizeof( ClientData ) );

    //更新记录
    if ( client.getAccountNumber() != 0 )
    {
        outputLine ( cout, client );

        //让用户选择进行的操作
        cout << "\n请输入数字，正数为充值，负数为支付 ";
        double transaction;
        cin >> transaction;

        double oldBalance = client.getBalance();
        client.setBalance( oldBalance + transaction );
        outputLine( cout, client );

        //移动写入指针位置
        updateFile.seekp( (accountNumber - 1) * sizeof(ClientData) );

        updateFile.write( reinterpret_cast< const char * >( &client ), sizeof(ClientData) );
    }
    else
        cerr << "Account # " << accountNumber << " has no information" << endl;

}

void newRecord( fstream &insertInFile )
{
    int accountNumber = getAccount( "Enter new account number ");

    insertInFile.seekg( (accountNumber - 1) * sizeof( ClientData ) );

    //将文件数据赋给client对象
    //先进行定位，读入，如果是空记录的话client的accountNumber为0
    //如果先前已存在，那么非0，if中的语句不能执行
    ClientData client;
    insertInFile.read( reinterpret_cast< char *>(&client), sizeof(ClientData) );

    //假如该账户先前未存在，创建账户
    if ( client.getAccountNumber() == 0 )
    {
        string lastName;
        string firstName;
        double balance;

        cout << "输入名字、姓氏、余额\n?";
        cin >> setw(15) >> lastName >> setw(10) >> firstName
            >> balance;

        client.setAccountNumber(accountNumber);
        client.setFirstName(firstName);
        client.setLastName(lastName);
        client.setBalance(balance);

        //移动输入指针到要new的位置
        insertInFile.seekp( (accountNumber - 1) * sizeof(ClientData) );
        //数据写入文件
        insertInFile.write( reinterpret_cast< const char *> (&client), sizeof(ClientData) );

    }//end if
    else
        cerr << "Account #" << accountNumber << " has existed "<<endl;
}

void deleteRecord( fstream & deleteFromFile)
{
    int accountNumber = getAccount("Enter account to delete ");

    deleteFromFile.seekg( (accountNumber - 1 ) * sizeof(ClientData) );

    //从文件中读取信息并给client对象
    ClientData client;
    deleteFromFile.read( reinterpret_cast< char * > ( &client ), sizeof(ClientData));

    if( client.getAccountNumber( ) != 0 )
    {
        ClientData blankClient;

        deleteFromFile.seekp( (accountNumber - 1) * sizeof(ClientData) );

        //用空白用户替换掉现有的用户，达到删除的目的
        deleteFromFile.write( reinterpret_cast< const char * > (&blankClient) , sizeof(ClientData) );

        cout << "Account #" << accountNumber << " has been deleted " << endl;

    }
    else  
        cerr << "Account #" << accountNumber << " is empty " << endl;
}

void outputLine( ostream &output, const ClientData& record )
{
    output<< left << setw( 10 ) <<record.getAccountNumber()
          << setw( 16 ) << record.getLastName()
          << setw( 11 ) << record.getFirstName()
          << setw( 10 ) << setprecision( 2 ) <<right << fixed<< showpoint << record.getBalance() <<endl ;
}

int getAccount( const char *const prompt )
{
    int accountNumber;

    do 
    {
        cout << prompt << "(1 ~ 100):";
        cin >> accountNumber;
    } while(accountNumber < 1 || accountNumber > 100 );
    return accountNumber;
}