# CPP复习 第十二章

多态的使用条件：父类指针或者引用指向子类对象.

> With polymorphism, we can design and implement systems that are easily extensible.
> New classes can be added with little or no modification to the general portions of the program, as long as the new classes are part of the inheritance hierarchy that the program processes generally.
> The only parts of a program that must be altered to accommodate new classes are those that require direct knowledge of the new classes that you add to the hierarchy.
> 使用多态性，我们可以设计和实现易于扩展的系统。
> 只要新类是程序通常处理的继承层次结构的一部分，就可以在对程序的一般部分进行很少或不进行修改的情况下添加新类。
> 只有那些需要直接了解添加到层次结构中的新类的部分才需要对程序进行修改以适应新类



![image-20240607170206131](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607170206131.png)

> 属于同一个层次的派生类，通过一个共同的基类指针或者引用来访问，可以让不同的派生类对象执行与它们相符合的行为。



![image-20240607170221385](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607170221385.png)

> 多态可以程序员不用修改原有的系统，只需要把能够响应现有信息的新类型的对象添加到系统即可。



> The next several sections present a series of examples that demonstrate how base-class and derived-class pointers can be aimed at base-class and derived-class objects, and how those pointers can be used to invoke member functions that manipulate those objects.
> A key concept in these examples is to demonstrate that an object of a derived class can be treated as an object of its base class.
> Despite the fact that the derived-class objects are of different types, the compiler allows this because each derived-class object is an object of its base class.
> However, we cannot treat a base-class object as an object of any of its derived classes.
> The is-a relationship applies only from a derived class to its direct and indirect base classes.
> 接下来的几节将提供一系列示例，演示基类和派生类指针如何指向基类和派生类对象，以及如何使用这些指针调用操作这些对象的成员函数。
> 这些示例中的一个关键概念是演示派生类的对象可以被视为其基类的对象。
> 尽管派生类对象具有不同的类型，但编译器允许这样做，因为每个派生类对象都是其基类的对象。
> 但是，不能将基类对象视为其任何派生类的对象。
> is-a关系仅适用于派生类的直接和间接基类。





> Aiming a Base-Class Pointer at a Derived-Class Object
> Line 49 assigns the address of derived-class object base-PlusCommissionEmployee to base-class pointer commissionEmployeePtr, which line 53 uses to invoke member function print.
> This “crossover” is allowed because an object of a derived class is an object of its base class.
> Note that despite the fact that the base class CommissionEmployee pointer points to a derived class BasePlusCommissionEmployee object, the base class CommissionEmployee’s print member function is invoked (rather than BasePlusCommissionEmployee’s print function).
> The output of each print member-function invocation in this program reveals that the invoked functionality depends on the type of the pointer (or reference) used to invoke the function, not the type of the object for which the member function is called. 
> 将基类指针指向派生类对象
> 第49行将派生类对象base-PlusCommissionEmployee的地址赋值给基类指针commissionEmployeePtr，第53行使用该指针调用成员函数print。
> 这种“交叉”是允许的，因为派生类的对象是其基类的对象。
>
> 注意，尽管基类CommissionEmployee指针指向派生类BasePlusCommissionEmployee对象，
> 但调用的是**基类CommissionEmployee的print成员函数(而不是BasePlusCommissionEmployee的print函数)。**
>
> 该程序中每个print成员函数调用的输出表明，被调用的功能取决于**用于调用该函数的指针(或引用)的类型，而不是调用该成员函数的对象的类型。**





> Off a base-class pointer, the compiler allows us to invoke only base-class member functions.
> If a base-class pointer is aimed at a derived-class object, and an attempt is made to access a derived-class-only member function, a compilation error will occur.
> Figure 12.3 shows the consequences of attempting to invoke a derived-class member function off a base-class pointer.
> 在基类指针之外，编译器只允许调用基类成员函数。
> 如果基类指针指向派生类对象，并且试图访问仅派生类成员函数，则会发生编译错误。
> 图12.3显示了试图从基类指针调用派生类成员函数的结果。



> Downcasting
> The compiler will allow access to derived-class-only members from a base-class pointer that is aimed at a derived-class object if we explicitly cast the base-class pointer to a derived-class pointer—known as downcasting.
> Downcasting allows a derived-class-specific operation on a derived-class object pointed to by a base-class pointer.
> After a downcast, the program can invoke derived-class functions that are not in the base class.
> Section 12.8 demonstrates how to safely use downcasting.
> 向下类型转换：
> 如果显式地将基类指针转换为派生类指针(称为向下转换)，编译器将允许从指向派生类对象的基类指针访问仅派生类成员。
> 向下转换允许在基类指针指向的派生类对象上执行特定于派生类的操作。向下转换后，程序可以调用不在基类中的派生类函数。
> 第12.8节演示了如何安全地使用向下转换。



**将一个基类指针强制类型转换为其直接派生类或者间接派生类是允许的 为了发送那些在基类中不出现的派生类对象的信息 这种转换是必要的**

![image-20240607193306336](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607193306336.png)

> Why virtual Functions Are Useful
> Consider why virtual functions are useful: Suppose that shape classes such as Circle, Triangle, Rectangle and Square are all derived from base class Shape.
> Each of these classes might be endowed with the ability to draw itself via a member function draw, but the function for each shape is quite different.
> In a program that draws a set of shapes, it would be useful to be able to treat all the shapes generally as objects of the base class Shape.
> To draw any shape, we could simply use a base-class Shape pointer to invoke function draw and let the program determine dynamically (i.e., at runtime) which derived-class draw function to use, based on the type of the object to which the base-class Shape pointer points at any given time.
> This is polymorphic behavior.
> 虚函数为什么有用：考虑一下虚函数有用的原因:假设形状类(如Circle、Triangle、Rectangle和Square)都派生自基类shape。
> 这些类中的每一个都可以通过成员函数draw来赋予自己绘图的能力，
>
> 但是每个形状的函数是完全不同的。
>
> 在绘制一组形状的程序中，如果能够将所有形状一般视为Shape基类的对象，这将是很有用的。
>
> 要绘制任何形状，我们可以简单地使用一个基类shape指针来调用函数draw，并让程序动态地(即，在运行时)
>
> 根据基类shape指针在任何给定时间所指向的对象的类型来决定要使用哪个派生类的绘制函数。这就是多态行为.



![image-20240607194403976](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607194403976.png)

> Declaring virtual Functions
> To enable this behavior, we declare draw in the base class as a virtual function, and we override draw in each of the derived classes to draw the appropriate shape.
> From an implementation perspective, overriding a function is no different than redefining one.
> An overridden function in a derived class has the same signature and return type (i.e., prototype) as the function it overrides in its base class.
> If we declare the base-class function as virtual, we can override that function to enable polymorphic behavior.
> We declare a virtual function by preceding the function’s prototype with the key-word virtual in the base class.
>
> 声明虚函数
> 为了启用这种行为，我们在基类中将draw声明为虚函数，并在每个派生类中重写draw以绘制适当的形状。
> 从实现的角度来看，重写函数与重新定义函数没有什么不同。
>
> **派生类中被重写的函数与它在基类中重写的函数具有相同的签名和返回类型(即原型)。**
>
> **如果将基类函数声明为virtual，则可以重写该函数以启用多态行为。**
>
> **通过在基类中在函数原型前面加上关键字virtual来声明虚函数。**



一个函数一旦声明为virtual，那么从它开始的所有继承的派生类中，它将始终保持是virtual的。

建议：即使一个函数在层次结构的高层中已经被声明为了virtual（也就是其已经成为了隐式的virtual函数），仍然建议在其前面添加virtual，在类层次结构的每一级中都把它显式声明为virtual。

override关键词：在每一个重载后的函数后面加上，声明是从父类的成员函数重载下来，会迫使编译器检查基类有没有对应的virtual成员函数，如果没有，则编译器会报错。

如果派生类函数不重载virtual函数，那么它会简单继承其父类的virtual函数。



> Invoking a virtual Function Through a Base-Class Pointer or Reference
> If a program invokes a virtual function through a base-class pointer to a derived-class object (e.g., shapePtr->draw()) or a base-class reference to a derived-class object (e.g., shapeRef.draw()), the program will choose the correct derived-class function dynamically (i.e., at execution time) based on the object type—not the pointer or reference type.
> Known as dynamic binding or late binding.
> 通过基类指针或引用调用虚函数
>
> 如果程序通过指向派生类对象的基类指针(例如shapetr ->draw())或指向派生类对象的基类引用(例如shapeRef.draw())调用虚函数，
>
> 程序将根据对象类型(即在执行时)动态地(即在执行时)选择正确的派生类函数，而不是指针或引用类型。
>
> 称为动态绑定或延迟绑定。



> Invoking a virtual Function Through an Object’s Name
> When a virtual function is called by referencing a specific object by name and using the dot member-selection operator (e.g., squareObject.draw()), the function invocation is re-solved at compile time (this is called static binding) and the virtual function that is called is the one defined for (or inherited by) the class of that particular object—this is not polymorphic behavior.
> Dynamic binding with virtual functions occurs only off pointers (and, as we’ll soon see, references).
> 通过对象的名称调用虚函数
>
> 当通过引用特定对象的名称并使用点成员选择操作符(例如，squareObject.draw())调用虚函数时，函数调用在编译时被重新解析(这称为静态绑定)，并且被调用的虚函数是为该特定对象的类定义的(或由该类继承的)虚函数——这不是多态行为。
>
> 与虚函数的动态绑定只发生在指针之外(我们很快就会看到，还有引用)。



静态绑定：virtual函数通过，按名引用特定对象，或者，使用圆点成员运算符，来调用 这个是在编译的时候已经被确定了。
动态绑定：只能通过指针，或者，引用句柄来完成 。

声明成员函数virtual会导致程序根据句柄指向的对象类型(而不是句柄的类型)动态地确定调用哪个函数。



> virtual Destructors
> A problem can occur when using polymorphism to process dynamically allocated objects of a class hierarchy. 
> If a derived-class object with a non-virtual destructor is destroyed by applying the delete operator to a base-class pointer to the object, the C++ standard specifies that the behavior is undefined.
> The simple solution to this problem is to create a public virtual destructor in the base class. 
> If a base class destructor is declared virtual, the destructors of any derived classes are also virtual and they override the base class destructor. 
>
> 虚拟析构函数：
> 当使用多态性处理类层次结构中动态分配的对象时，可能会出现问题。
> 如果通过对指向该对象的基类指针应用delete操作符来销毁带有非虚析构函数的派生类对象，则c++标准规定该行为未定义。
> 这个问题的简单解决方案是在基类中创建一个公共虚析构函数。
> 如果将基类析构函数声明为虚函数，则任何派生类的析构函数也是虚函数，并且它们覆盖基类析构函数。



> 在C++中，当我们使用基类指针指向一个派生类对象，并通过这个基类指针调用派生类对象的方法时，
> 如果这些方法在基类中被声明为虚函数（virtual），那么会发生动态绑定（或称为多态）。
> 然而，当涉及到析构函数时，如果基类的析构函数不是虚函数，那么就会有问题。
> 具体来说，当我们通过基类指针删除派生类对象时，
> 如果基类的析构函数不是虚函数，只会调用基类的析构函数，而不会调用派生类的析构函数。
> 这会导致派生类中特有的数据成员没有被正确释放，造成内存泄漏。





> 如果一个类含有一个virtual函数，那么该类就要提供一个virtual析构函数，即使不一定需要。
> 这样可以保证一个派生类对象通过基类指针删除时，这个派生类对象的析构函数能够被调用 。
>
> 但是构造函数不能是virtual函数。



> C++11: final Member Functions and Classes
> In C++11, a base-class virtual function that’s declared final in its prototype, as in 
> virtual someFunction( parameters ) final;
> cannot be overridden in any derived class—this guarantees that the base class’s final member function definition will be used by all base-class objects and by all objects of the base class’s direct and indirect derived classes. 
> c++ 11: final成员函数和类
>
> 在c++ 11中，在原型中声明为final的基类虚函数，如
>
> ```cpp
> virtual someFunction( parameters ) final;
> ```
>
> 保证了该函数在任何派生类中都不能被覆盖。
>
> 不能在任何派生类中重写——这保证了基类的最终成员函数定义将被所有基类对象以及基类的直接和间接派生类的所有对象使用。



> As of C++11, you can declare a class as final to prevent it from being used as a base class, as in
>
> ```cpp
> class MyClass final // this class cannot be a base class
> {
> // class body
> }; 
> ```
>
> Attempting to override a final member function or inherit from a final base class results in a compilation error. 
>
> 从c++ 11开始，可以将一个类声明为final，以防止它被用作基类，如
>
> ```cpp
> class MyClass final //这个类不能是基类
> ｛
> //类主体
> }；
> ```
>
> 尝试重写final成员函数或从final基类继承将导致编译错误。





![image-20240607204035143](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607204035143.png)

**使用多态可以避免上述使用switch语句遇到的问题，并且可以完成同样的功能**



> There are cases in which it’s useful to define classes from which you never intend to instantiate any objects.
> Such classes are called abstract classes.
> Because these classes normally are used as base classes in inheritance hierarchies, we refer to them as abstract base classes.
> These classes cannot be used to instantiate objects, because, as we’ll soon see, abstract classes are incomplete—derived classes must define the “missing pieces.” 
> An abstract class is a base class from which other classes can inherit.
> Classes that can be used to instantiate objects are called concrete classes.
> Such classes define every member function they declare.
>
> 在某些情况下，定义您从未打算从中实例化任何对象的类是有用的。
> 这样的类被称为抽象类。
> 由于这些类通常用作继承层次结构中的基类，因此我们将它们称为抽象基类。
>
> **这些类不能用于实例化对象，因为我们很快就会看到，抽象类是不完整的——派生类必须定义“缺失的部分”。**
>
> **抽象类是其他类可以继承的基类。**
>
> **可用于实例化对象的类称为具体类。**
>
> **这样的类定义了它们声明的每个成员函数。**
>
> 抽象基类的目的是为其他类提供合适的基类.



> Pure Virtual Functions
> A class is made abstract by declaring one or more of its virtual functions to be “pure.” A pure virtual function is specified by placing “= 0” in its declaration, as in
>
> ```cpp
> virtual void draw() const = 0; // pure virtual function
> ```
>
> The “= 0” is a pure specifier.
> Pure virtual functions typically do not provide implementations, though they can.
>
> 纯虚函数：
> 通过将类的一个或多个虚函数声明为“纯”，使类成为抽象的。纯虚函数通过在其声明中放置" = 0 "来指定，如
>
> ```cpp
> virtual void draw() const = 0; // pure virtual function
> ```
>
> “= 0”是一个纯说明符。
>
> 纯虚函数通常不提供实现，尽管它们可以。



> Each concrete derived class must override all base-class pure virtual functions with concrete implementations of those functions; otherwise the derived class is also abstract.
> The difference between a virtual function and a pure virtual function is that a virtual function has an implementation and gives the derived class the option of overriding the function.
> By contrast, a pure virtual function does not have an implementation and requires the derived class to override the function for that derived class to be concrete; otherwise the derived class remains abstract.
> Pure virtual functions are used when it does not make sense for the base class to have an implementation of a function, but you want all concrete derived classes to implement the function.
>
> 每个具体的派生类必须用这些函数的具体实现覆盖所有基类的纯虚函数，否则派生类也是抽象的。
>
> 虚函数和纯虚函数的区别在于虚函数有一个实现，并为派生类提供了重写函数的选项。
>
> 相比之下，纯虚函数没有实现，并且需要派生类重写该函数，以便派生类是具体的，**否则派生类仍然是抽象的。**
>
> **纯虚函数用于基类没有必要实现某个函数，但希望所有具体派生类都实现该函数的情况。**



![image-20240607205018334](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607205018334.png)

**抽象类为各个层次中的类提供了公共的通用函数接口，抽象类包含一个或者多个pure virtual函数，这些函数在具体的派生类中必须被重写。**

**如果在派生类没有重写pure virtual函数，那么这个派生类也会变成抽象类。**

**抽象类至少有一个pure virtual函数，也可以有自己的数据成员，具体的成员函数（包括构造和析构），它们被继承时符合继承的一般规则。**

**注意：虽然不能实例化抽象基类，但是可以使用抽象基类的指针或者引用，指向实例化的具体的派生类，从而实现多态。**



> Although we cannot instantiate objects of an abstract base class, we can use the abstract base class to declare pointers and references that can refer to objects of any concrete classes derived from the abstract class.
> Programs typically use such pointers and references to manipulate derived-class objects polymorphically.
>
> 虽然不能实例化抽象基类的对象，但可以使用抽象基类声明指针和引用，这些指针和引用可以引用从抽象类派生的任何具体类的对象。
> 程序通常使用这样的指针和引用以多态方式操作派生类对象。



**实现继承：
是指一个类从另一个类派生，并继承其成员变量和成员函数。在C++中，继承可以是public、protected或private三种访问控制方式。实现继承的关键是派生类能够复用基类的代码，派生类可以增加新的功能或重写基类的方法。**

**接口继承：
是指一个类实现一个接口，接口定义了类必须提供的行为，但不包含任何实现。在C++中，接口通常用纯虚函数来实现，一个包含纯虚函数的类称为抽象类。**





> This section discusses how C++ can implement polymorphism, virtual functions and dynamic binding internally.
> This will give you a solid understanding of how these capabilities really work.
> More importantly, it will help you appreciate the overhead of polymorphism—in terms of additional memory consumption and processor time.
> You’ll see that polymorphism is accomplished through three levels of pointers (i.e., “triple indirection”).
> Then we’ll show how an executing program uses these data structures to execute virtual functions and achieve the dynamic binding associated with polymorphism.
> Our discussion explains one possible implementation; this is not a language requirement.
> 本节讨论c++如何在内部实现多态性、虚函数和动态绑定。
> 这将使您对这些功能的实际工作方式有一个坚实的理解。
> 更重要的是，它将帮助您了解多态的开销——就额外的内存消耗和处理器时间而言。
> 您将看到，多态性是通过三层指针实现的(即“三重间接”)。
> 然后，我们将展示正在执行的程序如何使用这些数据结构来执行虚函数并实现与多态性相关的动态绑定。
> 我们的讨论解释了一种可能的实现;这不是语言要求。



> When C++ compiles a class that has one or more virtual functions, it builds a virtual function table (vtable) for that class.
> The vtable contains pointers to the class’s virtual functions. 
> Just as the name of a built-in array contains the address in memory of the array’s first element, a pointer to a function contains the starting address in memory of the code that performs the function’s task. 
> An executing program uses the vtable to select the proper function implementation each time a virtual function of that class is called.
> The leftmost column of Fig. 12.18 illustrates the vtables for classes Employee, SalariedEmployee, CommissionEmployee and BasePlusCommissionEmployee.
> 当c++编译一个具有一个或多个虚函数的类时，它为该类构建一个虚函数表(vtable)。
> 虚函数表包含指向该类虚函数的指针。
> 正如内置数组的名称包含该数组第一个元素在内存中的地址一样，
>
> 指向函数的指针包含执行该函数任务的代码在内存中的起始地址。
>
> 正在执行的程序在每次调用该类的虚函数时使用虚函数表选择适当的函数实现。
>
> 图12.18最左边的一列显示了Employee、salarieemployee、CommissionEmployee和BasePlusCommissionEmployee类的变量。



![image-20240607222304683](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607222304683.png)

> Employee Class vtable
> In the Employee class vtable, the first function pointer is set to 0 (i.e., the nullptr), because function earnings is a pure virtual function and therefore lacks an implementation.
> The second function pointer points to function print, which displays the employee’s full name and social security number.
> Any class that has one or more null pointers in its vtable is an abstract class.
> Classes without any null vtable pointers are concrete classes.
>
> 雇员类虚表
> 在Employee类虚函数表中，第一个函数指针被设置为0(即nullptr)，因为函数earnings是一个纯虚函数，因此缺乏实现。
> 第二个函数指针指向函数print，该函数显示员工的全名和社会保险号。
>
> **任何在虚函数表中有一个或多个空指针的类都是抽象类。**
>
> **没有空虚参指针的类是具体类。**



> SalariedEmployee Class vtable
> Class SalariedEmployee overrides function earnings to return the employee’s weekly salary, so the function pointer points to the earnings function of class SalariedEmployee.
> SalariedEmployee also overrides print, so the corresponding function pointer points to the SalariedEmployee member function that prints "salaried employee: " followed by the employee’s name, social security number and weekly salary.
>
> salarieemployee类变量表
> 类salariedemploye重写函数earnings以返回员工的周工资，因此函数指针指向类salariedemploye的收益函数。
> SalariedEmployee也覆盖了print，因此对应的函数指针指向SalariedEmployee成员函数，该函数打印“salaried employee:”，后面跟着员工的姓名、社会保险号和周薪。



> CommissionEmployee Class vtable
> The earnings function pointer in the vtable for class CommissionEmployee points to CommissionEmployee’s earnings function that returns the employee’s gross sales multiplied by the commission rate.
> The print function pointer points to the CommissionEmployee version of the function, which prints the employee’s type, name, social security number, commission rate and gross sales.
> As in class SalariedEmployee, both functions override the functions in class Employee.
>
> CommissionEmployee类函数表
> 类CommissionEmployee的实值表中的收益函数指针指向CommissionEmployee的收益函数，该函数返回雇员的销售总额乘以佣金率。
> print函数指针指向该函数的CommissionEmployee版本，后者打印员工的类型、姓名、社会保险号、佣金率和销售总额。
> 与salarieemployee类一样，这两个函数都覆盖了Employee类中的函数。



> BasePlusCommissionEmployee Class vtable
> The earnings function pointer in the vtable for class BasePlusCommissionEmployee points to the BasePlusCommissionEmployee’s earnings function, which returns the employee’s base salary plus gross sales multiplied by commission rate.
> The print function pointer points to the BasePlusCommissionEmployee version of the function, which prints the employee’s base salary plus the type, name, social security number, commission rate and gross sales.
> Both functions override the functions in class CommissionEmployee.
> BasePlusCommissionEmployee类虚表
>
> 类BasePlusCommissionEmployee的实值表中的收益函数指针指向BasePlusCommissionEmployee的收益函数，该函数返回员工的基本工资加上总销售额乘以佣金率。
> print函数指针指向该函数的BasePlusCommissionEmployee版本，该版本打印员工的基本工资加上类型、姓名、社会保险号、佣金率和总销售额。
> 这两个函数都覆盖了CommissionEmployee类中的函数。



> Three Levels of Pointers to Implement Polymorphism
> Polymorphism is accomplished through an elegant data structure involving three levels of pointers.
> We’ve discussed one level—the function pointers in the vtable.
> These point to the actual functions that execute when a virtual function is invoked.
> Now we consider the second level of pointers.
> Whenever an object of a class with one or more virtual functions is instantiated, the compiler attaches to the object a pointer to the vtable for that class.
> This pointer is normally at the front of the object, but it isn’t required to be implemented that way.
> 实现多态的三层指针
> 多态是通过包含三层指针的优雅数据结构实现的。
>
> 我们已经讨论了一个级别——虚函数表中的函数指针，这些指向在调用虚函数时执行的实际函数。
>
> 现在我们考虑第二级指针：每当实例化具有一个或多个虚函数的类的对象时，编译器将指向该类虚函数表的指针附加到该对象上。
>
> 该指针通常位于对象的前面，但并不需要以这种方式实现。



> In Fig. 12.18, these pointers are associated with the objects created in Fig. 12.17.
> Notice that the diagram displays each of the object’s data member values.
> The third level of pointers simply contains the handles to the objects that receive the virtual function calls.
> The handles in this level may also be references.
> Fig. 12.18 depicts the vector employees that contains Employee pointers.
>
> 在图12.18中，这些指针与图12.17中创建的对象相关联。
> 注意，图中显示了对象的每个数据成员值。
>
> **第三层指针仅包含接收虚函数调用的对象的句柄。**
>
> 这个级别的句柄也可以是引用。
> 图12.18描述了包含Employee指针的vector employees。



> Thus, the compiler compiles an offset or displacement of four bytes (four bytes for each pointer on today’s popular 32-bit machines, and only one pointer needs to be skipped) into the table of machine-language object-code pointers to find the code that will execute the virtual function call.
>
> 因此，编译器将四个字节的偏移量或位移(在当今流行的32位机器上每个指针四个字节，只需要跳过一个指针)
> 编译到机器语言对象代码指针表中，以查找将执行虚函数调用的代码。64位操作系统上是8个字节。



> The compiler generates code that performs the following operations. 
> Select the ith entry of employees, and pass it as an argument to function virtualViaPointer. This sets parameter baseClassPtr to point to commissionEmployee.
> Dereference that pointer to get to the commissionEmployee object.
> Dereference commissionEmployee’s vtable pointer to get to the CommissionEmployee vtable.
> Skip the offset of four bytes to select the print function pointer.
> Dereference the print function pointer to form the “name” of the actual function to execute, and use the function call operator () to execute the appropriate print function.
>
> 编译器生成执行以下操作的代码。
> 选择雇员的第i个条目，并将其作为参数传递给函数virtualViaPointer。这将baseClassPtr参数设置为指向commissionEmployee。
> 解引用该指针以获得commissionEmployee对象。
> 解引用commissionEmployee的实参表指针，以获得commissionEmployee实参表。
> 跳过四个字节的偏移量以选择打印函数指针。
>
> 取消对打印函数指针的引用，形成要执行的实际函数的“名称”，并使用函数调用operator()来执行相应的打印函数。



优化后的Cpp编译器生成的多态代码执行效率和switch语句的效率是一样的，但是对于性能要求很高的需要实时更新的应用程序，多态性的消耗就太高了。



> 当我们调用`delete`时，C++会检查指针是否为空。如果指针为空（即指向`nullptr`），`delete`操作符会立即返回，而不会尝试释放任何内存。这种行为的设计是为了简化内存管理，使得程序员不必在调用`delete`之前检查指针是否为空。
>
> ```cpp
> #include <iostream>
> 
> int main() {
>  int* ptr = nullptr;
> 
>  // 安全地删除空指针
>  delete ptr;
> 
>  // 重新分配并删除
>  ptr = new int(10);
>  delete ptr;
> 
>  // 再次删除空指针
>  ptr = nullptr;
>  delete ptr;
> 
>  std::cout << "All delete operations completed successfully." << std::endl;
> 
>  return 0;
> }
> 
> ```
>
> 
>
> ### 重要注意事项
>
> 1. **多次删除同一个指针**：对同一个指针多次调用`delete`会导致未定义行为。程序员应确保每个指针只调用一次`delete`，并在删除后将其设置为`nullptr`以避免重复删除。
> 2. **指针悬挂（Dangling Pointer）**：在删除指针后，继续使用这个指针会导致悬挂指针问题。这种情况下指针指向的内存已经被释放，再次访问该内存会导致未定义行为。
>
> 
>
> ### 总结
>
> - 对空指针调用`delete`是安全的，不会引发任何问题。
> - 删除指针后，应将指针设置为`nullptr`以避免悬挂指针和重复删除问题。
> - 多次删除同一个非空指针会导致未定义行为，程序员应避免这种情况。



> This section demonstrates the powerful capabilities of runtime type information (RTTI) and dynamic casting, which enable a program to determine an object’s type at execution time and act on that object accordingly.
> Figure 12.19 uses the Employee hierarchy developed in Section 12.6 and increases by 10 percent the base salary of each BasePlusCommissionEmployee.
>
> 本节演示运行时类型信息(RTTI)和动态类型转换的强大功能，它们使程序能够在执行时确定对象的类型，并相应地对该对象进行操作。
> 图12.19使用第12.6节中开发的Employee层次结构，并将每个BasePlusCommissionEmployee的基本工资增加10%。

![image-20240607233428216](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607233428216.png)

![image-20240607233438656](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240607233438656.png)



> Since we process the Employees polymorphically, we cannot (with the techniques you’ve learned so far) be certain as to which type of Employee is being manipulated at any given time.
> BasePlusCommissionEmployee employees must be identified when we encounter them so they can receive the 10 percent salary increase.
> To accomplish this, we use operator dynamic_cast (line 39) to determine whether the current Employee’s type is BasePlusCommissionEmployee.
> This is the downcast operation we referred to in Section 12.3.3.
> Lines 38–39 dynamically downcast employeePtr from type Employee * to type BasePlusCommissionEmployee *.
>
> 由于我们以多态方式处理Employee，
>
> 因此我们无法(使用到目前为止学到的技术)确定在任何给定时间正在操作哪种类型的Employee。
> 当我们遇到员工时，必须确认他们的身份，这样他们才能获得10%的加薪。
>
> 为此，我们使用操作符dynamic_cast(第39行)来确定当前Employee的类型是BasePlusCommissionEmployee。
>
> 这是我们在12.3.3节中提到的向下转换操作。
> 第38-39行动态地将employeePtr从Employee *类型向下转换为BasePlusCommissionEmployee *类型。



`dynamic_cast` 是 C++ 中用于类型安全的向下转换（downcasting）和横向转换（cross-casting）的运算符。它主要用于带有多态的继承层次中，确保在运行时类型转换的安全性。

### 使用场景

1. **向下转换（Downcasting）**：将基类指针或引用转换为派生类指针或引用。
2. **横向转换（Cross-casting）**：在具有共同基类的不同派生类之间进行转换。

### 语法

```cpp
dynamic_cast<new_type>(expression)
```

- `new_type`：目标类型，必须是指针或引用类型。
- `expression`：要转换的表达式，必须是指针或引用类型，并且是多态类型（即基类中至少有一个虚函数）。

### 动态类型检查

`dynamic_cast` 在运行时进行类型检查，如果转换是安全的，则返回一个指向新类型的指针或引用；如果转换不安全，则返回 `nullptr`（对于指针）或抛出 `std::bad_cast` 异常（对于引用）。

### 示例代码

#### 基本用法

```cpp
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {} // 必须有一个虚函数，通常是虚析构函数
};

class Derived1 : public Base {
public:
    void show() {
        std::cout << "Derived1" << std::endl;
    }
};

class Derived2 : public Base {
public:
    void display() {
        std::cout << "Derived2" << std::endl;
    }
};

void checkAndCast(Base* base) {
    if (Derived1* d1 = dynamic_cast<Derived1*>(base)) {
        d1->show();
    } else if (Derived2* d2 = dynamic_cast<Derived2*>(base)) {
        d2->display();
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}

int main() {
    Base* b1 = new Derived1();
    Base* b2 = new Derived2();
    Base* b3 = new Base();

    checkAndCast(b1); // 输出: Derived1
    checkAndCast(b2); // 输出: Derived2
    checkAndCast(b3); // 输出: Unknown type

    delete b1;
    delete b2;
    delete b3;

    return 0;
}
```

在这个例子中，`checkAndCast` 函数使用 `dynamic_cast` 将基类指针转换为派生类指针，并根据转换结果调用相应的方法。

### 注意事项

1. **必须是多态类型**：`dynamic_cast` 只能用于具有虚函数的类（多态类型）。
2. **性能开销**：由于 `dynamic_cast` 需要在运行时进行类型检查，所以比 `static_cast` 有更大的性能开销。
3. **转换失败**：对于指针类型，转换失败会返回 `nullptr`；对于引用类型，转换失败会抛出 `std::bad_cast` 异常。

#### 失败处理示例

```cpp
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() {
        std::cout << "Derived" << std::endl;
    }
};

int main() {
    Base* base = new Base();
    try {
        Derived& d = dynamic_cast<Derived&>(*base);
        d.show();
    } catch (const std::bad_cast& e) {
        std::cout << "Bad cast: " << e.what() << std::endl;
    }

    delete base;
    return 0;
}
```

在这个例子中，尝试将基类引用转换为派生类引用失败，`dynamic_cast` 抛出了 `std::bad_cast` 异常。

### 总结

- `dynamic_cast` 用于类型安全的向下转换和横向转换。
- 运行时类型检查，确保转换的安全性。
- 只能用于具有虚函数的多态类型。
- 转换失败时，对于指针返回 `nullptr`，对于引用抛出 `std::bad_cast` 异常。

使用 `dynamic_cast` 可以显著提高代码的类型安全性，尤其是在复杂的继承层次结构中。



**能够转化成功的条件是：该基类指向的派生类对象 与dynamic_cast<newType> 中的 newType相同**

**否则，如果是指针：则会赋值为nullptr，另外：则是抛出std::bad_cast异常。**



> `typeid` 运算符是C++中的一种运行时类型信息（RTTI）工具，用于获取对象的实际类型。它返回一个 `std::type_info` 对象，该对象可以用来比较和识别类型。`typeid` 运算符在编译时和运行时都可以使用，但在运行时更有用，尤其是处理多态对象时。
>
> ### 基本用法
>
> `typeid` 运算符的基本语法如下：
>
> ```cpp
> typeid(expression)
> ```
>
> 其中，`expression` 可以是任何表达式或类型。
>
> ### 示例代码
>
> 以下是一些示例，展示了 `typeid` 运算符的用法：
>
> #### 获取基本类型的类型信息
>
> ```cpp
> #include <iostream>
> #include <typeinfo>
> 
> int main() {
>  int a = 5;
>  double b = 3.14;
>  std::cout << "Type of a: " << typeid(a).name() << std::endl;
>  std::cout << "Type of b: " << typeid(b).name() << std::endl;
> 
>  return 0;
> }
> ```
>
> 输出：
>
> ```
> Type of a: i
> Type of b: d
> ```
>
> 注意：`typeid().name()` 返回的类型名是实现定义的（通常是编译器特定的表示形式），在不同的编译器中可能有所不同。
>
> #### 用于多态对象
>
> 在多态对象的情况下，`typeid` 可以用来获取对象的实际类型，而不仅仅是基类的类型。
>
> ```cpp
> #include <iostream>
> #include <typeinfo>
> 
> class Base {
> public:
>  virtual ~Base() {}
> };
> 
> class Derived : public Base {};
> 
> int main() {
>  Base* b = new Derived();
>  std::cout << "Type of b: " << typeid(b).name() << std::endl;
>  std::cout << "Type of *b: " << typeid(*b).name() << std::endl;
> 
>  delete b;
>  return 0;
> }
> ```
>
> 输出：
>
> ```
> Type of b: P4Base
> Type of *b: 7Derived
> ```
>
> 在这个例子中，`typeid(b)` 返回的是指针类型 `Base*`，而 `typeid(*b)` 返回的是 `Derived`，因为 `b` 实际上指向一个 `Derived` 对象。
>
> ### 比较类型
>
> 可以使用 `typeid` 运算符来比较两个对象的类型是否相同。
>
> ```cpp
> #include <iostream>
> #include <typeinfo>
> 
> class Base {
> public:
>  virtual ~Base() {}
> };
> 
> class Derived : public Base {};
> 
> int main() {
>  Base* base = new Base();
>  Base* derived = new Derived();
> 
>  if (typeid(*base) == typeid(*derived)) {
>      std::cout << "base and derived are of the same type." << std::endl;
>  } else {
>      std::cout << "base and derived are of different types." << std::endl;
>  }
> 
>  delete base;
>  delete derived;
>  return 0;
> }
> ```
>
> 输出：
>
> ```
> base and derived are of different types.
> ```
>
> 在这个例子中，`typeid(*base)` 和 `typeid(*derived)` 返回不同的类型信息，因此输出表明它们是不同类型的对象。
>
> ### 注意事项
>
> 1. **必须包含虚函数**：在使用 `typeid` 进行多态类型检查时，基类必须包含至少一个虚函数，否则 `typeid` 会返回基类的类型而不是派生类的类型。
> 2. **类型名的实现依赖**：`typeid().name()` 返回的类型名是实现定义的，通常在不同的编译器中可能不同。
> 3. **空指针**：如果对空指针使用 `typeid`（如 `typeid(*p)`），会抛出 `std::bad_typeid` 异常。
>
> #### 处理空指针的示例
>
> ```cpp
> #include <iostream>
> #include <typeinfo>
> 
> class Base {
> public:
>     virtual ~Base() {}
> };
> 
> int main() {
>     Base* p = nullptr;
>     try {
>         std::cout << "Type of *p: " << typeid(*p).name() << std::endl;
>     } catch (const std::bad_typeid& e) {
>         std::cerr << "Caught bad_typeid: " << e.what() << std::endl;
>     }
> 
>     return 0;
> }
> ```
>
> 在这个例子中，对空指针使用 `typeid` 会抛出 `std::bad_typeid` 异常，并输出错误信息。
>
> ### 总结
>
> - `typeid` 用于获取对象或类型的类型信息，返回一个 `std::type_info` 对象。
> - 在多态情况下，`typeid` 可以用于确定对象的实际类型。
> - 可以使用 `typeid` 比较两个对象的类型是否相同。
> - 对空指针使用 `typeid` 会抛出 `std::bad_typeid` 异常。
> - `typeid().name()` 返回的类型名是实现定义的，可能因编译器而异。



试图通过基类指针来调用仅在派生类中实现的函数是不允许的，只能调用在基类中实现的函数。