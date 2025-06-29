// Exercise 21.30 Solution Part b: ex21_30b.cpp
// Printing the characters corresponding to ASCII codes 0�255.
#include <iostream> 
#include <iomanip>
using namespace std;

int main()
{
   for ( int c = 0; c <= 255; c++ )
   {
      if ( c % 7 == 0 )
         cout << '\n';

      cout << setw( 6 ) << c << setw( 3 ) << static_cast< char > ( c );
   } // end for

   cout << endl;
} // end main 


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
 *************************************************************************/
