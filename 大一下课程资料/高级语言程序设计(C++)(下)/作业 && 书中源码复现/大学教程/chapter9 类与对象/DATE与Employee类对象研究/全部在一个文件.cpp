#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#ifndef DATE_H
#define DATE_H

class Date
{
public:
    static const unsigned int monthsPerYear = 12;
    //months in a year
    explicit Date( int = 1, int =1 ,int = 1900);
    //default constructor;
    void print( ) const;//打印日期

    ~Date();

private :
    unsigned int month ;
    unsigned int day ;
    unsigned int year;

    unsigned int checkDay ( int ) const;

};

#endif



//Employee类定义展示了“组成”的概念

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
public:
    Employee( const std::string &, const std::string &,
            const Date &, const Date &);
    void print() const;
    ~Employee();//满足确定析构命令执行的需要
private:
    std::string firstName;
    std::string lastName;
    const Date birthDate;
    const Date hireDate;
};

#endif

//member function definition


//让构造函数确定有效的月份，checkDay函数确定有效的日期

Date::Date( int mn, int dy, int yr )
{
    if( mn >0 && mn <= monthsPerYear)
        month = mn;
    else
        throw invalid_argument("month must be 1-12");
    
    year = yr;
    day=checkDay( dy );

    //当构造函数引用时，输出该对象的日期

    cout << "Date object constructour for date ";
    print();
    cout << endl;

}//end DATE CONSTRUCTOR

//以月/日/年的格式输出日期

void Date::print() const
{
    cout << month << '/' << day << '/' << year;
}

    //当析构函数被引用时，输出对象日期
Date::~Date()
{
    cout << "Date object destructor for date";
    print();
    cout << endl;
}

//基于年份（闰年）月份确定日期是否合理
unsigned int Date::checkDay( int testDay ) const
{
    static const array< int, monthsPerYear + 1 >
    daysPerMonth = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    //决定testDay对于特定的月份是否有效

    if( testDay > 0 && testDay <= daysPerMonth[ month ])
        return testDay;
    
    if( month == 2 && testDay == 29 &&
    ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0)))
        return testDay;

    throw invalid_argument( "Invalid day for current month and year");

}//end function checkDay;



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


int main()
{
    Date birth( 7, 24, 1949 );
    Date hire( 3, 12, 1988 );

    Employee manager( "Bob", "Blue", birth, hire );

    cout << endl;
    manager.print();
}
