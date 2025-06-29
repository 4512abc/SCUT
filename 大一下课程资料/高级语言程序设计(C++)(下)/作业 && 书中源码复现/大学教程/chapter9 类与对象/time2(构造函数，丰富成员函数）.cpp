#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

#ifndef Time_H
#define Time_H

class Time 
{
public:
    explicit Time( int = 0, int = 0, int = 0);

    //set Functions 
    void setTime(int,int,int);
    void setHour( int );
    void setMinute( int );
    void setSecond( int );

    //get Functions 
    unsigned int getHour() const;
    unsigned int getMinute() const ;
    unsigned int getSecond() const ;


    void printUniversal() const;
    void printStandard() const;
private:
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};
#endif



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


using namespace std;

int main ( )
{
    Time t1;
    Time t2( 2 );
    Time t3( 21, 34 );
    Time t4( 12, 25, 42 );

    cout << "Constructed with:\n\nt1: all arguments defaulted\n  ";
    t1.printStandard();
    cout << "\n  ";
    t1.printUniversal();

    cout << "\n\nt2: hour specified; minute and second defaulted\n  ";
    t2.printStandard();
    cout << "\n  ";
    t2.printUniversal();

    cout << "\n\nt3: second defaulted\n  ";
    t3.printStandard();
    cout << "\n  ";
    t3.printUniversal();

    cout << "\n\nt4: all arguments specified\n  ";
    t4.printStandard();
    cout << "\n  ";
    t4.printUniversal();


    //attempt to set the time with invalid values

    try
    {
        Time t5( 27, 74, 99 );
    } // end try
    catch ( invalid_argument &e )
    {
        cerr << "\n\nException while initializing t5 " << e.what() << endl ;
    }

    Time wakeUp( 6, 45, 0 );
    const Time noon( 12, 0 , 0 );

    wakeUp.setHour( 18 );

    noon.getMinute();
    noon.printUniversal();
    cout << endl;
    noon.printStandard();


}//end main