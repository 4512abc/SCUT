#include <iostream>
#include <stdexcept>
#include "Employee.h"

CommissionEmployee::CommissionEmployee(
    const string &first, const string &last, 
    const string &snn, double sales, double rate  )
    :FirstName(first),LastName(last),SocialSecurityNumber(snn)
   {
    CommissionEmployee::setGrossSales(sales);
    CommissionEmployee::setCommissionRate(rate);
    }
//set函数定义
void CommissionEmployee::setFirstName( const string &a )
{
    FirstName = a;
}

void CommissionEmployee::setLastName( const string &last)
{
    LastName = last;
}

void CommissionEmployee::setSocialSecurityNumber( const string &snn )
{
    SocialSecurityNumber = snn;
}

void CommissionEmployee::setGrossSales( double sales)
{//要根据实际情况判断sales大小
    if( sales >= 0.0)
        grossSales = sales;
    else 
        throw invalid_argument( "sales must be >= 0.0 ");
}

void CommissionEmployee::setCommissionRate( double rate)
{
    //根据实际情况判断rate
    if( rate >= 0.0 && rate <= 1.0 )
        commissionRate = rate;
    else    
        throw invalid_argument( "rate must be in 0 ~ 1");
}

//get函数定义
string CommissionEmployee::getFirstName() const
{
    return FirstName;
}
string CommissionEmployee::getLastName() const
{
    return LastName;
}
double CommissionEmployee::getCommisionRate() const
{
    return commissionRate;
}
double CommissionEmployee::getGrossSales() const
{
    return grossSales;
}
string CommissionEmployee::getSocialSecurityNumber() const
{
    return SocialSecurityNumber;
}

double CommissionEmployee::earnings() const
{
    return getCommisionRate() * getGrossSales();
}

void CommissionEmployee::print() const
{
    cout << "commission employee: " << getFirstName() << ' ' << getLastName()
    << "\nsocial security number: " << getSocialSecurityNumber()
    <<"\ngross sales: " << getGrossSales()
    << "\ncommission rate " << getCommisionRate();
}


//basaplusCommissionemployee 定义

BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first, const string &last, const string &SocialSecurityNumber,
    double sales, double rate, double salary)   
    : CommissionEmployee( first, last, SocialSecurityNumber, sales, rate )
    //显式调用基类的构造函数来完成子类对象初始化
    {
        setBaseSalary( salary );
    }

void BasePlusCommissionEmployee::setBaseSalary( double salary )
{
    if ( salary >= 0.0 )
        baseSalary = salary;
    else
        throw invalid_argument ( "salary must >= 0");
}
double BasePlusCommissionEmployee::getBaseSalary() const
{
    return baseSalary;
}

double BasePlusCommissionEmployee::earnings() const
{
    return baseSalary +  CommissionEmployee::earnings() ;
}

void BasePlusCommissionEmployee::print() const 
{
    cout << "base-salaried ";
    CommissionEmployee::print();
    cout << "\nbase salary: " << getBaseSalary();
}