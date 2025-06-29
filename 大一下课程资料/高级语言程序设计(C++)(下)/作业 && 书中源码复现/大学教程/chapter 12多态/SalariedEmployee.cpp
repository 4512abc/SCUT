#include <iostream>
#include "SalariedEmployee.h"
#include "stdexcept"
using namespace std;

//SalariedEmployee类在初始化列表中调用了Employee类的构造函数，将数据作为参数传入
SalariedEmployee::SalariedEmployee( const string &first, const string &last,
                const string &ssn, double salary )
    :Employee( first, last, ssn )
{
    setWeeklySalary( salary );
}

void SalariedEmployee::setWeeklySalary( double salary )
{
    if( salary >= 0.0 )
        weeklySalary = salary;
    else 
        throw invalid_argument( "weekly salary must be >= 0.0 ");
} 

double SalariedEmployee::getWeeklySalary() const 
{
    return weeklySalary;
}

//重载earnings函数，计算工资
double SalariedEmployee::earnings() const
{
    return getWeeklySalary();
}

void SalariedEmployee::print() const
{
    cout << "salaried employee:";
    Employee::print();//用employee基类的print函数打印已有的信息
    cout << "\nweekly salary: " << getWeeklySalary();
}
