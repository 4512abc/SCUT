#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Time.h"

using namespace std;

//Time constructor initializes each data number 
Time::Time(int hour, int minute, int second )
   {
    setTime( hour, minute, second);//构造对象并设置时间
   }//end Time constructor

//set new Time value using universal time 

//set Functions
void Time::setTime(int h ,int m,int s)
{
    setHour( h );
    setMinute( m );
    setSecond( s );
} //end setTime definition
void Time::setHour( int h )
{
    if ( h >= 0 && h < 24 )
    hour = h;
    else 
    throw invalid_argument( "hour must be 0~23" );
}

void Time::setMinute( int m )
{
    if( m >= 0 && m < 60)
    minute = m;
    else 
    throw invalid_argument( "minute must be 0~59" );
}
void Time::setSecond( int s )
{
    if( s >=0 && s<60 )
    second = s ;
    else
    throw invalid_argument( "second must be 0~59" );
}

//get Functions 
unsigned Time :: getHour() const
{
    return hour ;
}
unsigned Time :: getMinute() const
{
    return minute ;
}
unsigned Time :: getSecond() const 
{
    return second;
}


void Time::printUniversal( ) const
{
    cout << setfill( '0' ) << setw( 2 )<< hour << ":"
    << setw( 2 ) << minute << ":" << setw( 2 ) << second;
}//end function printUniversal

void Time :: printStandard( ) const 
{
    cout << (( hour == 0 || hour == 12) ? 12 : hour % 12) << 
    ":" << setfill( '0' ) << setw( 2 ) << minute << ":" << setw( 2 )
    << second << ( hour < 12 ? " AM " : " PM ");
}//end function difinition;