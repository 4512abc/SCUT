文章内容转载自[13 输入/输出流的深入剖析(cpp大学教程)学习笔记](https://blog.csdn.net/stay_alive001/article/details/121481813?spm=1001.2014.3001.5502)
如有侵权，请联系作者删除。

------------------------------------------------------------------------

# CPP复习 第十三章



## 13.2 流

### 非格式化与格式化I/O

非格式化I/O(低层次I/O)：通过字节的方式从设备传输到内存传输或者从内存传输到设备，提供速度快、容量大的传输，建议处理大容量文件时，使用这种方式处理

格式化I/O(高层次I/O)：通过字节组成特定的字符串、整数、浮点数和用户自定义类型传输，可能会导致性能的问题，传输大容量的文件速度较慢，并且可移植性也存在问题



### 传统流和标准流

传统流：传统流库允许输入/输出char类型的字符，一个char类型的字符占一个字节

标准流：标准流库允许输入/输出wchar_t类型的Unicode字符，一个wchar_t类型的字符占两个字节

Unicode字符的新类型：char16_t	char32_t



### iostream库的头文件

<iostream>头文件包换I/O流操作基本服务	cin、cout、cerr、clog

<iomanip>头文件包括参数化流操纵符	setw、setprecision

<fstream>头文件包含文件处理服务



### 输入/输出流的类和对象

#### typedef声明数据类型同义词

```
typedef Card *CardPtr;//将类型名CardPtr定义为Card*的同义词
```

使用typedef定义的同义词知识创建了一个名称，而并没有创建新的数据类型



> iostream库就是用typedef为类模板提供别名
>
> Class template basic_istream supports stream-input operations, class template basic_ostream supports stream-output operations, and class template basic_iostream supports both stream-input and stream-output operations.
>
> 类模板basic_istream支持流输入操作，类模板basic_ostream支持流输出操作，类模板basic_iostream同时支持流输入和流输出操作。
>
> The typedef istream represents a basic_istream<char> that enables char input.
>
> The typedef ostream represents a basic_ostream<char> that enables char output.
>
> The typedef iostream represents a basic_iostream<char> that enables both char input and output.
>
> We use these typedefs throughout this chapter.
>
> typepedef istream表示basic_istream<char>，它支持char输入。
> typepedef ostream表示basic_ostream<char>，它允许char输出。
> typepedef iostream表示basic_iostream<char>，它支持char输入和输出。



UML图表示继承关系

![image-20240608100632510](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608100632510.png)



#### 标准流对象

```
>>用于从cin输入到内存 编译器是通过输入时 变量的类型来选择合适的流提取运算符重载函数 
内置类型或者string或者指针需要override
<<原理相似
```

cin连接标准输入设备，通常是键盘

cout连接标准输出设备，通常是显示屏

cerr连接标准错误设备，对象cerr的输出无缓冲，每个针对cerr的对象必须立刻输出显示，用于迅速提示用户出现错误

clog连接标准错误设备，对象clog的输出有缓冲，对于clog的错误输出将会保存在缓存区内，直到缓存区被填满时才会输出，使用缓冲技术可以提高I/O的性能



#### 文件处理模板

> C++ file processing uses class templates basic_ifstream (for file input), basic_ofstream (for file output) and basic_fstream (for file input and output).
>
> As with standard streams, C++ provides typedefs for working with these class template.
>
> The typedef ifstream represents a basic_ifstream<char> that enables char input from a file.
>
> The typedef ofstream represents a basic_ofstream<char> that enables char output to a file.
>
> The typedef fstream represents a basic_fstream<char> that enables char input from, and output to, a file.
>
> c++文件处理使用类模板basic_ifstream(用于文件输入)，basic_ofstream(用于文件输出)和basic_fstream(用于文件输入和输出)。
> 与标准流一样，c++提供了用于处理这些类模板的类型定义。
> typepedef ifstream表示basic_ifstream<char>，它允许从文件输入char。
> typepedef ofstream表示basic_ofstream<char>，允许向文件输出字符。
> typepedef fstream表示basic_fstream<char>，它允许从文件输入和输出char。



UML继承关系图

![image-20240608101209142](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608101209142.png)



## 13.3 输出流

ostream提供格式化和非格式化的输出功能
流插入运算符（<<）执行标准数据类型的输出；成员函数cin.put()进行字符输出；成员函数cin.write()进行非格式化输出

hex;oct;dec进行十六进制、八进制、十进制输出，参数化流操纵符setbase()设置制定进制输出

setprecision();指定浮点数精度输出；fixed;选择小数点后位数而不是有效数字； scientific; 指定使用可续计数法输出；showpoint;指定小数格式的输出

setw();width();用于设置输出/输入域宽

cout.fill();setfill()用于填充空白区域

uppercase;用于设置科学计数法或者十六进制的字母大写格式输出



### char*变量的输出

当要输出字符串第一个字符的地址时，应该将地址的char* 类型转换为void* 类型，因为<<运算法被重载为读取到最后一个以空字符串结尾的字符串

```cpp
 int main(){
     const char *const word = "again";
     cout<<word<<endl;	//输出的C风格的字符串
     cout<<static_cast<const void*>(word)<<endl;	//静态类型转换
 }
```



### 使用成员函数put进行字符输出

```cpp
cout.put('A').put('\n').put(65)
//cout.put(65)输出也是A
```

1、成员函数put可以输出单个字符，可以使用级联输出

2、可以使用代表ASCII值的数字表达式作为参数进行输出



### 成员函数cout.write(string, size)

两个参数分表示输出的字符串以及输出的长度，可以结合cin.gcount()一起使用

```cpp
 int main(){
     const size_t size = 80;
     char buffer[size];
     cin.read(buffer, 20);//读取20个字符
     cout.write(buffer, cin.gcount());//输出20个字符
 }
```



## 13.4 输入流

### 流提取运算符（>>）

流提取运算符跳过输入流中空白字符（空格符 换行符 制表符）进行读取，并且每次读取会返回一个cin对象的引用，读取到文件尾会返回一个空指针



> Formatted and unformatted input capabilities are provided by istream.
>
> The stream extraction operator (>>) normally skips white-space characters (such as blanks, tabs and newlines) in the input stream; later we’ll see how to change this behavior.
>
> After each input, the stream extraction operator returns a reference to the stream object that received the extraction message (e.g., cin in the expression cin >> grade).
>
> If that reference is used as a condition, the stream’s overloaded void * cast operator function is implicitly invoked to convert the reference into a non-null pointer value or the null pointer based on the success or failure, respectively of the last input operation.
>
> A non-null pointer converts to the bool value true to indicate success and the null pointer converts to the bool value false to indicate failure.
>
> }When an attempt is made to read past the end of a stream, the stream’s overloaded void * cast operator returns the *null pointer* to indicate *end-of-file*. 
>
> istream提供了格式化和非格式化的输入功能。
> 流提取操作符(>>)通常跳过输入流中的空白字符(如空格、制表符和换行符);稍后我们将看到如何更改此行为。
> 每次输入后，流提取操作符返回一个对接收提取消息的流对象的引用(例如，表达式cin >> grade中的cin)。
> 如果将该引用用作条件，则隐式调用流重载的void *强制转换操作符函数，根据最后一次输入操作的成功或失败分别将引用转换为非空指针值或空指针。
> 非空指针转换为bool值true表示成功，空指针转换为bool值false表示失败。
> 当试图读取超过流的末尾时，流的重载void *强制转换操作符返回空指针，表示文件结束。



> Each stream object contains a set of state bits used to control the stream’s state (i.e., formatting, setting error states, etc.).
>
> These bits are used by the stream’s overloaded void * cast operator to determine whether to return a non-null pointer or the null pointer.
>
> Stream extraction causes the stream’s failbit to be set if data of the wrong type is input and causes the stream’s badbit to be set if the operation fails.
>
> 每个流对象包含一组状态位，用于控制流的状态(即格式化、设置错误状态等)。
> 流的重载void *强制转换操作符使用这些位来确定是返回非空指针还是空指针。
> 如果输入了错误类型的数据，流提取会导致设置流的failbit，如果操作失败，则会导致设置流的badbit。



### istream成员函数

> The get member function with no arguments inputs one character from the designated stream (including white-space characters and other nongraphic characters, such as the key sequence that represents end-of-file) and returns it as the value of the function call.
>
> This version of get returns EOF when end-of-file is encountered on the stream. 
>
> 没有参数的get成员函数从指定流输入一个字符(包括空白字符和其他非图形字符，例如表示文件结束的键序列)，并将其作为函数调用的值返回。
> 当在流上遇到文件结束时，这个版本的get返回EOF。

**注意这里character用的是int类型 因为char类型无法表示每个字符是否到达了文件尾**

![image-20240608103248064](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608103248064.png)

输出示例：
![image-20240608103314556](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608103314556.png)

Crtl+z对应的是^Z，（Windows系统），UNIX和Macinotsh是Crtl+d组合，表示输入文件结尾运算符



带有字符引用参数的get成员函数从输入流输入下一个字符(即使这是一个空白字符)，并将其存储在字符参数中。
这个版本的get返回对正在为其调用get成员函数的istream对象的引用。
第三个版本的get有三个参数——**一个内置数组或字符、一个大小限制和一个分隔符(默认值为'\n')。**
这个版本从输入流中读取字符。

它要么读取**比指定的最大字符数少一个**的字符，然后终止，要么**在读取分隔符后立即终止。**
插入一个空字符，来终止字符数组中的输入字符串，字符数组在程序中是作为缓冲区的。

**分隔符不放在字符数组中，而是留在输入流中(分隔符将是下一个读取的字符)**。



#### 成员函数cin.eof()

当读取到文件尾之后的字符时被设置为true，否则为false，判定是否读取到文件尾的标识符是EOF，windows下为ctrl+z，表示的值为-1



#### 成员函数cin.get()

无参数cin.get()，读取一个字符，包括空白字符，读取到'\n'停止，会返回提取值

带一个字符引用参数的cin.get(string1);,将输入流中的下一个字符输入包括空白字符并保存至该字符引用参数内

带三个参数cin.get(string1, size, interval);三个参数分别是字符串数组，字符串长度，分隔符(默认为'\n')。

注意：分隔符不会放入数组中，一个数组最多可以读取“最大长度-1”，因为最后一个位置放置结尾符。分隔符仍将保存在输入流中，因此如果不进行跳过(cin.ignore())则下一个数组为空



![image-20240608104954530](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608104954530.png)



![image-20240608105002166](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608105002166.png)

这里输入了

```
Contrasting string input with cin and cin.get
```

一开始使用的是cin， 因为有空格符，所以打印buffer1时，只有Contrasting

Contrasing后的" "字符被留在了缓冲区中，所以后来cin.get调用时，也被缓冲区中的字符输入到buffer2中，直到"\n"才结束。



```cpp
#include <iostream>
using namespace std;
int main() {
    const int size=12;
    char str1[size];
    char str2[size];
    char str3[size];
    cin>>str1;

    cout<<"string with cin"<<endl<<str1<<endl<<endl;

    cin.get(str2,size);
    cout<<"string with cin.get1"<<endl<<str2<<endl<<endl;

    cin.get(str3,size,' ');
    cout<<"string with cin.get2"<<endl<<str3<<endl<<endl;
    return 0;
}

//输出结果
compare between cin and cin.get
string with cin
compare

string with cin.get1
 between ci

string with cin.get2
n

```



#### 成员函数cin.getline(string1, size, interval)

其功能与带三个参数的成员函数cin.get(string1, size, interval)相似，不同点是：

getline()读到分隔符后停止并且会将分隔符从输入流中删除；get()读到分隔符后停止但分隔符仍保存在输入流中



#### 成员函数cin.peek()

返回输出流中的下一个字符，并且不将他从流中去除



#### 成员函数cin.ignore()

读取并丢弃一定数量的字符(默认为一个字符)，或者遇到指定分隔符(EOF)停止



#### 成员函数cin.putback()

将先前使用get()函数从输入流里获得的字符，再放回到流中。

一般用于扫描输入流，尤其是搜索以特定字符开头的字段的应用程序很有用。



> `cin.putback` 是 C++ 标准库中的一个方法，用于将一个字符放回输入流。这样做可以让该字符成为输入流中的下一个字符，从而可以被再次读取。这在处理输入时非常有用，尤其是在处理复杂输入或者需要根据某个字符决定不同的处理方式时。
>
> ### 用途和使用场景
>
> 1. **处理复杂输入**：当读取输入时，遇到某个字符需要重新判断时，可以将其放回流中以便再次读取。
> 2. **回退字符**：在读取一系列字符后，如果发现不符合预期，可以将最后一个字符放回流中。
> 3. **解析输入**：在解析输入时，可以根据读取的字符决定不同的解析路径。
>
> ### 使用示例
>
> 下面是一个简单的示例，展示了 `cin.putback` 的使用：
>
> ```cpp
> #include <iostream>
> #include <sstream>
> 
> int main() {
>     std::istringstream input("123 456");
>     char ch;
> 
>     // 读取一个字符
>     input >> ch;
>     std::cout << "Read character: " << ch << std::endl;
> 
>     // 将字符放回输入流
>     input.putback(ch);
> 
>     // 再次读取这个字符
>     input >> ch;
>     std::cout << "Read character again: " << ch << std::endl;
> 
>     return 0;
> }
> ```
>
> 输出：
>
> ```
> Read character: 1
> Read character again: 1
> ```
>
> 在这个示例中，我们首先读取一个字符 `1`，然后使用 `putback` 将其放回输入流。再次读取时，仍然是字符 `1`，说明 `putback` 成功地将字符放回了输入流。
>
> ### 实际应用
>
> 考虑一个更复杂的应用场景，比如解析一个简单的数学表达式：
>
> ```cpp
> #include <iostream>
> #include <sstream>
> 
> void parseExpression(std::istringstream& input) {
>     char ch;
> 
>     while (input >> ch) {
>         if (std::isdigit(ch)) {
>             input.putback(ch);
>             int number;
>             input >> number;
>             std::cout << "Parsed number: " << number << std::endl;
>         } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
>             std::cout << "Parsed operator: " << ch << std::endl;
>         } else {
>             std::cout << "Unknown character: " << ch << std::endl;
>         }
>     }
> }
> 
> int main() {
>     std::istringstream input("12 + 34 - 56 * 78 / 90");
>     parseExpression(input);
>     return 0;
> }
> ```
>
> 输出：
>
> ```
> Parsed number: 12
> Parsed operator: +
> Parsed number: 34
> Parsed operator: -
> Parsed number: 56
> Parsed operator: *
> Parsed number: 78
> Parsed operator: /
> Parsed number: 90
> ```
>
> 在这个示例中，`parseExpression` 函数读取输入流中的字符。如果读取到的是数字，则将其放回输入流，然后读取整个数字。如果读取到的是操作符，则直接处理。这样，我们可以灵活地处理和解析复杂的输入。
>
> ### 总结
>
> `cin.putback` 是一个有用的工具，允许程序员将字符放回输入流，从而在处理输入时有更多的灵活性。它特别适用于需要回溯或者重新判断的场景，比如解析复杂的输入或者表达式。理解和使用 `putback` 可以让你在处理输入流时更加得心应手。



> C++ offers type-safe I/O.
>
> The << and >> operators are overloaded to accept data items of specific types.
>
> If unexpected data is processed, various error bits are set, which the user may test to determine whether an I/O operation succeeded or failed.
>
> If operator << has not been overloaded for a user-defined type and you attempt to input into or output the contents of an object of that user-defined type, the compiler reports an error.
>
> This enables the program to “stay in control.” 
>
> c++提供类型安全的I/O。
> <<和>>操作符被重载以接受特定类型的数据项。
> 如果处理了意外数据，则设置各种错误位，用户可以通过测试来确定I/O操作是成功还是失败。
> 如果操作符<<没有为用户定义类型重载，并且您试图输入或输出该用户定义类型对象的内容，编译器将报告错误。这使程序能够“保持控制”。



#### 成员函数cin.read(string1, size)

两个参数分别表示读取字符存入的数组以及存入字符的数量，读取的字符包括空白字符

read用于将一定数量的字节读入到字符数组中。

**注意：如果当读取的字符数量少于size，则failbit则会被设置**



#### 成员函数cin.write()

用于从字符数组中输出字节，包括空字符



#### 成员函数cin.gcount()

返回最近一次输入操作所读取的字符数

![image-20240608112249518](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608112249518.png)

这里cin.gccount对应的就是上面的20



## 13.6 流操纵符

### 整形流的基数：doc, oct, hex, setbase()

doc：十进制输出

oct：八进制输出

hex：十六进制输出

setbase(size)：指定进制输出（必须包含<iomanip>header）

四者都为“黏性”流操纵符，对之后的输出都有效

注意都是在输出的变量前插入



### 浮点精度precision(), setprecision()

precision()为ios_base成员函数，不含参数返回当前的精度设置（这样就可以在不再使用黏性设置时，返回原原来的设置精度），含有一个参数返回先前精度设置

流操纵符setprecision(accuracy)

二者都为“黏性”设置，会总用于之后的所有输出



### 域宽cout.width(), setw(size)

width()为ios_base成员函数，不含参数返回当前的域宽设置，含参数的返回先前的域宽设置

如果输出值的宽度比域宽小，则插入字符进行填充。

宽度大于指定宽度的值不会被截断，会将整个值全部输出。

width()可以控制输入输出的精度

width是非黏性的，使用后被隐式地设置为0

 

```cpp
int main(){
     int widthValue = 4;
     char sentence[10];
     cin.width(5);//每次会读取4个字符，最后一个字符为结尾符
     cin>>sentence;
 }
```



### 流操纵符setw(size)

二者都为“非黏性”设置，之后会默认设置为0



### 自定义流操纵符

```cpp
 #include<iostream>
 using namespace std;

 operator& carriageReturn(ostream& output){
     return output<<'\r';
 }
 int main(){
     cout<<'......'<<carriageReturn<<'----';
 }
```



## 13.7 流的格式状态和流操纵符

以下所有流操纵符都属于类ios_base

> Various stream manipulators can be used to specify the kinds of formatting to be performed during stream-I/O operations.
>
> Stream manipulators control the output’s format settings.
>
> Figure 13.12 lists each stream manipulator that controls a given stream’s format state.
>
> All these manipulators belong to class ios_base.
>
> We show examples of most of these stream manipulators in the next several sections.
>
> 可以使用各种流操纵符来指定在流i /O操作期间执行的格式化类型。
> 流操纵符控制输出的格式设置。
> 图13.12列出了控制给定流格式状态的每个流操纵符。
> 所有这些操纵符都属于ios_base类。
> 在接下来的几节中，我们将展示大多数流操作符的示例。

![image-20240608124241579](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608124241579.png)

![image-20240608124250850](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608124250850.png)



### 尾数零和小数点showpoint

showpoint强制要求浮点数的输出必须带小数点和尾数零

cout<<showpoint<<79.0;//浮点数79.0当不使用showpoint时显示79，使用时显示79.000000

要重置showpoint的设置时，需要使用noshowpoint

浮点数的默认精度是6，精度值显示的是有效位数



### 对齐left, right, internal

left：让输出左对齐，并且右边填充字符

right：让输出右对齐，并且左边填充字符

internal：让数字的符号左对齐，数值部分右对齐，中间用填充字符填充

showpos强制要求输出符号，noshowpos可以关闭



### 内容填充fill(), setfill()

成员函数cout.fill()指定对齐域填充字符，如果没有指定则用空字符，无参数时返回之前的填充字符

setfill也是相同的功能。

> 在 C++ 标准库中，`fill` 和 `setfill` 是两个用于格式化输出流的成员函数，但它们的作用和使用方式略有不同。以下是这两个函数的详细介绍及它们的区别。
>
> ### `fill`
>
> `fill` 是一个成员函数，用于设置填充字符。当输出宽度大于实际输出内容的宽度时，会用填充字符来填充剩余的空位。`fill` 函数的返回值是上一次的填充字符。
>
> #### 语法
>
> ```cpp
> char fill(char ch);
> ```
>
> #### 示例
>
> ```cpp
> #include <iostream>
> #include <iomanip>
> 
> int main() {
>  std::cout.fill('*');
>  std::cout.width(10);
>  std::cout << 42 << std::endl;
> 
>  char previousFill = std::cout.fill(' ');
>  std::cout.width(10);
>  std::cout << 42 << std::endl;
> 
>  std::cout << "Previous fill character: " << previousFill << std::endl;
>  return 0;
> }
> ```
>
> 输出：
>
> ```
> ********42
>      42
> Previous fill character: *
> ```
>
> 在这个示例中，`fill('*')` 设置了填充字符为 `*`，并且设置了输出宽度为 10。然后，恢复到默认的填充字符 `' '`。
>
> ### `setfill`
>
> `setfill` 是一个操纵器，用于设置填充字符。操纵器是一种特殊的函数，可以直接插入到输出流中，改变流的状态。
>
> #### 语法
>
> ```cpp
> std::setfill(char ch);
> ```
>
> #### 示例
>
> ```cpp
> #include <iostream>
> #include <iomanip>
> 
> int main() {
>  std::cout << std::setfill('*') << std::setw(10) << 42 << std::endl;
>  std::cout << std::setfill(' ') << std::setw(10) << 42 << std::endl;
>  return 0;
> }
> ```
>
> 输出：
>
> ```
> ********42
>      42
> ```
>
> 在这个示例中，`std::setfill('*')` 设置了填充字符为 `*`，并且设置了输出宽度为 10。然后，通过 `std::setfill(' ')` 恢复到默认的填充字符 `' '`。
>
> ### 区别
>
> 1. **类型和用法**：
>    - `fill` 是输出流的成员函数。你需要通过输出流对象来调用它（如 `std::cout.fill('*')`）。
>    - `setfill` 是一个操纵器，直接插入到输出流中（如 `std::cout << std::setfill('*')`），这使得它更适合与其他操纵器（如 `std::setw`）结合使用。
>
> 2. **返回值**：
>    - `fill` 返回先前的填充字符，可以用于恢复以前的设置。
>    - `setfill` 不返回值，它是一个流操纵器，直接作用于输出流。
>
> 3. **结合其他操纵器使用**：
>    - `setfill` 更加方便地与其他操纵器（如 `std::setw`）一起使用，因为它可以链式调用，使得代码更加简洁。
>
> ### 示例对比
>
> #### 使用 `fill`
>
> ```cpp
> #include <iostream>
> #include <iomanip>
> 
> int main() {
>     std::cout.fill('*');
>     std::cout.width(10);
>     std::cout << 42 << std::endl;
> 
>     std::cout.fill(' ');
>     std::cout.width(10);
>     std::cout << 42 << std::endl;
> 
>     return 0;
> }
> ```
>
> #### 使用 `setfill`
>
> ```cpp
> #include <iostream>
> #include <iomanip>
> 
> int main() {
>     std::cout << std::setfill('*') << std::setw(10) << 42 << std::endl;
>     std::cout << std::setfill(' ') << std::setw(10) << 42 << std::endl;
> 
>     return 0;
> }
> ```
>
> 可以看出，使用 `setfill` 使代码更简洁，更容易与其他操纵器结合。
>
> ### 总结
>
> - **`fill`**：成员函数，需要通过输出流对象调用，返回先前的填充字符。
> - **`setfill`**：操纵器，可以直接插入到输出流中，与其他操纵器结合使用更加方便。
>
> 根据具体需求和代码风格选择使用哪种方法来设置填充字符。



### 整形流的基数showbase

showbase要求进制输出时显示前面的基数，如十六进制以0x或者0X开头，八进制以0开头

该流操纵符为"黏性"。

当流被指定为一个特定的基数时，流中的所有整数都按照该基数处理，除非指定另外一个，或者直到程序结束



### 浮点数、科学计数法、定点小数计数法scientific, fixed

scientific要求以科学计数法输出

fixed要求输出的精度为小数点后位数，而不是有效数字个数

二者为“黏性”设置



### 大小写控制uppercase

uppercase要求科学计数法中的e和十六进制输出的x用大写输出

科学计数法默认情况下保证小数点后6位



### 指定布尔格式boolalpha

boolalpha指定输出bool类型时以true或者false输出

关闭使用noboolalpha，这两个都是黏性的



### 通过成员函数cout.flags()设置和重置格式状态

成员函数cout.flags()无参数时返回之前格式状态以fmtflags数据类型（ios_base）的形式返回；有参数时返回之前的格式状态并将当前状态设置成参数的格式状态

![image-20240608130350304](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608130350304.png)

![image-20240608130359292](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608130359292.png)

```cpp
 "include......."
 int main(){
     int integer1 = 100;
     ios_base::fmtflags originalFormat = cout.flags();//返回当前格式状态
     cout<< showbase<<oct<<scientific;
     cout<<cout.flags()<<integer;
     
     cout.flags(originalFormat);//设置成原来的格式
     cout<<cout.flags()<<integer;
 }
```



## 13.8 流的错误状态

通过检测ios_base类中的相应位来判断

当遇到文件尾时，输入流的eofbit位将被设置，调用函数cin.eof()进行判断

当发生格式错误时，failbit位将被设置，并且不会读取任何字符，通过cin.fail()判断

当发生数据错误时，badbit位将被设置，通常这种错误无法修复，通过cin.bad()判断

当bad, fail, eof都为false时，goodbit将被设置成true，通过cin.good()判断



成员函数rdstate返回流的错误状态，通过switch语句检查这些状态：eofbit	badbit	failbit	goodbit。		

成员函数cin.clear()可以清空cin，然后将goodbit设置成true保持I/O状态良好继续执行

```
cin.clear(ios::failbit)将cin清空	并且为该流设置为goodbit位	
```



如果badbit或者failbit被设置，那么basic_ios中的!会被设置为true值，operator void* 也会返回false值。

可以用于文件操作中的文件处理。



## 13.9 将输出流连接到输入流

成员函数tie()让输出和输入同步操作

cin.tie(&cout);//让输出在接下来的输入操作之前被显示

inputStream.tie(0);//解除绑定



