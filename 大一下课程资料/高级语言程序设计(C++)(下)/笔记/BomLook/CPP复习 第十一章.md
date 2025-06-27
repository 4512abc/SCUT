# CPP复习 第十一章

## public private protected 继承

**注意： 以上三种中 基类的private成员都是不可以被它的派生类直接访问的 但是它们仍然被继承下来**
public继承中：其他类型的成员仍然在作为派生类的成员时保持看其原有的访问权限 如public还是public，protected还是protected
通过基类继承来的成员函数，派生类可以操作积累的private成员（前提是原来基类有提供这种功能）
注意：友元函数是不被继承的



**注意：由public继承的派生类，继承了所有基类中处构造函数外的所有成员，每个类都提供了自己的构造函数。析构也是同理。**



![image-20240607150422748](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607150422748.png)

注意：这里虽然没有继承基类的构造函数，但是可以调用基类的构造函数来实现派生类的构造函数。setBaseSalary是新增的内容
cpp要求派生类构造函数调用其基类的构造函数，来初始化继承到派生类的基类的数据成员，所以使用成员初始化器来初始化基类的数据成员，将参数传递给基类的构造函数，**注意参数需要与基类的构造函数定义相符合**。





> Figure 11.11 shows BasePlusCommissionEmployee’s member-function implementations.
> The constructor introduces base-class initializer syntax, which uses a member initializer to pass arguments to the base-class constructor.
> C++ requires that a derived-class constructor call its base-class constructor to initialize the base-class data members that are inherited into the derived class.
> If BasePlusCommissionEmployee’s constructor did not invoke class CommissionEmployee’s constructor explicitly, C++ would attempt to invoke class CommissionEmployee’s default constructor—but the class does not have such a constructor, so the compiler would issue an error.
> 图11.11显示了BasePlusCommissionEmployee的成员函数实现。
> 构造函数引入基类初始化式语法，该语法使用成员初始化式将参数传递给基类构造函数。
> c++要求派生类构造函数调用其基类构造函数来初始化继承到派生类中的基类数据成员。
> 如果BasePlusCommissionEmployee的构造函数没有显式地调用类CommissionEmployee的构造函数，c++将尝试调用类CommissionEmployee的默认构造函数——但是类没有这样的构造函数，因此编译器将发出错误。

**C++严格执行访问私有数据成员的限制，因此即使是派生类(与其基类密切相关)也不能访问基类的私有数据。**



> Including the Base-Class Header in the Derived-Class Header with #include
> We #include the base class’s header in the derived class’s header (line 8 of Fig. 11.10).
> This is necessary for three reasons.
> The derived class uses the base class’s name in line 10, so we must tell the compiler that the base class exists.
> The compiler uses a class definition to determine the size of an object of that class. A client program that creates an object of a class #includes the class definition to enable the compiler to reserve the proper amount of memory for the object.
> The compiler must determine whether the derived class uses the base class’s inherited members properly.
>
> 用#include将基类头包含在派生类头中
> 我们将基类的头文件包含在派生类的头文件中(图11.10的第8行)。
> 这是必要的，原因有三。
> 1、派生类在第10行使用基类的名称，**因此必须告诉编译器基类存在**。
> 2、编译器使用类定义来确定该类对象的大小。创建类的对象的客户端程序包含类定义，**以使编译器能够为该对象保留适当数量的内存。**
> 3、编译器必须确定派生类是否正确地使用基类的继承成员



> Linking Process in an Inheritance Hierarchy
> In Section 3.7, we discussed the linking process for creating an executable GradeBook application.
> The linking process is similar for a program that uses classes in an inheritance hierarchy.
> The process requires the object code for all classes used in the program and the object code for the direct and indirect base classes of any derived classes used by the program.
> The code is also linked with the object code for any C++ Standard Library classes used in the classes or the client code.
> 继承层次结构中的链接过程
> 在第3.7节中，我们讨论了创建可执行的GradeBook应用程序的链接过程。
> 链接过程与在继承层次结构中使用类的程序类似。
> 该过程需要程序中使用的所有类的目标代码，以及程序使用的任何派生类的直接和间接基类的目标代码。
> 代码还与类或客户端代码中使用的任何c++标准库类的目标代码链接。



**基类的受保护成员可以在基类的主体内访问，基类的成员和友类，以及从基类派生的任何类的成员和友类都可以访问。**



> Defining Base Class CommissionEmployee with protected Data
> Class CommissionEmployee (Fig. 11.12) now declares data members firstName, lastName, socialSecurityNumber, grossSales and commissionRate as protected (lines 31–36) rather than private.
> The member-function implementations are identical to those in Fig. 11.5.
> 用受保护的数据定义基类CommissionEmployee
> 类CommissionEmployee(图11.12)现在将数据成员firstName、lastName、socialSecurityNumber、grossSales和commissionRate声明为protected(第31-36行)，而不是private。
> 成员函数的实现与图11.5中的实现相同。

![image-20240607154700559](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607154700559.png)

**派生类的对象也可以访问该派生类的任何间接基类中的受保护成员。**





> Notes on Using protected Data
> Inheriting protected data members slightly increases performance, because we can directly access the members without incurring the overhead of calls to set or get member functions.
> 使用受保护资料须知
> 继承受保护的数据成员会略微提高性能，因为我们可以直接访问成员，而不会产生设置或获取成员函数的调用开销。
>
> 在多数情况下，使用private数据成员是更好的软件工程方法，把代码优化交给编译器就可以了。代码也过冗余维护修改和调试





> Using protected data members creates two serious problems.
> The derived-class object does not have to use a member function to set the value of the base class’s protected data member.
> Derived-class member functions are more likely to be written so that they depend on the base-class implementation. Derived classes should depend only on the base-class services (i.e., non-private member functions) and not on the base-class implementation.
> With protected data members in the base class, if the base-class implementation changes, we may need to modify all derived classes of that base class.
> Such software is said to be fragile or brittle, because a small change in the base class can “break” derived-class implementation.
>
> 使用受保护的数据成员会产生两个严重的问题。
> 派生类对象不必使用成员函数来设置基类受保护的数据成员的值。
> 派生类成员函数更有可能被编写为依赖于基类实现。派生类应该只依赖于基类服务(即，非私有成员函数)，而不依赖于基类实现。
> 对于基类中受保护的数据成员，如果基类实现发生变化，我们可能需要修改该基类的所有派生类。
> 这样的软件被认为是脆弱的，因为基类中的一个小变化就可以“破坏”派生类的实现。



![image-20240607160220270](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607160220270.png)

> 在基类仅向其派生类或者友元，提供服务时（例如非private成员函数时），使用protected成员访问标识符是合适的。
>
> 将基类的数据成员声明为private，可以在修改基类的实现时，不需要修改派生类的实现。





> 注意：从派生类调用重新定义的基类成员函数时使用的语法——将基类名称和二进制作用域解析操作符(::)放在基类成员函数名称之前。
> 注意：必须加上基类类名和:: 否则会造成无限递归的错误，即自己调用自己。
>
> 良好的软件工程实践:如果一个对象的成员函数执行了另一个对象所需的操作，我们应该调用该成员函数，而不是复制它的代码体。





> 子类对象可以直接访问子类中的同名成员。
> 子类对象可以通过加：父类名+::，来访问子类中同名成员。
> 当子类和父类具有相同名字的成员时，子类会隐藏从父类中同名的数据成员，加上父类名+::才可以访问。
> 同名的静态成员和非静态成员的处理方式也一样





> Instantiating a derived-class object begins a chain of constructor calls in which the derived-class constructor, before performing its own tasks, invokes its direct base class’s constructor either explicitly (via a base-class member initializer) or implicitly (calling the base class’s default constructor).
> If the base class is derived from another class, the base-class constructor is required to invoke the constructor of the next class up in the hierarchy, and so on.
> The last constructor called in this chain is the constructor of the class at the base of the hierarchy, whose body actually finishes executing first.
> The most derived-class constructor’s body finishes executing last.
> Each base-class constructor initializes the base-class data members that the derived-class object inherits.
>
> 派生类对象的实例化开始了构造函数调用链，其中派生类构造函数在执行自己的任务之前，显式(通过基类成员初始化项)或隐式(调用基类的默认构造函数)调用其直接基类的构造函数。
> 如果基类派生自另一个类，则基类构造函数需要调用层次结构中上一个类的构造函数，依此类推。
> 在此链中调用的最后一个构造函数是位于层次结构基础的类的构造函数，它的主体实际上首先完成执行。
> 派生最多的类的构造函数体最后完成执行。
> 每个基类构造函数初始化派生类对象继承的基类数据成员。



![image-20240607163345485](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607163345485.png)

先构造父类，在构造子类，析构的顺序相反。
派生类对象被创建时，派生类的构造函数先被调用（立即调用父类的构造函数，父类的构造函数被执行）。后调用成员初始化器，最后调用派生类构造函数的函数体执行。





> When a derived-class object is destroyed, the program calls that object’s destructor.
> This begins a chain (or cascade) of destructor calls in which the derived-class destructor and the destructors of the direct and indirect base classes and the classes’ members execute in reverse of the order in which the constructors executed.
> When a derived-class object’s destructor is called, the destructor performs its task, then invokes the destructor of the next base class up the hierarchy.
> This process repeats until the destructor of the final base class at the top of the hierarchy is called.
> Then the object is removed from memory.
> 当一个派生类对象被销毁时，程序调用该对象的析构函数。
> 这开始了析构函数调用链(或级联)，其中派生类的析构函数、直接基类和间接基类的析构函数以及类成员的执行顺序与构造函数的执行顺序相反。
> 当调用派生类对象的析构函数时，析构函数执行其任务，然后调用层次结构上的下一个基类的析构函数。
> 这个过程一直重复，直到调用位于层次结构顶端的最后一个基类的析构函数。
> 然后从内存中删除对象。





> Base-class constructors, destructors and overloaded assignment operators (Chapter 10) are not inherited by derived classes.
> Derived-class constructors, destructors and overloaded assignment operators, however, can call base-class versions.
> 基类的构造函数、析构函数和重载赋值操作符(第10章)不能被派生类继承。
> 但是，派生类的构造函数、析构函数和重载赋值操作符可以调用基类的版本。





## C++11：继承自基类的构造函数

> 在C++中，继承基类的构造函数是一个非常有用的功能，特别是当你希望子类继承和使用基类的构造函数。自C++11起，C++引入了一种新的语法来简化这个过程。下面是如何在C++中实现继承基类的构造函数。
>
> ### 基类和子类的定义
>
> 假设你有一个基类 `Base` 和一个子类 `Derived`。
>
> ```cpp
> #include <iostream>
> #include <string>
> 
> // 定义基类 Base
> class Base {
> public:
>  // 基类构造函数
>  Base(int a, double b) : m_a(a), m_b(b) {
>      std::cout << "Base constructor called with a = " << m_a << ", b = " << m_b << std::endl;
>  }
> 
> private:
>  int m_a;
>  double m_b;
> };
> 
> // 定义子类 Derived
> class Derived : public Base {
> public:
>  // 继承基类的构造函数
>  //使用Base::Base;
> 	//在派生类定义中的任何地方。
>  using Base::Base;
> 
>  // 你可以在子类中添加更多成员和函数
>  void display() {
>      std::cout << "Derived class function called." << std::endl;
>  }
> };
> 
> int main() {
>  // 使用继承的基类构造函数来创建 Derived 对象
>  Derived obj(42, 3.14);
>  obj.display();
> 
>  return 0;
> }
> ```
>
> ### 代码解释
>
> 1. **基类定义：**
>    - `Base` 类包含一个带有两个参数（`int` 和 `double`）的构造函数。
>    - 构造函数的实现打印出传递给它的参数值。
>
> 2. **子类定义：**
>    - `Derived` 类继承自 `Base` 类。
>    - `using Base::Base;` 这一行代码告诉编译器将基类 `Base` 的构造函数引入到子类 `Derived` 中。这允许你使用 `Base` 的构造函数来创建 `Derived` 对象。
>    - `Derived` 类中还定义了一个 `display` 函数，用于演示子类特有的功能。
>
> 3. **主函数：**
>    - 在 `main` 函数中，我们使用 `Base` 的构造函数来创建一个 `Derived` 对象，并传递两个参数。
>    - 创建对象时，将调用 `Base` 的构造函数，并输出相应的信息。
>    - 然后调用 `display` 函数来展示 `Derived` 类的特有功能。
>
> ### 结果
>
> 运行上述代码将输出：
>
> ```
> Base constructor called with a = 42, b = 3.14
> Derived class function called.
> ```
>
> 这种方式简化了代码，特别是在基类有多个构造函数的情况下，子类可以通过 `using` 语句一次性继承所有这些构造函数，而不必逐个定义。
>
> 希望这个示例能帮助你理解如何在C++中继承基类的构造函数。如果有更多问题或需要进一步的解释，请随时问我！





> When you inherit constructors:
> By default, each inherited constructor has the same access level (public, protected or private) as its corresponding base-class constructor. 
> The default, copy and move constructors are not inherited. 
> If a constructor is deleted in the base class by placing = delete in its prototype, the corresponding constructor in the derived class is also deleted.
> If the derived class does not explicitly define constructors, the compiler generates a default constructor in the derived class—even if it inherits other constructors from its base class.
> If a constructor that you explicitly define in a derived class has the same parameter list as a base-class constructor, then the base-class constructor is not inherited. 
> A base-class constructor’s default arguments are not inherited. Instead, the compiler generates overloaded constructors in the derived class.
> 当你继承构造函数时:
> 默认情况下，每个继承的构造函数与其相应的基类构造函数具有相同的访问级别(public、protected或private)。
> 默认的、复制的和移动的构造函数是不被继承的。
> 如果通过在原型中放置= delete来删除基类中的构造函数，则派生类中相应的构造函数也会被删除。
> 如果派生类没有显式定义构造函数，则编译器在派生类中生成默认构造函数——即使它从基类继承了其他构造函数。
> 如果在派生类中显式定义的构造函数具有与基类构造函数相同的参数列表，则不继承基类构造函数。
> 基类构造函数的默认参数不被继承。相反，编译器在派生类中生成重载构造函数。





> When deriving a class from a base class, the base class may be inherited through public, protected or private inheritance.
> Use of protected and private inheritance is rare.
> Figure 11.16 summarizes for each type of inheritance the accessibility of base-class members in a derived class.
> The first column contains the base-class access specifiers.
> A base class’s private members are never accessible directly from a derived class, but can be accessed through calls to the public and protected members of the base class.
> 从基类派生类时，基类可以通过公共继承、保护继承或私有继承继承。很少使用受保护的私有继承。
> 图11.16总结了每种继承类型对派生类中基类成员的可访问性。
> 第一列包含基类访问说明符。
> 基类的私有成员永远不能从派生类直接访问，但可以通过调用基类的公共成员和受保护成员来访问

![image-20240607164759069](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607164759069.png)



