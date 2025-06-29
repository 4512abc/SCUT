#include <iostream>
using namespace std;

int main()
{
    const char *const word = "again";

//display value of char*,then display value of char *//after a static_cast to void *cout 
    cout <<"Value ofword is:"<< word << endl;
    cout <<"Value ofstatic cast< const void *>( word ) is "<< static_cast<const void*>( word )<< endl;
}