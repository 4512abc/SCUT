# Cpp复习 第十八章

C++中的模板是一种通用编程的工具，使得函数和类能够以独立于具体类型的方式进行定义，从而支持代码复用。模板分为函数模板和类模板，此外还有模板特化、非类型模板参数和模板元编程等高级特性。

### 函数模板

函数模板允许编写独立于具体数据类型的函数。使用函数模板可以避免编写多个功能相同但参数类型不同的函数。

#### 基本语法

```cpp
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}
```

在这里，`max` 是一个函数模板，`T` 是一个模板参数，表示任意类型。可以用不同的类型实例化这个模板，例如 `int` 或 `double`：

```cpp
int main() {
    std::cout << max(3, 7) << std::endl;          // 实例化为 int 类型的 max 函数
    std::cout << max(3.14, 2.71) << std::endl;    // 实例化为 double 类型的 max 函数
    return 0;
}
```

### 类模板

类模板允许编写独立于具体数据类型的类。使用类模板可以定义通用的数据结构，例如栈、队列、链表等。

#### 基本语法

```cpp
template<typename T>
class Stack {
private:
    std::vector<T> elems;
public:
    void push(T const& elem) {
        elems.push_back(elem);
    }
    void pop() {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elems.pop_back();
    }
    T top() const {
        if (elems.empty()) {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elems.back();
    }
};
```

可以用不同的类型实例化这个模板，例如 `int` 或 `std::string`：

```cpp
int main() {
    Stack<int> intStack;
    intStack.push(7);
    std::cout << intStack.top() << std::endl;

    Stack<std::string> stringStack;
    stringStack.push("hello");
    std::cout << stringStack.top() << std::endl;

    return 0;
}
```

### 模板特化

模板特化允许为特定类型提供不同的实现，分为全特化和偏特化。

#### 全特化

```cpp
template<>
class Stack<bool> {
private:
    std::vector<bool> elems;
public:
    void push(bool elem) {
        elems.push_back(elem);
    }
    void pop() {
        if (elems.empty()) {
            throw std::out_of_range("Stack<bool>::pop(): empty stack");
        }
        elems.pop_back();
    }
    bool top() const {
        if (elems.empty()) {
            throw std::out_of_range("Stack<bool>::top(): empty stack");
        }
        return elems.back();
    }
};
```

#### 偏特化（类模板）

偏特化只适用于类模板，不适用于函数模板。

```cpp
template<typename T>
class Container {
    // 通用实现
};

template<typename T>
class Container<T*> {
    // 指针类型的偏特化实现
};
```

### 非类型模板参数

非类型模板参数允许模板参数是一个常量值而不是类型。

```cpp
template<typename T, int size>
class Array {
private:
    T elems[size];
public:
    T& operator[](int index) {
        return elems[index];
    }
    int getSize() const {
        return size;
    }
};
```

可以用不同的类型和大小实例化这个模板：

```cpp
int main() {
    Array<int, 10> intArray;
    std::cout << intArray.getSize() << std::endl;

    Array<double, 5> doubleArray;
    std::cout << doubleArray.getSize() << std::endl;

    return 0;
}
```

### 模板元编程

模板元编程是一种在编译期进行计算的编程技术，可以用于生成复杂的数据结构和算法。

#### 简单的例子：计算阶乘

```cpp
template<int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    std::cout << "Factorial<5>::value = " << Factorial<5>::value << std::endl;
    return 0;
}
```

输出：

```
Factorial<5>::value = 120
```

在这个例子中，`Factorial<5>` 在编译期计算出结果 `120`。

### 总结

- **函数模板**：用于定义独立于数据类型的函数。
- **类模板**：用于定义独立于数据类型的类。
- **模板特化**：用于为特定类型提供不同的实现。
- **非类型模板参数**：允许模板参数是常量值。
- **模板元编程**：在编译期进行计算。

模板是C++中非常强大且灵活的特性，使得编写高效、通用的代码成为可能。通过理解和使用模板，可以大大提升代码的复用性和可维护性。



> **注意：如果要使用用户自定义类型来创建一个模板的特化，那么用户提供的自定义类型，需要满足模板的要求。**
> 比方说可能要重载运算符<或者需要调用某一个函数。



> Class templates are called parameterized types, because they require one or more type parameters to specify how to customize a generic class template to form a class-template specialization.
> When a particular specialization is needed, you use a concise, simple notation, and the compiler writes the specialization source code.
>
> 类模板称为参数化类型，因为它们需要一个或多个类型参数来指定如何自定义泛型类模板
> 以形成类模板专门化。
> 当需要特定的专门化时，使用简洁、简单的符号，由编译器编写专门化源代码。



**注意：所有类模板都需要以关键字template开始，后面是括在一对尖括号(<和>)中的模板形参表**

```cpp
template<typename/class T>
```





`deque`（双端队列）和 `vector` 是 C++ 标准库中两种常用的容器，它们在内部实现、性能特征和使用场景上有显著区别。了解它们之间的区别有助于在编程中做出最佳选择。

### 基本定义

- **vector**：一种动态数组，提供连续的内存存储，支持高效的随机访问。
- **deque**：双端队列，支持在两端高效插入和删除操作，内部实现通常是分段连续的（即一系列连续的小块）。

### 内部实现

- **vector**：使用单一的连续内存块存储元素。如果需要扩展容量，会分配一个更大的内存块，并将原有元素复制到新内存块。
- **deque**：使用一系列固定大小的内存块来存储元素，这些块由一个指向块指针的数组管理。这样实现使得在头尾插入和删除元素更加高效。

### 内存布局

- **vector**：连续存储，所有元素在内存中是紧密排列的。这使得`vector`可以提供高效的随机访问，支持常数时间复杂度的索引操作。
- **deque**：分段存储，元素分布在多个小的连续内存块中。这使得在两端进行插入和删除操作更为高效，但随机访问的性能稍逊于`vector`。

### 访问和修改性能

- **随机访问**：
  - `vector`：提供常数时间复杂度的随机访问（通过索引）。
  - `deque`：提供平均常数时间复杂度的随机访问，但由于分段存储，访问性能稍差于`vector`。
- **插入和删除**：
  - `vector`：在尾部插入和删除操作是常数时间复杂度，但在中间或头部插入和删除需要线性时间复杂度，因为需要移动元素。
  - `deque`：在头部和尾部插入和删除操作都是常数时间复杂度，因为只需调整指针而不必移动元素。

### 迭代器

- **vector**：由于连续存储，`vector` 的迭代器是随机访问迭代器，支持所有标准迭代器操作。
- **deque**：迭代器也是随机访问迭代器，但由于分段存储，其实现更复杂，性能可能不如 `vector` 的迭代器。

### 使用场景

- **vector**：适合需要频繁随机访问，插入和删除操作主要在尾部进行的场景。典型使用包括动态数组、栈实现等。
- **deque**：适合需要在两端频繁插入和删除元素的场景，如双端队列、滑动窗口等。

### 示例代码

以下是 `vector` 和 `deque` 的一些简单示例，展示它们的用法和性能特征。

#### vector 示例

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    
    // 随机访问
    std::cout << "Element at index 5: " << vec[5] << std::endl;
    
    // 尾部插入
    vec.push_back(10);
    
    // 中间插入
    vec.insert(vec.begin() + 5, 20);
    
    for (int elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### deque 示例

```cpp
#include <iostream>
#include <deque>

int main() {
    std::deque<int> deq;
    for (int i = 0; i < 10; ++i) {
        deq.push_back(i);
    }
    
    // 随机访问
    std::cout << "Element at index 5: " << deq[5] << std::endl;
    
    // 尾部插入
    deq.push_back(10);
    
    // 头部插入
    deq.push_front(20);
    
    for (int elem : deq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 总结

- **vector**：连续存储，适合需要高效随机访问和在尾部进行插入删除的场景。
- **deque**：分段存储，适合需要在两端高效插入删除的场景，随机访问性能稍逊于`vector`。

选择合适的容器取决于具体的使用场景和性能需求。



> Class Template Stack<T>’s Data Representation
> A stack requires insertions and deletions only at its top. 
> So, for example, a vector or a deque could be used to store the stack’s elements. 
> A vector supports fast insertions and deletions at its back. 
> A deque supports fast insertions and deletions at its front and its back. 
> A deque is the default representation for the Standard Library’s stack adapter because a deque grows more efficiently than a vector. 
>
> 类模板栈<T>的数据表示
> 堆栈只需要在顶部进行插入和删除操作。
> 例如，可以使用vector或deque来存储堆栈的元素。
> vector支持在其背面快速插入和删除。
> deque支持前端和尾部的快速插入和删除操作。
> deque是标准库堆栈适配器的默认表示形式，因为deque比vector增长更有效。



> A vector is maintained as a contiguous block of memory—when that block is full and a new element is added, the vector allocates a larger contiguous block of memory and copies the old elements into that new block. 
> A deque, on the other hand, is typically implemented as list of fixed-size, built-in arrays—new fixed-size built-in arrays are added as necessary and none of the existing elements are copied when new items are added to the front or back. 
> For these reasons, we use a deque (line 42) as the underlying container for our Stack class.
>
> vector是作为一个连续的内存块来维护的——当该内存块已满并添加新元素时，vector会分配一个更大的连续内存块，并将旧元素复制到新内存块中。
> 另一方面，deque通常是作为固定大小的内置数组列表实现的——根据需要添加新的固定大小的内置数组，并且当向前面或后面添加新项时，不会复制现有元素。
> 由于这些原因，我们使用deque(第42行)作为Stack类的底层容器。



> Declaring a Class Template’s Member Functions Outside the Class Template Definition
> Though we did not do so in our Stack class template, member-function definitions can appear outside a class template definition. 
> If you do this, each must begin with the template keyword followed by the same set of template parameters as the class template. 
> In addition, the member functions must be qualified with the class name and scope resolution operator. 
> 在类模板定义之外声明类模板的成员函数
> 虽然在Stack类模板中没有这样做，但成员函数定义可以出现在类模板定义之外。
> 如果这样做，每个模板都必须以template关键字开头，后跟与类模板相同的一组模板参数。
> 此外，成员函数必须使用类名和作用域解析操作符进行限定。



> For example, you can define the pop function outside the class-template definition as follows: 
> template< typename T >
> inline void Stack<T>::pop()
> {
> stack.pop_front();
> } // end function template pop
> Stack<T>:: indicates that pop is in the scope of class Stack<T>. 
> The Standard Library’s container classes tend to define all their member functions inside their class definitions. 
> 例如，你可以在类模板定义之外定义pop函数，如下所示:
>
> ```cpp
> template< typename T >
> inline void Stack<T>::pop()
> {
> stack.pop_front ();
> } //结束函数模板pop
> ```
>
> Stack<T>::表示pop在类Stack<T>的作用域中。
>
> 标准库的容器类倾向于在其类定义中定义其所有成员函数。





![image-20240608013650662](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608013650662.png)

![image-20240608013658864](C:\Users\22635\Desktop\整合\笔记\cpp\image-20240608013658864.png)

![image-20240608013713874](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608013713874.png)

> Function template testStack uses T (specified at line 10) to represent the data type stored in the Stack<T>. 
> The function template takes five arguments (lines 12–16):
> the Stack<T> to manipulate
> a value of type T that will be the first value pushed onto the Stack<T>
> a value of type T used to increment the values pushed onto the Stack<T>
> the number of elements to push onto the Stack<T> 
> a string that represents the name of the Stack<T> object for output purposes
>
> 函数模板testStack使用T(在第10行指定)来表示存储在Stack<T>中的数据类型。
> 函数模板接受5个参数(第12-16行):
> 要操作的Stack<T>
> 类型为T的值，它将是第一个压入堆栈的值<T>
> 一个T类型的值，用于增加压入Stack的值<T>
> 要压入堆栈的元素数<T>
> 用于输出目的的表示Stack<T>对象名称的字符串



> Function main (lines 41–50) instantiates an object of type Stack<double> called doubleStack (line 43) and an object of type Stack<int> called intStack (line 47) and uses these objects in lines 45 and 49. 
> The compiler infers the type of T for testStack from the type used to instantiate the function’s first argument (i.e., the type used to instantiate doubleStack or intStack). 
>
> 函数main(第41-50行)实例化了一个名为doubleStack的Stack<double>类型对象(第43行)和一个名为intStack的Stack<int>类型对象(第47行)，并在第45行和第49行使用了这些对象。
>
> 编译器从用于实例化函数第一个参数的类型，(即用于实例化doubleStack或intStack的类型)推断出testStack的T类型。



> 非类型形参：可以在模板的参数列表中使用非类型模板形参，它可以具有默认的实参，并且是作为常数处理。
> eg：array类模板 template<class T,size_t N>



> In addition, a type parameter can specify a default type argument. 
> For example, the C++ standard’s stack container adapter class template begins with:  
>
> ```cpp
> 	template < class T, class Container = deque< T > >
> ```
>
> which specifies that a stack uses a deque by default to store the stack’s elements of type T. 
> 此外，类型形参可以指定默认类型实参。
> 例如，c++标准的堆栈容器适配器类模板以：
>
> ```cpp
> 	template < class T, class Container = deque< T > >
> ```
>
> 它指定堆栈在默认情况下使用deque来存储堆栈的T类型元素。





> Default type parameters must be the rightmost (trailing) parameters in a template’s type-parameter list. 
> When you instantiate a template with two or more default arguments, if an omitted argument is not the rightmost, then all type parameters to the right of it also must be omitted. 
> As of C++11, you can now use default type arguments for template type parameters in function templates. 
>
> 默认类型参数必须是模板类型参数列表中最右边(末尾)的参数。
>
> **当使用两个或更多默认实参实例化模板时，如果省略的实参不是最右边的，那么它右边的所有类型形参也必须省略。**
>
> 从c++11开始，现在可以在函数模板中为模板类型形参使用默认类型实参。



> Function templates and overloading are intimately related. 
> In Section 6.19, you learned that when overloaded functions perform identical operations on different types of data, they can be expressed more compactly and conveniently using function templates. 
> You can then write function calls with different types of arguments and let the compiler generate separate function-template specializations to handle each function call appropriately. 
> The function-template specializations generated from a given function template all have the same name, so the compiler uses overload resolution to invoke the proper function.
> 函数模板和重载密切相关。
> 在第6.19节中，您了解了当重载函数对不同类型的数据执行相同的操作时，可以使用函数模板更紧凑、更方便地表示它们。
>
> 然后，您可以使用不同类型的参数编写函数调用，并让编译器生成单独的函数模板专门化，以适当地处理每个函数调用。
>
> 从给定函数模板生成的函数模板专门化都具有相同的名称，因此编译器使用重载解析来调用适当的函数。



> You may also overload function templates. 
> For example, you can provide other function templates that specify the same function name but different function parameters. 
> A function template also can be overloaded by providing nontemplate functions with the same function name but different function parameters. 
> 你也可以重载函数模板。
>
> 例如，您可以提供指定相同函数名称但不同函数参数的其他函数模板。
>
> 函数模板也可以通过提供具有相同函数名但不同函数参数的非模板函数来重载。



> Matching Process for Overloaded Functions
> The compiler performs a matching process to determine what function to call when a function is invoked. 
> It looks at both existing functions and function templates to locate a function or generate a function-template specialization whose function name and argument types are consistent with those of the function call. 
> If there are no matches, the compiler issues an error message. If there are multiple matches for the function call, the compiler attempts to determine the best match.
> If there’s more than one best match, the call is ambiguous and the compiler issues an error message.
>
> 重载函数的匹配过程
> 编译器执行匹配过程，以确定在调用函数时调用哪个函数。
>
> 它查看现有函数和函数模板来定位函数或生成函数模板专门化，其函数名和参数类型与函数调用的函数名和参数类型一致。
>
> 如果没有匹配项，编译器将发出错误消息。
>
> 如果函数调用有多个匹配项，编译器将尝试确定最佳匹配项。
>
> 如果有多个最佳匹配，则调用是二义性的，编译器会发出错误消息。
>
> 如果调用时，函数模板和非模板函数都适用，那么将调用非模板的版本。

