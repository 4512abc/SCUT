#include<iostream>
#include"Employee.h"
#include"date.h"
using namespace std;

//构造函数用初始化列表传递了对象初始化值
Employee::Employee( const string &first, const string &last,
                    const Date &dateOfBirth, const Date &dateOfHire )
        //在原型中引入了Date类对象
        :firstName( first ),
         lastName( last ),
         birthDate( dateOfBirth ),
         hireDate( dateOfHire )
{
    //当构造函数执行时输出信息
    cout << "Employee object constructor: "
    << firstName << ' ' << lastName << endl;

}
void Employee::print() const
{
    cout << lastName << ", " << firstName << " Hired: ";
    hireDate.print();
    cout << " Birthday: ";
    birthDate.print();
    cout << endl ;
}

Employee::~Employee()
{
    cout << "Employee object destructor: "
        << lastName << ", " << firstName << endl;
}