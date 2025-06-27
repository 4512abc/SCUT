# CPP复习 第九章



> Coverage includes (cont.):
> How default arguments can be used in constructors.
> Destructors that perform “termination housekeeping” on objects before they’re destroyed.
> The order in which constructors and destructors are called.
> We show that returning a reference or pointer to private data breaks the encapsulation of a class, allowing client code to directly access an object’s data.
> We use default memberwise assignment to assign an object of a class to another object of the same class.
> 承保范围包括(续):
> 如何在构造函数中使用默认实参。
> 在对象被销毁之前对其执行“终止管理”的析构函数。
> 调用构造函数和析构函数的顺序。
> 我们展示了返回私有数据的引用或指针打破了类的封装，允许客户端代码直接访问对象的数据。
> 使用默认的成员赋值将类的一个对象赋值给同一类的另一个对象。



> Coverage includes (cont.):
> const objects and const member functions to prevent modifications of objects and enforce the principle of least privilege. 
> Composition—a form of reuse in which a class can have objects of other classes as members. 
> Friendship to specify that a nonmember function can also access a class’s non-public members—a technique that’s often used in operator overloading for performance reasons. 
> this pointer, which is an implicit argument in all calls to a class’s non-static member functions, allowing them to access the correct object’s data members and non-static member functions. 
> 承保范围包括(续):
> Const对象和Const成员函数，以防止对对象的修改并执行最小权限原则。
> 组合——一种重用形式，其中一个类可以拥有其他类的对象作为成员。
> 指定非成员函数也可以访问类的非公共成员——出于性能原因，在操作符重载中经常使用这种技术。
> 这个指针是所有调用类的非静态成员函数的隐式参数，允许它们访问正确对象的数据成员和非静态成员函数。



> Prevents the code between #ifndef and #endif from being included if the name TIME_H has been defined.
> If the header has not been included previously in a file, the name TIME_H is defined by the #define directive and the header file statements are included.
> If the header has been included previously, TIME_H is defined already and the header file is not included again.
> 如果已经定义了名称TIME_H，则防止包含#ifndef和#endif之间的代码。
> 如果头文件之前没有包含在文件中，则名称TIME_H由#define指令定义，并包含头文件语句。
> 如果头文件之前已经包含，TIME_H已经被定义，并且头文件不再被包含。



> Before C++11, only static const int data members (which you saw in Chapter 7) could be initialized where they were declared in the class body.
> For this reason, data members typically should be initialized by the class’s constructor as there is no default initialization for fundamental-type data members. 
> As of C++11, you can now use an in-class initializer to initialize any data member where it’s declared in the class definition. 
>
> 在c++11之前，只有静态const int数据成员(你在第7章看到过)可以在类体中声明的地方初始化。
> 由于这个原因，数据成员通常应该由类的构造函数初始化，因为基本类型数据成员没有默认初始化。
> 从c++11开始，您现在可以使用类内初始化器来初始化在类定义中声明的任何数据成员。



> Parameterized stream manipulator setfill specifies the fill character that is displayed when an integer is output in a field wider than the number of digits in the value.
> The fill characters appear to the left of the digits in the number, because the number is right aligned by default—for left aligned values, the fill characters would appear to the right.
> If the number being output fills the specified field, the fill character will not be displayed.
> Once the fill character is specified with setfill, it applies for all subsequent values that are displayed in fields wider than the value being displayed.
> 参数化流操纵符setfill指定当在大于值中位数的字段中输出整数时显示的填充字符。
> 填充字符出现在数字中数字的左边，因为默认情况下数字是右对齐的——对于左对齐的值，填充字符将出现在右边。
> 如果正在输出的数字填充了指定的字段，则不显示填充字符。
> 一旦用setfill指定了填充字符，它就应用于显示在比所显示的值更宽的字段中的所有后续值。
> 即setfill是黏性设置，注意setw不是黏性设置。



> Defining Member Functions Outside the Class Definition; Class Scope
> Even though a member function declared in a class definition may be defined outside that class definition, that member function is still within that class’s scope.
> If a member function is defined in the class’s body, the compiler attempts to inline calls to the member function.
> 在类定义之外定义成员函数;类作用域
> 即使在类定义中声明的成员函数可以在该类定义之外定义，该成员函数仍然在该类的作用域中。
> 如果在类的主体中定义了成员函数，则编译器会尝试内联调用该成员函数。



> A class’s data members and member functions belong to that class’s scope.
> Nonmember functions are defined at global namespace scope, by default.
> Within a class’s scope, class members are immediately accessible by all of that class’s member functions and can be referenced by name.
> Outside a class’s scope, public class members are referenced through one of the handles on an object—an object name, a reference to an object or a pointer to an object.
> 类的数据成员和成员函数属于该类的作用域。
> 默认情况下，非成员函数在全局命名空间范围内定义。
> 在类的作用域中，类的所有成员函数都可以立即访问类成员，并且可以通过名称引用类成员。
> 在类的作用域之外，通过对象的句柄之一(对象名称、对象引用或对象指针)引用公共类成员。



> Class Scope and Block Scope
> If a member function defines a variable with the same name as a variable with class scope, the class-scope variable is hidden in the function by the block-scope variable.
> Such a hidden variable can be accessed by preceding the variable name with the class name followed by the scope resolution operator (::).
> 类作用域和块作用域
> 如果成员函数定义了与具有类作用域的变量同名的变量，则类作用域变量被块作用域变量隐藏在函数中。
> 可以通过在变量名前面加上类名和作用域解析操作符(::)来访问这样的隐藏变量



> Dot (.) and Arrow (->) Member Selection Operators
> The dot member selection operator (.) is preceded by an object’s name or with a reference to an object to access the object’s members.
> The arrow member selection operator (->) is preceded by a pointer to an object to access the object’s members.
> 点(.)和箭头(->)成员选择操作符
> 点成员选择运算符(.)前面是对象的名称或对象的引用，以访问对象的成员。
> 箭头成员选择操作符(->)前面有一个指向对象的指针，用于访问对象的成员。



> Access Functions
> Access functions can read or display data.
> A common use for access functions is to test the truth or falsity of conditions—such functions are often called predicate functions.
> Utility Functions
> A utility function (also called a helper function) is a private member function that supports the operation of the class’s other member functions.
> 访问函数
> 访问函数可以读取或显示数据。
> 访问函数的一个常见用途是测试条件的真假——这类函数通常称为谓词函数。
> 效用函数
> 实用函数(也称为辅助函数)是一个私有成员函数，它支持类的其他成员函数的操作

   

> C++11: Using List Initializers to Call Constructors 
> C++11 now provides a uniform initialization syntax called list initializers that can be used to initialize any variable. Lines 11–13 of Fig. 9.6 can be written using list initializers as follows:
>
> ```cpp
> Time t2{ 2 }; // hour specified; minute and second defaulted     
> Time t3{ 21, 34 }; // hour and minute specified; second defaulted
> Time t4{ 12, 25, 42 }; // hour, minute and second specified 
> or
> Time t2 = { 2 }; // hour specified; minute and second defaulted     
> Time t3 = { 21, 34 }; // hour and minute specified; second defaulted
> Time t4 = { 12, 25, 42 }; // hour, minute and second specified 
> ```
>
> c++ 11:使用列表初始化式调用构造函数
> c++ 11现在提供了一种统一的初始化语法，称为列表初始化器，可用于初始化任何变量。图9.6中的第11-13行可以使用列表初始化式编写如下:
>
> ```cpp
> Time t2{ 2 }; // hour specified; minute and second defaulted     
> Time t3{ 21, 34 }; // hour and minute specified; second defaulted
> Time t4{ 12, 25, 42 }; // hour, minute and second specified 
> or
> Time t2 = { 2 }; // hour specified; minute and second defaulted     
> Time t3 = { 21, 34 }; // hour and minute specified; second defaulted
> Time t4 = { 12, 25, 42 }; // hour, minute and second specified 
> ```
>
> 不带=的形式是首选的。



> C++11: Overloaded Constructors and Delegating Constructors 
> A class’s constructors and member functions can also be overloaded. 
> Overloaded constructors typically allow objects to be initialized with different types and/or numbers of arguments. 
> To overload a constructor, provide in the class definition a prototype for each version of the constructor, and provide a separate constructor definition for each overloaded version. 
> This also applies to the class’s member functions. 
>
> c++ 11:重载构造函数和委托构造函数
> 类的构造函数和成员函数也可以被重载。
> 重载构造函数通常允许使用不同类型和/或数量的参数初始化对象。
> 要重载构造函数，请在类定义中为每个版本的构造函数提供原型，并为每个重载版本提供单独的构造函数定义。
> 这也适用于类的成员函数。



> In Figs. 9.4–9.6, the Time constructor with three parameters had a default argument for each parameter. We could have defined that constructor instead as four overloaded constructors with the following prototypes:
> Time(); // default hour, minute and second to 0
> Time( int ); // initialize hour; default minute and second to 0
> Time( int, int); // initialize hour and minute; default second to 0
> Time( int, int, int ); // initialize hour, minute and second
> C++11 now allows constructors to call other constructors in the same class. 
> The calling constructor is known as a delegating constructor—it delegates its work to another constructor. 
>
> 在图9.4-9.6中，带有三个形参的Time构造函数对每个形参都有一个默认实参。我们可以将该构造函数定义为四个重载构造函数，并使用以下原型:
>
> ```cpp
> Time(); // default hour, minute and second to 0
> Time( int ); // initialize hour; default minute and second to 0
> Time( int, int); // initialize hour and minute; default second to 0
> Time( int, int, int ); // initialize hour, minute and second
> ```
>
> c++ 11现在允许构造函数调用同一类中的其他构造函数。
> 调用构造函数称为委托构造函数——它将自己的工作委托给另一个构造函数。
>
> The first three of the four Time constructors declared on the previous slide can delegate work to one with three int arguments, passing 0 as the default value for the extra parameters. 
> Use a member initializer with the name of the class as follows:
>
> ```cpp
> Time::Time()
> Time( 0, 0, 0 ) //delegate to Time( int, int, int )
> {
> } // end constructor with no arguments
> 
> Time::Time( int hour )
> Time( hour, 0, 0 ) //delegate to Time( int, int, int )   
> {
> } // end constructor with one argument
> Time::Time( int hour, int minute )
> Time( hour, minute, 0 ) //delegate to Time( int, int, int )
> {
> } // end constructor with two arguments
> ```
>
> 



> The name of the destructor for a class is the tilde character (~) followed by the class name.
> Called implicitly when an object is destroyed.
> The destructor itself does not actually release the object’s memory—it performs termination housekeeping before the object’s memory is reclaimed, so the memory may be reused to hold new objects.
> Receives no parameters and returns no value.
> May not specify a return type—not even void.
> A class has one destructor. 
> A destructor must be public.
> If you do not explicitly define a destructor, the compiler defines an “empty” destructor.
> 类的析构函数的名称是类名后面的波浪字符(~)。
> 当对象被销毁时隐式调用。
> 析构函数本身实际上并不释放对象的内存——它在回收对象的内存之前执行终止管理，因此可以重用内存来保存新对象。
> 不接收参数也不返回值。
> 不能指定返回类型——甚至不能指定void。
> 一个类有一个析构函数。
> 析构函数必须是公共的。
> 如果没有显式定义析构函数，编译器将定义一个“空”析构函数。



> Constructors and destructors are called implicitly.
> The order in which these function calls occur depends on the order in which execution enters and leaves the scopes where the objects are instantiated.
> Generally, destructor calls are made in the reverse order of the corresponding constructor calls
> The storage classes of objects can alter the order in which destructors are called.
> 隐式调用构造函数和析构函数。
> 这些函数调用发生的顺序取决于执行进入和离开对象实例化的作用域的顺序。
> 通常，析构函数调用的顺序与相应的构造函数调用的顺序相反
> 对象的存储类可以改变调用析构函数的顺序。



> Constructors and destructors are called implicitly.
> The order in which these function calls occur depends on the order in which execution enters and leaves the scopes where the objects are instantiated.
> Generally, destructor calls are made in the reverse order of the corresponding constructor calls
> The storage classes of objects can alter the order in which destructors are called.
> 隐式调用构造函数和析构函数。
> 这些函数调用发生的顺序取决于执行进入和离开对象实例化的作用域的顺序。
> 通常，析构函数调用的顺序与相应的构造函数调用的顺序相反
> 对象的存储类可以改变调用析构函数的顺序。



> Constructors and Destructors for Local Objects
> Constructors and destructors for local objects are called each time execution enters and leaves the scope of the object.
> Destructors are not called for local objects if the program terminates with a call to function exit or function abort.
> 局部对象的构造函数和析构函数
> 每次执行进入和离开对象的作用域时，都会调用局部对象的构造函数和析构函数。
> 如果程序因调用函数exit或函数abort而终止，则不会调用局部对象的析构函数。



> A reference to an object is an alias for the name of the object and, hence, may be used on the left side of an assignment statement.
> In this context, the reference makes a perfectly acceptable lvalue that can receive a value.
> Unfortunately a public member function of a class can return a reference to a private data member of that class.
> Such a reference return actually makes a call to that member function an alias for the private data member! 
> The function call can be used in any way that the private data member can be used, including as an lvalue in an assignment statement
> The same problem would occur if a pointer to the private data were to be returned by the function.
> If a function returns a reference that’s declared const, the reference is a non-modifiable lvalue and cannot be used to modify the data.
> 对对象的引用是该对象名称的别名，因此可以在赋值语句的左侧使用。
> 在这个上下文中，引用创建了一个完全可以接受的左值，它可以接收值。
> 不幸的是，类的公共成员函数可以返回对该类私有数据成员的引用。
> 这样的引用返回实际上使对该成员函数的调用成为私有数据成员的别名！
> 函数调用可以以私有数据成员的任何方式使用，包括作为赋值语句中的左值
> 如果函数返回指向私有数据的指针，也会出现同样的问题。
> 如果函数返回声明为const的引用，则该引用是不可修改的左值，不能用于修改数据。



> The assignment operator (=) can be used to assign an object to another object of the same type.
> By default, such assignment is performed by memberwise assignment (also called copy assignment).
> Each data member of the object on the right of the assignment operator is assigned individually to the same data member in the object on the left of the assignment operator.
> [Caution: Memberwise assignment can cause serious problems when used with a class whose data members contain pointers to dynamically allocated memory; we discuss these problems in Chapter 10 and show how to deal with them.] 
> 赋值操作符(=)可用于将一个对象赋值给同一类型的另一个对象。
> 默认情况下，这种赋值是通过成员赋值(也称为拷贝赋值)执行的。
> 赋值操作符右侧对象的每个数据成员分别赋值给赋值操作符左侧对象中的相同数据成员。
> 注意:如果类的数据成员包含指向动态分配内存的指针，则按成员赋值可能会导致严重的问题。我们将在第10章讨论这些问题，并说明如何处理它们。



> Objects may be passed as function arguments and may be returned from functions.
> Such passing and returning is performed using pass-by-value by default—a copy of the object is passed or returned.
> C++ creates a new object and uses a copy constructor to copy the original object’s values into the new object.
> For each class, the compiler provides a default copy constructor that copies each member of the original object into the corresponding member of the new object.
> Copy constructors can cause serious problems when used with a class whose data members contain pointers to dynamically allocated memory.
> Chapter 10 discusses customized copy constructors.
> 对象可以作为函数参数传递，也可以从函数返回。
> 默认情况下，这种传递和返回是使用按值传递来执行的——传递或返回对象的副本。
> c++创建一个新对象，并使用复制构造函数将原始对象的值复制到新对象中。
> 对于每个类，编译器提供默认的复制构造函数，将原始对象的每个成员复制到新对象的相应成员中。
> 当将复制构造函数用于数据成员包含指向动态分配内存的指针的类时，可能会导致严重的问题。
> 第10章讨论自定义复制构造函数。



> C++ disallows member function calls for const objects unless the member functions themselves are also declared const. 
> This is true even for get member functions that do not modify the object. 
> This is also a key reason that we’ve declared as const all member-functions that do not modify the objects on which they’re called. 
> A member function is specified as const both in its prototype by inserting the keyword const after the function’s parameter list and, in the case of the function definition, before the left brace that begins the function body. 
>
> c++不允许对const对象调用成员函数，除非成员函数本身也声明为const。
> 即使对于不修改对象的get成员函数也是如此。
> 这也是我们将所有成员函数声明为const的一个关键原因，这些成员函数不会修改调用它们的对象。
> 成员函数在原型中被指定为const，方法是在函数的形参列表之后插入关键字const，在函数定义中，在函数体开始的左大括号之前插入关键字const。



> A constructor must be allowed to modify an object so that the object can be initialized properly. 
> A destructor must be able to perform its termination housekeeping chores before an object’s memory is reclaimed by the system. 
> Attempting to declare a constructor or destructor const is a compilation error. 
> The “constness” of a const object is enforced from the time the constructor completes initialization of the object until that object’s destructor is called.
> 必须允许构造函数修改对象，以便正确初始化对象。
> 析构函数必须能够在系统回收对象的内存之前执行其终止家务。
> 试图声明构造函数或析构函数const是编译错误。
> 从构造函数完成对象初始化到调用该对象的析构函数，const对象的“constness”被强制执行。



> What Happens When You Do Not Use the Member Initializer List?
> If a member object is not initialized through a member initializer, the member object’s default constructor will be called implicitly. 
> Values, if any, established by the default constructor can be overridden by set functions. 
> However, for complex initialization, this approach may require significant additional work and time.
> 当不使用成员初始化列表时会发生什么?
> 如果成员对象没有通过成员初始化器初始化，则将隐式调用成员对象的默认构造函数。
> 默认构造函数建立的值(如果有)可以被set函数覆盖。
> 然而，对于复杂的初始化，这种方法可能需要大量的额外工作和时间。



> A friend function of a class is a non-member function that has the right to access the public and non-public class members. 
> Standalone functions, entire classes or member functions of other classes may be declared to be friends of another class. 
> 类的友元函数是具有访问公共和非公共类成员权限的非成员函数。
> 可以将独立函数、整个类或其他类的成员函数声明为另一个类的友元。



> Declaring a friend
> To declare a function as a friend of a class, precede the function prototype in the class definition with keyword friend. 
> To declare all member functions of class ClassTwo as friends of class ClassOne, place a declaration of the form
> friend class ClassTwo;
> in the definition of class ClassOne.
> Friendship is granted, not taken—for class B to be a friend of class A, class A must explicitly declare that class B is its friend. 
> Friendship is not symmetric—if class A is a friend of class B, you cannot infer that class B is a friend of class A. 
> Friendship is not transitive—if class A is a friend of class B and class B is a friend of class C, you cannot infer that class A is a friend of class C.
> 宣布成为朋友
> 要将函数声明为类的友元，可以在类定义中的函数原型前面加上关键字friend。
> 要将类ClassTwo的所有成员函数声明为类ClassOne的友元，请放置一个窗体声明
> 朋友班班二;
> 在ClassOne类的定义中。
> 友谊是授予的，而不是索取的——类B要成为类a的朋友，类a必须明确声明类B是它的朋友。
> 友谊不是对称的——如果A类是B类的朋友，你就不能推断B类是A类的朋友。
> 友谊是不可传递的——如果类A是类B的朋友，类B是类C的朋友，你不能推断类A是类C的朋友。



> Overloaded friend Functions
> It’s possible to specify overloaded functions as friends of a class. 
> Each function intended to be a friend must be explicitly declared in the class definition as a friend of the class.
> 重载友元函数
> 可以将重载函数指定为类的友元。
> 每个想要成为友元的函数都必须在类定义中显式声明为类的友元。



> Every object has access to its own address through a pointer called this (a C++ keyword). 
> The this pointer is not part of the object itself—i.e., the memory occupied by the this pointer is not reflected in the result of a sizeof operation on the object. 
> Rather, the this pointer is passed (by the compiler) as an implicit argument to each of the object’s non-static member functions. 
> 每个对象都可以通过一个名为this的指针(c++关键字)访问自己的地址。
> this指针不是对象本身的一部分。， this指针占用的内存不会反映在对对象进行sizeof操作的结果中。
> 相反，this指针(由编译器)作为隐式参数传递给对象的每个非静态成员函数。



> Using the this Pointer to Avoid Naming Collisions
> Member functions use the this pointer implicitly (as we’ve done so far) or explicitly to reference an object’s data members and other member functions. 
> A common explicit use of the this pointer is to avoid naming conflicts between a class’s data members and member-function parameters (or other local variables). 
> 使用this指针避免命名冲突
> 成员函数隐式或显式地使用this指针来引用对象的数据成员和其他成员函数。
> this指针的一个常见显式用法是避免类的数据成员和成员函数参数(或其他局部变量)之间的命名冲突。



> Type of the this Pointer
> The type of the this pointer depends on the type of the object and whether the member function in which this is used is declared const. 
> For example, in a non-const member function of class Employee, the this pointer has the type Employee *. In a const member function, the this pointer has the type const Employee *.
> this指针的类型：
> this指针的类型取决于对象的类型以及使用this的成员函数是否声明为const。
> 例如，在Employee类的非const成员函数中，this指针的类型是Employee *。在const成员函数中，this指针的类型为const Employee *。



**.圆点运算符具有比->箭头运算符更高的优先级**



> In certain cases, only one copy of a variable should be shared by all objects of a class. 
> A static data member is used for these and other reasons. 
> Such a variable represents “class-wide” information, i.e., data that is shared by all instances and is not specific to any one object of the class. 
> 在某些情况下，一个类的所有对象只能共享一个变量的副本。
> 静态数据成员用于这些和其他原因。
> 这样的变量表示“类范围”信息，即由所有实例共享的数据，而不是特定于类的任何一个对象。



> Scope and Initialization of static Data Members
> static data members have class scope. 
> A static data member must be initialized exactly once. 
> Fundamental-type static data members are initialized by default to 0. 
> Prior to C++11, a static const data member of int or enum type could be initialized in its declaration in the class definition and all other static data members had to be defined and initialized at global namespace scope (i.e., outside the body of the class definition). 
> Again, C++11’s in-class initializers also allow you to initialize these variables where they’re declared in the class definition. 
> 静态数据成员的作用域和初始化
> 静态数据成员具有类作用域。
> 静态数据成员必须只初始化一次。
> 基本类型静态数据成员默认初始化为0。
> 在c++11之前，int或enum类型的静态const数据成员可以在类定义的声明中初始化，而所有其他静态数据成员必须在全局命名空间范围内定义和初始化(即，在类定义的主体之外)。
> 同样，c++11的类内初始化器还允许您在类定义中声明这些变量的地方初始化它们。



> Accessing static Data Members
> A class’s private and protected static members are normally accessed through the class’s public member functions or friends. 
> A class’s static members exist even when no objects of that class exist. 
> To access a public static class member when no objects of the class exist, simply prefix the class name and the scope resolution operator (::) to the name of the data member. 
> To access a private or protected static class member when no objects of the class exist, provide a public static member function and call the function by prefixing its name with the class name and scope resolution operator. 
> A static member function is a service of the class, not of a specific object of the class.
> 访问静态数据成员：
> 类的私有和受保护的静态成员通常通过类的公共成员函数或友元来访问。
> 即使类的对象不存在，类的静态成员仍然存在。
> 要在不存在类的对象时访问公共静态类成员，只需在数据成员的名称前加上类名和范围解析操作符(::)。
> 若要在不存在类的对象时访问私有或受保护的静态类成员，请提供一个公共静态成员函数，并在函数名前加上类名和作用域解析操作符来调用该函数。
> 静态成员函数是类的服务，而不是类的特定对象的服务。
>
> 局部变量在他们定义的作用域结束时被销毁：
> static成员函数没有this指针，因为static数据成员和函数都是独立于对象存在的
> 将static成员函数定义为const是一个编译错误 因为static函数需要对数据进行修改

