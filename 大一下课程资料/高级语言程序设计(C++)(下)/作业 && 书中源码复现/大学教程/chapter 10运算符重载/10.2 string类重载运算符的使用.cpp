#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1( "happy" );
    string s2( "birthday" );
    string s3;

    //测试重载的等号和关系运算符
    cout << "s1 is \"" << s1 << "\"\n s2 is \"" << s2
    << "\""
    << "s3 is \"" << s3 << "\"" << "\n\nThe result of comparing s2 and s1:"
    << "\ns2 == s1 yields " << ( s2 == s1 ? "true" : "false" )
    <<"\ns2 != s1 yields " << ( s2 != s1 ? "true" : "false" )
    << "\ns2 > s1 yields " << ( s2 > s1 ? "true" : "false" )
    << "\ns2 < s1 yields " << ( s2 < s1 ? "true" : "false" )
    <<"\ns2 >= s1 yields " << ( s2 >= s1 ? "true" : "false" )
    << "\ns2 <= s1 yields " << ( s2 <= s1 ? "true" : "false" )
;
    //测试string成员函数
    cout << "\n\nTesting s3.empty():" << endl;
    if(s3.empty())
    {
        cout << "s3 is empty; assigning s1 to s3;" << endl;
        s3 = s1;
        cout << "s3 is \"" << s3 << "\"";
    }

    //测试重载的+=运算符 (yield:产出，产生)
    cout << "\n\ns1 + =s2 yields s1 = ";
    s1 += s2;
    cout << s1;

    cout << "\n\ns1 += \" to you\" yields" << endl;
    s1 += " to you";
    cout << "s1 = " << s1 << "\n\n";

    //测试string成员函数
    cout << "The substring of s1 starting at location 0 for\n"
    <<"14 characters, s1.substr( 0, 14), is:\n"
    << s1.substr( 0, 14) << "\n\n";

    //测试substr重载函数（括号里为字符串的末尾）
    cout << "The substring of s1 starting at\n" << 
    "location 15, s1.substr( 15 ), is \n" <<
    s1.substr( 14 ) << endl;

    //测试复制函数
    string s4(s1);
    cout << "\ns4 = " << s4 <<"\n\n";

    //测试重载的赋值号
    cout << "assigning s4 to s4" << endl;
    s4 = s4;
    cout << "s4 = " << s4 << endl;

    //测试重载的subscript(下标)运算符
    s1[ 0 ] = 'H';
    s1[ 5 ] = 'B';
    cout << "\ns1 after s1[ 0 ] = 'H',  s1[ 6 ] = 'B' is:"
    << s1 << "\n\n";

    try
    {
        cout << " Attempt to assign 'd' to s1.at( 30 ) yields:"
            << endl;
        s1.at( 30 ) = 'd';
            //会报错，下标超出范围
    }//end try
    catch( out_of_range &ex )
    {
        cout << " An exception occurred: " << ex.what() << endl;
        //ex
    }//end catch
    
    s2.substr( 0, 4 ) = "Thurs";
    cout << "\n" << s2;
}


