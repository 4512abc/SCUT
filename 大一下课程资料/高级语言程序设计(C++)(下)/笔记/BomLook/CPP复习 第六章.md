# CPP复习 第六章

函数原型的形参表中的每一个形参都应该显式地说明类型。

函数原型中、函数头以及函数调用时的在对应的实参和形参个数、类型型、顺序和返回类型必须一致。



函数原型（又称为 函数声明）提供了函数名、返回类型、函数预计接收的形参个数、以及形参的类型和顺序。

函数在调用前就已被定义，那么函数定义也可以作为函数原型，但是为了清晰易读，还是建议添加函数原型。



函数签名：函数名和实参部分，并未指定函数返回类型。

函数原型的一个特性是强制类型转换：将实参用合适的方式转换为形参指定的类型，从而正常执行。





函数被调用时实参个数与相应的函数形参个数或者类型不匹配，或者参数个数相同，但是无法隐式地转换为期望的类型，也会产生编译错误。



## 随机数

`rand` 函数是 C++ 标准库中的一个函数，用于生成伪随机数。它在 `<cstdlib>` 头文件中定义。以下是 `rand` 函数的详细介绍及其使用方法：

### 基本用法

`rand` 函数返回一个范围在 `0` 到 `RAND_MAX` 之间的整数，其中 `RAND_MAX` 是一个常量，表示可生成的最大随机数值。不同的实现中，`RAND_MAX` 的值可能不同，但它至少为 32767。

```cpp
#include <iostream>
#include <cstdlib> // 包含 rand 和 srand
using namespace std;

int main() {
    int random_number = rand(); // 生成一个随机数
    cout << "Random number: " << random_number << endl;
    return 0;
}
```

### 生成特定范围内的随机数

为了生成一个特定范围内的随机数，可以使用取模运算符 `%`。例如，要生成一个范围在 `0` 到 `99` 之间的随机数：

```cpp
#include <iostream>
#include <cstdlib> // 包含 rand 和 srand
using namespace std;

int main() {
    int random_number = rand() % 100; // 生成 0 到 99 之间的随机数
    cout << "Random number (0-99): " << random_number << endl;
    return 0;
}
```

要生成一个范围在 `min` 到 `max` 之间的随机数，可以使用以下公式：

```cpp
#include <iostream>
#include <cstdlib> // 包含 rand 和 srand
using namespace std;

int main() {
    int min = 10;
    int max = 20;
    int random_number = min + rand() % (max - min + 1); // 生成 min 到 max 之间的随机数
    cout << "Random number (" << min << "-" << max << "): " << random_number << endl;
    return 0;
}
```

### 初始化随机数生成器

`rand` 函数生成的随机数是伪随机数，每次运行程序时都会生成相同的序列。为了避免这种情况，可以使用 `srand` 函数初始化随机数生成器的种子。通常使用当前时间作为种子，这样每次运行程序时都会生成不同的随机数序列。如果种子相同，那么产生的也是相同的随机数字序列。

```cpp
#include <iostream>
#include <cstdlib> // 包含 rand 和 srand
#include <ctime>   // 包含 time 函数
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // 使用当前时间作为随机数种子

    int random_number = rand();
    cout << "Random number with seed: " << random_number << endl;
    return 0;
}
```

### `rand` 函数的注意事项

1. **伪随机性**：`rand` 生成的数并不是真正的随机数，而是伪随机数，基于确定的算法。如果种子相同，生成的数列也会相同。
2. **线程安全**：`rand` 函数不是线程安全的。如果在多线程环境中使用，需要进行适当的同步。
3. **更好的随机数生成器**：对于需要更高质量随机数的应用，可以使用 C++11 提供的随机数库（`<random>` 头文件）。该库提供了更好的随机数生成器和更多的分布选项。

### 使用 C++11 随机数库

C++11 提供了更强大的随机数生成器，可以生成更高质量的随机数。以下是一个简单的示例，使用 `std::mt19937` 生成器和 `std::uniform_int_distribution` 分布来生成随机数：

```cpp
#include <iostream>
#include <random> // 包含随机数库
using namespace std;

int main() {
    // 创建随机数生成器
    random_device rd; // 随机设备，提供种子
    mt19937 gen(rd()); // Mersenne Twister 随机数生成器
    uniform_int_distribution<> dist(10, 20); // 定义 10 到 20 之间的均匀分布

    // 生成随机数
    int random_number = dist(gen);
    cout << "Random number (10-20) using C++11 random library: " << random_number << endl;

    return 0;
}
```

这个例子展示了如何使用 C++11 的随机数库生成一个范围在 10 到 20 之间的随机数。相比 `rand` 函数，这种方法提供了更高质量的随机数和更多的控制选项。



## 枚举类型

枚举类型（`enum`）是 C++ 中一种用户自定义的数据类型，用于表示一组相关的常量。枚举类型使代码更具可读性和维护性，通过为常量赋予有意义的名字，取代了魔法数字（magic numbers）。

### 基本用法

枚举类型通过 `enum` 关键字定义，语法如下：

```cpp
enum EnumName {
    CONSTANT1,
    CONSTANT2,
    CONSTANT3,
    // ...
};
```

每个常量默认为一个整数值，从 `0` 开始递增。

**示例**：

```cpp
#include <iostream>
using namespace std;

enum Color {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};

int main() {
    Color color = RED;
    if (color == RED) {
        cout << "The color is red." << endl;
    }
    return 0;
}
```

在这个示例中，`Color` 枚举包含三个常量：`RED`、`GREEN` 和 `BLUE`。默认情况下，它们分别对应整数值 `0`、`1` 和 `2`。

### 指定枚举常量的值

可以显式地为枚举常量指定整数值：

```cpp
enum Weekday {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY = 10,
    FRIDAY,
    SATURDAY,
    SUNDAY
};
```

在这个例子中，`MONDAY` 被显式指定为 `1`，`TUESDAY` 和 `WEDNESDAY` 分别是 `2` 和 `3`，`THURSDAY` 被指定为 `10`，其后的常量 `FRIDAY`、`SATURDAY` 和 `SUNDAY` 分别为 `11`、`12` 和 `13`。

### 枚举类型的作用域

在 C++11 及更高版本中，可以使用 `enum class` 或 `enum struct` 定义强类型枚举（scoped enum），避免与其他枚举或常量发生命名冲突。

**示例**：

```cpp
#include <iostream>
using namespace std;

enum class Color {
    RED,
    GREEN,
    BLUE
};

int main() {
    Color color = Color::RED;
    if (color == Color::RED) {
        cout << "The color is red." << endl;
    }
    return 0;
}
```

在这个示例中，`Color::RED` 是强类型枚举的用法，枚举常量必须通过枚举类型名限定，这样可以避免命名冲突。

### 枚举类型的底层类型

在 C++11 及更高版本中，可以指定枚举类型的底层类型：

```cpp
enum class Color : unsigned char {
    RED,
    GREEN,
    BLUE
};
```

在这个示例中，`Color` 的底层类型被指定为 `unsigned char`，这可以控制枚举类型的大小和表示范围。

### 枚举类型的用法

枚举类型常用于状态机、选项标志、枚举集合等情景，以提高代码的可读性和维护性。

**示例**：

```cpp
#include <iostream>
using namespace std;

enum class TrafficLight {
    RED,
    YELLOW,
    GREEN
};

void printTrafficLight(TrafficLight light) {
    switch (light) {
        case TrafficLight::RED:
            cout << "Red light" << endl;
            break;
        case TrafficLight::YELLOW:
            cout << "Yellow light" << endl;
            break;
        case TrafficLight::GREEN:
            cout << "Green light" << endl;
            break;
    }
}

int main() {
    TrafficLight light = TrafficLight::GREEN;
    printTrafficLight(light);
    return 0;
}
```

在这个示例中，`TrafficLight` 枚举用于表示交通信号灯的三种状态，通过 `switch` 语句处理每种状态的具体逻辑。

### 总结

- **基本枚举**：使用 `enum` 定义一组相关的常量，默认整数值从 `0` 开始递增。
- **指定值**：可以显式指定枚举常量的整数值。
- **强类型枚举**：使用 `enum class` 或 `enum struct` 定义强类型枚举，避免命名冲突。
- **底层类型**：在 C++11 及更高版本中，可以指定枚举类型的底层类型。

通过使用枚举类型，可以使代码更具可读性和可维护性，尤其在处理一组相关常量时更加便利。



枚举类型中的常量代表的是整数。

默认情况下，作用域限定的枚举类型所隐含的整数类型是int，如果一个枚举常量的值超出了范围（也就是枚举类型所隐含的整数类型所表示的范围），则会编译错误。



`default_random_engine` 是 C++11 标准库中的一个伪随机数生成器，定义在 `<random>` 头文件中。它提供了一种简单且标准化的方法来生成随机数。`default_random_engine` 是一种通用的随机数引擎，适用于大多数一般用途。

### 基本用法

下面是一个简单的例子，演示如何使用 `default_random_engine` 生成随机数：

```cpp
#include <iostream>
#include <random> // 包含随机数库
using namespace std;

int main() {
    // 创建随机数生成器
    default_random_engine generator;

    // 创建一个均匀分布，范围是 [0, 99]
    uniform_int_distribution<int> distribution(0, 99);

    // 生成并打印10个随机数
    for (int i = 0; i < 10; ++i) {
        int random_number = distribution(generator);
        cout << random_number << endl;
    }

    return 0;
}
```

### 初始化随机数生成器

为了确保每次运行程序时生成不同的随机数序列，可以使用一个种子来初始化 `default_random_engine`。通常使用当前时间作为种子：

```cpp
#include <iostream>
#include <random>
#include <ctime> // 包含 time 函数
using namespace std;

int main() {
    // 使用当前时间作为种子
    unsigned seed = static_cast<unsigned>(time(0));
    default_random_engine generator(seed);

    uniform_int_distribution<int> distribution(0, 99);

    for (int i = 0; i < 10; ++i) {
        int random_number = distribution(generator);
        cout << random_number << endl;
    }

    return 0;
}
```

### 使用不同的分布

C++11 标准库提供了多种分布（distribution）用于生成不同类型的随机数，如均匀分布（`uniform_int_distribution`、`uniform_real_distribution`）、正态分布（`normal_distribution`）等。以下是一些示例：

**生成浮点数的均匀分布**：

```cpp
#include <iostream>
#include <random>
using namespace std;

int main() {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < 10; ++i) {
        double random_number = distribution(generator);
        cout << random_number << endl;
    }

    return 0;
}
```

**生成正态分布的随机数**：

```cpp
#include <iostream>
#include <random>
using namespace std;

int main() {
    default_random_engine generator;
    normal_distribution<double> distribution(5.0, 2.0); // 平均值 5.0，标准差 2.0

    for (int i = 0; i < 10; ++i) {
        double random_number = distribution(generator);
        cout << random_number << endl;
    }

    return 0;
}
```

### 总结

- **`default_random_engine`**：C++11 提供的默认随机数生成器，适用于大多数通用用途。
- **初始化种子**：为了生成不同的随机数序列，可以使用当前时间或其他种子来初始化随机数生成器。
- **不同的分布**：C++11 提供了多种分布，可以生成不同类型和范围的随机数。

使用 `default_random_engine` 及其相关的分布，可以方便地在 C++ 程序中生成高质量的随机数。



在 C++ 中，存储期和作用域是理解变量生命周期和可见性的两个重要概念。存储期描述了变量在内存中的存在时间，而作用域描述了变量在代码中的可访问区域。

### 存储期

存储期决定了变量在程序执行期间的生命周期。C++ 中有四种主要的存储期：

1. **自动存储期（Automatic Storage Duration）**：

   - 变量在块作用域内创建，当程序执行离开该块时销毁。
   - 默认情况下，局部变量具有自动存储期。
   - 存储在栈（stack）中。
   - 变量类型包括：函数中声明的局部变量，函数形参，以及用register声明的局部变量或者函数形参。

   **示例**：

   ```cpp
   void foo() {
       int a = 10; // 'a' 是一个自动存储期变量
       // 'a' 存在于函数 foo() 的作用域内
   } // 当 foo() 结束时，'a' 被销毁
   ```

2. **静态存储期（Static Storage Duration）**：

   - 变量在程序开始时分配，在程序结束时销毁。静态存储类期的函数，就像其他函数一样，在程序开始时函数名就已经存在。
   - 包括全局变量、静态局部变量和静态成员变量。
   - 存储在全局/静态内存区。
   - extern与static为函数和具有静态存储期的变量声明标识符。

   **示例**：

   ```cpp
   int global_var = 10; // 'global_var' 是一个静态存储期变量
   
   void foo() {
       static int static_var = 20; // 'static_var' 也是静态存储期变量
       // 'static_var' 只在第一次调用 foo() 时初始化
   }
   ```

3. **线程存储期（Thread Storage Duration）**：

   - 变量在线程启动时创建，在线程结束时销毁。
   - 使用 `thread_local` 关键字声明。
   - 每个线程有自己独立的实例。

   **示例**：

   ```cpp
   thread_local int thread_var = 30; // 'thread_var' 是一个线程存储期变量
   ```

4. **动态存储期（Dynamic Storage Duration）**：

   - 变量在运行时动态分配和释放内存，通常使用 `new` 和 `delete` 操作符。
   - 存储在堆（heap）中。

   **示例**：

   ```cpp
   void foo() {
       int* dynamic_var = new int(40); // 'dynamic_var' 是一个动态存储期变量
       // 使用动态内存分配
       delete dynamic_var; // 手动释放动态内存
   }
   ```

### 作用域

作用域决定了变量在程序中的可见性和访问权限。C++ 中有几种主要的作用域：

1. **块作用域（Block Scope）**：

   - 变量在一对 `{}` 内声明，其作用域限于该块。
   - 包括函数体、控制结构（如 if、for、while）和代码块。

   **示例**：

   ```cpp
   void foo() {
       int a = 10;
       if (a > 5) {
           int b = 20; // 'b' 具有块作用域
           // 'b' 只在 if 语句块内可见
       }
       // 'b' 在这里不可见
   }
   ```

2. **函数作用域（Function Scope）**：

   - 标签的作用域，通常用于 `goto` 语句。

   **示例**：

   ```cpp
   void foo() {
       goto label;
   label:
       int a = 10; // 'label' 具有函数作用域
   }
   ```

3. **文件作用域（File Scope）**：

   - 变量在文件级别声明，其作用域覆盖整个文件。
   - 使用 `static` 关键字声明的文件范围内的静态变量。
   - 全局变量默认具有文件作用域。

   **示例**：

   ```cpp
   static int file_static_var = 50; // 文件作用域的静态变量
   
   int global_var = 60; // 文件作用域的全局变量
   ```

4. **命名空间作用域（Namespace Scope）**：

   - 变量在命名空间内声明，其作用域限于该命名空间。
   - 可以使用 `namespace` 关键字定义。
   - 声明于任何的函数或者类之外的标识符

   **示例**：

   ```cpp
   namespace MyNamespace {
       int namespace_var = 70; // 命名空间作用域的变量
   }
   
   int main() {
       cout << MyNamespace::namespace_var << endl; // 访问命名空间内的变量
       return 0;
   }
   ```

5. **类作用域（Class Scope）**：

   - 变量或成员函数在类或结构体内声明，其作用域限于该类或结构体。

   **示例**：

   ```cpp
   class MyClass {
   public:
       int class_var;
       void myMethod() {
           // 'class_var' 在类作用域内可见
       }
   };
   ```

6.**函数原型作用域（Class Scope）**：

指的是那些用在函数形参列表中的标识符，不需要它们的名字，只需要类型。

### 总结

- **存储期**：描述变量在内存中的生命周期，包括自动存储期、静态存储期、线程存储期和动态存储期。
- **作用域**：描述变量在代码中的可见性和访问权限，包括块作用域、函数作用域、文件作用域、命名空间作用域和类作用域。

理解存储期和作用域是编写高效、清晰和错误较少的 C++ 代码的关键。



> Each identifier in a program also has other attributes, including storage duration, scope and linkage.
>
> C++ provides several storage-class specifiers that determine a variable’s storage duration: 
>
> ◦register, extern, mutable and static.
>
> 程序中的每个标识符还具有其他属性，包括存储持续时间、作用域和链接。
> c++提供了几个存储类说明符来确定变量的存储持续时间:
> 注册，外部，可变和静态。



> **Storage Duration**
>
> An identifier’s storage duration determines the period during which that identifier exists in memory.
>
> ◦Some exist briefly, some are repeatedly created and destroyed and others exist for a program’s entire execution.
>
> **Scope**
>
> An identifier’s *scope* is where *the identifier can be referenced* in a program.
>
> ◦Some identifiers can be referenced throughout a program; others can be referenced from only limited portions of a program.
>
> **Linkage**
>
> An identifier’s *linkage* determines whether it’s known only in the *source file where it’s declared* or *across multiple files that are compiled, then linked together.*
>
> 存储时间
> 标识符的存储持续时间决定了该标识符在内存中存在的时间。
> 有些是短暂存在的，有些是反复创建和销毁的，还有一些是在程序的整个执行过程中存在的。
>
> 范围
> 标识符的作用域是标识符可以在程序中被引用的地方。
> 有些标识符可以在整个程序中引用;其他的只能从程序的有限部分引用。
>
> 链接
> 标识符的链接决定了它是只在声明它的源文件中已知，还是在编译后链接在一起的多个文件中已知。



> **Storage Duration**
>
> The storage-class specifiers can be split into four storage durations: 
>
> ◦*automatic*, *static*, *dynamic* and *thread*. 
>
> 
>
> **Local Variables and Automatic Storage Duration**
>
> Variables with *automatic storage duration* include: 
>
> ◦local variables declared in functions
>
> ◦function parameters 
>
> ◦local variables or function parameters declared with register
>
> 存储时间
> 存储类说明符可以分为四个存储持续时间:
> 自动、静态、动态、螺纹。
>
> 局部变量和自动存储时间
> 具有自动保存期限的变量包括:
> 函数中声明的局部变量
> 函数参数
> 用寄存器声明的局部变量或函数参数



> **Static Storage Duration** 
>
> Keywords extern and static declare identifiers for variables with *static storage duration* and for functions.
>
> ◦Exist from the point at which the program begins execution and until the program terminates. 
>
> Such a variable is initial*ized once when its declaration is encountered.* 
>
> 静态存储时长
> 关键字extern和static声明具有静态存储时间的变量和函数的标识符。
> 从程序开始执行到程序终止时存在。
> 这样的变量在遇到声明时初始化一次。



> **Identifiers with Static Storage Duration**
>
> There are two types of identifiers with *static storage duration*
>
> ◦external identifiers (such as global variables and global function names) 
>
> ◦local variables declared with the storage-class specifier static.
>
> **具有静态存储时间的标识符**
>
> 有两种类型的标识符带有静态存储持续时间
>
> ◦外部标识符(如全局变量和全局函数名)
>
> ◦用存储类说明符static声明的局部变量。



> **static** **Local Variables**
>
> Local variables declared static are still known only in the function in which they’re declared, but, unlike automatic variables, *static* *local variables retain their values when the function returns to its caller*.
>
> The next time the function is called, the static local variables contain the values they had when the function last completed execution.
>
> 静态局部变量
> 声明为静态的局部变量仍然只在声明它们的函数中是已知的，但是，与自动变量不同，静态局部变量在函数返回给调用者时保留其值。
> 下次调用函数时，静态局部变量包含函数上次完成执行时的值。



## 内联函数

> 内联函数（inline function）是C++中的一种优化机制，通过减少函数调用的开销来提高程序性能。内联函数使用`inline`关键字声明，建议编译器在调用内联函数时将其展开，而不是进行常规的函数调用。
>
> ### 内联函数的定义
>
> 内联函数的定义通常放在头文件中，以便编译器在每个使用该函数的地方都能看到函数的定义。
>
> ```cpp
> inline int add(int a, int b) {
>  return a + b;
> }
> ```
>
> ### 内联函数的特点和使用场景
>
> 1. **减少函数调用开销**：
>    - 内联函数通过在调用点直接展开函数体，避免了常规函数调用的开销（如压栈、跳转和返回）。
>    - 适用于短小、频繁调用的函数，如简单的getter和setter函数。
>
> 2. **编译器建议**：
>    - `inline` 关键字只是对编译器的建议，编译器可能会根据具体情况决定是否内联。
>    - 现代编译器会根据函数的复杂度和调用频率自动决定是否内联，无需显式使用`inline`关键字。
>
> 3. **代码膨胀**：
>    - 过度使用内联函数会导致代码膨胀（code bloat），增加二进制文件的大小。
>    - 应避免将大型或复杂的函数声明为内联函数。
>
> ### 定义和声明内联函数
>
> 内联函数通常在类定义内定义，以确保编译器在使用该类时能够看到内联函数的定义。
>
> ```cpp
> class Math {
> public:
>     inline int add(int a, int b) {
>         return a + b;
>     }
> };
> ```
>
> 对于非类成员函数，可以在头文件中定义，也可以在头文件中声明，在实现文件中定义：
>
> **头文件（math.h）**：
>
> ```cpp
> #ifndef MATH_H
> #define MATH_H
> 
> inline int add(int a, int b);
> 
> #endif // MATH_H
> ```
>
> **实现文件（math.cpp）**：
>
> ```cpp
> #include "math.h"
> 
> inline int add(int a, int b) {
>     return a + b;
> }
> ```
>
> ### 内联函数和宏的对比
>
> 内联函数比宏（macro）更安全和灵活。宏使用预处理器展开，不进行类型检查，可能导致难以调试的错误。
>
> **示例（使用宏定义）**：
>
> ```cpp
> #define ADD(a, b) ((a) + (b))
> ```
>
> **示例（使用内联函数）**：
>
> ```cpp
> inline int add(int a, int b) {
>     return a + b;
> }
> ```
>
> 内联函数在编译阶段进行类型检查，并且支持C++的各种功能（如模板、重载等），而宏只在预处理阶段简单文本替换。
>
> ### 内联函数的使用限制
>
> 1. **递归函数**：
>    - 递归函数不能完全内联，因为递归调用在编译时无法确定展开次数。
>
> 2. **复杂函数**：
>    - 大型或复杂的函数不适合作为内联函数，会导致代码膨胀，影响性能。
>
> 3. **虚函数**：
>    - 虚函数不能在编译时确定调用目标，通常不会被内联。
>
> ### 总结
>
> 内联函数是提高程序性能的一种手段，通过减少函数调用的开销来优化短小、频繁调用的函数。然而，应谨慎使用内联函数，避免导致代码膨胀和性能问题。编译器会根据具体情况自动决定是否内联函数，因此在现代C++编程中，显式使用`inline`关键字的需求相对较少。



对内联函数的任意修改，都要求该函数重新该函数的所有用户都重新编译。



## 引用与引用形参

引用可以提高性能，但是安全性会降低，因为被调用函数可能会削弱调用者的数据。

引用形参是函数调用中实参的别名。

传递大型对象时建议使用引用传递。

如果一个引用不应当修改实参，那么在形参的说明符前面加上const限定符即可。

函数也可以返回引用，但是这是非常危险的，因为如果返回的是被调用函数中的局部变量时，如果没有声明为static，那么它会在函数执行结束时自动销毁。产生对一个未定义变量的引用。

对一个未定义变量的引用称为虚悬引用。



> 在 C++ 中，引用（reference）是一种别名机制，允许一个变量作为另一个变量的别名。引用形参是函数参数的一种，通过引用传递参数，使得函数可以直接操作调用者传入的变量。
>
> ### 引用
>
> #### 基本语法
>
> 引用在定义时使用符号 `&`，并且必须在定义时进行初始化。
>
> ```cpp
> int a = 10;
> int& ref = a; // 'ref' 是 'a' 的引用
> ```
>
> 在这个例子中，`ref` 是 `a` 的引用，任何对 `ref` 的操作实际上都是对 `a` 的操作。
>
> #### 特点
>
> 1. **引用必须初始化**：
>    - 引用在声明时必须被初始化。
> 2. **引用不可改变引用对象**：
>    - 一旦引用被初始化为某个对象，就不能改变引用对象。
> 3. **引用是别名**：
>    - 引用只是现有变量的另一个名字，不分配新的内存。
>
> ### 引用形参
>
> 引用形参是函数参数的一种，通过引用传递参数，使得函数可以直接操作实参，而不是其副本。这样可以避免不必要的拷贝，提高效率。
>
> #### 例子
>
> ```cpp
> #include <iostream>
> using namespace std;
> 
> void increment(int& num) {
>     num++; // 直接修改实参
> }
> 
> int main() {
>     int a = 5;
>     increment(a); // 传递 'a' 的引用
>     cout << "a: " << a << endl; // 输出 6
>     return 0;
> }
> ```
>
> 在这个例子中，函数 `increment` 接受一个 `int` 类型的引用参数 `num`。在 `main` 函数中，`a` 的引用被传递给 `increment`，因此 `increment` 可以直接修改 `a` 的值。
>
> ### 引用形参的优点
>
> 1. **避免拷贝**：
>
>    - 传递大对象时，通过引用传递避免了对象的拷贝，提高了性能。
>
> 2. **允许修改实参**：
>
>    - 通过引用传递，可以在函数内部修改调用者传入的变量。
>
> 3. **实现常量引用**：
>
>    - 使用 `const` 引用形参，既可以避免拷贝，又可以防止修改实参。
>
>    ```cpp
>    void print(const string& str) {
>        cout << str << endl;
>    }
>    ```
>
> ### 常量引用
>
> 常量引用（`const reference`）允许引用一个常量或非常量对象，并且在引用的生命周期内不允许修改引用对象。
>
> ```cpp
> void print(const int& num) {
>     // num = 10; // 错误，不能修改
>     cout << num << endl;
> }
> 
> int main() {
>     int a = 5;
>     print(a); // 可以传递非常量对象
>     print(10); // 可以传递常量对象
>     return 0;
> }
> ```
>
> ### 引用的应用场景
>
> 1. **函数返回值**：
>
>    - 函数可以返回一个引用，使得调用者可以直接操作函数内部的变量。
>
>    ```cpp
>    int& getElement(int arr[], int index) {
>        return arr[index];
>    }
>    
>    int main() {
>        int arr[3] = {1, 2, 3};
>        getElement(arr, 1) = 10; // 修改 arr[1] 的值为 10
>        return 0;
>    }
>    ```
>
> 2. **避免拷贝大对象**：
>
>    - 传递大型对象时，通过引用传递避免了对象的拷贝，节省了时间和空间。
>
>    ```cpp
>    void processLargeObject(const LargeObject& obj) {
>        // 处理大对象
>    }
>    ```
>
> 3. **实现类成员函数链式调用**：
>
>    - 类成员函数可以返回对象本身的引用，实现链式调用。
>
>    ```cpp
>    class MyClass {
>    public:
>        MyClass& setValue(int value) {
>            this->value = value;
>            return *this;
>        }
>       
>    private:
>        int value;
>    };
>       
>    int main() {
>        MyClass obj;
>        obj.setValue(10).setValue(20); // 链式调用
>        return 0;
>    }
>    ```
>
> ### 总结
>
> - **引用**：引用是现有变量的别名，必须初始化，且不能改变引用对象。
> - **引用形参**：函数参数通过引用传递，使得函数可以直接操作实参，提高效率。
> - **常量引用**：通过 `const` 修饰引用，避免拷贝的同时防止修改引用对象。
> - **应用场景**：引用在避免对象拷贝、函数返回值、链式调用等方面有广泛应用。
>
> 理解引用和引用形参在 C++ 编程中的作用，对于编写高效、优雅的代码非常重要。



## 默认实参

```cpp
It isn’t uncommon for a program to invoke a function repeatedly with the same argument value for a particular parameter.
Can specify that such a parameter has a default argument, i.e., a default value to be passed to that parameter.
When a program omits an argument for a parameter with a default argument in a function call, the compiler rewrites the function call and inserts the default value of that argument.
Default arguments must be the rightmost (trailing) arguments in a function’s parameter list.
Figure 6.21 demonstrates using default arguments to calculate a box’s volume. 
程序对特定形参使用相同的实参值反复调用函数的情况并不少见。
可以指定这样的形参有一个默认实参，即传递给该形参的默认值。
当程序在函数调用中省略带有默认实参的形参的实参时，编译器会重写函数调用并插入该实参的默认值。
默认参数必须是函数形参列表中最右边(末尾)的参数。
图6.21演示了使用默认参数来计算盒子的体积。
```

![image-20240609005608260](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240609005608260.png)

![image-20240609005617123](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240609005617123.png)

显式地传递给函数地任何实参都按照从左到右的顺序赋值给了函数的形参。

默认实参简化了函数调用的书写。



## 一元的作用域分辨运算符

> It’s possible to declare local and global variables of the same name.
>
> C++ provides the unary scope resolution operator (::) to access a global variable when a local variable of the same name is in scope.
>
> Using the unary scope resolution operator (::) with a given variable name is optional when the only variable with that name is a global variable.
>
> Figure 6.22 shows the unary scope resolution operator with local and global variables of the same name.
>
> 可以声明同名的局部变量和全局变量。
> c++提供一元作用域解析操作符(::)，当同名局部变量在作用域中时，它可以访问全局变量。
> 当唯一具有该名称的变量是全局变量时，对给定变量名使用一元范围解析运算符(::)是可选的。
> 图6.22显示了具有相同名称的局部变量和全局变量的一元作用域解析操作符。

![image-20240609005917218](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240609005917218.png)



总是使用::来引用全局变量可以降低出错概率，可以知道访问的是一个局部变量还是全局变量。



## 函数重载

> C++ enables several functions of the same name to be defined, as long as they have different signatures.
>
> This is called function overloading.
>
> The C++ compiler selects the proper function to call by examining the number, types and order of the arguments in the call.
>
> Function overloading is used to create several functions of the *same* name that perform similar tasks, but on different data types.
>
> c++允许定义多个同名函数，只要它们具有不同的签名即可。
> 这被称为函数重载。
> c++编译器通过检查调用中参数的数量、类型和顺序来选择要调用的适当函数。
> 函数重载用于创建多个同名的函数，这些函数执行类似的任务，但使用不同的数据类型。

重载的函数可以有不同的返回类型，但是必须有不同的形参列表。编译器通过形参列表来区分重载的函数。



> 函数重载（Function Overloading）是C++中一种允许在同一个作用域内定义多个同名函数的特性，这些函数必须具有不同的参数列表（参数的数量、类型或顺序不同）。函数重载的主要目的是提高代码的可读性和可维护性，使得同一操作可以适用于不同类型的数据。
>
> ### 函数重载的规则
>
> 1. **参数列表必须不同**：
>    - 函数的参数数量不同。
>    - 参数的类型不同。
>    - 参数的顺序不同（对于不同类型的参数）。
>
> 2. **返回类型不参与重载**：
>    - 函数的返回类型不用于区分重载函数。
>
> ### 示例
>
> 以下是函数重载的几个例子：
>
> ```cpp
> #include <iostream>
> using namespace std;
> 
> // 重载函数 'print'
> void print(int i) {
>     cout << "Printing int: " << i << endl;
> }
> 
> void print(double d) {
>     cout << "Printing double: " << d << endl;
> }
> 
> void print(string s) {
>     cout << "Printing string: " << s << endl;
> }
> 
> int main() {
>     print(10);        // 调用 print(int)
>     print(5.7);       // 调用 print(double)
>     print("Hello");   // 调用 print(string)
>     return 0;
> }
> ```
>
> 在这个例子中，函数 `print` 被重载了三次，分别接受 `int`、`double` 和 `string` 类型的参数。根据传递的参数类型，编译器会选择调用相应的重载函数。
>
> ### 注意事项
>
> 1. **默认参数和函数重载**：
>
>    - 默认参数与函数重载结合使用时，可能会导致二义性问题。
>
>    ```cpp
>    void func(int i, int j = 10);
>    void func(int i);
>    
>    int main() {
>        func(5); // 调用 func(int) 或 func(int, int) 都可以
>        return 0;
>    }
>    ```
>
>    在这种情况下，编译器无法确定调用哪个函数，会产生二义性错误。
>
> 2. **函数重载与模板**：
>
>    - 模板函数也可以重载，但要注意模板函数和普通函数的匹配规则。
>
>    ```cpp
>    template <typename T>
>    void func(T x) {
>        cout << "Template function: " << x << endl;
>    }
>    
>    void func(int x) {
>        cout << "Non-template function: " << x << endl;
>    }
>    
>    int main() {
>        func(10); // 调用非模板函数，因为它是一个更具体的匹配
>        func(5.5); // 调用模板函数，因为没有更具体的匹配
>        return 0;
>    }
>    ```
>
> 3. **重载与类型转换**：
>
>    - 类型转换可能会导致意想不到的重载解析结果。
>
>    ```cpp
>    void func(int x) {
>        cout << "Int function: " << x << endl;
>    }
>       
>    void func(double x) {
>        cout << "Double function: " << x << endl;
>    }
>       
>    int main() {
>        func('a'); // 调用 func(int)，因为 'a' 可以转换为 int
>        return 0;
>    }
>    ```
>
>    在这种情况下，`char` 类型的 `'a'` 会被转换为 `int` 类型，调用 `func(int)`。
>
> ### 函数重载的实际应用
>
> 函数重载在实际编程中非常有用，可以使代码更加简洁和易于维护。例如，标准库中的 `abs` 函数就有多个重载版本，用于处理不同类型的参数：
>
> ```cpp
> int abs(int n);
> long abs(long n);
> long long abs(long long n);
> float abs(float n);
> double abs(double n);
> long double abs(long double n);
> ```
>
> 通过重载 `abs` 函数，标准库提供了一种统一的接口，可以计算不同类型数字的绝对值，而不需要用户记住不同的函数名称。
>
> ### 总结
>
> - **函数重载**：允许在同一个作用域内定义多个同名函数，必须具有不同的参数列表。
> - **参数列表**：可以通过参数数量、类型或顺序来区分。
> - **返回类型**：不参与重载的区分。
> - **应用场景**：提高代码可读性和维护性，统一接口处理不同类型的数据。
>
> 函数重载是C++中的重要特性之一，掌握函数重载有助于编写更灵活、可维护的代码。



### 函数的尾随返回值类型

> 在C++11中，引入了一种新的函数返回值声明方式，称为尾随返回类型（trailing return type）。这种方式将返回类型写在函数签名的末尾，而不是像传统方法那样写在函数名前面。尾随返回类型在某些情况下特别有用，例如当返回类型依赖于参数类型时。
>
> ### 基本语法
>
> 尾随返回类型使用箭头符号 `->`，并将返回类型写在函数签名的最后。下面是一个简单的例子：
>
> ```cpp
> auto add(int a, int b) -> int {
>  return a + b;
> }
> ```
>
> 在这个例子中，`add` 函数的返回类型是 `int`，写在函数签名的最后。
>
> ### 使用场景
>
> 尾随返回类型在以下几个场景中特别有用：
>
> 1. **返回类型依赖于模板参数**：
>    当返回类型依赖于函数参数的类型时，使用尾随返回类型可以更清晰地表达类型关系。
>
> 2. **简化类型声明**：
>    当返回类型是一个复杂的类型（如函数指针或带有多个模板参数的类型）时，使用尾随返回类型可以使代码更简洁和易读。
>
> ### 示例
>
> #### 返回类型依赖于模板参数
>
> 假设有一个模板函数，返回类型依赖于模板参数类型的某些操作。在这种情况下，使用尾随返回类型可以很方便地表达这种依赖关系。
>
> ```cpp
> #include <iostream>
> #include <type_traits>
> 
> template <typename T, typename U>
> auto add(T t, U u) -> decltype(t + u) {
>     return t + u;
> }
> 
> int main() {
>     auto result = add(1, 2.5); // result 的类型是 double
>     std::cout << result << std::endl; // 输出 3.5
>     return 0;
> }
> ```
>
> 在这个例子中，`add` 函数的返回类型是 `decltype(t + u)`，表示 `t` 和 `u` 相加后的类型。使用尾随返回类型，可以让返回类型的定义依赖于参数类型。
>
> #### 复杂类型声明
>
> 对于一些复杂的返回类型（例如，返回一个函数指针），尾随返回类型可以使声明更简洁。
>
> ```cpp
> #include <iostream>
> 
> // 使用传统方式声明返回函数指针的函数
> int (*function1(int)) (int);
> 
> // 使用尾随返回类型声明返回函数指针的函数
> auto function2(int) -> int(*)(int);
> 
> int add(int x) {
>     return x + 1;
> }
> 
> int main() {
>     function1 = add;
>     function2 = add;
> 
>     std::cout << function1(5) << std::endl; // 输出 6
>     std::cout << function2(5) << std::endl; // 输出 6
> 
>     return 0;
> }
> 
> int (*function1(int))(int) {
>     return add;
> }
> 
> auto function2(int) -> int(*)(int) {
>     return add;
> }
> ```
>
> 在这个例子中，`function1` 和 `function2` 都返回一个指向函数的指针。使用尾随返回类型，可以使返回类型的声明更加直观和易读。
>
> ### 总结
>
> - **尾随返回类型**：在C++11引入的一种新的函数返回类型声明方式，将返回类型写在函数签名的末尾。
> - **语法**：`auto 函数名(参数列表) -> 返回类型`
> - **适用场景**：
>   - 当返回类型依赖于函数参数类型时（特别是模板函数）。
>   - 当返回类型较复杂时，使代码更简洁和易读。
> - **示例**：模板函数、返回复杂类型（如函数指针）。
>
> 尾随返回类型在现代C++编程中提供了更大的灵活性和可读性，特别是在处理模板和复杂类型时。



> `decltype` 是 C++11 引入的一种关键字，用于获取表达式的数据类型。它的主要作用是在编译时推导出表达式的类型，并且可以用于定义变量、函数返回类型以及模板参数等。
>
> ### 基本语法
>
> `decltype` 关键字后面跟着一个表达式，用于推导该表达式的类型。
>
> ```cpp
> decltype(expression) variable_name;
> ```
>
> 在这个语法中，`expression` 是任何有效的表达式，可以是变量、函数调用、算术运算等。
>
> ### 示例
>
> #### 定义变量的类型与表达式相同
>
> ```cpp
> int x = 5;
> decltype(x) y; // 'y' 的类型为 'int'
> ```
>
> 在这个示例中，`decltype(x)` 返回的类型与变量 `x` 的类型相同，即 `int`。
>
> #### 定义变量的类型与函数调用的返回类型相同
>
> ```cpp
> int func() {
>  return 42;
> }
> 
> decltype(func()) result; // 'result' 的类型为 'int'
> ```
>
> 在这个示例中，`decltype(func())` 返回的类型与函数 `func()` 的返回类型相同，即 `int`。
>
> #### 获取数组元素类型
>
> ```cpp
> int arr[] = {1, 2, 3, 4, 5};
> decltype(arr[0]) element; // 'element' 的类型为 'int'
> ```
>
> 在这个示例中，`decltype(arr[0])` 返回的类型与数组 `arr` 的元素类型相同，即 `int`。
>
> #### 函数返回类型推导
>
> ```cpp
> template <typename T, typename U>
> auto add(T t, U u) -> decltype(t + u) {
>  return t + u;
> }
> ```
>
> 在这个示例中，`add` 函数返回类型使用了 `decltype(t + u)`，表示该函数的返回类型与 `t + u` 表达式的类型相同。
>
> ### 注意事项
>
> 1. **表达式不执行**：`decltype` 只会获取表达式的类型，而不会执行表达式。因此，即使表达式是不合法的或者不完整的，也不会引发编译错误，只有当 `decltype` 语句被使用时才会检查表达式的合法性。
>
> 2. **表达式中的括号**：`decltype` 会保留表达式中的括号，以及可能的引用、常量性等。
>
> ```cpp
> int x = 5;
> decltype((x)) y = x; // 'y' 的类型为 'int&'，而不是 'int'
> ```
>
> 在这个示例中，`decltype((x))` 返回的类型是 `int&`，因为表达式 `(x)` 是一个左值引用。
>
> ### 总结
>
> - **`decltype` 关键字**：用于获取表达式的类型。
> - **语法**：`decltype(expression)`
> - **适用场景**：
>   - 定义变量的类型与表达式的类型相同。
>   - 定义函数返回类型与表达式的类型相同。
>   - 获取数组元素类型。
> - **注意事项**：
>   - 表达式不执行，只获取类型。
>   - 保留表达式中的括号和可能的引用、常量性。
>
> `decltype` 关键字在模板、泛型编程、自动类型推导等方面具有重要作用，使得 C++ 中的类型推导更加灵活和方便。