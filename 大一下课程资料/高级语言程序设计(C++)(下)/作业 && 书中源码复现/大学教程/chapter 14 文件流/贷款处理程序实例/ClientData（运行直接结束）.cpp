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

int main()
{
    ofstream outCredit( "credit.dat", ios::out | ios::binary);
    
    if ( !outCredit )
    {
        cerr << "File can not be opened";
        exit(EXIT_FAILURE);
    }

    ClientData blankClient;

    for ( int i = 0; i < 100 ; i ++)
        outCredit.write( reinterpret_cast< const char * >( &blankClient ),
                            sizeof( ClientData));
                //创建一百条空记录
}