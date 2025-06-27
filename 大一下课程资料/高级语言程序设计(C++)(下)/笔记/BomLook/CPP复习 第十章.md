# CPP复习 第十章

> string类中的[]重载运算符没有提供任何的边界检查 。
> 而at有提供边界检查，如果是一个无效的下标，会抛出一个异常。如果在范围内，返回的是一个可以修改的左值或者const引用(右值)
> cpp不允许创建新的运算符 但允许大部分运算符被重载



> Operator overloading is not automatic—you must write operator-overloading functions to perform the desired operations. 
> An operator is overloaded by writing a non-static member function definition or non-member function definition as you normally would, except that the function name starts with the keyword operator followed by the symbol for the operator being overloaded.
> For example, the function name operator+ would be used to overload the addition operator (+) for use with objects of a particular class (or enum).
> 操作符重载不是自动的，您必须编写操作符重载函数来执行所需的操作。
> 操作符通过编写非静态成员函数定义或通常的非成员函数定义来重载，只是函数名以关键字operator开头，后跟被重载操作符的符号。
> 例如，函数名operator+可用于重载加法操作符(+)，以便与特定类(或enum)的对象一起使用。



**运算符优先级：算术运算、逻辑运算、赋值运算**



> When operators are overloaded as member functions, they must be non-static, because they must be called on an object of the class and operate on that object.
> To use an operator on class objects, you must define overloaded operator functions for that class—with three exceptions.
> The assignment operator (=) may be used with most classes to perform memberwise assignment of the data members—each data member is assigned from the assignment’s “source” object (on the right) to the “target” object (on the left). 
> Memberwise assignment is dangerous for classes with pointer members, so we’ll explicitly overload the assignment operator for such classes.
> The address operator (&) returns a pointer to the object; this operator also can be overloaded. 
> The comma operator evaluates the expression to its left then the expression to its right, and returns the value of the latter expression.
>
> 当操作符作为成员函数重载时，它们必须是非静态的，因为它们必须在类的对象上调用并对该对象进行操作。
> 要在类对象上使用操作符，必须为该类定义重载的操作符函数——有三个例外。
> 大多数类都可以使用赋值操作符(=)来执行数据成员的成员赋值——每个数据成员从赋值的“源”对象(右侧)赋值到“目标”对象(左侧)。
> 对于具有指针成员的类，按成员赋值是危险的，因此将显式重载此类类的赋值操作符。
> 地址操作符(&)返回指向该对象的指针;该操作符也可以被重载。
> 逗号操作符对左边的表达式求值，然后对右边的表达式求值，并返回后一个表达式的值。



> **不允许重载的运算符：.     .*     ::    ?:**



> The precedence of an operator cannot be changed by overloading. 
> However, parentheses can be used to force the order of evaluation of overloaded operators in an expression. 
> The associativity of an operator cannot be changed by overloading
> if an operator normally associates from left to right, then so do all of its overloaded versions.
> You cannot change the “arity” of an operator (that is, the number of operands an operator takes)
> overloaded unary operators remain unary operators; overloaded binary operators remain binary operators. Operators &, * , + and - all have both unary and binary versions; these unary and binary versions can be separately overloaded.
> 操作符的优先级不能通过重载来改变。
> 但是，括号可用于强制表达式中重载操作符的求值顺序。
> 操作符的结合性不能通过重载来改变
> 如果操作符通常从左到右关联，那么它的所有重载版本也是如此。
> 不能更改操作符的“arity”(即操作数的个数)。
> 重载一元操作符仍然是一元操作符;重载的二元操作符仍然是二元操作符。操作符&、*、+和-都有一元和二元版本;这些一元和二进制版本可以分别重载。



> You cannot create new operators; only existing operators can be overloaded.
> The meaning of how an operator works on values of fundamental types cannot be changed by operator overloading. 
> For example, you cannot make the + operator subtract two ints. Operator overloading works only with objects of user-defined types or with a mixture of an object of a user-defined type and an object of a fundamental type. 
> 你不能创建新的运营商;只能重载现有的操作符。
> 操作符对基本类型的值的操作方式不能通过操作符重载来改变。
> 例如，不能使用+操作符减去两个int型。操作符重载只适用于用户定义类型的对象，或者用户定义类型的对象和基本类型的对象的混合。



> Related operators, like + and +=, must be overloaded separately.
> When overloading (), [], -> or any of the assignment operators, the operator overloading function must be declared as a class member. 
> For all other overloadable operators, the operator overloading functions can be member functions or non-member functions.
> 相关操作符，如+和+=，必须分别重载。
> 当重载()、[]、->或任何赋值操作符时，必须将操作符重载函数声明为类成员。
> 对于所有其他可重载操作符，操作符重载函数可以是成员函数或非成员函数。



> A binary operator can be overloaded as a non-static member function with one parameter or as a non-member function with two parameters (one of those parameters must be either a class object or a reference to a class object).
> As a non-member function, binary operator < must take two arguments—one of which must be an object (or a reference to an object) of the class.
> 二元操作符可以重载为带有一个形参的非静态成员函数，也可以重载为带有两个形参的非成员函数(其中一个形参必须是类对象或对类对象的引用)。
> 作为非成员函数，二元操作符<必须接受两个实参——其中一个必须是类的对象(或对对象的引用)。
> 一个非成员运算符函数因为性能原因 通常被声明为类的友元



> **作为成员函数的二元重载运算符：
> 仅当左操作数是该类的对象且重载函数是一个成员时，二元运算符的重载函数才能作为成员函数。**
>
> **作为非成员函数：
> 必须带有两个参数：其中一个必须是运算符有关系的类的对象或者是该类对象的引用。**



> **istream的ignore成员函数: ignore(n)n指的是跳过的字符个数，不设置默认为1个字符**



> Function operator>> returns istream reference input (i.e., cin).
> This enables input operations on PhoneNumber objects to be cascaded with input operations on other PhoneNumber objects or on objects of other data types.
> 函数操作符>>返回istream引用输入(即cin)。
> 这使得PhoneNumber对象上的输入操作可以与其他PhoneNumber对象或其他数据类型的对象上的输入操作级联。



> 二元运算符的重载运算符函数可以作为成员函数来实现的前提条件是仅当左操作数是该函数所在类的对象



> Why Overloaded Stream Insertion and Stream Extraction Operators Are Overloaded as Non-Member Functions
> The overloaded stream insertion operator (<<) is used in an expression in which the left operand has type ostream &, as in cout << classObject.
> To use the operator in this manner where the right operand is an object of a user-defined class, it must be overloaded as a non-member function.
> 为什么重载流插入和流提取操作符重载为非成员函数
> 重载流插入操作符(<<)用于左操作数类型为ostream &的表达式，如cout << classsobject。
> 若要以这种方式使用操作符，右操作数是用户定义类的对象，则必须将其重载为非成员函数。
>
> Similarly, the overloaded stream extraction operator (>>) is used in an expression in which the left operand has type istream &, as in cin >> classObject, and the right operand is an object of a user-defined class, so it, too, must be a non-member function.
> Each of these overloaded operator functions may require access to the private data members of the class object being output or input, so these overloaded operator functions can be made friend functions of the class for performance reasons.
> 类似地，在左操作数类型为istream &的表达式中使用重载流提取操作符(>>)，如cin >> classsobject，右操作数是用户定义类的对象，因此它也必须是非成员函数。
> 这些重载操作符函数中的每一个都可能需要访问作为输出或输入的类对象的私有数据成员，因此出于性能原因，可以将这些重载操作符函数设置为类的友元函数。



> A unary operator for a class can be overloaded as a non-static member function with no arguments or as a non-member function with one argument that must be an object (or a reference to an object) of the class.
> A unary operator such as ! may be overloaded as a non-member function with one parameter.
> 类的一元操作符可以重载为不带参数的非静态成员函数，也可以重载为带一个参数的非成员函数，该参数必须是类的对象(或对对象的引用)。
> 一元操作符，如!可以作为带有一个形参的非成员函数重载。



> The prefix and postfix versions of the increment and decrement operators can all be overloaded.
> To overload the increment operator to allow both prefix and postfix increment usage, each overloaded operator function must have a distinct signature, so that the compiler will be able to determine which version of ++ is intended.
> The prefix versions are overloaded exactly as any other prefix unary operator would be. 
> 自增和自减操作符的前缀和后缀版本都可以重载。
> 要重载自增操作符以允许同时使用前缀和后缀自增，每个重载的操作符函数必须具有不同的签名，以便编译器能够确定要使用哪个版本的++。
> 前缀版本的重载与任何其他前缀一元操作符完全相同



> Suppose that we want to add 1 to the day in Date object d1.
> When the compiler sees the preincrementing expression ++d1, the compiler generates the member-function call
> d1.operator++()
> The prototype for this operator function would be
> Date &operator++();
> If the prefix increment operator is implemented as a non-member function, then, when the compiler sees the expression ++d1, the compiler generates the function call
> operator++( d1 )
> The prototype for this operator function would be declared in the Date class as 
> Date &operator++( Date & );
> 前置运算符返回的是类对象的引用 后置运算返回的是一个类的副本
> 不能返回对一个局部对象的引用（或者指针）



> Overloading the Postfix Increment Operator
> Overloading the postfix increment operator presents a challenge, because the compiler must be able to distinguish between the signatures of the overloaded prefix and postfix increment operator functions.
> The convention that has been adopted in C++ is that, when the compiler sees the postincrementing expression d1++, it generates the member-function call
> d1.operator++( 0 )
> The prototype for this function is 
> Date operator++( int )
> The argument 0 is strictly a “dummy value” that enables the compiler to distinguish between the prefix and postfix increment operator functions.
> The same syntax is used to differentiate between the prefix and postfix decrement operator functions.
> 重载后缀自增操作符
> 参数0是严格意义上的“假值”，它使编译器能够区分前缀和后缀自增操作符函数。
> 相同的语法用于区分前缀和后缀递减操作符函数。



> Obtaining Dynamic Memory with new
> The new operator allocates storage of the proper size for an object of type Time, calls the default constructor to initialize the object and returns a pointer to the type specified to the right of the new operator (i.e., a Time *).
> If new is unable to find sufficient space in memory for the object, it indicates that an error occurred by “throwing an exception.” 
> 使用new获取动态内存
> new操作符为Time类型的对象分配适当大小的存储空间，调用默认构造函数初始化该对象，并返回指向new操作符右侧指定的类型的指针(即Time *)。
> 如果new无法在内存中为对象找到足够的空间，则通过“抛出异常”表示发生了错误。



> Releasing Dynamic Memory with delete
> To destroy a dynamically allocated object, use the delete operator as follows:
>
> ```cpp
> 	delete ptr;
> ```
>
> This statement first calls the destructor for the object to which ptr points, then deallocates the memory associated with the object, returning the memory to the free store.
> 使用delete释放动态内存
> 要销毁动态分配的对象，使用delete操作符，如下所示:
>
> ```cpp
> 	delete ptr;
> ```
>
> 该语句首先调用ptr所指向对象的析构函数，然后释放与该对象关联的内存，将内存返回给自由存储区。



> Initializing Dynamic Memory
> You can provide an initializer for a newly created fundamental-type variable, as in
> double *ptr = new double( 3.14159 ); 
> The same syntax can be used to specify a comma-separated list of arguments to the constructor of an object.
> 初始化动态内存
> 可以为新创建的基本类型变量提供初始化项，如
> Double *ptr = new Double (3.14159);
> 可以使用相同的语法为对象的构造函数指定以逗号分隔的参数列表。



> Dynamically Allocating Built-In Arrays with new []
> You can also use the new operator to allocate built-in arrays dynamically.
> For example, a 10-element integer array can be allocated and assigned to gradesArray as follows:
> int *gradesArray = new int[ 10 ]();
> The parentheses following new int[10] value initialize the array’s elements—fundamental numeric types are set to 0, bools are set to false, pointers are set to nullptr and class objects are initialized by their default constructors. 
> A dynamically allocated array’s size can be specified using any non-negative integral expression that can be evaluated at execution time.
> 使用new[]动态分配内置数组
> 还可以使用new操作符动态分配内置数组。
> 例如，一个包含10个元素的整数数组可以这样分配给gradesArray:
> int *gradesArray = new int[10]();
> new int[10] value后面的圆括号初始化数组的元素——基本数字类型设置为0,bool设置为false，指针设置为nullptr，类对象由其默认构造函数初始化。
>
> 动态分配数组的大小可以使用任何可以在执行时计算的非负积分表达式来指定。



> C++11: Using a List Initializer with a Dynamically Allocated Built-In Array
> Prior to C++11, when allocating a built-in array of objects dynamically, you could not pass arguments to each object’s constructor—each object was initialized by its default constructor. In C++11, you can use a list initializer to initialize the elements of a dynamically allocated built-in array, as in 
> int *gradesArray = new int[ 10 ]{};
> The empty set of braces as shown here indicates that default initialization should be used for each element—for fundamental types each element is set to 0. 
> The braces may also contain a comma-separated list of initializers for the array’s elements. 
> c++ 11:在动态分配的内置数组中使用列表初始化式
> 在c++ 11之前，当动态分配内置对象数组时，不能向每个对象的构造函数传递参数——每个对象都由其默认构造函数初始化。在c++ 11中，可以使用列表初始化器初始化动态分配的内置数组的元素，如
>
> ```cpp
> int *gradesArray = new int[10]{};
> ```
>
> 这里所示的空大括号表明应该对每个元素使用默认初始化—对于基本类型，每个元素都设置为0。
> 大括号还可以包含一个以逗号分隔的数组元素初始化式列表。



> Releasing Dynamically Allocated Built-In Arrays with delete []
> To deallocate a dynamically allocated array, use the statement
>
> ```cpp
> delete [] ptr;
> ```
>
> If the pointer points to a built-in array of objects, the statement first calls the destructor for every object in the array, then deallocates the memory.
> Using delete or [] on a nullptr has no effect.
> 使用delete释放动态分配的内置数组[]
> 要释放动态分配的数组，请使用语句
>
> ```cpp
> Delete [] ptr;
> ```
>
> 如果指针指向内置的对象数组，则语句首先为数组中的每个对象调用析构函数，然后释放内存。
> 在nullptr上使用delete或[]不起作用。



> 用delete []来删除单个对象的结果 是没有定义的（根据不同的编译器 结果可能不同）



> C++11: Managing Dynamically Allocated Memory with unique_ptr 
> C++11’s new unique_ptr is a “smart pointer” for managing dynamically allocated memory. 
> When a unique_ptr goes out of scope, its destructor automatically returns the managed memory to the free store. 
> c++ 11:用unique_ptr管理动态分配的内存
> c++ 11新增的unique_ptr是一个“智能指针”，用于管理动态分配的内存。
> 当unique_ptr超出作用域时，它的析构函数自动将托管内存返回给自由存储区。



