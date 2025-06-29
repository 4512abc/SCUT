// Exercise 3.16 Solution: HeartRates.h
// HeartRates class for computing target heart rates.
#include <string>
using namespace std;

class HeartRates
{
public:
   // Constructor
   HeartRates( string first, string last, int m, int d, int y )
   {
      setFirstName( first ); // set first name
      setLastName( last ); // set last name
      setBirthMonth( m ); // set month
      setBirthDay( d ); // set day
      setBirthYear( y ); // set year
   } // end constructor

   // set first name
   void setFirstName( string first )
   {
      firstName = first;
   } // end function setFirstName

   // get first name
   string getFirstName()
   {
      return firstName;
   } // end function getFirstName

   // set last name
   void setLastName( string last )
   {
      lastName = last;
   } // end function setLastName

   // get last name
   string getLastName()
   {
      return lastName;
   } // end function getLastName

   // set birth month
   void setBirthMonth( int m )
   {
      birthMonth = m;
   } // end function setBirthMonth

   // get birth month
   int getBirthMonth()
   {
      return birthMonth;
   } // end function getBirthMonth

   // set birth day
   void setBirthDay( int d )
   {
      birthDay = d;
   } // end function setBirthDay

   // get birth day
   int getBirthDay()
   {
      return birthDay;
   } // end function getBirthDay

   // set birth year
   void setBirthYear( int y )
   {
      birthYear = y;
   } // end function setBirthYear

   // get birth year
   int getBirthYear()
   {
      return birthYear;
   } // end function getBirthYear

   // calculate age
   int getAge()
   {
      // if current date has not yet been set, get it from user
      if ( currentYear == 0 )
      {
         cout << "Please enter today's month, day, and year:" << endl;
         cin >> currentMonth >> currentDay >> currentYear;
      } // end if

      if ( currentMonth >= birthMonth )
         if ( currentDay >= birthDay )
            return currentYear - birthYear;

      return currentYear - birthYear - 1;
   } // end function getAge

   // get maximum heart rate
   int getMaximumHeartRate()
   {
      return 220 - getAge();
   } // end function getMaximumHeartRate

   // calculate minimum target heart rate
   int getMinimumTargetHeartRate()
   {
      return 50 * getMaximumHeartRate() / 100;
   } // end function getMinimumTargetHeartRate

   // calculate maximum target heart rate
   int getMaximumTargetHeartRate()
   {
      return 85 * getMaximumHeartRate() / 100;
   } // end function getMaximumTargetHeartRate
private:
   string firstName; // user's first name
   string lastName; // user's last name
   int birthMonth; // user's birth month
   int birthDay; // user's birth day
   int birthYear; // user's birth year
   int currentMonth; // current month
   int currentDay; // current day
   int currentYear; // current year
}; // end class HeartRates


/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
