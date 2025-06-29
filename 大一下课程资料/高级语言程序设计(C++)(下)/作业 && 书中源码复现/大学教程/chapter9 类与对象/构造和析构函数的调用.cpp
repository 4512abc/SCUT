#include <string>
using namespace std;
#ifndef CREATE_H
#define CREATE_H

class CreateAndDestroy
{
public : 
    CreateAndDestroy( int, string );//constructor;
    ~CreateAndDestroy(); // destructor;
private :
    int objectID;
    string message;
};
#endif

//Define Functions 
#include<iostream>
using namespace std;

CreateAndDestroy::CreateAndDestroy( int ID, string messageString )
     :objectID( ID ),message( messageString)
     {
        cout << "Object " << objectID <<"   constructor runs   "
        <<message << endl;
     }

CreateAndDestroy::~CreateAndDestroy()
{
    //output newline for certain objects; helps readability
    cout << ( objectID == 1 || objectID == 6 ? "\n" : "");

    cout << "Object " << objectID << "   destructor runs   "
    << message <<endl ;

}

void create( void );//prototype

//所有类成员函数以及函数原型已经完成声明

CreateAndDestroy first( 1, "(global before main)" );
//作用域为全局的对象

int main()
{
    cout << "\nMAIN FUNCTION: EXCUTION BEGINS"<<endl;
    CreateAndDestroy second( 2, "(local automatic in main)");
    static CreateAndDestroy third( 3, "(local static in main)");
//声明了一个static类的对象3，注意观察
    create();

    cout << "\nMAIN FUNCTION: EXECUTION RESUMES"<<endl;
    CreateAndDestroy fourth( 4, "(local automatic in main)");
//在create函数后又声明了一个对象4，注意观察
    cout << "\nMAIN FUNCTION: EXCUTION ENDS"<<endl;
}//END MAIN;

void create( void )
{
    cout << "\n CREATE FUNCTION: EXECUTION BEGINS "<< endl;
    CreateAndDestroy fifth( 5, "(local automatic in create)");
    static CreateAndDestroy sixth( 6, "(local static int create)");
    CreateAndDestroy seventh( 7, "(local automatic in create)");
    cout << "\nCREATE FUNCTION: EXECUTION ENDS" << endl;
}// end function create;