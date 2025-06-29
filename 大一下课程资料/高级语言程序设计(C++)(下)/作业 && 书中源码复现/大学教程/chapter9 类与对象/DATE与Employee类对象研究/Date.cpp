//member function definition

#include <array>
#include <iostream>
#include <stdexcept>
#include "date.h"
using namespace std;

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