#include <iostream>
#include <stdexcept>
#include "Time.h"
#include "Time.cpp"
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



}//end main