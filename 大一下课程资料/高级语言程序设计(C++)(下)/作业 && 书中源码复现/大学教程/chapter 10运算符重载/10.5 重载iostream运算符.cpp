#ifndef PHONENUMBER_H
#define PHONENUMBER_H
#include <iostream>

class PhoneNumber
{
    friend std::ostream &operator<<( std::ostream &, const PhoneNumber &);
    friend std::istream &operator>>( std::istream &, PhoneNumber &);

private:
    std::string areaCode;
    std::string exchange;
    std::string line;
};//end PhoneNumber class definition

#endif

#include <iomanip>
using namespace std;

//重载<<运算符，如果我们想要用 cout << 或者 cin >>
//则不能声明为成员函数

ostream &operator<<( ostream &output, const PhoneNumber &number )
{
    output << "(" << number.areaCode << ")"
    << number.exchange << "-" << number.line;
    return output;
}
istream &operator>>( istream &input, PhoneNumber &number)
//此处的类对象不能加const否则无法插入值
{
    input.ignore();
    input >> setw( 3 ) >> number.areaCode;
    input.ignore( 2 );
    input >> setw( 3 ) >> number.exchange;
    input.ignore();
    input >> setw( 4 ) >>number.line;
    return input;
}

int main()
{
    PhoneNumber phone;
    cout << "Enter phone number in the form (123) 456-7890:";
    // cin >> phone 调用了重载的运算符>>（ cin，phone )
    cin >> phone;
    cout << "The phone number entered was: ";
    cout << phone << endl;
}
