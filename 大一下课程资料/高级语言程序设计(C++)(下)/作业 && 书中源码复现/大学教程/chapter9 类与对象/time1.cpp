
class Time 
{
    public:
    Time();
    void setTime(int,int,int);
    void printUniversal() const;
    void printStandard() const;
    private:
    unsigned int hour;
    unsigned int minute;
    unsigned int second;

};

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Time.h"

using namespace std;

Time::Time()
   :hour( 0 ),minute( 0 ),second( 0 )
   {
}//end Time constructor

//set new Time value using universal time 
void Time:: setTime(int h ,int m,int s)
{
    //validate hour ,minute and second 
    if ( (h >= 0 && h < 24) && (m >= 0 && m < 60)
              && (0 <= s && s < 60) )
    {
        hour = h;
        minute = m;
        second = s ;

    }
    else
        throw invalid_argument(
        "hour,minute and/or second was out of range"
    );
} //end setTime definition

void Time :: printUniversal( ) const
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

int main ( )
{
    Time t;//create a Time object

    //output Time object t's initial values;

    cout << "The initial universal time is ";
    t.printStandard();//12:00:00 AM 

    t.setTime( 13 , 27 , 6 );// change time 
    
    //输出新的时间
    cout<< "\n\n Universal time after setTime is ";
    t.printUniversal();

    cout <<"\n Standardtime after setTime is";
    t.printStandard();

    //attempt to set the time with invalid values

    try
    {
        t.setTime( 99, 99, 99 );
    } // end try
    catch ( invalid_argument &e )
    {
        cout << "Exception : " << e.what() << endl ;
    }

    cout <<" \n\nAfter attempting invalid settings :"
      << "\n Universal time : ";
      t.printUniversal();
    cout << " \n Standard time : ";
    t.printStandard();
    cout << endl;
    cout << "please enter the time now \n";
}//end main