// Exercise 5.27 Solution: ex05_27.cpp
// Structured equivalent for continue statement.
#include <iostream>
using namespace std;

int main()
{
   for ( int count = 1; count <= 10; count++ ) // loop 10 times
   {
      if ( count != 5 ) // if count == 5, skip to next iteration
         cout << count << " ";
   } // end for

   cout << "\nUsed if condition to skip printing 5" << endl;
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
 **************************************************************************/
