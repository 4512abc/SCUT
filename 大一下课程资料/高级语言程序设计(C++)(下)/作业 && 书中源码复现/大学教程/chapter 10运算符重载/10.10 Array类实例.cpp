#include<bits/stdc++.h>
using namespace std;
#ifndef ARRAY_H
#define ARRAY_h

class Array
{
    friend std::ostream &operator<<( std::ostream &, const Array &);
    friend std::istream &operator>>( std::istream &, Array &);

public:
    explicit Array( int = 10 );//默认构造函数
    Array(const Array & );//复制构造函数
    ~Array();
    size_t getSize() const; // 返回数组大小

    const Array &operator=( const Array &);
    bool operator==( const Array &) const;
    bool operator!=( const Array &right ) const
    {
        return !(*this == right);//调用相等的函数判断不相等
    }
    int &operator[]( int );
private:
    size_t size;
    int *ptr;
};
#endif



//member function definition

Array::Array( int arraySize )
    :size( arraySize > 0 ? arraySize : throw invalid_argument("Array size must be greater than 0")),
    ptr( new int[ size ])
{
    for( size_t i = 0; i < size ; i++)
        ptr[ i ] = 0; // 动态数组，全部初始化为0
}
Array::Array( const Array &arrayToCopy )//传入复制对象的引用，
        //用初始化列表复制数组大小参数，创建int型动态数组
    :size( arrayToCopy.size ),
    ptr( new int[ size ])
{
    for ( size_t i = 0; i < size ; i++)
        ptr[ i ] = arrayToCopy.ptr[ i ];//指向同一块区域
}
Array::~Array()
{
    delete [] ptr;//删除已用的堆区
}

size_t Array::getSize() const
{
    return size;
}

//重载赋值运算符
const Array &Array::operator=( const Array &right )
{
    if( &right != this)//避免自我赋值
    {
        if( size != right.size )
            {
                delete [] ptr;//释放空间
                size = right.size;
                ptr = new int[ size ];
            }

            for ( size_t i = 0; i< size; i++ )
                {
                    ptr [ i ] = right.ptr[ i ];
                    //指向同一个值
                }
    }
    return *this;//多次赋值
}

bool Array::operator==( const Array &right ) const 
{
    if ( size != right.size )
        return false;
    
    for ( size_t i = 0; i < size; i++ )
        if ( ptr[ i ] != right.ptr[ i ])
            return false;
    return true;
}

int &Array::operator[]( int subscript )//subscript : 下标
{
    if ( subscript < 0 || subscript >= size )
        throw out_of_range( "Subscript out of range");
    return ptr[ subscript ];
}

istream &operator>>( std::istream &is, Array &a)
{
    for ( size_t i = 0; i < a.size; i++ )
        is >> a.ptr[ i ];
    return is;
}
ostream &operator<<( ostream &os, const Array &a)
{
    for ( size_t i = 0; i<a.size; i++ )
        {
            os << setw(12) << a.ptr[i];

            if( i+1 % 4 == 0)
                os << endl;
        }
    if( a.size % 4 != 0)
    os << endl; //此处是对循环中的补充，要求为输出完数组一定换行
    return  os ; 
}

 void outputArray( const Array &arrayToOutput );

int main()
{
    Array integer1( 7 );
    Array integer2;

    cout << "Size of Array interger1 is "
        << integer1.getSize()
        <<endl;
    
    cout << "Size of Array integer2 is "
        << integer2.getSize()
        <<endl;

    cout << "enter 17 integers :";
    cin >> integer1 >> integer2 ;

    cout << "\nAfter input, the Array s contain: \n"
    << "integer1 :\n" << integer1
    <<"integer2 : \n" << integer2;
    cout << "\n Evaluating: integer1 != integer2 "<<endl;

    if ( integer1 != integer2 )
        cout << " integer1 and integer2 are not equal" << endl;

    Array integer3( integer1 );
    cout << "\nAfter copy integer1, Size of Array integer3  is :"
    << integer3.getSize();

    cout << "\nAssigning integer2 to integer1: "<< endl;
    integer1 = integer2;

    cout << "integer1 :\n" << integer1 
        << "integer2 :\n" << integer2;
    
    cout << "\n Evaluating: integer1 == integer2 ";

    if ( integer1 == integer2 )
        cout << "integer1 and integer2 are equal" << endl;
    
    cout << "\ninteger1[5] is " << integer1[5];

    cout << "\n\nAssigning 1000 to integer1[5]" << endl;
    integer1[5] = 1000;

    cout << "integer1:\n" <<integer1;

    //使用超过范围的下标
    try
    {
        cout << "\nAttempt to assign 1000 to integer1[15]" <<endl;
        integer1[15] = 1000;
    }
    catch(out_of_range &ex)
    {
        cout << "An exception occurred: " << ex.what() << endl;
    }

    cout << "类型转换运算符";

    ccout <<"output(3)在该版本编译器已经被禁止使用";
   

}
    void outputArray( const Array &arrayToOutput )
    {
        cout << "The Array received has " << arrayToOutput.getSize()
        << "elements. The contents are:\n" <<arrayToOutput <<endl;

    }
