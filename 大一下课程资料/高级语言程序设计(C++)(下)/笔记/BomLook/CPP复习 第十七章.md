# Cpp复习 第十七章

在浮点运算中，许多c++实现允许除零，在这种情况下，正无穷大或负无穷大分别显示为INF或-INF

> ### C++ 中的异常处理 (Exception Handling)
>
> 异常处理是一种控制结构，用于处理程序中的错误和异常情况，使程序能够在遇到错误时采取适当的措施而不是直接崩溃。在 C++ 中，异常处理机制使用 `try`、`throw` 和 `catch` 关键字来实现。
>
> #### 基本语法
>
> 1. **`try` 块**：包含可能会抛出异常的代码。
> 2. **`throw` 语句**：用于抛出一个异常。
> 3. **`catch` 块**：用于捕获异常并处理。
>
> #### 示例
>
> ```cpp
> #include <iostream>
> #include <stdexcept>  // 包含标准异常类
> 
> void mightGoWrong() {
>     bool error = true;
>     if (error) {
>         throw std::runtime_error("Something went wrong");
>     }
> }
> 
> int main() {
>     try {
>         mightGoWrong();
>     } catch (const std::runtime_error& e) {
>         std::cerr << "Caught an exception: " << e.what() << std::endl;
>     }
> 
>     std::cout << "Program continues..." << std::endl;
>     return 0;
> }
> ```
>
> ### 异常类
>
> C++ 标准库提供了一些常用的异常类，这些类都继承自 `std::exception`：
>
> - `std::logic_error`
> - `std::runtime_error`
> - `std::bad_alloc`（用于内存分配失败）
> - `std::out_of_range`
> - `std::invalid_argument`
>
> #### 自定义异常类
>
> 你可以定义自己的异常类，继承自 `std::exception` 或其他标准异常类：
>
> ```cpp
> #include <iostream>
> #include <exception>
> 
> class MyException : public std::exception {
> public:
>     const char* what() const noexcept override {
>         return "My custom exception";
>     }
> };
> 
> void mightGoWrong() {
>     throw MyException();
> }
> 
> int main() {
>     try {
>         mightGoWrong();
>     } catch (const MyException& e) {
>         std::cerr << "Caught my exception: " << e.what() << std::endl;
>     }
> 
>     std::cout << "Program continues..." << std::endl;
>     return 0;
> }
> ```
>
> ### 栈展开 (Stack Unwinding)
>
> 当一个异常被抛出时，C++ 运行时系统会进行栈展开，即逐层退出函数调用栈直到找到一个匹配的 `catch` 块。如果在栈展开过程中需要执行清理操作（如释放资源），应该在类的析构函数中进行，因为析构函数会在对象离开作用域时自动调用。
>
> #### 示例
>
> ```cpp
> #include <iostream>
> #include <stdexcept>
> 
> class Resource {
> public:
>     Resource() {
>         std::cout << "Resource acquired\n";
>     }
>     ~Resource() {
>         std::cout << "Resource released\n";
>     }
> };
> 
> void mightGoWrong() {
>     Resource res;
>     throw std::runtime_error("Error occurred");
> }
> 
> int main() {
>     try {
>         mightGoWrong();
>     } catch (const std::runtime_error& e) {
>         std::cerr << "Caught an exception: " << e.what() << std::endl;
>     }
> 
>     std::cout << "Program continues..." << std::endl;
>     return 0;
> }
> ```
>
> 输出：
>
> ```
> Resource acquired
> Resource released
> Caught an exception: Error occurred
> Program continues...
> ```
>
> ### 总结
>
> 1. **异常处理**：使用 `try`、`throw` 和 `catch` 进行。
> 2. **标准异常类**：C++ 标准库提供了一些常用的异常类，便于错误处理。
> 3. **自定义异常类**：可以继承标准异常类来创建自定义异常。
> 4. **栈展开**：异常抛出后，系统会进行栈展开，析构函数会在此过程中被调用，确保资源被释放。
>
> 异常处理机制使得程序可以在遇到错误时采取适当的措施，而不是直接崩溃，从而提高程序的健壮性和可维护性。



> A typical exception class that derives from the runtime_error class defines only a constructor (e.g., lines 11–12) that passes an error-message string to the base-class runtime_error constructor.
> Every exception class that derives directly or indirectly from exception contains the virtual function what, which returns an exception object’s error message.
> You are not required to derive a custom exception class, such as DivideByZeroException, from the standard exception classes provided by C++.
> Doing so allows you to use the virtual function what to obtain an appropriate error message.
> We use an object of this DivideByZeroException class in Fig. 17.2 to indicate when an attempt is made to divide by zero.
> 从runtime_error类派生的典型异常类只定义一个构造函数(例如，第11-12行)，该构造函数将错误消息字符串传递给基类runtime_error构造函数。
> 每个直接或间接从exception派生的异常类都包含虚函数what，它返回异常对象的错误消息。
> 您不需要从c++提供的标准异常类派生自定义异常类，例如DivideByZeroException。
> 但是，这样做允许您使用虚函数what来获得适当的错误消息。
> 在图17.2中，我们使用DivideByZeroException类的一个对象来指示何时尝试除零。

![image-20240608155155834](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608155155834.png)

> Demonstrating Exception Handling
> Fig. 17.2 uses exception handling to wrap code that might throw a DivideByZeroException and to handle that exception, should one occur.
> Function quotient divides its first parameter (numerator) by its second parameter (denominator).
> Assuming that the user does not specify 0 as the denominator for the division, quotient returns the division result.
> However, if the user inputs 0 for the denominator, function quotient throws an exception.
> 演示异常处理
> 图17.2使用异常处理来包装可能抛出DivideByZeroException的代码，并在出现异常时处理该异常。
> 函数商将它的第一个参数(分子)除以它的第二个参数(分母)。
> 假设用户没有指定0作为除法的分母，那么quotient将返回除法结果。
> 但是，如果用户为分母输入0，则函数quotient抛出异常。

![image-20240608155348998](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608155348998.png)



![image-20240608155355435](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608155355435.png)

![image-20240608155402213](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608155402213.png)

![image-20240608155416381](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608155416381.png)

> Enclosing Code in a try Block
> Exception handling is geared to situations in which the function that detects an error is unable to handle it. 
> try blocks enable exception handling.
> The try block encloses statements that might cause exceptions and statements that should be skipped if an exception occurs.
> In this example, because the invocation of function quotient (line 34) can throw an exception, we enclose this function invocation in a try block.
> Enclosing the output statement (line 35) in the try block ensures that the output will occur only if function quotient returns a result.
>
> 在try块中封装代码
> 异常处理适用于检测到错误的函数无法处理错误的情况。
> Try块启用异常处理。
> try块包含可能导致异常的语句和在发生异常时应该跳过的语句。
> 在本例中，由于调用函数quotient(第34行)会抛出异常，因此我们将该函数调用包含在try块中。
> 在try块中封装输出语句(第35行)确保只有当函数quotient返回结果时才会输出。



**异常可能出现在try语句块中明确提到的代码中，有可能在try语句块中的代码对其他函数的调用或者嵌套调用。**



> Defining a catch Handler to Process a DivideByZeroException
> Exceptions are processed by catch handlers.
> At least one catch handler (lines 37–41) must immediately follow each try block.
> An exception parameter should always be declared as a reference to the type of exception the catch handler can process (DivideByZeroException in this case)—this prevents copying the exception object when it’s caught and allows a catch handler to properly catch derived-class exceptions as well.
> When an exception occurs in a try block, the catch handler that executes is the first one whose type matches the type of the exception that occurred (i.e., the type in the catch block matches the thrown exception type exactly or is a direct or indirect base class of it).
> 定义一个catch处理程序来处理一个DivideByZeroException：
> 异常由catch处理程序处理。
> 在每个try块之后必须立即执行至少一个catch处理程序(第37-41行)。
> 异常参数应该始终声明为catch处理程序可以处理的异常类型的引用(在本例中是DivideByZeroException)——这可以防止在捕获异常对象时复制异常对象，并允许catch处理程序正确捕获派生类异常。
> 当在try块中发生异常时，执行的catch处理程序是第一个类型与发生的异常类型匹配的处理程序(即，catch块中的类型与抛出的异常类型完全匹配，或者是它的直接或间接基类)。
>
> If an exception parameter includes an optional parameter name, the catch handler can use that parameter name to interact with the caught exception in the body of the catch handler, which is delimited by braces ({ and }).
> A catch handler typically reports the error to the user, logs it to a file, terminates the program gracefully or tries an alternate strategy to accomplish the failed task.
> In this example, the catch handler simply reports that the user attempted to divide by zero. Then the program prompts the user to enter two new integer values.
> 如果异常参数包含可选参数名，catch处理程序可以使用该参数名与catch处理程序体中捕获的异常进行交互，该处理程序体由大括号({和})分隔。
> catch处理程序通常向用户报告错误，将其记录到文件中，优雅地终止程序或尝试替代策略来完成失败的任务。
> 在本例中，catch处理程序只是报告用户试图除以0。然后程序提示用户输入两个新的整数值。



注意：1、**try语句块和catch语句之间不能有其他的代码。**
			2、**一个catch处理器只能由一个参数。**
			3、**不同的catch处理器捕获的异常必须是不同的，否则会编译错误。**



> **Termination Model of Exception Handling**
>
> If an exception occurs as the result of a statement in a try block, the try block expires (i.e., terminates immediately).
>
> Next, the program searches for the first catch handler that can process the type of exception that occurred.
>
> The program locates the matching catch by comparing the thrown exception’s type to each catch’s exception-parameter type until the program finds a match.
>
> A match occurs if the types are *identical* or if the thrown exception’s type is a *derived class* of the exception-parameter type.
>
> When a match occurs, the code in the matching catch handler executes.
>
> 异常处理的终止模型
> 如果由于try块中的语句而发生异常，则try块将过期(即立即终止)。
> 接下来，程序搜索第一个可以处理所发生异常类型的catch处理程序。
> 程序通过将抛出异常的类型与每个catch的异常参数类型进行比较，直至找到匹配的catch，从而定位匹配的catch。
> 如果类型相同，或者抛出异常的类型是异常参数类型的派生类，则会发生匹配。
> 当出现匹配时，执行匹配catch处理程序中的代码。
>
> When a catch handler finishes processing by reaching its closing right brace (}), the exception is considered handled and the local variables defined within the catch handler (including the catch parameter) go out of scope.
>
> Program control does *not* return to the point at which the exception occurred (known as the throw point), because the try block has *expired*.
>
> Rather, control resumes with the first statement after the last catch handler following the try block.
>
> This is known as the termination model of exception handling.
>
> As with any other block of code, *when a* *try* *block terminates, local variables defined in the block go out of scope*.
>
> 当catch处理程序通过到达右括号(})结束处理时，认为异常已处理，并且在catch处理程序中定义的局部变量(包括catch形参)超出了作用域。
> 程序控制不会返回到发生异常的点(称为抛出点)，因为try块已经过期。
> 相反，控制在try块后面的最后一个catch处理程序之后的第一个语句中恢复。
> 这被称为异常处理的终止模型。
> 与任何其他代码块一样，当try块终止时，块中定义的局部变量将超出作用域。
>
> 还有另外一种模式：恢复模式，控制将在异常抛出后重新开始。
>
> 异常处理可以让程序在解决问题后，能够继续运行，保证了程序的健壮性。



> Flow of Program Control When the User Enters a Denominator of Zero
> As part of throwing an exception, the throw operand is created and used to initialize the parameter in the catch handler, which we discuss momentarily.
> Central characteristic of exception handling: If your program explicitly throws an exception, it should do so before the error has an opportunity to occur.
> In general, when an exception is thrown within a try block, the exception is caught by a catch handler that specifies the type matching the thrown exception.
> 当用户输入分母为零时的程序控制流程
> 作为抛出异常的一部分，将创建throw操作数，并使用该操作数初始化catch处理程序中的参数，稍后将对此进行讨论。
> 异常处理的核心特征：如果程序显式抛出异常，它应该在错误有机会发生之前抛出异常。
> 通常，当在try块中抛出异常时，该异常由catch处理程序捕获，该处理程序指定与所抛出异常匹配的类型。
>
>
> throw语句用于指定一个抛出的操作数
>  In this program, the catch handler specifies that it catches DivideByZeroException objects—this type matches the object type thrown in function quotient.
> Actually, the catch handler catches a reference to the DivideByZeroException object created by function quotient’s throw statement.
> The exception object is maintained by the exception-handling mechanism.
> 在这个程序中，catch处理程序指定它捕获DivideByZeroException对象——该类型与函数quotient中抛出的对象类型匹配。
> 实际上，catch处理程序捕获对DivideByZeroException对象的引用，该对象是由function quotient的throw语句创建的。
> 异常对象由异常处理机制维护。



**将每种运行时的错误与一个有相应名称的异常类型结合，可以提高程序的清晰度。**

**重新抛出异常，就是由异常处理器接受到异常后，再次抛出一个异常进行处理。**

**在处理器外部更进一步处理而重新抛出异常，外层的try语句将检测这个重新抛出的异常，其之后的catch语句负责捕捉处理异常。**

参考以下例子：

这里不需要用到异常参数，所以直接使用&即可，不需要参数名

![image-20240608162505808](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608162505808.png)

![image-20240608162513292](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608162513292.png)

![image-20240608162526819](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608162526819.png)

堆栈展开：一般用于函数嵌套调用，如果在某一个函数中抛出异常，但是没有try...catch语句块来捕获，那么当前函数中所有在该函数体内初始化的局部变量都将被销毁，并且返回上一级函数，查看有没有try...catch语句，如果有，则捕获抛出异常并且处理，否则按照上面的内容类推。可以具体查看以下例子：

> When an exception is thrown but not caught in a particular scope, the function call stack is “unwound,” and an attempt is made to catch the exception in the next outer try…catch block.
> Unwinding the function call stack means that the function in which the exception was not caught terminates, all local variables that have completed intitialization in that function are destroyed and control returns to the statement that originally invoked that function.
> If a try block encloses that statement, an attempt is made to catch the exception.
> If a try block does not enclose that statement, stack unwinding occurs again.
> If no catch handler ever catches this exception, the program terminates.
> The program of Fig. 17.4 demonstrates stack unwinding.
> 当抛出异常但未在特定范围内捕获异常时，将“展开”函数调用堆栈，并尝试在下一个外部try…catch块中捕获异常。
> 展开函数调用堆栈意味着未捕获异常的函数终止，该函数中已完成初始化的所有局部变量将被销毁，控制返回到最初调用该函数的语句。
> 如果try块包含该语句，则尝试捕获异常。
> 如果try块没有包含该语句，则再次执行堆栈展开。
> 如果没有捕获处理程序捕获此异常，则程序终止。
> 图17.4的程序演示了堆栈展开。

![image-20240608163916400](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608163916400.png)

![image-20240608163923105](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608163923105.png)

![image-20240608163932020](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608163932020.png)



> Exception handling is designed to process synchronous errors, which occur when a statement executes, such as out-of-range array subscripts, arithmetic overflow (i.e., a value outside the representable range of values), division by zero, invalid function parameters and unsuccessful memory allocation (due to lack of memory).
> Exception handling is not designed to process errors associated with asynchronous events (e.g., disk I/O completions, network message arrivals, mouse clicks and keystrokes), which occur in parallel with, and independent of, the program’s flow of control.
> 异常处理的设计目的是处理同步错误，这种错误在语句执行时发生，例如超出范围的数组下标、算术溢出(即值超出可表示范围)、除零、无效的函数参数和不成功的内存分配(由于缺乏内存)。
> 异常处理不是设计用来处理与异步事件(例如，磁盘I/O完成、网络消息到达、鼠标点击和击键)相关的错误的，这些错误与程序的控制流并行发生，并且独立于程序的控制流。

**异常处理有助于在同一个大型项目中的程序员相互了解各自的错误处理代码。**

**带有常见错误情况的函数应该返回nullptr，0或者其他合适的值，而不是抛出异常，这样就可以让调用函数的程序通过检查返回值来确定函数调用是否成功。**



异常问题可以解决预定义组件和由预定义组件构成的特定组件的问题，当预定义组件遇到问题时，可以通过异常处理来与特定组件进行沟通。（预定义组件一开始就是定义好的，无法预知接下来可能会出现的问题）



> C++11: Declaring Functions That Do Not Throw Exceptions
> As of C++11, if a function does not throw any exceptions and does not call any functions that throw exceptions, you should explicitly state that a function does not throw exceptions. 
> This indicates to client-code programmers that there’s no need to place calls to the function in a try block. 
> Add noexcept to the right of the function’s parameter list in both the prototype and the definition. 
> For a const member function, place noexcept after const. 
> If a function that’s declared noexcept calls another function that throws an exception or executes a throw statement, the program terminates. 
> c++ 11:声明不抛出异常的函数
> 从c++ 11开始，如果函数不抛出任何异常，也不调用任何抛出异常的函数，则应该显式声明函数不抛出异常。
> 这向客户端代码程序员表明，不需要将对函数的调用放在try块中。
> 在原型和定义的函数参数列表的右侧添加noexcept。
> 对于const成员函数，在const之后放置noexcept。
> 如果声明为noexcept的函数调用另一个抛出异常或执行throw语句的函数，则程序终止。





下面的内容和上面的内容可能有点割裂，耐心看。

> The preferred alternative is to require the constructor to throw an exception that contains the error information, thus offering an opportunity for the program to handle the failure.
> Before an exception is thrown by a constructor, destructors are called for any member objects whose constructors have run to completion as part of the object being constructed.
> Destructors are called for every automatic object constructed in a try block before the exception is caught.
> Stack unwinding is guaranteed to have been completed at the point that an exception handler begins executing.
> If a destructor invoked as a result of stack unwinding throws an exception, the program terminates.
> This has been linked to various security attacks.
> 首选的替代方法是要求构造函数抛出包含错误信息的异常，从而为程序提供处理故障的机会。
>
> **在构造函数抛出异常之前，对其构造函数作为正在构造的对象的一部分运行到完成的任何成员对象调用析构函数。**
> **在捕获异常之前，对在try块中构造的每个自动对象调用析构函数。**
> **栈展开保证在异常处理程序开始执行时完成。**
>
> 如果由于堆栈展开而调用的析构函数抛出异常，则程序终止。这与各种安全攻击有关。



注意：析构函数应该是捕捉异常，而不是抛出异常。

> 在C++中，如果在异常传播过程中（即堆栈展开期间）一个析构函数抛出异常，将会导致程序调用`std::terminate`并立即终止。这是因为在C++中，异常的处理机制设计为在同一时间只能有一个活动异常。如果一个异常正在传播，而另一个异常在此过程中被抛出，系统将不知道如何处理多个同时存在的异常，因而选择终止程序。
>
> ### 为什么在析构函数中抛出异常会导致程序终止
>
> 堆栈展开期间，程序需要释放资源和调用栈上的所有对象的析构函数。如果析构函数在释放资源时抛出异常，这将会导致程序在处理中出现两个活动异常（一个是原本正在处理的异常，另一个是析构函数抛出的新异常）。这会导致无法正确管理异常的控制流。
>
> 以下是一个示例，展示了在堆栈展开期间析构函数抛出异常的情况：
>
> ```cpp
> #include <iostream>
> #include <exception>
> 
> class Resource {
> public:
>  ~Resource() {
>      std::cout << "Resource destructor called\n";
>      throw std::runtime_error("Destructor exception");
>  }
> };
> 
> void mightGoWrong() {
>  Resource res;
>  throw std::runtime_error("Original exception");
> }
> 
> int main() {
>  try {
>      mightGoWrong();
>  } catch (const std::runtime_error& e) {
>      std::cerr << "Caught an exception: " << e.what() << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> 在这个例子中，当 `mightGoWrong` 函数抛出“Original exception”异常时，程序会进入堆栈展开过程，调用`Resource`对象的析构函数。而在析构函数中抛出了另一个异常“Destructor exception”，这会导致程序调用`std::terminate`并立即终止。
>
> ### 与安全攻击的关系
>
> 这种情况不仅仅是技术细节问题，还与安全性有关。在安全攻击中，攻击者可能会试图利用程序的不当行为或未处理的异常来执行恶意代码。如下几种情况：
>
> 1. **资源泄漏**：如果在堆栈展开过程中，析构函数抛出异常，资源可能无法正确释放。这可能导致资源泄漏，攻击者可能利用这一点耗尽系统资源。
> 2. **不确定行为**：未处理的异常可能导致程序以不确定的方式行为，攻击者可以利用这种不确定性来破坏程序的正常执行流程。
> 3. **崩溃利用**：攻击者可能通过故意触发异常并利用程序崩溃的行为来获得对系统的控制。
>
> ### 如何防止析构函数抛出异常
>
> 为了避免这些问题，通常的做法是在析构函数中捕获并处理所有可能的异常，确保析构函数不会抛出异常。以下是一个示例：
>
> ```cpp
> #include <iostream>
> #include <exception>
> 
> class Resource {
> public:
>     ~Resource() {
>         try {
>             // 可能抛出异常的代码
>             throw std::runtime_error("Destructor exception");
>         } catch (...) {
>             std::cerr << "Exception caught in destructor" << std::endl;
>             // 处理异常（例如，记录日志、释放资源等），确保不抛出
>         }
>     }
> };
> 
> void mightGoWrong() {
>     Resource res;
>     throw std::runtime_error("Original exception");
> }
> 
> int main() {
>     try {
>         mightGoWrong();
>     } catch (const std::runtime_error& e) {
>         std::cerr << "Caught an exception: " << e.what() << std::endl;
>     }
> 
>     return 0;
> }
> ```
>
> ### 总结
>
> 在析构函数中抛出异常会导致程序终止，这与异常处理机制设计有关，也是为了防止出现未处理的多个异常导致程序行为不确定或资源泄漏等问题。为了保证程序的健壮性和安全性，应该确保析构函数不会抛出异常，通常通过在析构函数中捕获并处理所有可能的异常来实现。这样可以确保在堆栈展开期间正确释放资源，避免程序因未处理的异常而崩溃。





> If an object has member objects, and if an exception is thrown before the outer object is fully constructed, then destructors will be executed for the member objects that have been constructed prior to the occurrence of the exception.
> If an array of objects has been partially constructed when an exception occurs, only the destructors for the constructed objects in the array will be called.
> 如果对象具有成员对象，并且在外部对象完全构造之前抛出异常，则将对在异常发生之前构造的成员对象执行析构函数。
> 如果在发生异常时已经部分构造了对象数组，则只调用数组中构造对象的析构函数。





> 在 C++ 中，正确地管理资源（如内存、文件句柄、网络连接等）是非常重要的。一个常见的模式是使用局部对象的构造函数和析构函数来管理资源的分配和释放。这种模式被称为 RAII（Resource Acquisition Is Initialization，资源获取即初始化）。
>
> ### RAII 模式
>
> RAII 的核心思想是将资源的分配和释放绑定到对象的生命周期。在对象的构造函数中获取资源，在对象的析构函数中释放资源。这样可以确保在异常情况下资源也能得到正确释放。
>
> ### 示例：文件资源管理
>
> 下面是一个简单的示例，展示如何使用 RAII 模式管理文件资源：
>
> ```cpp
> #include <iostream>
> #include <fstream>
> 
> class FileWrapper {
> public:
>  // 构造函数中打开文件
>  FileWrapper(const std::string& filename) : file(filename) {
>      if (!file.is_open()) {
>          throw std::runtime_error("Could not open file");
>      }
>  }
> 
>  // 析构函数中关闭文件
>  ~FileWrapper() {
>      if (file.is_open()) {
>          file.close();
>      }
>  }
> 
>  // 提供接口操作文件
>  void write(const std::string& data) {
>      if (file.is_open()) {
>          file << data;
>      }
>  }
> 
> private:
>  std::ofstream file;
> };
> 
> void writeToFile(const std::string& filename, const std::string& data) {
>  FileWrapper fileWrapper(filename);
>  fileWrapper.write(data);
>  // FileWrapper 对象离开作用域时，析构函数会自动关闭文件
> }
> 
> int main() {
>  try {
>      writeToFile("example.txt", "Hello, RAII!");
>  } catch (const std::exception& e) {
>      std::cerr << "Exception: " << e.what() << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> 在这个例子中，`FileWrapper` 类管理一个文件对象。它在构造函数中打开文件，在析构函数中关闭文件。即使在 `writeToFile` 函数中抛出异常，`FileWrapper` 的析构函数也会被调用，从而确保文件被正确关闭。
>
> ### 使用智能指针管理动态内存
>
> 除了文件资源，RAII 模式还可以用于管理动态内存。C++11 引入了智能指针，提供了一种简单而安全的方式来管理动态分配的内存。
>
> - `std::unique_ptr`：独占所有权的智能指针。
> - `std::shared_ptr`：共享所有权的智能指针。
> - `std::weak_ptr`：与 `std::shared_ptr` 搭配使用，防止循环引用。
>
> #### 示例：使用 `std::unique_ptr`
>
> ```cpp
> #include <iostream>
> #include <memory>
> 
> class Resource {
> public:
>     Resource() {
>         std::cout << "Resource acquired\n";
>     }
>     ~Resource() {
>         std::cout << "Resource released\n";
>     }
>     void doSomething() {
>         std::cout << "Doing something with resource\n";
>     }
> };
> 
> void useResource() {
>     std::unique_ptr<Resource> resource = std::make_unique<Resource>();
>     resource->doSomething();
>     // Resource 对象会在函数结束时自动释放
> }
> 
> int main() {
>     useResource();
>     return 0;
> }
> ```
>
> 在这个例子中，`std::unique_ptr` 管理一个 `Resource` 对象。当 `useResource` 函数结束时，`std::unique_ptr` 会自动释放 `Resource` 对象的内存。
>
> ### 其他资源管理
>
> RAII 可以用于管理任何需要显式释放的资源，例如：
>
> - 数据库连接
> - 互斥锁
> - 网络连接
>
> #### 示例：使用 `std::lock_guard` 管理互斥锁
>
> ```cpp
> #include <iostream>
> #include <thread>
> #include <mutex>
> 
> std::mutex mtx;
> 
> void printThreadId(int id) {
>     std::lock_guard<std::mutex> lock(mtx);
>     std::cout << "Thread " << id << std::endl;
>     // mtx 会在 lock 离开作用域时自动释放
> }
> 
> int main() {
>     std::thread t1(printThreadId, 1);
>     std::thread t2(printThreadId, 2);
> 
>     t1.join();
>     t2.join();
> 
>     return 0;
> }
> ```
>
> 在这个例子中，`std::lock_guard` 自动管理 `std::mutex` 的锁定和解锁操作，确保互斥锁在函数退出时被正确释放。
>
> ### 总结
>
> RAII 是 C++ 中一种重要的资源管理模式，它将资源的分配和释放绑定到对象的生命周期中，利用构造函数和析构函数确保资源在正常和异常情况下都能被正确释放。通过使用智能指针和其他 RAII 工具类（如 `std::lock_guard`），可以更安全、方便地管理各种资源，避免资源泄漏和其他潜在问题。



> Various exception classes can be derived from a common base class, as we discussed in Section 17.2, when we created class DivideByZeroException as a derived class of class exception.
> If a catch handler catches a reference to an exception object of a base-class type, it also can catch a reference to all objects of classes publicly derived from that base class—this allows for polymorphic processing of related exceptions.
> 正如我们在第17.2节中所讨论的，可以从公共基类派生出各种异常类，当时我们创建了类DivideByZeroException作为类exception的派生类。
> 如果catch处理程序捕获对基类类型的异常对象的引用，那么它也可以捕获对从该基类公开派生的类的所有对象的引用——这允许对相关异常进行多态处理。



**异常处理器：一种方法是分别捕获每一个派生类异常对象的每种引用，另一种是捕获基类异常对象的指针和引用，更高效。**



> When operator new fails, it throws a bad_alloc exception (defined in header file <new>).
> In this section, we present two examples of new failing.
> The first uses the version of new that throws a bad_alloc exception when new fails.
> The second uses function set_new_handler to handle new failures.
> [Note: The examples in Figs. 17.5–17.6 allocate large amounts of dynamic memory, which could cause your computer to become sluggish.]
> 当operator new失败时，它抛出一个bad_alloc异常(在头文件<new>中定义)。
> 在本节中，我们将介绍两个新故障的示例。
> 第一个使用new的版本，当new失败时抛出bad_alloc异常。
> 第二个使用set_new_handler函数来处理新的故障。
> [注意:图17.5-17.6中的例子分配了大量的动态内存，这可能会导致您的计算机变得迟钝。]

![image-20240608182753828](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608182753828.png)

![image-20240608182801972](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608182801972.png)

这些异常的输出取决于内存和编译器等原因。



> new Returning nullptr on Failure
> The C++ standard specifies that programmers can use an older version of new that returns nullptr upon failure.
> For this purpose, header <new> defines object nothrow (of type nothrow_t), which is used as follows:
> double *ptr = new( nothrow ) double[ 50000000 ];
> The preceding statement uses the version of new that does not throw bad_alloc exceptions (i.e., nothrow) to allocate an array of 50,000,000 doubles.
>
> new失败返回nullptr
> c++标准规定程序员可以使用旧版本的new，在失败时返回nullptr。
> 为此，header <new>定义了nothrow对象(nothrow_t类型)，使用方法如下:
> Double *ptr = new(nothrow) Double [50000000];
> 前面的语句使用不抛出bad_alloc异常(即nothrow)的new版本来分配一个包含50,000,000个double类型的数组。
> 推荐使用这种方法，使得代码更具有健壮性。



> Handling new Failures Using Function set_new_handler
> Function set_new_handler (prototyped in standard header file <new>) takes as its argument a pointer to a function that takes no arguments and returns void.
> This pointer points to the function that will be called if new fails.
> This provides you with a uniform approach to handling all new failures, regardless of where a failure occurs in the program.
> Once set_new_handler registers a new handler in the program, operator new does not throw bad_alloc on failure; rather, it defers the error handling to the new-handler function.
> If new fails to allocate memory and set_new_handler did not register a new-handler function, new throws a bad_alloc exception.
> If new fails to allocate memory and a new-handler function has been registered, the new-handler function is called.
> 使用set_new_handler函数处理新的故障：
> 函数set_new_handler(原型在标准头文件<new>中)接受一个指针作为参数，该指针指向一个不接受参数并返回void的函数。
> 这个指针指向如果new失败将被调用的函数。
> 这为您提供了处理所有新故障的统一方法，而不管故障发生在程序中的哪个位置。
> 一旦set_new_handler在程序中注册了一个新的处理程序，operator new就不会抛出bad_alloc;相反，它将错误处理延迟到new-handler函数。
> 如果new分配内存失败，并且set_new_handler没有注册一个new-handler函数，new抛出一个bad_alloc异常。
> 如果new分配内存失败，并且注册了new-handler函数，则调用new-handler函数。



> The new-handler function should perform one of the following tasks:
> Make more memory available by deleting other dynamically allocated memory (or telling the user to close other applications) and return to operator new to attempt to allocate memory again.
> Throw an exception of type bad_alloc.
> Call function abort or exit (both found in header file <cstdlib>) to terminate the program. These were introduced in Section 9.7.
> Figure 17.6 demonstrates set_new_handler.
> Function customNewHandler (lines 9–13) prints an error message (line 11), then calls abort (line 12) to terminate the program.
> The output shows that the loop iterated four times before new failed and invoked function customNewHandler.
>
> new-handler函数应该执行以下任务之一:
> 通过删除其他动态分配的内存(或告诉用户关闭其他应用程序)来获得更多可用内存，并返回到operator new以尝试再次分配内存。
> 抛出类型为bad_alloc的异常。
> 调用函数abort或exit(都在头文件<cstdlib>中找到)来终止程序。第9.7节介绍了这些特性。
> 图17.6演示了set_new_handler。
> 函数customNewHandler(第9-13行)打印一条错误消息(第11行)，然后调用abort(第12行)终止程序。
> 输出显示，在new失败并调用函数customNewHandler之前，循环迭代了四次。
> 课本的例子这里不再展示 和下面的基本一样



> 在 C++ 中，`set_new_handler` 是一个非常有用的工具，用于在内存分配失败时自定义处理行为。默认情况下，如果 `new` 运算符无法分配足够的内存，会抛出 `std::bad_alloc` 异常。但是，通过使用 `set_new_handler`，你可以指定一个函数，当 `new` 无法分配内存时调用该函数，而不是直接抛出异常。
>
> ### `set_new_handler` 的用法
>
> 以下是如何使用 `set_new_handler` 的示例：
>
> 1. **定义一个处理函数**：
>    这个函数将在 `new` 运算符分配内存失败时调用。这个函数必须是无参的，并且返回类型为 `void`。
>
> ```cpp
> #include <iostream>
> #include <new> // 包含 std::set_new_handler
> 
> void myNewHandler() {
>     std::cerr << "Memory allocation failed. Terminating.\n";
>     std::abort(); // 终止程序
> }
> ```
>
> 2. **设置处理函数**：
>    使用 `std::set_new_handler` 函数设置你自定义的处理函数。
>
> ```cpp
> int main() {
>     std::set_new_handler(myNewHandler); // 设置新的内存分配失败处理函数
> 
>     try {
>         // 尝试分配大量内存以触发内存分配失败
>         while (true) {
>             new char[1024 * 1024 * 1024]; // 分配1GB内存块
>         }
>     } catch (const std::bad_alloc& e) {
>         std::cerr << "Caught std::bad_alloc: " << e.what() << '\n';
>     }
> 
>     return 0;
> }
> ```
>
> 在这个例子中，`myNewHandler` 是一个处理函数，当 `new` 运算符无法分配内存时，它会被调用，输出错误信息并终止程序。
>
> ### 处理函数的作用
>
> 处理函数在 `new` 运算符分配内存失败时调用，你可以在处理函数中执行以下操作：
>
> - 记录日志或输出错误信息。
> - 尝试释放一些内存，然后返回以重试内存分配。
> - 调用 `std::abort` 或 `std::exit` 终止程序。
>
> ### 示例：尝试释放内存
>
> 假设你有一些可以释放的全局资源，可以在内存分配失败时释放这些资源并重试分配：
>
> ```cpp
> #include <iostream>
> #include <new>
> #include <vector>
> 
> std::vector<char*> allocatedMemory;
> 
> void myNewHandler() {
>     std::cerr << "Memory allocation failed. Freeing allocated memory.\n";
> 
>     // 释放一些已分配的内存
>     if (!allocatedMemory.empty()) {
>         delete[] allocatedMemory.back();
>         allocatedMemory.pop_back();
>         return; // 尝试再次分配内存
>     }
> 
>     std::abort(); // 如果没有可释放的内存，则终止程序
> }
> 
> int main() {
>     std::set_new_handler(myNewHandler);
> 
>     try {
>         while (true) {
>             char* ptr = new char[1024 * 1024 * 10]; // 分配10MB内存块
>             allocatedMemory.push_back(ptr); // 记录分配的内存
>         }
>     } catch (const std::bad_alloc& e) {
>         std::cerr << "Caught std::bad_alloc: " << e.what() << '\n';
>     }
> 
>     // 释放所有已分配的内存
>     for (char* ptr : allocatedMemory) {
>         delete[] ptr;
>     }
> 
>     return 0;
> }
> ```
>
> 在这个例子中，当 `new` 运算符无法分配内存时，`myNewHandler` 释放一些已分配的内存，然后返回以重试内存分配。如果没有更多的内存可以释放，它将调用 `std::abort` 终止程序。
>
> ### 注意事项
>
> 1. **`set_new_handler` 是全局性的**：当你设置一个新的处理函数时，它会覆盖任何先前设置的处理函数，并且对整个程序有效。
> 2. **线程安全**：C++11 及以后的标准中，`set_new_handler` 是线程安全的。不同线程可以有各自的处理函数。
> 3. **处理函数不应抛出异常**：在处理函数中抛出异常是不明智的，因为这可能会导致未定义行为。处理函数应该确保完成它的任务并返回，或者终止程序。
>
> 通过使用 `set_new_handler`，你可以更灵活地处理内存分配失败的情况，确保程序在资源紧张时能够有更好的应对措施。



> A common programming practice is to allocate dynamic memory, assign the address of that memory to a pointer, use the pointer to manipulate the memory and deallocate the memory with delete when the memory is no longer needed.
> If an exception occurs after successful memory allocation but before the delete statement executes, a memory leak could occur.
> C++ 11 provides class template unique_ptr in header file <memory> to deal with this situation.
> 一种常见的编程做法是分配动态内存，将该内存的地址分配给指针，使用指针操作内存，并在不再需要内存时使用delete释放内存。
> 如果在成功分配内存之后但在执行delete语句之前发生异常，则可能发生内存泄漏。
> c++ 11在头文件<memory>中提供了类模板unique_ptr来处理这种情况。



> An object of class unique_ptr maintains a pointer to dynamically allocated memory.
> When an unique_ptr object destructor is called (for example, when an unique_ptr object goes out of scope), it performs a delete operation on its pointer data member.
> Class template unique_ptr provides overloaded operators * and -> so that an unique_ptr object can be used just as a regular pointer variable is.
> Figure 17.9 demonstrates an unique_ptr object that points to a dynamically allocated object of class Integer (Figs. 17.7–17.8).
>
> unique_ptr类的对象维护一个指向动态分配内存的指针。
> 当调用unique_ptr对象析构函数时(例如，当unique_ptr对象超出作用域时)，它对其指针数据成员执行delete操作。
> 类模板unique_ptr提供了重载操作符*和->，这样unique_ptr对象就可以像普通指针变量一样使用。
> 图17.9演示了一个unique_ptr对象，它指向一个动态分配的Integer类对象(图17.7-17.8)。

![image-20240608185945944](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608185945944.png)

![image-20240608185954422](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608185954422.png)

![image-20240608190002234](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608190002234.png)

![image-20240608190010125](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608190010125.png)

![image-20240608190016231](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608190016231.png)

> Because ptrToInteger is a local automatic variable in main, ptrToInteger is destroyed when main terminates.
> The unique_ptr destructor forces a delete of the Integer object pointed to by ptrToInteger, which in turn calls the Integer class destructor.
> The memory that Integer occupies is released, regardless of how control leaves the block (e.g., by a return statement or by an exception).
> Most importantly, using this technique can prevent memory leaks.
>
> 因为ptrToInteger是main中的一个局部自动变量，所以当main终止时ptrToInteger将被销毁。
> unique_ptr析构函数强制删除ptrToInteger所指向的Integer对象，而ptrToInteger又调用Integer类析构函数。
> Integer占用的内存被释放，无论控制如何离开块(例如，通过返回语句或异常)。
> 最重要的是，使用这种技术可以防止内存泄漏。



> unique_ptr Notes
> The class is called unique_ptr because only one unique_ptr at a time can own a dynamically allocated object.
> By using its overloaded assignment operator or copy constructor, an unique_ptr can transfer ownership of the dynamic memory it manages.
> unique_ptr笔记
> 这个类被称为unique_ptr，因为一次只能有一个unique_ptr拥有一个动态分配的对象。
> 通过使用它的重载赋值操作符或复制构造函数，unique_ptr可以转移它所管理的动态内存的所有权。
>
> The last unique_ptr object that maintains the pointer to the dynamic memory will delete the memory.
> This makes unique_ptr an ideal mechanism for returning dynamically allocated memory to client code.
> When the unique_ptr goes out of scope in the client code, the unique_ptr’s destructor destroys the dynamically allocated object and deletes its memory.
> 最后一个维护动态内存指针的unique_ptr对象将删除该内存。
> 这使得unique_ptr成为将动态分配的内存返回给客户端代码的理想机制。
> 当unique_ptr在客户端代码中超出作用域时，unique_ptr的析构函数会销毁动态分配的对象并删除其内存。



> unique_ptr to a Built-In Array
> You can also use a unique_ptr to manage a dynamically allocated built-in array. 
> For example, consider the statement
> unique_ptr< string[] > ptr( new string[ 10 ] ); 
> which dynamically allocates an array of 10 strings managed by ptr. 
> The type string[] indicates that the managed memory is a built-in array containing strings. 
> unique_ptr转换为内置数组
> 您还可以使用unique_ptr来管理动态分配的内置数组。
> 例如，考虑这个语句
> unque_ptr < string[] > ptr(new string[10]);
> 它动态地分配一个由ptr管理的包含10个字符串的数组。
> string[]类型表示托管内存是包含字符串的内置数组。
>
> unique_ptr to a Built-In Array
> You can also use a unique_ptr to manage a dynamically allocated built-in array. 
> For example, consider the statement
> unique_ptr< string[] > ptr( new string[ 10 ] ); 
> which dynamically allocates an array of 10 strings managed by ptr. 
> The type string[] indicates that the managed memory is a built-in array containing strings. 
> unique_ptr转换为内置数组
> 您还可以使用unique_ptr来管理动态分配的内置数组。
> 例如，考虑这个语句
> unque_ptr < string[] > ptr(new string[10]);
> 它动态地分配一个由ptr管理的包含10个字符串的数组。
> string[]类型表示托管内存是包含字符串的内置数组。



> Experience has shown that exceptions fall nicely into a number of categories.
> The C++ Standard Library includes a hierarchy of exception classes, some of which are shown in Fig. 17.10.
> As we first discussed in Section 17.2, this hierarchy is headed by base-class exception (defined in header file <exception>), which contains virtual function what that derived classes can override to issue appropriate error messages.
> 经验表明，例外情况可以很好地分为几类。
> c++标准库包括异常类的层次结构，其中一些异常类如图17.10所示。
> 正如我们在第17.2节中首先讨论的那样，这个层次结构以基类异常(在头文件<exception>中定义)为首，它包含虚函数，派生类可以覆盖该虚函数以发出适当的错误消息。

![image-20240608191200111](C:\Users\22635\AppData\Roaming\Typora\typora-user-images\image-20240608191200111.png)

> Immediate derived classes of base-class exception include runtime_error and logic_error (both defined in header <stdexcept>), each of which has several derived classes.
> Also derived from exception are the exceptions thrown by C++ operators—for example, bad_alloc is thrown by new (Section 17.8), bad_cast is thrown by dynamic_cast (Chapter 12) and bad_typeid is thrown by typeid (Chapter 12).
> 基类异常的直接派生类包括runtime_error和logic_error(两者都定义在头文件<stdexcept>中)，它们每个都有几个派生类。
> c++操作符抛出的异常也派生自exception——例如，new抛出bad_alloc(第17.8节)，dynamic_cast抛出bad_cast(第12章)，typeid抛出bad_typeid(第12章)。



> 在 C++ 中，`std::bad_typeid` 是一个异常类，它在使用 `typeid` 运算符时出现问题时被抛出。特别地，当使用 `typeid` 运算符对一个空指针进行操作时，会抛出 `std::bad_typeid` 异常。
>
> ### `typeid` 运算符
>
> `typeid` 运算符用于获取对象的类型信息，它返回一个 `std::type_info` 对象，该对象包含了类型的信息。通常情况下，`typeid` 运算符可以用来获取变量或对象的类型信息：
>
> ```cpp
> #include <iostream>
> #include <typeinfo>
> 
> class Base {
>  virtual void dummy() {}
> };
> 
> class Derived : public Base {};
> 
> int main() {
>  Base* pbase = new Derived;
>  std::cout << "Type of pbase: " << typeid(*pbase).name() << std::endl;
>  delete pbase;
>  return 0;
> }
> ```
>
> ### `std::bad_typeid` 异常
>
> 当 `typeid` 运算符对一个空指针进行操作时，就会抛出 `std::bad_typeid` 异常。例如：
>
> ```cpp
> #include <iostream>
> #include <typeinfo>
> 
> class Base {
>  virtual void dummy() {}
> };
> 
> int main() {
>  Base* pbase = nullptr;
>  try {
>      std::cout << "Type of pbase: " << typeid(*pbase).name() << std::endl;
>  } catch (const std::bad_typeid& e) {
>      std::cerr << "Caught std::bad_typeid: " << e.what() << std::endl;
>  }
>  return 0;
> }
> ```
>
> 在这个例子中，`pbase` 是一个空指针，当对 `*pbase` 使用 `typeid` 运算符时，会抛出 `std::bad_typeid` 异常。
>
> ### 捕获 `std::bad_typeid` 异常
>
> 当你在程序中使用 `typeid` 运算符时，应当考虑到可能会出现的空指针问题，并捕获 `std::bad_typeid` 异常以避免程序崩溃：
>
> ```cpp
> #include <iostream>
> #include <typeinfo>
> 
> class Base {
>  virtual void dummy() {}
> };
> 
> class Derived : public Base {};
> 
> void printType(Base* pbase) {
>  try {
>      std::cout << "Type: " << typeid(*pbase).name() << std::endl;
>  } catch (const std::bad_typeid& e) {
>      std::cerr << "Caught std::bad_typeid: " << e.what() << std::endl;
>  }
> }
> 
> int main() {
>  Base* pbase = nullptr;
>  printType(pbase);
> 
>  pbase = new Derived;
>  printType(pbase);
> 
>  delete pbase;
>  return 0;
> }
> ```
>
> 在这个示例中，函数 `printType` 尝试打印对象的类型信息。如果指针为空，会捕获 `std::bad_typeid` 异常，并输出相应的错误信息。
>
> ### 总结
>
> - `std::bad_typeid` 是在使用 `typeid` 运算符对空指针操作时抛出的异常。
> - 使用 `typeid` 运算符时，特别是对指针解引用进行类型查询时，应当考虑并处理可能出现的空指针情况。
> - 捕获 `std::bad_typeid` 异常可以防止程序因空指针操作而崩溃，并提供适当的错误处理机制。
>
> 通过理解和正确处理 `std::bad_typeid` 异常，可以提高程序的健壮性，确保在类型查询操作中能够有效处理空指针情况。



> Class logic_error is the base class of several standard exception classes that indicate errors in program logic.
> For example, class invalid_argument indicates that a function received an invalid argument.
> Proper coding can, of course, prevent invalid arguments from reaching a function. 
> Class length_error indicates that a length larger than the maximum size allowed for the object being manipulated was used for that object.
> Class out_of_range indicates that a value, such as a subscript into an array, exceeded its allowed range of values.
>
> 类logic_error是几个标准异常类的基类，用于指示程序逻辑中的错误。
> 例如，invalid_argument类表示函数收到了无效参数。
> 当然，正确的编码可以防止无效参数到达函数。
> 类length_error表示该对象使用的长度大于被操作对象所允许的最大长度。
> 类out_of_range表示一个值(例如数组的下标)超出了其允许的值范围。



> Class runtime_error, which we used briefly in Section 17.4, is the base class of several other standard exception classes that indicate execution-time errors.
> For example, class overflow_error describes an arithmetic overflow error (i.e., the result of an arithmetic operation is larger than the largest number that can be stored in the computer) and class underflow_error describes an arithmetic underflow error (i.e., the result of an arithmetic operation is smaller than the smallest number that can be stored in the computer).
>
> 类runtime_error(我们在第17.4节中简要使用过)是其他几个指示执行时错误的标准异常类的基类。
> 例如，类overflow_error描述了一个算术溢出错误(即，算术运算的结果大于计算机可存储的最大数字)，类underflow_error描述了一个算术下溢错误(即，算术运算的结果小于计算机可存储的最小数字)。



**异常类可以不继承自exception类，所以当捕获类型为exception时，不能保证能够程序捕获到所有可能的异常。**

**为了捕获一个try语句中的所有异常，可以使用catch(...)语句，但是无法确定类型，也无法获得参数名，因此无法引用。**

**catch(...)语句可以用来不依赖于异常类型的恢复操作（eg：释放公有资源），异常可以被重新抛出，让其他特定的catch处理器捕获处理。**

