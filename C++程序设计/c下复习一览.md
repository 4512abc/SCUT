---
title: c下复习一览
date: 2024-06-08 01:27:31
tags:
---
# 枚举

## 语法

```c++
enum test
{
one=0,two,three=10
};
```

类似于类，其中，每个枚举值都代表了一个unsigned int，但是你无法将一个unsigned int的值赋给这样一个枚举类型。

此外，定义枚举时，每个枚举变量都可以自己设计值，无值的为前一个枚举量加1

```c++
int main()
{
    int a = 1;
    test s(one);
    test a(static_cast<test>(a + s));
    s = test(1);
}
```

其构造函数必须接受一个枚举的对象，但我们可以通过强制类型转换实现赋值。

## 应用

```c++
int main()
{
    test a=one;
    witch(a)
    {
        case one:
        ...
            break;
        case two:
        ...
            break;
    }
}
```

# 强制类型转换

## 显示

### static_cast

```c++
static_cast:

主要用于基本类型的转换，如int到double，以及在类层次结构中的指针或引用的转换。
它能够执行安全的转换，如果转换不合法（例如，从子类指针转换为基类指针，但实际对象不是那个基类的实例），编译器会报错。
不适用于解除const约束，如果尝试解除const，编译器会发出警告或错误。
如上转换int到enum时所示例子，转换的两者必须要有关联，要么存在默认的类型转换（子类），要么就是存在定义好的类型转换函数，一般都可以绕过此方法而使用类型转换；
```

### const_cast

```c++
const_cast:

专门用于添加或移除const或volatile属性。
可以用来改变指针或引用的const属性，但并不能改变实际对象的const属性。试图通过const_cast修改const对象的行为是未定义的，可能会导致运行时错误。一般的，用于将只能找到指针的对象的const属性去除，得到一个非const的指针，以便对地址中的数据进行修改(该地址的数据不能是const)
    int main()
{
    int a=0;
    const int*b=&a;
    //现在无法通过b对a修改
    int *c=const_cast<int*>(b);
    //现在可以通过c对a修改
}
```

### dynamic_cast

```c++
dynamic_cast:

用于运行时多态性，通常与虚函数一起使用。
它可以将指针或引用从基类转换为派生类，如果转换成功，返回有效指针；如果转换的对象不是目标类型，返回nullptr。
只适用于指向具有虚函数的类的指针或引用。
用于将基类对象的指针安全的转换为子类的指针
#include <iostream>
#include <vector>

// 基类
class Base {
public:
    virtual ~Base() {}
    virtual void print() { std::cout << "Base" << std::endl; }
};

// 派生类1
class Derived1 : public Base {
public:
    void print() override { std::cout << "Derived1" << std::endl; }
};

// 派生类2
class Derived2 : public Base {
public:
    void print() override { std::cout << "Derived2" << std::endl; }
};

int main() {
    std::vector<Base*> objects;
    objects.push_back(new Derived1());
    objects.push_back(new Derived2());

    for (Base* basePtr : objects) {
        // 动态类型检查和转换
        Derived1* derived1Ptr = dynamic_cast<Derived1*>(basePtr);
        if (derived1Ptr) {
            derived1Ptr->print();  // 如果是Derived1，打印Derived1
        } else {
            Derived2* derived2Ptr = dynamic_cast<Derived2*>(basePtr);
            if (derived2Ptr) {
                derived2Ptr->print();  // 如果是Derived2，打印Derived2
            } else {
                std::cout << "Not Derived1 or Derived2" << std::endl;
            }
        }
    }

    // 清理内存
    for (Base* obj : objects) {
        delete obj;
    }

    return 0;
}
```

### reinterpret_cast

```
reinterpret_cast:

最为灵活，但也是最危险的转换。
它可以将任何指针或整数类型转换为另一个，甚至可以无视类型系统，执行底层的位转换。
这种转换通常用于低级别的操作，如将指针转换为整数，然后再转换回去，或者在不兼容的指针类型之间转换。它不保证结果有意义，因此应谨慎使用。
```

## 隐式

### 默认
1. 当派生类的对象被赋值给基类的对象时，会发生隐式转换。
2. 当派生类的对象传递给函数参数为基类的引用或指针时，也会发生隐式转换。
3. 其他

```c++
void ew(int c)
{
    cout<<c;
}
-----------------------------------------------------
int main()
{
    char s='1';
    ew(s);
}
-----------------------------------------------------
int main()
{
    int a=10;
    double b=a;
}
-----------------------------------------------------
class test
{
    explicit test(int)
}
此处限制显式转换，即只能通过强制类型转换来完成，不能通过赋值语句来完成。
-----------------------------------------------------
等诸如此类的类型转换
```

## 定义

```c++
类可以定义非显式的转换函数（通常为成员函数），使其对象能够被隐式或显式地转换为其他类型。
使用关键字operator定义，如operator double() const { return this->value; }可以让类实例能够被当作double使用。
class t
{
public:
    int a;
    int b;
    virtual void re()
    {
        cout << 1;
    }
    string operator string()
    {
    char empt1 = static_cast<char>(a); // 显式类型转换提高可读性
    char empt2 = static_cast<char>(b);
    std::string str(1, empt1); // 将字符转换为长度为1的字符串
    str += std::string(1, empt2); // 使用+=拼接第二个字符
    str += std::to_string(static_cast<int>(empt2)); // 将第二个字符的整数值转换为字符串并拼接
    return str;
}
};
```

# String

## 相关操作

### getline

```c++
getline(cin, b,';');
此函数比较常见
```

### 复制

```c++
std::string str1 = str2;：使用复制构造函数创建str1作为str2的副本。
std::string str3(str2);：同上，使用复制构造函数。
str1.assign(str2);：将str2的内容赋值给str1。
```

### 剪切/子串提取:

```c++
std::string substr(size_t pos = 0, size_t n = npos) const;：提取从pos位置开始的n个字符的子串。默认到字符串末尾。
```

### 删除:

```c++
string& erase(size_t pos = 0, size_t n = npos);：删除从pos开始的n个字符。默认删除到末尾。
```

### 查找:

```c++
size_t find(const string& str, size_t pos = 0) const noexcept;：查找str第一次出现的位置，从pos开始。未找到返回npos。
类似的有find_first_of, find_last_of, find_first_not_of, find_last_not_of等
```

### 插入:

```c++
string& insert(size_t pos, const string& str);：在pos位置插入str。
也可以插入单个字符或字符数组。
```

### 替换:

```c++
string& replace(size_t pos, size_t n, const string& str);：从pos开始的n个字符被str替换
```

### 拼接:

```c++
string& operator+=(const string& str);：将str追加到字符串末尾。
string operator+(const string& str1, const string& str2);：返回str1和str2的拼接字符串。
```

### 大小和容量:

```c++
size_t length() const noexcept; 或 size_t size() const noexcept;：返回字符串长度。
size_t capacity() const noexcept;：返回当前容量。
void resize(size_t n, char c = char());：调整字符串大小为n，可选填充值c填充新空间。
```

### 对应指针

```c++
file.write(text.c_str(), text.size()); // 使用二进制写操作
此函数得到const指针
    &text[0]为非const指针
```



# 模板

## 函数模板

```cpp
template <typename T>
T add(T a, T b)
{
    return a + b;
}
int main()
{
    char a,b;
    int z,x;
    double q,w;
    add(a,b);
    add(z,x);
    add(q,w);
}
```

使用模板时，编译器会根据实参的类型来确定模板的实参类型，从而生成对应的函数。

### 形式

```c++
T add(vector<T> a, T b)
{
    return b;
}
```

### 传入引用

template <typename T>，用typename指代函数的参数类型，T是模板的形参。
使用范围仅限紧跟着的第一个函数声明，后续的函数声明不能使用模板。若使用模板但不使用，则需要强制类型转换才能调用这个函数，如：

```c++
add<int>(a,b); 
```

填入的所有元素必须保持一致。

### 类型转换

类型转换是模板的一大考点：

隐式类型转换：
即类似于char和int的转换

```c++
char a='a';
void sd(int);
sd(a);
```

强制类型转换：
即

```c++
int a=1;
char b='a';
b=(char)a;
强制类型转换，需要强制类型转换符，如：(char)a。
```

体现在模板上，就是

```c++
T add(vector<T> a, T b)
{
    return b;
}
add<int>(a,b);
```

### 重载

可以实现重载
当函数模板和普通函数重名时，编译器会优先选择函数模板，除非使用空模板参数列表。

```c++
template <typename T>
T add(T a, T b)
{
}
int add(int a, int b)
{
}
int main()
{
    add<>(int a=1,int b=0);
}
<>记为空模板参数列表。
```

### 特化

```c++
template<>add(person a,person b)
{
    if(a.?==b.?)
    return a;
    else return b;
}
貌似没什么用
```

## 类模板

```c++
template <class AH,class sd>
class person
{
    public:
    AN s;
    sd a;
    person(AH s,sd a);
}
int main()
{
    person<int,int> a(1,2);
}
```

用于创建类的模板，类模板的类名与模板名相同，类模板的类名后接尖括号，尖括号内为模板形参列表。

### 类型

类模板不会自动类型推导

```c++
template <class AH>
void nam(AH a)
{
    a.pp();
    //模板的函数
}
```

麻烦的东西，狗都不看
需要的时候直接把模板类的声明填进去就完事了。

### 继承

模板类的继承

```c++
template <class AH>
class person
{
    public:
    AH s;
    person(AH s);
}
class son():public person<int>
继承时必须强制类型转换
否则，子类也必须是模板类
如：
```c++
template <class AH>

class son():public person<AH>
```

现在，用户将类传入模板类person，person带着参数传入模板类son。
## 类型
```c++
std::type_info 可以通过 typeid 运算符获取对象的类型信息。typeid 返回一个指向 std::type_info 对象的常量引用。


#include <typeinfo>
#include <iostream>

int main() {
    int num = 10;
    const std::type_info& type = typeid(num);
    std::cout << "Type of num: " << type.name() << std::endl;

    return 0;
}
在上面的示例中，typeid(num) 返回 std::type_info 对象，表示变量 num 的类型信息。type.name() 可以获取类型名称的字符串表示。
```

# 迭代器

## 输入迭代器

只允许读取迭代器的内容，遍历（++）后找到/找不到需求值，返回其索引，反之返回超尾或空值。

## 输出迭代器

输出指定区域的所有值而不需要对其进行修改

```c++
 std::ostream_iterator<int>(std::cout, " ")
     同cout输出，附带一个“ ”
```

## 正向迭代器

可读也可写

## 双向迭代器

## 随机访问迭代器

需要operator+

迭代器或许是一种概念，一种方法，一种单位，一个小区域，方法为这些区域指定找到他们的途径。

# 异常

## try-catch

```c++
#include <iostream>
using namespace std;

int main() {
    try {
        int x = 10;
        int y = 0;
        if (y == 0) throw y; // 抛出异常
        int result = x / y; // 这一行不会执行
    }
    catch (int e) { // 捕获整型异常
        cout << "捕获到除数为零的异常: " << e << endl;
    }
    catch (...) { // 万能捕获，捕获所有类型的异常
        cout << "捕获到未知类型的异常" << endl;
    }

    cout << "程序继续执行..." << endl;
    return 0;
}
一旦发现错误，如y==0，抛出错误，内容为int类型的y，其值为0；此时退出当前函数或域，寻找第一个匹配的错误类型，随后执行其内部的语句
```

# 友元

## 友元类

```c++
    friend class tt;
```

## 友元函数

```c++
friend void cde(t& a);
```

主要注重于友元函数叙述

```c++
class person
{
    friend istream& operator>>(istream& in, person& a);
    friend person operator+(person& a, person& b);
private:
    int age;
public:
    person(int a = 10)
    {
        age = a;
    }
    person operator+(person& a);
    person operator-(person& b);
    bool operator==(person& a);
    bool operator>(person& a);
};
person person::operator+(person& a)
{
    cout << "in";
    person empt;
    empt.age=this->age += a.age;
    return empt;
}

person operator+(person& a, person& b)
{
    cout << "out";
    person empt;
    empt.age = a.age + b.age;
    return empt;
}
istream& operator>>(istream& in, person& a)
{
    in >> a.age;
    return in;
}
person& person::operator++()
{
    this->age++;
    return *this;
}
person person::operator++(int)
{    
    person empt(*this);
    this->age++;
    return empt;
}
一般的，+，-，==，>等既可以声明为友元，，也可以不这样做。
    同时声明为友元和函数成员会引发报错。
    istream& operator>>(istream& in, person& a)的确可以声明为成员函数，但这需要更改函数签名
```

# 类

## const
存在指针常量，常量指针，指针常量指针。
存在
const int sd();

int sd(const int);

int sd()const;
此处const表明此函数可以为常量对象调用，其中成员变量无法被修改，除非此成员变量为静态变量或被mutable修饰过
```c++
    mutable int a;
    int b;
    void sd()const
    {
        a = 10;
    }
    void ss()const
    {
        sd();
    }
```

## 重載

```c++
大部分上述友元已經介紹
1. 操作符重载函数不能为静态成员函数

```
## 静态数据成员

```c++
class t
{
public:
    static int tty;
    t()
    {
        a = 0;
        tty++;
    }
    int a;

protected:
    int b;
private:
    static int ccy;
    int c;
};
class t1 :public t
{
public:
    t1()
    {
        tty++;
        cout << ccy;
    }
};
int t::tty = 0;
int t::ccy = 0;
int main()
{
    t1 a;
    cout << t::ccy;
}
静态数据成员在己类和子类共用，但也分访问权限。与普通成员一样，只不过不需要对象来调用。
```



## 静态成员函数

```c++
class t
{
public:
    t()
    {
        a = 0;
    }
    int a;
    static void tochar(t*);
protected:
    int b;
private:
    int c;
};
class t1 :public t
{
public:
    t1()
    {
    }
};
void t::tochar(t* a)
{
    a->c++;
}
静态成员函数是所有对象公用的一个接口，类似于工具，他不可能存在this这种宣誓主权的东西，他可以对传入的对象的数据进行修改，可以在类内声明，后果是无法在外界使用这个函数，也不能通过对象调用。
```

## 其他成员

### 类型转换

```c++
    string operator string()
    {
    char empt1 = static_cast<char>(a); // 显式类型转换提高可读性
    char empt2 = static_cast<char>(b);
    std::string str(1, empt1); // 将字符转换为长度为1的字符串
    str += std::string(1, empt2); // 使用+=拼接第二个字符
    str += std::to_string(static_cast<int>(empt2)); // 将第二个字符的整数值转换为字符串并拼接
    return str;
    }
```

### 拷贝

```c++
class t
{
public:
    t(int c=0) : a(c) {} 
    ~t() { cout << 1; }
    t(t& q)
    {
        a = q.a;
        cout << "ddd";
    }
private:
    int a;
};

t dd(t a)
{
    return a;
}
int main()
{
    t a(2);
    dd(a);
}
此函数运行了两次，一次是传入函数，第二是传出函数，都通过此方法构造了一个副本。
    由此引发的深拷贝需要根据情景来看
```



## 继承

四种继承，public protect private是各自具备一个父类为自己的一个可能的对象，但必然存在重叠部分而不能是视为完全的对象。virtual继承将子类的父类化为共用的一个，因此而引发考点

### p继承

```
既然类似于对象作为数据成员，那么初始化必不可少，由此，构造函数是无法继承而来的。
存在考点：
1.生成以及销毁的顺序。
2.作用域下的同名成员
3.3p各自的特点
4.虚函数
```

### v继承

```c++
别名菱形继承，所以共有三层，第一层为基类，第二层为v继承的各个子类，第三层为这些子类共同的孙类。
所有类共用一个基类，故此基类只需要构造一个即可
using namespace std;
class A //长度 x,y
{
public:
    double x, y;
    A(double px = 1, double py = 1) :x(px), y(py) { cout << "a"; show(); }
    virtual ~A() { }
    virtual void show()
    {
        cout << "[A]=>" << x << "," << y<< endl;
    }
};
class B1 : virtual public A //矩形面积
{
public:
    B1(double px = 2, double py = 2) :A(px, py) { cout << "B1"; show(); }
    void show()
    {
        cout << "b1" << x << y;
    }
};
class B2 : virtual public A //梯形面积
{
public:
    double z;
    B2(double px = 3, double py = 3, double pz = 3) :A(px, py), z(pz) { cout << "B2"; show(); }
    void show()
    {
        cout << "b2" << x << y << z;
    }
};
class C : public B1, public B2 //体积
{
public:
    double h;
    C(double px = 4, double py = 4, double pz = 4, double ph = 4) :B2(px, py, pz),B1(px,py),A(px,py), h(ph) {}
    void show()
    {
        cout << "c" << x << y << z << h;
        B1::show();
        B2::show();
        A::show();
    }
};
int main()
{
    C c;
    c.show();
}
由此引发的是C的构造函数中必须构造A，否则A的值为默认值。而一旦A被正确构造，那么b1,b2中的值也都会同步改变。
```

## 多态

### 虚函数

虚函数不要求子类重写同名函数，无影响。

### 纯虚函数

纯虚函数要求子类必须重写，无法显示创建对象，但其子类调用其构造函数没有问题。

### 虚析构

```c++
class t
{
public:
    t() : a(0) {} 
    virtual ~t() { cout << 1; }
private:
    int a;
};

class t1 : public t
{
public:
    t1() : t() {} 
    ~t1() { cout << 2; }
};

int main()
{
    t *a= new t1;
    delete a;
}
输出结果为2 1；
    由此得到虚析构的作用：释放空间更彻底
```

### 纯虚析构

用来强制其子类写一个析构函数，强制其安全规范了

# 文件

## 文本文件

### 写文件

```c++
#include<fstream>头文件

创建流对象
ofstream ofs;写
fstream fs;读写

ofs.open();打开文件
或者if (file)，隐式调用 void* 转换运算符，检查流状态，void*为通用指针类型，可以用static_cast转换。
如ofs("abc.txt",ios::out)
或ofs("abc.txt",ios::out|ios::ate)(这里复用)
如果没有abc文件，则创建

ofs<<"...";写入文件
ofs.close();关闭文件
```

| ios::in     | 为读文件而打开文件 |
| ----------- | ------------------ |
| ios::out    | 写文件（覆盖）     |
| ios::ate    | 在文章尾写文件     |
| ios::app    | 追加方式写文集     |
| ios::trunc  | 删除文件再创建     |
| ios::binary | 二进制方式         |

### 读文件

```c++
#include<fstream>头文件

创建流对象
ifstream ifs;读

ifs.open("abc.txt",ios::in);如上
if(ifs.is_open())接着判断，如果有则返回1
{
    ifs>>...输入流>>,输出流<<
}
while( (c=ifs.get())!=EOF)
{

}表示读到结尾结束
ifs.close();
```



## 相关函数操作

```c++
    ifs.seekg(36*(a-1),ios_base::beg);用于写操作
    ofs.seekp(36*(a-1),ios_base::beg);用于读取操作
    用于移动文件指针到36（a-1）的位置，即跳过36*（a-1）个元素在进行输入。
    getline(ifs,str,'\n');
    读取一行，直到遇到换行符(\n)。输入的对象必须是string类型，即例子中的str。可以指定停止读取的位置，默认为'\n'。
    ios_base::beg：从文件开始处计算指针位置
    ios_base::cur：从当前位置计算指针位置
    ios_base::end：从文件末尾计算指针位置
    ifs.tellg();获取文件指针位置
    ifs.peek();查看文件指针位置
    ifs.eof();判断文件是否结束
    ifs.clear();清空错误

    std::ios::goodbit：无错误。
    std::ios::eofbit：到达文件末尾。
    std::ios::failbit：发生格式错误或提取操作失败。
    std::ios::badbit：发生不可恢复的错误。
    可以通过流对象的成员函数（如good()、eof()、fail()和bad()）来检查这些状态位。

    #include <iostream>
    #include <fstream>

    int main() {
        std::ifstream file("example.txt");
        
        if (file.good()) {
            std::cout << "No errors, file is good." << std::endl;
        }
        
        while (file) {
            char ch;
            file.get(ch);
        }
        
        if (file.eof()) {
            std::cout << "Reached end of file." << std::endl;
        }
        
        if (file.fail()) {
            std::cout << "Logical error on input operation." << std::endl;
        }
        
        if (file.bad()) {
            std::cout << "Read/writing error on i/o operation." << std::endl;
        }
        
        file.close();
        return 0;
    }
```

## 二进制文件

```c++
int main()
{
    std::cout << readText << std::endl;
    std::string text = "Hello, World!"; // 要写入的文本
    std::ofstream file("textfile.bin", std::ios::binary); // 打开文件以二进制模式写入

    // 将文本写入文件
    file.write(text.c_str(), text.size()); // 使用二进制写操作

    file.close(); // 关闭文件
    
    ifstream inputFile("textfile.bin", std::ios::binary);
    std::string readText;

    // 读取文件内容
    inputFile.seekg(0, std::ios::end); // 移动文件指针到文件末尾
    std::streamsize size = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg); // 回到文件开头
    readText.resize(size);

    inputFile.read(readText.c_str(), size); // 读取文件内容到字符串

    inputFile.close(); // 关闭文件

    // 输出读取的内
}
文件后缀为bin，写入用write(const char*,size)
读取用read(char *,size)
此处相关操作与string绑定
```

# I/O操作

## cerr clog

```c++


cerr是非粘滞性的，clog，cout，cin是粘滞性的，即cerr不经过缓冲区，而clog，cout，cin经过缓冲区。
缓冲区是存储在计算机内存中的，当缓冲区满时，会自动写入到文件。
设置缓冲区可以防止多次进行昂贵的I/O操作

```

## cout cin

```c++

cout.put(char);
单独输出一个字符
cout.ignore(int,'!');
cin.ignore(int,'!');
用于忽略int个字符，直到遇到字符'!'，即忽略'!'之前的字符。
```

## iomanip
```c++
1. setbase、hex、dec、oct

setbase：用于设置整数输出的基数（如十进制、十六进制或八进制）。这是一个非黏性的操纵符，只对紧接着的一次输出操作生效。

std::cout << std::setbase(16) << 255 << std::endl;  // 输出：ff
std::cout << 255 << std::endl;  // 输出：255
hex、dec、oct：分别用于将整数输出设置为十六进制、十进制和八进制。这些操纵符是黏性的，会持续影响后续的输出操作，直到显式地改变设置。

std::cout << std::hex << 255 << std::endl;  // 输出：ff
std::cout << 255 << std::endl;  // 输出：ff
std::cout << std::dec << 255 << std::endl;  // 输出：255

2. precision、setprecision

precision（成员函数）：设置输出流中浮点数的精度，这是一个黏性的操作。

std::cout.precision(5);
std::cout << 3.14159265 << std::endl;  // 输出：3.1416
std::cout << 2.71828 << std::endl;     // 输出：2.7183

setprecision（操纵符）：同样用于设置浮点数的精度，也是一个黏性的操作。

std::cout << std::setprecision(3) << 3.14159265 << std::endl;  // 输出：3.14
std::cout << 2.71828 << std::endl;  // 输出：2.72
3. width、setw

width（成员函数）：设置输出流中字段的宽度，这是一个非黏性的操作，只对紧接着的一次输出操作生效。

std::cout.width(10);
std::cout << 42 << std::endl;  // 输出：        42
std::cout << 42 << std::endl;  // 输出：42

setw（操纵符）：设置输出字段的宽度，也是一个非黏性的操作。
用十位空位填充，数字从后往前替换，超出了则视为stew失效
std::cout << std::setw(10) <<setfill('n')<< 42 << std::endl;  // 输出：        42
std::cout << 42 << std::endl;  // 输出：42
常添加setfill('n')用来填充
```