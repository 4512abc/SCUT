文章内容转载自[14 chapter 文件处理（cpp大学教程）学习笔记](https://blog.csdn.net/stay_alive001/article/details/121520290)
如有侵权，请联系作者删除。

----------------------------------------------------------

# Cpp复习 第十四章

## 14.1 文件和流

### 文件

内存中数据的存储是临时的，而用文件存储的数据是永久的——文件被储存在辅助存储设备中，如硬盘、CD、DVD、闪存驱动器和磁带

特点：每个文件都以一个文件结束符或者以存储在操作系统维护、管理的数据结构中的一个特定字节数



### 文件处理模板

typedef ifstream是一个对basic_ifstream的特化，允许文件输入字符（读）

typedef ofstream是一个对basic_ofstream的特化，允许文件输出字符（写）

typedef fstream是一个对basic_fstream的特化，允许文件输入、输出字符（读写）

注意：该模板都是从basic_iostream、basic_istream、basic_ostream中“继承”而来，包含其所有的成员函数

![image-20240608131628656](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608131628656.png)



## 14.2 创建顺序文件

### 打开一个文件

```cpp
ofstream outputFile("credit.dat", ios::out);
 if(!outputFile){cerr<<"File could not be opened";exit(EXIT_FAILURE);}
```

打开文件有两个参数：文件名和文件打开模式

文件名：若文件不存在，则自动创建该文件名的文件

文件打开模式ios::out——向一个文件输出数据：默认截顶，会自动清空文件里的数据重新输出

ofstream对象默认为ios::out文件打开模式

> 模式	描述
> ios::app	将输出文件添加到文件尾，不截顶
> ios::ate	可以再文件任何位置输出数据，默认为文件尾
> ios::in	打开文件输入
> ios::out	打开文件输出，截顶
> ios::trunc	丢弃文件的内容
> ios::binary	打开一个文件进行二进制输入/输出

 

### 使用open打开一个文件

一个ofstream对象可以在没有打开特定文件的情况下被创建，之后文件再关联到这个对象。

```cpp
ofstream outputFile;
 outputFile.open("credit.dat", ios::out);
```



### 测试一个文件是否被成功打开

![image-20240608132702823](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608132702823.png)

![image-20240608132711047](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608132711047.png)

> **Testing Whether a File Was Opened Successfully**
>
> After creating an ofstream object and attempting to open it, the program tests whether the open operation was successful.
>
> The if statement in lines 15–19 uses the overloaded ios member function operator! to determine whether the open operation succeeded.
>
> ◦The condition returns a true value if either the failbit or the badbit is set for the stream on the open operation.
>
> Some possible errors are 
>
> ◦attempting to open a nonexistent file for reading, 
>
> ◦attempting to open a file for reading or writing with-out permission, and 
>
> ◦opening a file for writing when no disk space is available. 
>
> 测试文件是否成功打开：
> 在创建ofstream对象并尝试打开它之后，程序将测试打开操作是否成功。
> 第15-19行的if语句使用了重载的ios成员函数操作符!判断手术是否成功。
> 如果在打开操作中为流设置了failbit或badbit，则条件返回真值。
> 一些可能的错误包括：试图打开一个不存在的文件进行读取，试图在未经许可的情况下打开文件进行读写，并且
> 在没有可用的磁盘空间时打开文件以供写入。



> Function exit terminates a program.
>
> ◦The argument to exit is returned to the environment from which the program was invoked.
>
> ◦Passing EXIT_SUCCESS (also defined in <cstdlib>) to exit indicates that the program terminated *normally*; passing any other value (in this case EXIT_FAILURE) indicates that the program terminated due to an *error*.
>
> 函数退出终止程序：
> exit参数返回到调用程序的环境。
> 将EXIT_SUCCESS(也在<cstdlib>中定义)传入exit表示程序正常终止;传递任何其他值(在本例中为EXIT_FAILURE)表示程序因错误而终止。



### 重载void* 指针

> The Overloaded void * Operator
> Another overloaded ios member function—operator void *—converts the stream to a pointer, so it can be tested as 0 (i.e., the null pointer) or nonzero (i.e., any other pointer value).
> When a pointer value is used as a condition, C++ interprets a null pointer in a condition as the bool value false and interprets a non-null pointer as the bool value true.
> If the failbit or badbit has been set for the stream, 0 (false) is returned.
> The condition in the while statement of lines 29–33 invokes the operator void * member function on cin implicitly.
> The condition remains true as long as neither the failbit nor the badbit has been set for cin.
> Entering the end-of-file indicator sets the failbit for cin.
>
> 重载void *操作符：
> 另一个重载的ios成员函数——operator void *——将流转换为指针，因此它可以被测试为0(即空指针)或非零(即任何其他指针值)。
> 当将指针值用作条件时，c++将条件中的空指针解释为bool值false，将非空指针解释为bool值true。
> 如果为流设置了failbit或badbit，则返回0 (false)。
> 第29-33行while语句中的条件隐式地调用cin上的操作符void *成员函数。
> 只要cin的failbit和badbit都没有设置，条件就保持为真。
> 输入文件结束指示器设置cin的failbit。



> The operator void * function can be used to test an input object for end-of-file, but you can also call member function eof on the input object.
> Processing Data
> Figure 14.5 lists the keyboard combinations for entering end-of-file for various computer systems.
> 操作符void *函数可用于测试输入对象是否有文件结束，但也可以在输入对象上调用成员函数eof。
> 处理数据	图14.5列出了各种计算机系统中输入文件结束符的键盘组合。



> When end-of-file is encountered or bad data is entered, operator void * returns the null pointer (which converts to the bool value false) and the while statement terminates.
> The user enters end-of-file to inform the program to process no additional data.
> The end-of-file indicator is set when the user enters the end-of-file key combination.
> Line 31 writes a set of data to the file clients.txt, using the stream insertion operator << and the outClientFile object associated with the file at the beginning of the program.
> The data may be retrieved by a program designed to read the file (see Section 14.4).
> The file created in Fig. 14.3 is simply a text file, so it can be viewed by any text editor.
> 当遇到文件结束符或输入错误数据时，操作符void *返回空指针(该指针将转换为bool值false)， while语句终止。
> 用户输入文件尾以通知程序不处理其他数据。
> 当用户输入文件结束键组合时，设置文件结束指示符。
> 第31行使用流插入操作符<<和程序开头与文件关联的outClientFile对象，将一组数据写入文件clients.txt。
> 数据可以通过一个程序来读取文件(参见第14.4节)。
> 图14.3中创建的文件只是一个文本文件，因此任何文本编辑器都可以查看它。



> Closing a File
> Once the user enters the end-of-file indicator, main terminates.
> This implicitly invokes outClientFile’s destructor, which closes the clients.txt file.
> You also can close the ofstream object explicitly, using member function close.
> 关闭文件：
> 一旦用户输入文件结束指示符，main就终止。
> 这将隐式调用outClientFile的析构函数，从而关闭clients.txt文件。还可以使用成员函数close显式地关闭ofstream对象。
>
> ```cpp
> outClientFile.close()
> ```



## 14.3 从顺序文件中读取数据

> ```cpp
> ifstream inFile("credit.dat", ios::in);
> if(!inFile){cerr<<"File coule not be opened";exit(EXIT_FAILURE);};
> ```
>
> 默认为输入打开模式，也可以使用open成员函数打开文件
>
> 文件定位指针
> seekg()成员函数重定位下一个文件读入的字节号
>
> seekp()成员函数重定位下一个文件输出的字节号
>
> 传递给重定位成员函数的第一个参数通常是一个long类型的整数
>
> 参数2	作用
> ios::beg	从流的开始位置定位
> ios::cur	从流的当前位置进行定位
> ios::end	相对于流的结尾进行定位
> tellg();tellp();用于高速下一个文件输入/输出的字节号



打开格式：

```cpp
ifstream inClientFile("clients.txt")
```

可以再创建时不打开，后面再次关联。

如果文件的内容不应该被修改，那么打开方式应该是ios::in。



### 文件定位指针

istream和ostream中都提供了成员函数来重定位文件的定位指针（文件中下一个要被读取或者写入的字节）

在istream中，这个为seekg，ostream中为seekp

**`seekp` (seek put)**：用于输出（写）操作，设置输出位置指针。

**`seekg` (seek get)**：用于输入（读）操作，设置输入位置指针。

格式为：

```cpp
inClientFile.seekg(0)	//表示是从文件的起始位置开始
//第一个参数：通常是一个long类型的变量 指定位置（从文件开始位置到当前位置的字节数，或者说是文件的偏移量）
//第二个参数：指定方向：ios::beg（默认，一般是流的开始）	ios::cur（当前位置）	ios::end（流的末尾开始）
```



tellp和tellg用来返回当前put和get指针的位置。



为了执行多次文件的搜索读取，我们可以在遍历完一次文件后，对流执行clear操作，使其状态设置为goodbit，然后seekg(0)，返回文件开头的位置，便于执行下一次I/O操作。



## 14.5 更新顺序文件

> 采用格式化的输入输出模式，不方便用于更新记录。
>
> The problem is that, in the formatted input/output model using the stream insertion operator << and the stream extraction operator >>, fields—and hence records—can vary in size.
>
> ◦For example, values 7, 14, –117, 2074, and 27383 are all ints, which store the same number of “raw data” bytes internally (typically four bytes on 32-bit machines and eight bytes on 64-bit machines).
>
> ◦However, these integers become different-sized fields, depending on their actual values, when output as formatted text (character sequences).
>
> ◦Therefore, the formatted input/output model usually is not used to update records in *place*.
>
> 问题在于，在使用流插入操作符<<和流提取操作符>>的格式化输入/输出模型中，字段和记录的大小可能不同。
> 例如，值7、14、-117、2074和27383都是整数，它们在内部存储相同数量的“原始数据”字节(通常在32位机器上存储4个字节，在64位机器上存储8个字节)。
> 但是，当作为格式化文本(字符序列)输出时，这些整数将根据其实际值变成大小不同的字段（字符序列）。
> 因此，格式化的输入/输出模型通常不用于就地更新记录。



## 14.6 随机存取文件

将所有的记录的长度都固定，这样可以方便随机查找或者顺序读取，并且能够修改，删除，对其他数据也没有影响。



## 14.7 创建随机存取文件

### 输出和读取

成员函数write()从内存中一个指定位置开始输出固定数目的字节到指定的流。

关联到文件，则从文件中"put"文件定位指针指定的位置开始写入数据

成员函数read()则将固定数目的字节从一个指定的流输入到内存中指定地址开始的一部分空间。

关联到文件，则从文件中“get”文件定位指针指定的位置开始读取字节数据。



> Writing Bytes with ostream Member Function write
> Outputting a four-byte integer as text could print as few digits as one or as many as 11 (10 digits plus a sign, each requiring a single byte of storage)
> The following statement always writes the binary version of the integer’s four bytes (on a machine with four-byte integers):
> outFile.write( reinterpret_cast<    const char * >( &number ), sizeof( number ) );
> Function write treats its first argument as a group of bytes by viewing the object in memory as a const char *, which is a pointer to a byte.
> Starting from that location, function write outputs the number of bytes specified by its second argument—an integer of type size_t.
> istream function read can be used to read the four bytes back into an integer variable. 
> 使用ostream成员函数write写入字节：
> 输出一个四字节的整数作为文本可以输出少到1的数字，多到11的数字(10个数字加一个符号，每个需要一个字节的存储空间)
> 下面的语句总是写入整数的四个字节的二进制版本(在具有四个字节整数的机器上):
> outFile.write(reinterpret_cast <Const char * >(&number)， sizeof(number);
> write函数将其第一个参数视为一组字节，方法是将内存中的对象视为const char *，这是一个指向字节的指针。
> 从该位置开始，函数write输出其第二个参数指定的字节数——size_t类型的整数。
> Istream函数read可用于将四个字节读入整数变量。

**成员函数write()输出字节数据**

```cpp
outputFile.write(reinterpret_cast<const char*>(&client), sizeof(ClientData));
```

write()函数将第一个参数作为一组字节数据，将内存中的对象看做const char*类型，表示指向一个字节的指针；第二个参数为对象的字节数大小



### reinterpret_cast<>()运算符转换指针类型

作用：把某种类型强制转换为其他无关类型

注意：该转换是在编译阶段完成，不会改变指针所指对象的类型

并且在不同的平台上运行结果可能是不同的，除非有绝对的必要，否则不使用。



> Converting Between Pointer Types with the reinterpret_cast Operator
> Most pointers that we pass to function write as the first argument are not of type const char *.
> Must convert the pointers to those objects to type const char *; otherwise, the compiler will not compile calls to function write.
> C++ provides the reinterpret_cast operator for cases like this in which a pointer of one type must be cast to an unrelated pointer type.
> Without a reinterpret_cast, the write statement that outputs the integer number will not compile because the compiler does not allow a pointer of type int * (the type returned by the expression &number) to be passed to a function that expects an argument of type const char *—as far as the compiler is concerned, these types are inconsistent.
> A reinterpret_cast is performed at compile time and does not change the value of the object to which its operand points.
>
> 使用reinterpret_cast操作符在指针类型之间进行转换
> 大多数传递给write函数作为第一个实参的指针都不是const char *类型的。
> 必须将指向这些对象的指针转换为const char *类型;否则，编译器将不会编译对write函数的调用。
> c++为这种情况提供了reinterpret_cast操作符，在这种情况下，必须将一种类型的指针强制转换为不相关的指针类型。
> 如果没有reinterpret_cast，输出整数的write语句将无法编译，因为编译器不允许将int *类型的指针(由表达式&number返回的类型)传递给需要const char *类型参数的函数——就编译器而言，这些类型是不一致的。
> reinterpret_cast在编译时执行，不会改变其操作数所指向的对象的值。



#### string类成员函数copy()

 string string1 = "stringCopy";
 char string2[10];
 string1.copy(string2, 10);
成员函数copy()的两个参数：

第一个参数：将要复制赋值的string数组

第二个参数：要复制的字符个数



#### 用二进制模式打开一个输出文件

 ofstream outputFile("credit.dat", ios::out|ios::binary);
通过运算符"|"可以组合多种打开模式



## 14.8 向随机存取文件随机写入数据

> Figure 14.12 writes data to the file credit.dat and uses the combination of fstream functions seekp and write to store data at exact locations in the file.
> Function seekp sets the “put” file-position pointer to a specific position in the file, then write outputs the data.
> Line 6 includes the header ClientData.h defined in Fig. 14.9, so the program can use ClientData objects.
> 图14.12将数据写入文件credit.dat，并使用fstream函数seekp和write的组合将数据存储在文件中的准确位置。
> 函数seekp将“put”文件位置指针设置为文件中的特定位置，然后write输出数据。
> 第6行包括图14.9中定义的头文件ClientData.h，因此程序可以使用ClientData对象。

![image-20240608144044684](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608144044684.png)





![image-20240608144056004](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608144056004.png)

可以发现：上面使用了：

```cpp
outCredit to the byte location calculated by
( client.getAccountNumber() - 1 )*sizeof( ClientData )
```

来定位新数据将要在文件中写入的位置。对于记录1，文件指针定位在0。



## 14.9 从随机存取文件顺序读取数据

> In this section, we develop a program that reads a file sequentially and prints only those records that contain data.
> The istream function read inputs a specified number of bytes from the current position in the specified stream into an object.
> For example, lines 31–32 from Fig. 14.13 read the number of bytes specified by sizeof(ClientData) from the file associated with ifstream object inCredit and store the data in the client record.
> Function read requires a first argument of type char *.
> Since &client is of type ClientData *, &client must be cast to char * using the cast operator reinterpret_cast.
> 在本节中，我们将开发一个程序，它按顺序读取文件并只打印包含数据的记录。
> istream函数read将指定流中当前位置的指定字节数输入到对象中。
> 例如，图14.13中的31-32行从与ifstream对象credit关联的文件中读取sizeof(ClientData)指定的字节数，并将数据存储在客户端记录中。
> 函数read需要char *类型的第一个参数。
> 由于&client是ClientData *类型，因此必须使用强制转换操作符reinterpret_cast将&client强制转换为char *类型。

![image-20240608144853289](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608144853289.png)

![image-20240608144901519](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608144901519.png)

![image-20240608144908383](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608144908383.png)





#### 成员函数read()读取文件数据

```cpp
inFile.read(reinterpret_cast<char*>(&client), sizeof(ClientData));
```

第一个参数：要求的参数类型为char *，需用强制类型转换

第二个参数：读取的字符数



#### 判断是否读取到文件尾

```cpp
 while(inFile && !inFile.eof()){};
```

如果出错，或者到达文件尾，都会报错。



## 14.11 对象序列化

对象序列化是指将对象的状态转换为可存储或传输的格式的过程，以便以后可以重建该对象。序列化的目标是将对象表示为字节流，从而可以保存到文件、数据库，或通过网络传输给其他应用程序。反序列化是序列化的逆过程，即从字节流重建对象。

在C++中，对象序列化不是语言本身提供的特性，而是通过编写自定义代码或使用第三方库来实现的。以下是几种常见的对象序列化方法：

### 手动序列化

你可以手动编写代码，将对象的成员变量写入字节流，然后读取这些字节流以重建对象。以下是一个示例，演示如何手动序列化和反序列化一个简单的对象：

#### 示例类

```cpp
#include <iostream>
#include <fstream>

class Person {
public:
    std::string name;
    int age;

    Person() : name(""), age(0) {}
    Person(std::string name, int age) : name(name), age(age) {}

    void serialize(std::ostream& os) const {
        size_t nameLength = name.size();
        os.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        os.write(name.c_str(), nameLength);
        os.write(reinterpret_cast<const char*>(&age), sizeof(age));
    }

    void deserialize(std::istream& is) {
        size_t nameLength;
        is.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        name.resize(nameLength);
        is.read(&name[0], nameLength);
        is.read(reinterpret_cast<char*>(&age), sizeof(age));
    }
};

int main() {
    Person p1("Alice", 30);

    // 序列化到文件
    std::ofstream ofs("person.dat", std::ios::binary);
    p1.serialize(ofs);
    ofs.close();

    // 从文件反序列化
    Person p2;
    std::ifstream ifs("person.dat", std::ios::binary);
    p2.deserialize(ifs);
    ifs.close();

    std::cout << "Name: " << p2.name << ", Age: " << p2.age << std::endl;

    return 0;
}
```

### 使用Boost.Serialization库

Boost.Serialization 是一个功能强大且灵活的库，可以简化序列化和反序列化过程。使用这个库，你只需为类定义序列化函数，然后使用库提供的接口进行序列化和反序列化。

#### 示例类

```cpp
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Person {
public:
    std::string name;
    int age;

    Person() : name(""), age(0) {}
    Person(std::string name, int age) : name(name), age(age) {}

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & name;
        ar & age;
    }
};

int main() {
    Person p1("Alice", 30);

    // 序列化到文件
    {
        std::ofstream ofs("person.txt");
        boost::archive::text_oarchive oa(ofs);
        oa << p1;
    }

    // 从文件反序列化
    Person p2;
    {
        std::ifstream ifs("person.txt");
        boost::archive::text_iarchive ia(ifs);
        ia >> p2;
    }

    std::cout << "Name: " << p2.name << ", Age: " << p2.age << std::endl;

    return 0;
}
```

### 使用 JSON 或 XML 进行序列化

可以使用诸如 JSON 或 XML 格式来序列化对象。许多第三方库可以方便地处理这些格式，例如 nlohmann/json 库（用于 JSON）和 pugixml 库（用于 XML）。

#### 使用 nlohmann/json

以下是一个使用 nlohmann/json 库进行 JSON 序列化和反序列化的示例：

```cpp
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Person {
public:
    std::string name;
    int age;

    Person() : name(""), age(0) {}
    Person(std::string name, int age) : name(name), age(age) {}

    json to_json() const {
        return json{{"name", name}, {"age", age}};
    }

    void from_json(const json& j) {
        j.at("name").get_to(name);
        j.at("age").get_to(age);
    }
};

int main() {
    Person p1("Alice", 30);

    // 序列化到文件
    {
        std::ofstream ofs("person.json");
        json j = p1.to_json();
        ofs << j.dump(4);
    }

    // 从文件反序列化
    Person p2;
    {
        std::ifstream ifs("person.json");
        json j;
        ifs >> j;
        p2.from_json(j);
    }

    std::cout << "Name: " << p2.name << ", Age: " << p2.age << std::endl;

    return 0;
}
```

### 总结

对象序列化在 C++ 中可以通过多种方式实现：

1. **手动序列化**：通过手动编写代码，将对象的成员变量写入字节流并读取。
2. **使用 Boost.Serialization 库**：一个功能强大且灵活的库，可以简化序列化和反序列化过程。
3. **使用 JSON 或 XML 格式**：使用第三方库（如 nlohmann/json 或 pugixml）来处理这些格式。

选择哪种方法取决于具体的应用需求和项目环境。



## 补充

Qt 中的 `QDataStream` 可以用于对象序列化，它提供了一种方便的方式将数据从一个对象写入字节流，或者从字节流中读取数据以构建对象。这与对象序列化的基本原理一致：将对象的状态转换为可存储或传输的格式（字节流），然后可以重建该对象。

`QDataStream` 通常与 `QIODevice` 类（如 `QFile`）一起使用，以实现数据的持久化存储或网络传输。

### QDataStream 简介

`QDataStream` 类用于序列化基本数据类型以及许多 Qt 类（如 `QString`、`QVector` 等）。它提供了简单的操作符重载来读取和写入数据。

### 示例：使用 QDataStream 进行对象序列化

以下示例展示了如何使用 `QDataStream` 将一个对象序列化到文件中，然后再从文件中反序列化出来。

#### 示例类

```cpp
#include <QCoreApplication>
#include <QDataStream>
#include <QFile>
#include <QDebug>

class Person {
public:
    QString name;
    int age;

    Person() : name(""), age(0) {}
    Person(QString name, int age) : name(name), age(age) {}

    // 序列化操作符
    friend QDataStream& operator<<(QDataStream& out, const Person& person) {
        out << person.name << person.age;
        return out;
    }

    // 反序列化操作符
    friend QDataStream& operator>>(QDataStream& in, Person& person) {
        in >> person.name >> person.age;
        return in;
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Person p1("Alice", 30);

    // 序列化到文件
    QFile file("person.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << p1;
        file.close();
    }

    // 从文件反序列化
    Person p2;
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> p2;
        file.close();
    }

    qDebug() << "Name:" << p2.name << ", Age:" << p2.age;

    return 0;
}
```

### 关键步骤说明

1. **定义操作符重载**：
   - `operator<<` 用于序列化对象，将对象的各个成员变量写入数据流。
   - `operator>>` 用于反序列化对象，从数据流中读取各个成员变量。

2. **序列化到文件**：
   - 打开文件，创建 `QDataStream` 对象，并使用 `<<` 操作符将对象写入文件。

3. **从文件反序列化**：
   - 打开文件，创建 `QDataStream` 对象，并使用 `>>` 操作符从文件中读取对象。

### QDataStream 的其他用法

除了基本的读写操作，`QDataStream` 还提供了许多其他功能，比如设置数据流的版本以确保不同版本之间的数据兼容性：

```cpp
QDataStream out(&file);
out.setVersion(QDataStream::Qt_5_15); // 设置数据流版本
```

### 支持的类型

`QDataStream` 支持许多 Qt 的基本类型和容器类型，例如 `QString`、`QByteArray`、`QList`、`QMap` 等。对于用户自定义类型，您需要定义序列化和反序列化操作符。

### 总结

`QDataStream` 是 Qt 提供的一个方便的类，用于将对象序列化到字节流中或从字节流中读取对象。这与对象序列化的基本原理一致，使得数据的存储和传输变得更加容易和高效。通过定义序列化和反序列化操作符，可以方便地序列化自定义对象。