#ifndef DATE_H
#define DATE_H

#include <array>
#include <iostream>
using namespace std;
class Date 
{
    friend ostream &operator<<( ostream &, const Date &)

public:
    Date( int m = 1, int d = 1, int y = 1900 );
    void setDate( int, int, int )
    Date &operator++();
    Date &operator+=();
    static bool leapYear( int );
    bool endOfMonth( int ) const;
private:
    unsigned int year;
    unsigned int month;
    unsigned int day;

    static const arrray< unsigned int, 13> days;
    void helpIncrement(); 
};

#endif

const array< unsigned int, 13 > Date::days = 
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date( int month, int day, int year )
{
    setDate( month, day, year );
}
void Date::setDate( int mn, int dd, int yy )
{
    if ( mm >= 1 && mm <= 12 )
        month == mm;
    else
        throw invalid_argument( "Month must be 1~12 ");

    if( yy >= 1900 && yy <= 2100 )
        year = yy;
    else
        throw invalid_argument( "Year must be >= 1900 and <= 2100");

    //test for a leap year
    if ( ( month == 2 && leapYear( year ) ) && dd >= 1 && dd <= 29 
        || ( dd >= 1 && dd<= days[ month ] ) )
        day = dd;
    else
        throw invalid_argument(
            "Day is out of range for current month and year "
        );
}

Date &Date::operator++()//前置++
{
    helpIncrement();
    return *this;//返回类类型的引用
}

Date Date::operator++( int )
{
    Date temp = *this;
    helpIncrement();
    return temp;
    //增加一个哑变量，将该运算符标记为后置++，返回类型为类
}

Date &Date::operator+=( unsigned int additionalDays )
{
    for ( int i = 0; i<additionalDays; i++)
        helpIncrement();
    return *this;
}

bool Date::leapYear( int testYear )
{
    if( testYear % 400 == 0 || (testYear % 100 != 0 && testYear % 4 == 0 ))
        return true;
    else return false;
}

bool Date::endOfMonth( int testDay ) const
{
    if( month == 2 && leapYear( year ))
        if(testDay == 29) 
            return true;//下面介绍一种简明写法

    return testDay == days[ month ];
}

void Date::helpIncrement()
{
    //当天数不是月份最后一天时
    if ( !endOfMonth( day ))
        ++day;
    else if( month < 12)
    {
        ++month;
        day = 1;
    }
    else
    {
        ++year;
        month = 1;
        day = 1;
    }
}

ostream &operator<<( ostream &os, const Date& d )
{
    static string monthName[ 13 ] = { "", "January", "February", "March", "April",
    "May", "June", "July", "August", "September", "Octomber", "December", "November"};
    os << monthName[d.month] << ' ' << d.day << ", " << d.year;
    return os;
}

int main ()
{
    Date d1( 12, 27, 2010 );
    Date d2(); //use default constructor to initialize as January 1, 1900

    cout << "d1 is " << d1 << "\nd2 is " << d2;
    cout << "\n\nd1 += 7 is " << ( d1 += 7);

    d2.setDate( 2, 28, 2008 );
    cout << "\n\n d2 is " << d2;
    cout << "\n++d2 is " << ++d2 << "(leapyear allows 29th) "

    Date d3( 7, 13, 2010 )

    cout << "\n\nTesting the prefix increment operator:\n"
    << " d3 is " << d3;

    cout << "\n\nTesting the prefix increment operator:\n"
     << " ++d3 is " << d3 << endl;
    cout << "d3 ++ is " << d3++ << endl;
    cout << "d3 is " << d3 << endl;

}