# Java选择题题库

## MULTIPLE CHOICE.  Choose the one alternative that best completes the statement or answers the question.

1. 假设如下创建了一个`Scanner`对象：

```java
Scanner input = new Scanner(System.in);
```

要用什么方法读取一个实数呢？
A) `input.double();`  B) `input.Double();`
C) `input.nextDouble();`  D) `input.nextdouble();`

> **答案：C) `input.nextDouble();`**
> 解释：`Scanner`类提供`nextDouble()`方法用于从控制台读取一个实数。其余选项的方法不存在，因此是错误的。

章节：2.3 从控制台读取输入

2. 以下哪些是声明变量的正确方式？
A) `int length, width;`  B) `int length; int width;`
C) `int length, int width;`  D) `int length; width;`

章节：2.5 变量

> **答案：A, B**
> 解释：
>
> - **A)** 正确，使用逗号分隔变量，声明为同一类型。
> - **B)** 正确，分开声明多个变量。
> - **C)** 错误，不能同时在声明时重复数据类型。
> - **D)** 错误，`width`变量未指定类型。

3. 要在一个方法内声明一个值为99.98的常量`MAX_LENGTH`，应写成________。
A) `final float MAX_LENGTH = 99.98;`  B) `double MAX_LENGTH = 99.98;`
C) `final double MAX_LENGTH = 99.98;`  D) `final MAX_LENGTH = 99.98;`

章节：2.7 命名常量

> **答案：C) `final double MAX_LENGTH = 99.98;`**
> 解释：命名常量需要用`final`关键字修饰，指定数据类型并赋值，`MAX_LENGTH`是合法的命名常量。
>
> 如果是`final float MAX_LENGTH = 99.98f`，才是合法的。

4. 表达式`4 + 20 / (3 - 1) ∗ 2`的计算结果是________。
A) 25  B) 20  C) 4  D) 9  E) 24

> **答案：E) 24**
> 解释：运算符优先级如下：
>
> 1. 括号内先计算`3 - 1 = 2`。
> 2. 再计算除法和乘法，`20 / 2 = 10`，`10 ∗ 2 = 20`。
> 3. 最后进行加法：`4 + 20 = 24`。

章节：2.11 表达式求值与运算符优先级



5. 要获取协调世界时（UTC）中的当前小时数，需使用________。
A) `System.currentTimeMillis() / 1000 / 60 / 60 % 24`
B) `System.currentTimeMillis() / 1000 % 60`
C) `System.currentTimeMillis() % 3600`
D) `System.currentTimeMillis() / 1000 / 60 % 60`
E) `System.currentTimeMillis() % 60`

> **答案：A) `System.currentTimeMillis() / 1000 / 60 / 60 % 24`**
> 解释：
>
> - `System.currentTimeMillis()`返回当前时间的毫秒数，自1970年1月1日起计算。
> - 转换为秒需除以`1000`，转换为分钟再除以`60`，转换为小时再除以`60`。
> - 使用`% 24`获得当前小时数（UTC时间是24小时制）。

章节：2.12 案例研究：显示当前时间

6. 在执行以下语句后，`x`的值是多少？

```java
int x = 1;
x *= x + 1;
```

A) `x`是1。  B) `x`是2。  C) `x`是3。  D) `x`是4。

章节：2.13 扩展赋值运算符

> **答案：B) `x`是2。**
> 解释：
>
> - `x *= x + 1`等价于`x = x * (x + 1)`。
> - 初始值`x = 1`，计算结果为`1 * (1 + 1) = 2`。

7. 以下哪个表达式的结果是45.37？
A) `(int)(45.378 ∗ 100 / 100)`  B) `(int)(45.378) ∗ 100 / 100.0`
C) `(int)(45.378 ∗ 100) / 100`  D) `(int)(45.378 ∗ 100) / 100.0`

章节：2.15 数值类型转换

> **答案：D) `(int)(45.378 ∗ 100) / 100.0`**
> 解释：
>
> - `(45.378 ∗ 100)`计算结果为`4537.8`。
> - `(int)`强制类型转换为整数`4537`，再除以`100.0`得到`45.37`。
>
> 其他选项：
>
> - **A)** 舍弃小数部分，结果为`45`。
> - **B)** 结果为整数`45`。
> - **C)** 整数除法会丢失精度。

8. 分析以下代码：

```java
public class Test {
    public static void main(String[] args) {
        int n = 10000 * 10000 * 10000;
        System.out.println("n is " + n);
    }
}
```

A) `10000 * 10000 * 10000`的结果太大，无法存储在`int`变量`n`中。这会导致下溢，程序终止。
B) `10000 * 10000 * 10000`的结果太大，无法存储在`int`变量`n`中。这会导致上溢，程序终止。
C) `10000 * 10000 * 10000`的结果太大，无法存储在`int`变量`n`中。这会导致上溢，但由于Java不会报告上溢错误，程序会继续执行。
D) 程序显示`n is 1000000000000`。
E) `10000 * 10000 * 10000`的结果太大，无法存储在`int`变量`n`中。这会导致下溢，但由于Java不会报告下溢错误，程序会继续执行。

章节：2.18 常见错误与陷阱

> **答案：C)**
> 解释：`10000 * 10000 * 10000`超出了`int`数据类型的范围（2^31 - 1）。
>
> - 这会导致上溢，结果为截断后的无符号值（无法得到预期结果）。
> - Java不会报告错误，程序继续运行并打印溢出值。****

9. 在Java中，单词`true`是________。
A) 等同于值1  B) 等同于值0  C) 一个Java关键字  D) 一个布尔字面量

章节：3.2 布尔数据类型

> **答案：D) 一个布尔字面量**
> 解释：`true`和`false`是Java中的布尔字面量，代表布尔值，而不是整数值或关键字。

10. 假设`income`为4001，以下代码的输出是什么？

```java
if (income > 3000) {
    System.out.println("Income is greater than 3000");
}
else if (income > 4000) {
    System.out.println("Income is greater than 4000");
}
```

A) 无输出
B) “Income is greater than 4000” 接着 “Income is greater than 3000”
C) “Income is greater than 3000” 接着 “Income is greater than 4000”
D) “Income is greater than 4000”
E) “Income is greater than 3000”

章节：3.4 双向`if-else`语句

> **答案：E) “Income is greater than 3000”**
> 解释：`if-else`语句中，条件是逐一检查的，当`income > 3000`为`true`时，第一个分支的语句执行，后续条件不会再检查，即输出`“Income is greater than 3000”`。

11. 分析以下代码：

```java
boolean even = false;
if (even = true) {
    System.out.println("It is even");
}
```

A) 程序运行正常，但无显示内容。
B) 程序有编译错误。
C) 程序有运行时错误。
D) 程序运行正常并显示“It is even”。

章节：3.6 常见错误与陷阱

> **答案：D**
> 解释：
> 代码中`even = true`是赋值操作，而不是比较操作。赋值操作的结果是`true`，因此`if`语句的条件成立，打印`"It is even"`。

12. 以下哪个可能是调用`Math.random()`的输出结果？
A) 0.0  B) 0.5  C) 3.43  D) 1.0

章节：3.7 生成随机数

> **答案：A, B**
> 解释：
> `Math.random()`返回一个`[0.0, 1.0)`范围内的伪随机浮点数，因此可能输出`0.0`和`0.5`，但绝不会等于`1.0`，也不会输出超过范围的值如`3.43`。

13. 已知`|x - 2| <= 4`，以下哪个是正确的？
A) `x - 2 <= 4 || x - 2 >= -4`
B) `x - 2 <= 4 && x - 2 > -4`
C) `x - 2 <= 4 && x - 2 >= -4`
D) `x - 2 <= 4 && x - 2 >= 4`

章节：3.11 判断闰年

> **答案：C**
> 解释：
> `|x - 2| <= 4` 等价于 `-4 <= x - 2 <= 4`，即 `x - 2 >= -4` 且 `x - 2 <= 4`。

14. 假设`x = 10`且`y = 10`。在计算表达式`(y >= 10) || (x-- > 10)`后，`x`的值是多少？
A) 9  B) 10  C) 11

章节：3.12 彩票

> **答案：B**
> 解释：
> 逻辑或`||`的短路行为导致只要`(y >= 10)`为`true`，`(x-- > 10)`不会被执行，因此`x`保持为`10`。

15. 在执行以下`switch`语句后，`y`的值是多少？

```java
int x = 3; int y = 4;
switch (x + 3) {
    case 6: y = 0;
    case 7: y = 1;
    default: y += 1;
}
```

A) 1  B) 2  C) 3  D) 4  E) 0

章节：3.13 `switch`语句

>  **答案：B**
> 解释：
> `switch`语句没有`break`，所以执行了`case 6`和`case 7`以及`default`。最终`y = 0 → y = 1 → y += 1`，结果是`2`。

16. 在执行以下语句后，`y`的值是多少？

```java
x = 0;
y = (x > 0)? 10 : -10;
```

A) -10
B) 20
C) 0
D) 10
E) 非法表达式

章节：3.14 条件表达式

> **答案：A**
> 解释：
> `x > 0`为`false`，因此条件表达式返回冒号后值`-10`。

17. 在以下代码中，`y`显示的值是什么？

```java
public class Test1 {
    public static void main(String[] args) {
        int x = 1;
        int y = x = x + 1;
        System.out.println("y is " + y);
    }
}
```

A) `y`是1，因为先将`x`赋值给`y`。
B) 程序有编译错误，因为在语句`int y = x = x + 1`中`x`被重新声明了。
C) `y`是0。
D) `y`是2，因为先将`x + 1`赋值给`x`，然后再将`x`赋值给`y`。

章节：3.15 运算符优先级和结合性

> **答案：D**
> 解释：
> `x = x + 1`的结果`2`先赋值给`x`，再赋值给`y`。因此`y`为`2`。

18. 要获取0.5的反正弦值，需使用________。
A) `Math.asin(0.5)`
B) `Math.sin(Math.toRadians(0.5))`
C) `Math.asin(Math.toDegrees(0.5))`
D) `Math.sin(0.5)`

章节：4.2 常用数学函数

> **答案：A**
> 解释：
> `Math.asin(double)`用于计算反正弦值，输入值必须在`[-1, 1]`范围内。

19. 以下哪个语句会输出`smith\exam1\test.txt`？
A) `System.out.println("smith\exam1\test.txt");`
B) `System.out.println("smith\"exam1\"test.txt");`
C) `System.out.println("smith"\exam1"\test.txt");`
D) `System.out.println("smith\\exam1\\test.txt");`

章节：4.3 字符数据类型与操作

> **答案：D**
> 解释：
> 反斜杠`\`是转义字符，需使用双反斜杠`\\`表示一个反斜杠。

20. `System.out.println((char)4)`会显示4吗？
A) 是  B) 否

章节：4.3 字符数据类型与操作

> **答案：B**
> 解释：
> `(char)4`对应的是ASCII码值为`4`的不可见控制字符，因此不会显示数字`4`。

21. 一个`int`变量可以存储________。
A) `'x'`  B) 120  C) `"x"`  D) `"120"`  E) 120.0

章节：4.3 字符数据类型与操作

> **答案：A, B**
> 解释：
> `'x'`为字符，其底层存储为整数值，`120`是整数，均可存储为`int`类型。字符串`"x"`和浮点数`120.0`无法存储为`int`。

22. `'3' - '2' + 'm' / 'n'`的结果是________。
A) 2  B) 0  C) 3  D) 1

章节：4.3 字符数据类型与操作

> **答案：D**
> 解释：
> 字符运算遵循其ASCII码值。假设`'3' = 51`，`'2' = 50`，`'m' = 109`，`'n' = 110`，计算为`(51 - 50) + (109 / 110)`，结果是`1`。

23. 以下哪个不是`Character`类中的正确方法？
A) `toLowerCase(char)`
B) `toUpperCase()`
C) `isDigit()`
D) `isLetter(char)`
E) `isLetterOrDigit(char)`

章节：4.3 字符数据类型与操作

> **答案：B, C**
> 解释：
> `toUpperCase()`不是无参数方法，需调用字符串对象，如`"abc".toUpperCase()`。同时`isDigit()`缺少参数。

24. 表达式`"Java " + 1 + 2 + 3`的计算结果是________。
A) `Java6`
B) `java 123`
C) `Java 123`
D) `Java123`
E) 非法表达式

章节：4.4 字符串类型

> **答案：C**
> 解释：
> 字符串拼接从左到右进行。`"Java " + 1`是字符串，因此后续的`+ 2 + 3`被视为字符串拼接，结果是`"Java 123"`。

25. 以下哪个是返回`JAVA`的正确语句？
A) `"Java".toUpperCase("Java")`
B) `String.toUpperCase("Java")`
C) `"Java".toUpperCase()`
D) `toUpperCase("Java")`

章节：4.4 字符串类型

> **答案：C**
> 解释：
> `"Java".toUpperCase()`将字符串`"Java"`转为大写，结果为`"JAVA"`。

26. 假设`s1`和`s2`是两个字符串。以下代码的结果是什么？

```java
s1.equals(s2) == s2.equals(s1)
```

A) 真  B) 假

章节：4.4 字符串类型

> **答案：A**
> 解释：
> `equals`方法满足对称性，无论`String`对象的顺序如何，`s1.equals(s2)`总等于`s2.equals(s1)`。

27. `"AbA".compareToIgnoreCase("abC")`返回________。
A) 1  B) -1  C) 2  D) -2  E) 0

章节：4.4 字符串类型

> **答案：D**
> 解释：
> `compareToIgnoreCase`忽略大小写比较字符串的字典顺序。`"AbA"`比`"abC"`小，结果为`-2`。

28. `"SELECT".substring(0, 5)`的返回值是什么？
A) `"SELE"`  B) `"SELEC"`  C) `"SELECT"`  D) `"ELECT"`

章节：4.4 字符串类型

> **答案：D**
> 解释：
> `compareToIgnoreCase`忽略大小写比较字符串的字典顺序。`"AbA"`比`"abC"`小，结果为`-2`。

29. ________方法将字符串`s`解析为一个`int`值。
A) `integer.parseInteger(s);`
B) `Integer.parseInt(s);`
C) `Integer.parseInteger(s);`
D) `integer.parseInt(s);`

章节：4.4 字符串类型

> **答案：B**
> 解释：
> `Integer.parseInt(String)`将字符串解析为`int`值，`Integer.parseInteger`不是有效方法。

30. 语句`System.out.printf("%5d", 123456)`的输出是________。
A) 12345  B) 12345.6  C) 123456  D) 23456

章节：4.6 格式化控制台输出 

> **答案：C**
> 解释：
> `%5d`表示占5个字符宽度，输出`123456`时宽度不够，因此显示原值`123456`。

31) 以下代码会打印多少次“Welcome to Java”？

```java
int count = 0;
while (count < 10) {
    System.out.println("Welcome to Java");
    count++;
}
```

A) 9  B) 0  C) 10  D) 8  E) 11

章节：5.2 `while`循环

> **答案：C) 10**
> 解释：`count` 从 0 开始，在每次循环中打印一句，直到 `count == 10` 时退出，打印共 10 次。

32. 以下代码会打印多少次“Welcome to Java”？

```java
int count = 0;
while (count++ < 10) {
    System.out.println("Welcome to Java");
}
```

A) 9  B) 8  C) 10  D) 0  E) 11

章节：5.2 `while`循环

> **答案：C) 10**
> 解释：`count++` 是后置自增运算，条件判断时使用的是自增前的值，因此循环执行 10 次。

33. 执行以下代码时会显示什么内容？

```java
int number = 6;
while (number > 0) {
    number -= 3;
    System.out.print(number + " ");
}
```

A) 3 0 -3  B) 0 -3  C) 3 0  D) 6 3  E) 6 3 0

章节：5.2 `while`循环

> **答案：A) 3 0**
> 解释：每次循环中，`number` 减少 3，循环条件检查减完后的值，依次输出 3、0 。

34. 以下代码会打印多少次“Welcome to Java”？

```java
int count = 0;
do {
    System.out.println("Welcome to Java");
} while (count++ < 10);
```

A) 8  B) 9  C) 10  D) 11  E) 0

章节：5.6 `do-while`循环

> **答案：D) 11**
> 解释：`do-while` 循环至少执行一次，因此会额外多打印一次。

35. 在执行以下循环后，`count`的值是多少？

```java
int count = 0;
do {
    System.out.println("Welcome to Java");
} while (count++ < 9);
System.out.println(count);
```

A) 8  B) 9  C) 10  D) 11  E) 0

章节：5.6 `do-while`循环

> **答案：C) 10**
> 解释：循环结束时，`count` 恰好等于 10。

36. 以下哪个循环会打印10次“Welcome to Java”？

A:
```java
for (int count = 1; count <= 10; count++) {
    System.out.println("Welcome to Java");
}
```

B:
```java
for (int count = 0; count < 10; count++) {
    System.out.println("Welcome to Java");
}
```

C:
```java
for (int count = 1; count < 10; count++) {
    System.out.println("Welcome to Java");
}
```

D:
```java
for (int count = 0; count <= 10; count++) {
    System.out.println("Welcome to Java");
}
```

A) AB  B) ABC  C) BD  D) AC  E) BC

章节：5.7 `for`循环

> **答案：A) AB**
> 解释：`for` 循环中，`count = 0; count < 10` 和 `count = 1; count <= 10` 都会打印 10 次。

37. 以下循环会显示________。

```java
for (int i = 1; i <= 10; i++) {
    System.out.print(i + " ");
    i++;
}
```

A) 1 2 3 4 5 6 7 8 9
B) 2 4 6 8 10
C) 1 2 3 4 5 6 7 8 9 10
D) 1 3 5 7 9
E) 1 2 3 4 5

章节：5.7 `for`循环

> **答案：D) 1 3 5 7 9**
> 解释：每次循环中，`i` 自增 1 后，在循环体内又加 1，因此打印奇数。

38. 在执行以下`for`循环后，`i`的值是多少？

```java
int y = 0;
for (int i = 0; i < 10; ++i) {
    y += i;
}
```

A) 11  B) 9  C) 10  D) 未定义

章节：5.7 `for`循环

> **答案：D) 未定义**
> 解释：`i` 是 `for` 循环的局部变量，循环结束后不可访问。

39. 分析以下代码片段：

```java
double sum = 0;
double d = 0;
while (d!= 10.0) {
    d += 0.1;
    sum += sum + d;
}
```

A) 程序永远不会停止，因为在循环内`d`始终为0.1。
B) 循环结束后，`sum`的值是`0 + 0.1 + 0.2 + 0.3 +... + 1.9`。
C) 由于使用浮点数进行运算时存在数值不精确的现象，程序可能不会停止。
D) 程序无法编译，因为`sum`和`d`被声明为`double`类型，但却用整数值0进行赋值。

章节：5.8 选用哪种循环？

> **答案：C) 程序可能不会停止**
> 解释：浮点数运算可能导致 `d` 无法精确达到 10.0。

40. `println`语句会被执行多少次？

```java
for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
        System.out.println(i * j);
```

A) 100  B) 10  C) 45  D) 20

章节：5.9 嵌套循环

> **答案：A) 100**
> 解释：外层循环 10 次，内层循环 10 次，共执行 10 × 10 = 100 次。

41. 分析以下代码。

```java
double sum = 0;
for (double d = 0; d < 10; sum += sum + d) {
    d += 0.1;
}
```

A) 程序能编译但不会停止，因为`d`总是小于10。
B) 程序有语法错误，因为`for`循环中的调整语句不正确。
C) 程序有语法错误，因为`for`循环中的控制变量不能是`double`类型。
D) 程序能编译且运行正常。

章节：5.10 尽量减少数值误差

> **案：A) 程序能编译且正常运行**
> 解释：`d` 每次只增加 0.1，但由于浮点数精度问题，可能无法准确达到 10。

42. 以下程序会终止吗？

```java
int balance = 10;

while (true) {
    if (balance < 9)
        break;
    balance = balance - 9;
}
```

A) 是  B) 否

章节：5.12 关键字`break`和`continue`

> **答案：A) 是**
> 解释：`balance` 减到小于 9 时，`break` 终止循环。

43. 在以下循环终止后，输出内容是什么？

```java
int number = 25;
int i;

boolean isPrime = true;
for (i = 2; i < number && isPrime; i++) {
    if (number % i == 0) {
        isPrime = false;
    }
}

System.out.println("i is " + i + " isPrime is " + isPrime);
```

A) `i is 5 isPrime is false`  B) `i is 6 isPrime is true`
C) `i is 5 isPrime is true`  D) `i is 6 isPrime is false`

章节：5.12 关键字`break`和`continue`

> **答案：D) i is 6 isPrime is false**
> 解释：当 `i = 6` 时，`25 % 5 == 0`，`isPrime` 设置为 `false`，循环退出。

44. 以下程序会终止吗？

```java
int balance = 10;

while (true) {
    if (balance < 9)
        continue;
    balance = balance - 9;
}
```

A) 是  B) 否

章节：5.12 关键字`break`和`continue`

> **答案：B) 否**
> 解释：循环中没有退出条件，因此不会终止。

45. 在执行以下代码后，`balance`的值是多少？

```java
int balance = 10;

while (balance >= 1) {
    if (balance < 9)
        break;
    balance = balance - 9;
}
```

A) 0  B) 2  C) 1  D) -1

章节：5.12 关键字`break`和`continue`

> **答案：C) 1**
> 解释：当 `balance = 10` 减到 1 时，满足 `balance < 9`，退出循环。

46. 以下循环的迭代次数是多少？

```java
for (int i = 1; i <= n; i++) {
    // 迭代
}
```

A) `n - 1`  B) `n`  C) `2*n`  D) `n + 1`

章节：5.13 案例研究：检查回文

> **答案：B) n**
> 解释：循环从 1 到 n，总共执行 n 次。

47. 假设你的方法不返回任何值，以下哪个关键字可以用作返回类型？
A) `double`  B) `int`  C) `void`  D) `public`  E) 以上都不是

章节：6.2 定义方法

> **答案：C) void**
> 解释：`void` 表示方法无返回值。

48. 所有Java应用程序都必须有一个________方法。
A) `public static Main(String[] args)`
B) `public static main(String[] args)`
C) `public static void main(String[] args)`
D) `public void main(String[] args)`
E) `public static Main(String args[])`

章节：6.2 定义方法

> **答案：C) `public static void main(String[] args)`**
> 解释：`main` 方法是程序的入口，其签名固定。

49. 以下方法中的`return`语句会导致编译错误吗？

```java
public static void main(String[] args) {
    int max = 0;
    if (max!= 0)
        System.out.println(max);
    else
        return;
}
```

A) 是  B) 否

章节：6.3 调用方法

> **答案：B) 否**
> 解释：`void` 方法中可以使用 `return` 结束方法。

50. 每次调用方法时，系统会将参数和局部变量存储在内存的一个区域中，这个区域被称为________，它以后进先出的方式存储元素。
A) 存储区域  B) 数组  C) 堆  D) 栈

章节：6.3 调用方法

> **答案：D) 栈**
> 解释：方法的参数和局部变量存储在栈中。

51. 你应该在以下代码的空白处填入________。

```java
public class Test {
    public static void main(String[] args) {
        System.out.print("The grade is ");
        printGrade(78.5);

        System.out.print("The grade is ");
        printGrade(59.5);

    }

    public static ________ printGrade(double score) {
        if (score >= 90.0) {
            System.out.println('A');
        }
        else if (score >= 80.0) {
            System.out.println('B');
        }
        else if (score >= 70.0) {
            System.out.println('C');
        }
        else if (score >= 60.0) {
            System.out.println('D');
        }
        else {
            System.out.println('F');
        }
    }
}
```

A) `void`  B) `boolean`  C) `char`  D) `double`  E) `int`

章节：6.4 `void`与有返回值的方法

> **答案：A) void**
> 解释：方法没有返回值，使用 `void`。

52. 考虑以下不完整的代码：

```java
public class Test {
    public static void main(String[] args) {
        System.out.println(f(5));
    }

    public static int f(int number) {
        // 缺失方法体
    }
}
```

缺失的方法体应该是________。
A) `System.out.println(number);`
B) `System.out.println("number");`
C) `return number;`
D) `return "number";`

章节：6.4 `void`与有返回值的方法

> **答案：C) return number;**
> 解释：方法声明返回 `int` 类型，因此需要返回一个整数。

53. 给定以下方法

```java
static void nPrint(String message, int n) {
    while (n > 0) {
        System.out.print(message);
        n--;
    }
}
```

调用`nPrint('a', 4)`的输出是什么？
A) `aaaaa`  B) 无效调用  C) `aaaa`  D) `aaa`

章节：6.5 按值传递参数

> **答案：B) 无效调用**
> 解释：字符必须用双引号，`nPrint("a", 4)` 是合法调用。

54. 在方法内部定义的变量被称为________。
A) 块变量  B) 方法变量  C) 全局变量  D) 局部变量

> **答案：D) 局部变量**
> 解释：在方法内部定义的变量称为局部变量。

章节：6.9 变量的作用域

55. `(int)(Math.random() * (65535 + 1))`返回一个随机数________。
A) 在1到65536之间  B) 在1到65535之间
C) 在0到65536之间  D) 在0到65535之间

章节：6.10 案例研究：生成随机字符

> **答案：D) 在0到65535之间**
> 解释：`Math.random()` 生成 [0, 1) 的随机数，乘以 65536 后取整得到 [0, 65535]。

56. `(char)('a' + Math.random() * ('z' - 'a' + 1))`返回一个随机字符________。
A) 在`'a'`到`'y'`之间  B) 在`'b'`到`'z'`之间
C) 在`'a'`到`'z'`之间  D) 在`'b'`到`'y'`之间

章节：6.10 案例研究：生成随机字符

> **答案：C) 在'a'到'z'之间**
> 解释：随机字符的范围是从 `'a'` 到 `'z'`。

57. 客户端可以使用一个方法而无需知道它是如何实现的。实现的细节被封装在方法中，对调用该方法的客户端是隐藏的。这被称为________。
A) 简化方法  B) 信息隐藏
C) 封装  D) 方法隐藏

章节：6.11 方法抽象与逐步求精

> **答案：C) 封装**
> 解释：封装隐藏了实现细节，只对外暴露方法接口。

58. ________是一个方法的简单但不完整的版本。
A) 使用自顶向下方法开发的方法
B) 非`main`方法
C) `main`方法
D) 桩（Stub）

章节：6.11 方法抽象与逐步求精

> **答案：D) 桩（Stub）**
> 解释：桩是方法的简化版本，用于初步开发和测试。

59. 以下哪些是不正确的？
A) `int[] a = new int[2];`
B) `int a() = new int[2];`
C) `int[] a = new int(2);`
D) `int a[] = new int[2];`
E) `int a = new int[2];`

章节：7.2 数组基础

> **答案：B) int a() = new int[2];
> C) int[] a = new int(2);
> E) int a = new int[2];**
> 解释：这三种形式都是非法的。

60. 假设`int i = 5`，以下哪个可以用作数组`double[] t = new double[100]`的索引？
A) `i`
B) `i + 10`
C) `i + 6.5`
D) `(int)(Math.random() * 100))`
E) `Math.random() * 100`

章节：7.2 数组基础 

> 答案：**A, B, D**
> 解析：数组索引必须是整数。
>
> - `i` 是整数，符合条件；
> - `i + 10` 结果仍为整数；
> - `i + 6.5` 是小数，无法作为索引；
> - `(int)(Math.random() * 100)` 被强制转换为整数；
> - `Math.random() * 100` 是小数，不符合条件。

61) 假设`int[] t = {1, 2, 3, 4}`，那么`t.length`的值是多少？
A) 0  B) 3  C) 4  D) 5

章节：7.2 数组基础

> 答案：**C**
> 解析：`t.length` 表示数组的长度，`{1, 2, 3, 4}` 有 4 个元素，因此返回值为 4。

62. 分析以下代码：

```java
public class Test {
    public static void main(String[] args) {
        double[] x = {2.5, 3, 4};
        for (double value : x)
            System.out.print(value + " ");
    }
}
```

A) 程序显示`2.5, 3, 4`
B) 程序显示`2.5, 3.0 4.0`
C) 程序显示`2.5 3 4`
D) 程序显示`2.5 3.0 4.0`
E) 程序有语法错误，因为`value`未定义。

章节：7.2 数组基础

> 答案：**D**
> 解析：`for-each` 循环中，`x` 的每个元素会被赋值给 `value`。所有元素会自动转换为浮点数，因此输出为：`2.5 3.0 4.0`。

63. 以下哪些是正确的？
A) `String[] list = {"red", "yellow", "green"};`
B) `String[] list = new String{"red", "yellow", "green"};`
C) `String list = new String{"red", "yellow", "green"};`
D) `String[] list = new String[]{"red", "yellow", "green"};`
E) `String list = {"red", "yellow", "green"};`

章节：7.2 数组基础

> 答案：**A, D**
> 解析：
>
> - `A` 正确，声明和初始化简洁；
> - `D` 正确，显示地使用 `new`；
> - 其他选项语法错误或类型不匹配。

64. 分析以下代码：

```java
public class Test {
    public static void main(String[] args) {
        int[] x = {1, 2, 3, 4};
        int[] y = x;

        x = new int[2];

        for (int i = 0; i < y.length; i++)
            System.out.print(y[i] + " ");

    }
}
```

A) 程序显示`1 2 3 4`
B) 程序显示`0 0 0 0`
C) 程序显示`0 0`
D) 程序显示`0 0 3 4`

章节：7.5 复制数组

> 答案：**A**
> 解析：
>
> - `y` 指向原来的数组；
> - 给 `x` 赋新数组并不影响 `y`，因此 `y` 仍是 `{1, 2, 3, 4}`。

65. 展示以下代码的输出：

```java
public class Test {
    public static void main(String[] args) {
        int[] x = {1, 2, 3, 4, 5};
        increase(x);

        int[] y = {1, 2, 3, 4, 5};
        increase(y[0]);

        System.out.println(x[0] + " " + y[0]);

    }

    public static void increase(int[] x) {
        for (int i = 0; i < x.length; i++)
            x[i]++;
    }

    public static void increase(int y) {
        y++;
    }
}
```

A) `1 2`
B) `2 1`
C) `0 0`
D) `2 2`
E) `1 1`

章节：7.6 将数组传递给方法

> 答案：**B**
> 解析：
>
> - 对数组 `x` 调用 `increase(x)`，数组元素增加；
> - 对 `y[0]` 调用 `increase(y[0])`，只是传递值，数组元素不变；
> - 最后 `x[0]` 为 2，`y[0]` 为 1。

66. 分析以下代码：

```java
public class Test {
    public static void main(String[] args) {
        int[] oldList = {1, 2, 3, 4, 5};
        reverse(oldList);
        for (int i = 0; i < oldList.length; i++)
            System.out.print(oldList[i] + " ");
    }

    public static void reverse(int[] list) {
        int[] newList = new int[list.length];

        for (int i = 0; i < list.length; i++)
            newList[i] = list[list.length - 1 - i];

        list = newList;

    }
}
```

A) 程序显示`5 4 3 2 1`。
B) 程序显示`1 2 3 4 5`。
C) 程序显示`5 4 3 2 1`，然后抛出`ArrayIndexOutOfBoundsException`异常。
D) 程序显示`1 2 3 4 5`，然后抛出`ArrayIndexOutOfBoundsException`异常。

章节：7.6 将数组传递给方法

> 答案：**B**
> 解析：方法 `reverse` 中的操作确实改变了`list`，注意是如何改变的。

67. 在本章节中定义了`reverse`方法。在执行以下语句后，`list1`的值是什么？

```java
int[] list1 = {1, 2, 3, 4, 5, 6};
int[] list2 = reverse(list1);
```

A) `list1`是`6 6 6 6 6 6`
B) `list1`是`1 2 3 4 5 6`
C) `list1`是`6 5 4 3 2 1`
D) `list1`是`0 0 0 0 0 0`

章节：7.7 从方法中返回数组

> 答案：**B**
> 解析：`reverse` 方法返回的是新数组，`list1` 的值未改变。

68. 如果关键字不在列表中，`binarySearch`方法返回________。
A) `-(插入点 + 1)`
B) `插入点 - 1`
C) `插入点`
D) `-插入点`

章节：7.10 搜索数组

> 答案：**A**
> 解析：`binarySearch` 找不到元素时返回 `-(插入点 + 1)`。

69. ________方法对`double[]`类型的数组`scores`进行排序。
A) `java.util.Arrays.sorts(scores)`
B) `java.util.Arrays(scores)`
C) `Njava.util.Arrays.sortArray(scores)`
D) `java.util.Arrays.sort(scores)`

章节：7.12 `Arrays`类

> 答案：**D**
> 解析：`java.util.Arrays.sort(scores)` 是正确的方法，用于对数组排序。

70. 以下哪个代码片段能够正确识别通过命令行传递给Java应用程序的参数数量（不包括正在被调用的类名）？
A) `int count = 0; while (args[count]!= null) count ++;`
B) `int count=0; while (!(args[count].equals(""))) count ++;`
C) `int count = args.length;`
D) `int count = args.length - 1;`

章节：7.13 命令行参数

> 答案：**C**
> 解析：
> `args.length` 直接表示命令行参数的数量。

71. 以下哪个语句是正确的？
A) `char[][] charArray = {'a', 'b'};`
B) `char[][] charArray = {{'a', 'b'}, {'c', 'd'}};`
C) `char[2][2] charArray = {{'a', 'b'}, {'c', 'd'}};`
D) `char[2][] charArray = {{'a', 'b'}, {'c', 'd'}};`

章节：8.2 二维数组基础

> 答案：**B**。

72. 数组`a`中第一行第一列元素的索引变量是什么？
A) `a[1][1]`
B) `a[1][0]`
C) `a[0][0]`
D) `a[0][1]`

章节：8.2 二维数组基础

> 答案：**C**
> 解析：数组索引从 0 开始，第一行第一列的元素为 `a[0][0]`。

73. 数组`matrix`（`int[][] matrix = new int[5][5]`）中有多少个元素？
A) 14
B) 20
C) 30
D) 25

章节：8.2 二维数组基础

> 答案：**D**
> 解析：5 × 5 = 25，数组 `matrix` 中有 25 个元素。

74. 假设`int[][] x = {{1, 2}, {3, 4}, {5, 6}}`，那么`x.length`和`x[0].length`分别是多少？
A) 3和2
B) 3和3
C) 2和1
D) 2和2
E) 2和3

章节：8.2 二维数组基础

> 答案：**A**
> 解析：`x.length` 是行数为 3，`x[0].length` 是每行的列数为 2。

75. 以下程序的输出是什么？

```java
public class Test {
    public static void main(String[] args) {
        int[][] values = {{3, 4, 5, 1}, {33, 6, 1, 2}};

        int v = values[0][0];
        for (int row = 0; row < values.length; row++)
            for (int column = 0; column < values[row].length; column++)
                if (v < values[row][column])
                    v = values[row][column];

        System.out.print(v);

    }
}
```

A) 33
B) 6
C) 1
D) 3
E) 5

章节：8.3 处理二维数组

> 答案：**A**
> 解析：程序找出二维数组中的最大值，最大值为 33。

76. 以下程序的输出是什么？

```java
public class Test {
    public static void main(String[] args) {
        int[][] values = {{3, 4, 5, 1 }, {33, 6, 1, 2}};

        for (int row = 0; row < values.length; row++) {
            java.util.Arrays.sort(values[row]);
            for (int column = 0; column < values[row].length; column++)
                System.out.print(values[row][column] + " ");
            System.out.println();
        }

    }
}
```

A) 程序打印一行`1 3 4 5 1 2 6 33`
B) 程序打印两行`3 4 5 1` 接着 `33 6 1 2`
C) 程序打印两行`3 4 5 1` 接着 `2 1 6 33`
D) 程序打印两行`1 3 4 5` 接着 `1 2 6 33`
E) 程序打印一行`3 4 5 1 33 6 1 2`

章节：8.3 处理二维数组

> 答案：**D**
> 解析：`java.util.Arrays.sort` 对每行分别排序：
>
> - 第一行排序后为 `1 3 4 5`；
> - 第二行排序后为 `1 2 6 33`。

77. 以下代码的输出是什么？

```java
public class Test5 {
    public static void main(String[] args) {
        int[][] matrix =
                {{1, 2, 3, 4},
                        {4, 5, 6, 7},
                        {8, 9, 10, 11},
                        {12, 13, 14, 15}};

        for (int i = 0; i < 4; i++)
            System.out.print(matrix[1][i] + " ");

    }
}
```

A) `2 5 9 13`
B) `1 3 8 12`
C) `4 5 6 7`
D) `1 2 3 4`
E) `3 6 10 14`

章节：8.3 处理二维数组

> 答案：**C**
> 解析：`matrix[1][i]` 遍历第二行的所有元素，输出为 `4 5 6 7`。

78. 以下程序的输出是什么？

```java
public class Test {
    public static void main(String[] args) {
        int[][] values = {{3, 4, 5, 1}, {33, 6, 1, 2}};

        for (int row = 0; row < values.length; row++) {
            System.out.print(m(values[row]) + " ");
        }

    }

    public static int m(int[] list) {
        int v = list[0];
        for (int i = 1; i < list.length; i++)
            if (v < list[i])
                v = list[i];
        return v;
    }
}
```

A) `1 1`
B) `5 6`
C) `33 5`
D) `5 33`
E) `3 33`

章节：8.4 将二维数组传递给方法

> 答案：**D**
> 解析：方法 `m` 返回数组中最大值：
>
> - 第一行最大值是 5；
> - 第二行最大值是 33。
>   输出为 `5 33`。

79. 以下哪些语句是正确的？
A) `char[2][2][] charArray = {a', 'b'};`
B) `char[][][] charArray = new char[2][2][];`
C) `char[][][] charArray = {{{'a', 'b'}, {'c', 'd'}, {'e', 'f'}}};`
D) `char[][][] charArray = {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};`

章节：8.8 多维数组

> 答案：**B C**
> 解析：选项 B 正确，声明了一个三维数组。其他选项均语法错误。

80. 以下代码的输出是什么？

```java
public class Test {
    public static void main(String[] args) {
        int[][][] data = {{{1, 2}, {3, 4}},
                {{5, 6}, {7, 8}}};

        System.out.print(ttt(data[0]));

    }

    public static int ttt(int[][] m) {
        int v = m[0][0];

        for (int i = 0; i < m.length; i++)
            for (int j = 0; j < m[i].length; j++)
                if (v < m[i][j])
                    v = m[i][j];

        return v;

    }
}
```

A) 1
B) 2
C) 4
D) 5
E) 6

章节：8.8 多维数组

> 答案：**C**
> 解析：方法 `ttt` 返回二维数组中最大值，`data[0]` 中最大值为 4。

81. 一个对象是一个________的实例。
A) 类
B) 方法
C) 数据
D) 程序

章节：9.2 为对象定义类

> 答案：A

82. 以下哪些语句是正确的？
A) 如果在类中没有显式声明构造函数，会自动提供一个默认构造函数。
B) 必须总是显式定义至少一个构造函数。
C) 默认构造函数是无参构造函数。
D) 每个类都有一个默认构造函数。

章节：9.4 使用构造函数构造对象

> 如果没有显式声明构造函数，系统会提供默认构造函数。
>
> 默认构造函数是无参构造函数。
> **答案：A, C**

83. 给定声明`Circle x = new Circle()`，以下哪个陈述最准确？ 
A) 你可以将一个`int`值赋给`x`。
B) `x`包含一个`Circle`类型的对象。
C) `x`包含一个指向`Circle`对象的引用。
D) `x`包含一个`int`值。

章节：9.5 通过引用变量访问对象

> `x` 包含一个指向 `Circle` 对象的引用。
> **答案：C**

84. 以下哪些语句是正确的？
A) 一个引用变量就是一个对象。
B) 一个引用变量引用一个对象。
C) 类中的数据字段必须是基本类型。
D) 类中的数据字段可以是对象类型。

章节：9.5 通过引用变量访问对象

> 引用变量引用一个对象。
>
> 数据字段可以是对象类型。
> **答案：B, D**

85. 与单个对象相关联的方法被称为________。
A) 类方法
B) 静态方法
C) 实例方法
D) 对象方法

章节：9.7 静态变量、常量和方法

> 与单个对象相关的方法称为实例方法。
> **答案：C**

86. 在空白处填入什么代码不会导致语法或运行时错误？

```java
public class Test {
    java.util.Date date;

    public static void main(String[] args) {
        Test test = new Test();
        System.out.println(________);
    }
}
```

A) `test.date`
B) `date`
C) `test.date.toString()`
D) `date.toString()`

章节：9.7 静态变量、常量和方法

> 代码中 `date` 未初始化，`date.toString()` 会报空指针异常；`date` 也无法直接使用，因为它不是静态成员。合法的是 `test.date`。
> **答案：A**

87. 要防止一个类被实例化，________。
A) 对构造函数使用`private`修饰符
B) 对构造函数使用`static`修饰符
C) 不对构造函数使用任何修饰符
D) 对构造函数使用`public`修饰符

章节：9.8 可见性修饰符

> 使用 `private` 修饰构造函数可以防止实例化。
> **答案：A**

88. 封装的优点是什么？
A) 它可以在不改变类的契约的情况下更改实现，并且不会对其他代码造成相应的更改。
B) 它可以在不改变实现的情况下更改类的契约，并且不会对其他代码造成相应的更改。
C) 将类声明为`final`不会对其他代码造成相应的更改。
D) 只需要公共方法。

章节：9.9 数据字段封装

> 封装的优点是可以在不改变类的契约的情况下更改实现，而不影响其他代码。
> **答案：A**

89. 显示的`times`的值是多少？

```java
public class Test {
    public static void main(String[] args) {
        Count myCount = new Count();
        int times = 0;

        for (int i = 0; i < 100; i++)
            increment(myCount, times);

        System.out.println(
                "myCount.count =   " + myCount.count);
        System.out.println("times = " + times);

    }

    public static void increment(Count c, int times) {
        c.count++;
        times++;
    }
}

class Count {
    int count;

    Count(int c) {
        count = c;
    }

    Count() {
        count = 1;
    }
}
```

A) 0
B) 98
C) 99
D) 100
E) 101

章节：9.10 将对象传递给方法

> 变量 `times` 是值传递，不会改变其值。其输出为 `0`。
> **答案：A**

90. 给定声明`Circle[] x = new Circle[10]`，以下哪个陈述最准确？
A) `x`包含一个对数组的引用，并且数组中的每个元素都可以保存一个指向`Circle`对象的引用。
B) `x`包含一个对数组的引用，并且数组中的每个元素都可以保存一个`Circle`对象。
C) `x`包含一个由十个`Circle`类型对象组成的数组。
D) `x`包含一个由十个`int`值组成的数组。

章节：9.11 对象数组 

> **90.** `x` 是一个数组引用，数组的每个元素可以保存对 `Circle` 对象的引用。
> **答案：A**


91) `main`方法中第二条语句的输出是什么？

```java
public class Foo {
    static int i = 0;
    static int j = 0;

    public static void main(String[] args) {
        int i = 2;
        int k = 3;
        {
            int j = 3;
            System.out.println("i + j is " + i + j);
        }

        k = i + j;
        System.out.println("k is " + k);
        System.out.println("j is " + j);

    }
}
```

A) `k is 0`
B) `k is 1`
C) `k is 2`
D) `k is 3`

章节：9.13 变量的作用域

> **91.** `k = i + j`，其中 `i` 是局部变量值为 `2`，`j` 是静态变量值为 `0`，故 `k` 为 `2`。
> **答案：C**

92. 要创建一个表示`454`的`BigInteger`实例，需使用________。
A) `BigInteger(454);`
B) `BigInteger("454");`
C) `new BigInteger(454);`
D) `new BigInteger("454");`

章节：10.9 `BigInteger`和`BigDecimal`类

> **92.** `BigInteger` 的构造需要传入字符串，如 `new BigInteger("454")`。
> **答案：D**

93. 要将`BigInteger`类型的`b1`加到`b2`上，应写成________。
A) `b2 = b2.add(b1);`
B) `b1.add(b2);`
C) `b2 = b1.add(b2);`
D) `b2.add(b1);`
E) `b1 = b2.add(b1);`

章节：10.9 `BigInteger`和`BigDecimal`类

> `BigInteger` 的加法返回一个新对象，因此需要赋值：`b2 = b2.add(b1)` 或 `b2 = b1.add(b2)`。
> **答案：A, C**

94. 要将`BigDecimal`类型的`b1`除以`b2`并将结果赋给`b1`，应写成________。
A) `b1.divide(b2);`
B) `b2 = b2.divide(b1);`
C) `b2.divide(b1);`
D) `b1 = b1.divide(b2);`
E) `b1 = b2.divide(b1);`

章节：10.9 `BigInteger`和`BigDecimal`类

> **94.** 同加法，`b1` 的除法结果必须赋值：`b1 = b1.divide(b2)`。
> **答案：D**

95. 以下代码的输出是什么？

```java
public class Test {  
    public static void main(String[] args) {
        String s1 = "Welcome to Java!";
        String s2 = s1;

        if (s1 == s2)
            System.out.println("s1 and s2 reference to the same String object");
        else
            System.out.println("s1 and s2 reference to different String objects");

    }
}
```

A) `s1`和`s2`引用同一个`String`对象
B) `s1`和`s2`引用不同的`String`对象

章节：10.10 `String`类

> **95.** 字符串常量池中，`s1` 和 `s2` 引用同一个对象。
> **答案：A**

96. 假设`s`为`" abc "`，方法________会返回一个新字符串`"abc"`。
A) `s.trim()`
B) `s.trim(s)`
C) `trim(s)`
D) `String.trim(s)`

章节：10.10 `String`类

> **96.** `s.trim()` 去掉字符串首尾的空格，返回新字符串。
> **答案：A**

97. 假设`s`为`"ABCABC"`，方法________会返回一个字符数组。
A) `s.toCharArray()`
B) `String.toCharArray()`
C) `toChars(s)`
D) `s.toChars()`
E) `String.toChars()`

章节：10.10 `String`类

> **97.** `s.toCharArray()` 将字符串转换为字符数组。
> **答案：A**

98. 以下语句会显示什么内容？

```java
System.out.println("Java is neat".replaceAll("is", "AAA"));
```

A) `JavaAAA neat`
B) `Java AAA neat`
C) `Java AAAneat`
D) `JavaAAAneat`

章节：10.10 `String`类

> `replaceAll("is", "AAA")` 替换所有出现的 "is" 为 "AAA"，结果为 `Java AAA neat`。
> **答案：B**

99. 以下代码会显示什么内容？

```java
System.out.print("A,B;C".replaceAll(",;", "#") + " ");
System.out.println("A,B;C".replaceAll("[,;]", "#"));
```

A) `A B C A B C`
B) `A,B;C A#B#C`
C) `A B C A#B#C`
D) `A#B#C A#B#C`

章节：10.10 `String`类

> `replaceAll(",;", "#")` 不匹配任何内容，结果为 `A,B;C`。
>
> `replaceAll("[,;]", "#")` 替换 `,` 和 `;`，结果为 `A#B#C`。
> **答案：B**

100. 分析以下代码：

```java
class Test {  
    public static void main(String[] args)  { 
        StringBuilder strBuf = new StringBuilder(4);
        strBuf.append("ABCDE");
        System.out.println("What's strBuf.charAt(5)? " + strBuf.charAt(5));
    }
}
```

A) 程序有运行时错误，因为缓冲区的容量是4，但有五个字符`"ABCDE"`被添加到缓冲区中。
B) 程序有运行时错误，因为在`"ABCDE"`被添加到缓冲区后，缓冲区中字符串的长度为5。因此，`strBuf.charAt(5)`超出范围。
C) 程序能编译并正常运行。
D) 程序有编译错误，因为不能在`StringBuilder`构造函数中指定初始容量。

章节：10.11 `StringBuilder/StringBuffer`类

> `StringBuilder` 自动扩展容量，但 `charAt(5)` 会超出范围，导致运行时错误。
> **答案：B**

101. 运行类`C`的输出是什么？

```java
class A {
    public A() {
        System.out.println(
                "The default constructor of A is invoked");
    }
}

class B extends A {
    public B() {
        System.out.println(
                "The default constructor of B is invoked");
    }
}

public class C  {
    public static void main(String[] args) {
        B b = new B();
    }
}
```

A) `"The default constructor of A is invoked"`
B) `"The default constructor of B is invoked"` 接着 `"The default constructor of A is invoked"`
C) `"The default constructor of B is invoked"`
D) 无显示内容
E) `"The default constructor of A is invoked"` 接着 `"The default constructor of B is invoked"`

章节：11.3 使用`super`关键字

> **E)** `"The default constructor of A is invoked"` 接着 `"The default constructor of B is invoked"`
>
> 原因：在Java中，当创建子类对象时，会先调用父类的默认构造函数，然后才调用子类的构造函数。

102. 关于`super`关键字，以下哪个陈述是不正确的？
A) 可以使用`super`调用超类的构造函数。
B) 不能调用超类的父类中的方法。
C) 可以使用`super.super.p`调用超类的父类中的方法。
D) 可以使用`super`调用超类的方法。

章节：11.3 使用`super`关键字

> 答案：**C)** 可以使用`super.super.p`调用超类的父类中的方法。
>
> 原因：Java中不支持直接通过`super.super`访问父类的父类成员。

103. `getValue()`方法有两种重写方式。哪一种是正确的？

I:
```java
public class Test {
    public static void main(String[] args) {
        A a = new A();
        System.out.println(a.getValue());
    }
}

class B {
    public String getValue() {
        return "Any object";
    }
}

class A extends B {
    public Object getValue() {
        return "A string";
    }
}
```

II:
```java
public class Test {
    public static void main(String[] args) {
        A a = new A();
        System.out.println(a.getValue());
    }
}

class B {
    public Object getValue() {
        return "Any object";
    }
}

class A extends B {
    public String getValue() {
        return "A string";
    }
}
```

A) I
B) II
C) I和II都是
D) 都不是

章节：11.4 重写方法

> 答案：**B)** II
>
> 原因：II符合Java的协变返回类型（Covariant Return Type）规则，子类可以在重写方法中返回比父类方法更具体的类型。

104. 分析以下代码：

```java
public class Test {
    public static void main(String[] args) {
        new B();
    }
}

class A {
    int i = 7;

    public A() {
        setI(20);
        System.out.println("i from A is " + i);
    }

    public void setI(int i) {
        this.i = 2 * i;
    }
}

class B extends A {
    public B() {
        // System.out.println("i from B is " + i);    
    }

    @Override
    public void setI(int i) {
        this.i = 3 * i;
    }
}
```

A) 调用类`A`的构造函数，它显示`"i from A is 7"`。
B) 调用类`A`的构造函数，它显示`"i from A is 60"`。
C) 调用类`A`的构造函数，它显示`"i from A is 40"`。
D) 类`A`的构造函数未被调用。

章节：11.5 重写与重载

> 答案：**B)** 调用类`A`的构造函数，它显示`"i from A is 60"`。
>
> 原因：`setI(20)`在子类中被重写，会被调用，因此`i = 3 * 20 = 60`。

105. 给定以下类及其对象：

```java
class C1 {};
class C2 extends C1 {};
class C3 extends C1 {};

C2 c2 = new C2();
C3 c3 = new C3();

分析以下语句：

c2 = (C2)((C1)c3);
```

A) `c3`成功被转换为`c2`。
B) 语句正确。
C) 会出现运行时错误，因为Java运行时系统无法执行嵌套形式的多重转换。
D) 会出现运行时错误，因为不能将兄弟类的对象进行转换。

章节：11.9 转换对象与`instanceof`运算符

> 答案：**D)** 会出现运行时错误，因为不能将兄弟类的对象进行转换。
>
> 原因：兄弟类（`C2`与`C3`）间不存在继承关系，无法互相转换。

106. 分析以下代码：

```java
public class Test {
    public static void main(String[] args) {
        String s = new String("Welcome to Java");
        Object o = s;
        String d = (String)o;
    }  
}
```

A) 在`String d = (String)o`中将`o`转换为`s`时，会创建一个新对象。
B) 在`String d = (String)o`中将`o`转换为`s`时，`o`的内容会改变。
C) `s`、`o`和`d`引用同一个`String`对象。
D) 在`Object o = s`中将`s`赋给`o`时，会创建一个新对象。

章节：11.9 转换对象与`instanceof`运算符

> 答案：**C)** `s`、`o`和`d`引用同一个`String`对象。
>
> 原因：`String`是不可变的，类型转换不会创建新对象。

107. 以下代码的输出是什么？

```java
public class Test {
    public static void main(String[] args) {
        Object o1 = new Object();
        Object o2 = new Object();
        System.out.print((o1 == o2) + " " + (o1.equals(o2)));
    }
}
```

A) `false true`
B) `true true`
C) `true false`
D) `false false`

章节：11.10 `Object`的`equals()`方法

> 答案：**D)** `false false`
>
> 原因：`==`比较引用，`equals()`默认比较引用，两个`Object`是不同实例。

108. 分析以下代码：

```java
// 程序1
public class Test {
    public static void main(String[] args) {
        Object a1 = new A();
        Object a2 = new A();
        System.out.println(((A)a1).equals((A)a2));
    }
}

class A {
    int x;

    public boolean equals(A a) {
        return this.x == a.x;    
    }
}


// 程序2
public class Test {
    public static void main(String[] args) {
        A a1 = new A();
        A a2 = new A();
        System.out.println(a1.equals(a2));
    }
}

class A {
    int x;

    public boolean equals(A a) {
        return this.x == a.x;    
    }
}
```

A) 程序1显示`true`，程序2显示`true`。
B) 程序1显示`false`，程序2显示`true`。
C) 程序1显示`true`，程序2显示`false`。
D) 程序1显示`false`，程序2显示`false`。

章节：11.10 `Object`的`equals()`方法

> 答案：**A)** 程序1显示`true`，程序2显示`true`。

109. 假设`ArrayList`列表包含`{"red", "green", "red", "green"}`。执行以下代码后，列表是什么样的？

```java
list.remove("red");
```

A) `{"green", "green"}`
B) `{"green", "red", "green"}`
C) `{"red", "green", "red", "green"}`
D) `{"red", "green", "green"}`

章节：11.11 `ArrayList`类

> 答案：**B)** `{"green", "red", "green"}`
>
> 原因：`ArrayList`的`remove(Object)`方法删除第一个匹配的元素。

110. 组合（Composition）意味着________。
A) 数据字段应该声明为私有
B) 一个类继承另一个类
C) 超类型的变量引用子类型的对象
D) 一个类包含一个引用另一个对象的数据字段

章节：综合

> 答案：**D)** 一个类包含一个引用另一个对象的数据字段。
>
> 原因：组合（Composition）是指一个类通过数据字段持有另一个类的对象引用。

111. ________的一个实例用于描述编程错误，例如错误的类型转换、访问越界数组以及数值错误等。
A) `RuntimeException`
B) `Exception`
C) `Error`
D) `Throwable`
E) `NumberFormatException`

章节：12.3 异常类型

> 答案：**A)** `RuntimeException`
>
> 原因：`RuntimeException`是用于描述编程错误的主要类。

112. 以下程序会抛出什么异常类型？

```java
public class Test {
    public static void main(String[] args) {
        String s = "abc";
        System.out.println(s.charAt(3));
    }
}
```

A) `ArithmeticException`
B) `ArrayIndexOutOfBoundsException`
C) `StringIndexOutOfBoundsException`
D) `ClassCastException`
E) 无异常

章节：12.3 异常类型

> 答案：**C)** `StringIndexOutOfBoundsException`
>
> 原因：`s.charAt(3)`尝试访问字符串超出索引的字符。

113. 分析以下代码：

```java
public class Test {
    public static void main(String[] args) {
        try {
            String s = "5.6";
            Integer.parseInt(s); // 引发NumberFormatException

            int i = 0;
            int y = 2 / i;
        }
        catch (Exception ex) {
            System.out.println("NumberFormatException");
        }
        catch (RuntimeException ex) {
            System.out.println("RuntimeException");             
        }

    }
}
```

A) 程序有编译错误。
B) 程序显示`NumberFormatException`，接着显示`RuntimeException`。
C) 程序显示`RuntimeException`。
D) 程序显示`NumberFormatException`。

章节：12.4 更多关于异常处理的内容

> 答案：**A)** 程序有编译错误。
>
> 原因：多个`catch`块存在包含关系，`Exception`会捕获所有子类异常，因此后续的`RuntimeException`块不可达。

114. 运行以下程序时，控制台会显示什么内容？

```java
public class Test {
    public static void main(String[] args) {
        try {
            p();
            System.out.println("After the method call");   
        }
        catch (NumberFormatException ex) {
            System.out.println("NumberFormatException");  
        }   
        catch (RuntimeException ex) {
            System.out.println("RuntimeException");
        }   
    }

    static void p() {
        String s = "5.6";
        Integer.parseInt(s); // 引发NumberFormatException

        int i = 0;
        int y = 2 / i;
        System.out.println("Welcome to Java");   

    }
}
```

A) 程序显示`NumberFormatException`。
B) 程序显示`RuntimeException`。
C) 程序显示`NumberFormatException`，接着显示`After the method call`。
D) 程序有编译错误。
E) 程序显示`NumberFormatException`，接着显示`RuntimeException`。

章节：12.4 更多关于异常处理的内容

> 答案：**A)** 程序显示`NumberFormatException`。
>
> 原因：`Integer.parseInt(s)`抛出`NumberFormatException`，方法`p()`中的后续代码不会执行

115. 运行以下程序时，控制台会显示什么内容？

```java
public class Test {
    public static void main (String[] args) {
        try {
            System.out.println("Welcome to Java");
        }
        finally {
            System.out.println("The finally clause is executed"); 
        }
    }
}
```

A) `The finally clause is executed`
B) `Welcome to Java`
C) `Welcome to Java`，接着在下一行显示`The finally clause is executed`
D) 以上都不是

章节：12.5 `finally`子句

> 答案：**C)** `Welcome to Java`，接着在下一行显示`The finally clause is executed`
>
> 原因：`finally`块无论是否有异常都会执行。

116. 运行以下程序时，控制台会显示什么内容？

```java
public class Test {
    public static void main(String[] args) {
        try {
            System.out.println("Welcome to Java");
            int i = 0;
            int y = 2/i;
            System.out.println("Welcome to Java");
        }
        catch (RuntimeException ex) {
            System.out.println("Welcome to Java");
        }
        finally {
            System.out.println("End of the block");
        }
    }
}
```

A) 程序显示`Welcome to Java`三次，接着显示`End of the block`。
B) 程序显示`Welcome to Java`两次，接着显示`End of the block`。
C) 程序显示`Welcome to Java`两次。
D) 程序显示`Welcome to Java`三次。

章节：12.5 `finally`子句

> 答案：**B)** 程序显示`Welcome to Java`两次，接着显示`End of the block`。
>
> 原因：
>
> 1. `System.out.println("Welcome to Java");` 执行一次。
> 2. 捕获`RuntimeException`后又打印一次。
> 3. `finally`块始终执行。

117. 以下哪些陈述是正确的？
A) 如果一个目录（例如`c:\liang`）不存在，`new File("c:\liang")`会创建一个名为`c:\liang`的新目录。
B) 如果一个文件（例如`c:\temp.txt`）不存在，`new File("c:\\temp.txt")`会返回`null`。
C) 如果一个目录（例如`c:\liang`）不存在，`new File("c:\liang")`会返回`null`。
D) 如果一个文件（例如`c:\temp.txt`）不存在，`new File("c:\\temp.txt")`会创建一个名为`c:\temp.txt`的新文件。
E) 以上都

> 答案：**E)** 以上都
>
> 原因：所有选项描述均正确。

118) 要用哪个类从文本文件中读取数据？
A) `File`
B) `PrintWriter`
C) `Scanner`
D) `System`

章节：12.11 文本I/O

> 答案：**C)** `Scanner`
>
> 原因：`Scanner`是从文本文件读取数据的主要类。

119. 以下哪些语句是正确的？

I: 
```java
try (PrintWriter output = new PrintWriter("output.txt")) {
    output.println("Welcome to Java");
}
```

II: 
```java
try (PrintWriter output = new PrintWriter("output.txt");) {
    output.println("Welcome to Java");
}
```

III: 
```java
PrintWriter output;
try (output = new PrintWriter("output.txt");) {
    output.println("Welcome to Java");
}
```

IV: 
```java
try (PrintWriter output = new PrintWriter("output.txt");) {
    output.println("Welcome to Java");
}
finally {
    output.close();
}
```

A) I
B) II
C) III
D) IV

章节：12.11 文本I/O

> 答案：**A B C** 
>
> 原因：
>
> 1. I是正确的。
> 2. II中的分号多余，语法正确但不推荐。
> 3. III声明方式错误。
> 4. IV不能在`try-with-resources`后手动调用`close()`。

120. 要创建一个`InputStream`来从Web服务器上的文件读取数据，需使用`URL`类中的________方法。
A) `connectStream();`
B) `getInputStream();`
C) `openStream();`
D) `obtainInputStream();`

章节：12.12 从Web读取数据

> 答案：**C)** `openStream();`

121. 关于抽象方法，以下哪个陈述是错误的？
A) 抽象类有构造函数。
B) 非抽象类中不能包含抽象方法。
C) 包含抽象方法的类必须是抽象类。
D) 可以声明一个不包含抽象方法的抽象类。
E) 数据字段可以声明为抽象的。

章节：13.2 抽象类

> **答案：E)** 数据字段可以声明为抽象的。
> **解析：** 抽象仅能用于方法，不能用于数据字段。

122. 分析以下代码。以下哪个陈述是正确的？

```java
public class Test {
    public static void main(String[] args) {
        Number x = new Integer(3);
        System.out.println(x.intValue());
        System.out.println((Integer)x.compareTo(new Integer(4)));
    }
}
```

A) 程序能编译并正常运行。
B) 程序有编译错误，因为`intValue`是`Number`类中的抽象方法。
C) 程序有编译错误，因为成员访问运算符（`.`）在强制类型转换运算符之前执行了。
D) 程序有编译错误，因为`Integer`实例不能赋值给`Number`变量。
E) 程序有编译错误，因为`x`不能转换为`Integer`类型。

章节：13.3 案例研究：抽象`Number`类

> **答案：C**。

123. 假设`Calendar calendar = new GregorianCalendar()`，________会返回一年中的月份。
A) `calendar.get(Calendar.WEEK_OF_YEAR)`
B) `calendar.get(Calendar.MONTH_OF_YEAR)`
C) `calendar.get(Calendar.MONTH)`
D) `calendar.get(Calendar.WEEK_OF_MONTH)`

章节：13.4 案例研究：`Calendar`和`GregorianCalendar`

> **答案：C)** `calendar.get(Calendar.MONTH)`
> **解析：** `MONTH` 返回从 `0` 开始计数的月份值。

124. 假设`Calendar calendar = new GregorianCalendar()`，________会返回一个月中的天数。
A) `calendar.get(Calendar.MONTH_OF_YEAR)`
B) `calendar.get(Calendar.WEEK_OF_YEAR)`
C) `calendar.getActualMaximum(Calendar.DAY_OF_MONTH)`
D) `calendar.get(Calendar.WEEK_OF_MONTH)`
E) `calendar.get(Calendar.MONTH)`

章节：13.4 案例研究：`Calendar`和`GregorianCalendar`

> **答案：C)** `calendar.getActualMaximum(Calendar.DAY_OF_MONTH)`
> **解析：** `getActualMaximum` 返回指定字段的最大可能值。

125. ________不是引用类型。
A) 基本类型
B) 数组类型
C) 类类型
D) 接口类型

章节：13.5 接口

> **答案：A)** 基本类型
> **解析：** 基本类型如 `int`、`double` 等，不是引用类型。

126. 以下代码的输出是________。

```java
java.util.ArrayList<String> list = new java.util.ArrayList<String>();
list.add("New York");
java.util.ArrayList<String> list1 = (java.util.ArrayList<String>)(list.clone());
list.add("Atlanta");
list1.add("Dallas");
System.out.println(list1);
```

A) `[New York, Dallas]`
B) `[New York, Atlanta]`
C) `[New York, Atlanta, Dallas]`
D) `[New York]`

章节：13.7 `Cloneable`接口

> **答案：A)** `[New York, Dallas]`
> **解析：** `clone` 创建一个浅拷贝。对 `list1` 的修改不会影响 `list`。

127. 本章中定义的`Rational`类是`java.lang.Number`的子类。以下哪些表达式是正确的？
A) `Rational.doubleValue();`
B) `Rational.doubleValue("5/4");`
C) `new Rational(5, 4).intValue();`
D) `new Rational(5, 4).toDoubleValue();`
E) `new Rational(5, 4).doubleValue();`

章节：13.9 案例研究：`Rational`类

> **答案：C)** `new Rational(5, 4).intValue();`
> **E)** `new Rational(5, 4).doubleValue();`
> **解析：** `Rational` 类实现了 `intValue()` 和 `doubleValue()` 方法。

128. 以下哪些陈述是正确的？
A) 构造函数可以是受保护的。
B) 一个类应该总是包含无参构造函数。
C) 构造函数必须总是公共的。
D) 一个类应该描述一个单一的实体，并且所有的类操作在逻辑上应该相互配合以支持一个连贯的目的。

章节：13.10 类设计指南

> **答案：A)** 构造函数可以是受保护的。
> **D)** 一个类应该描述一个单一的实体，并且所有的类操作在逻辑上应该相互配合以支持一个连贯的目的。

129. 以下代码的作用是什么？

```java
FileInputStream fis = new FileInputStream("test.dat");
```

A) 无论`test.dat`是否存在，都会创建一个名为`test.dat`的新文件，并打开该文件以便可以对其进行读写操作。
B) 如果`test.dat`不存在，则创建一个名为`test.dat`的新文件，并打开该文件以便可以向其写入数据。
C) 如果`test.dat`不存在，则创建一个名为`test.dat`的新文件，并打开该文件以便可以对其进行读写操作。
D) 无论`test.dat`是否存在，都会创建一个名为`test.dat`的新文件，并打开该文件以便可以向其写入数据。
E) 如果`test.dat`存在，则为其创建一个`FileInputStream`。

章节：17.4 二进制I/O类

> **答案：E)** 如果 `test.dat` 存在，则为其创建一个 `FileInputStream`。
> **解析：** `FileInputStream` 仅用于打开现有文件进行读取，不会创建新文件。

130. 以下哪个语句正确地创建了一个`DataOutputStream`，用于向名为`out.dat`的文件写入数据？
A) `DataOutputStream outfile =  new DataOutputStream("out.dat");`
B) `DataOutputStream outfile = new DataOutputStream(FileOutputStream("out.dat"));`
C) `DataOutputStream outfile = new DataOutputStream(new File("out.dat"));`
D) `DataOutputStream outfile =  new DataOutputStream(new FileOutputStream("out.dat"));`

章节：17.4 二进制I/O类

> **答案：D)** `DataOutputStream outfile = new DataOutputStream(new FileOutputStream("out.dat"));`
> **解析：** `FileOutputStream` 提供写入文件的功能，`DataOutputStream` 包装它以支持数据操作。

131. 以下程序执行完后，向文件`t.dat`中写入了多少字节？

```java
import java.io.*;

public class Test {
    public static void main(String[] args) throws IOException {
        DataOutputStream output = new DataOutputStream(
                new FileOutputStream("t.dat"));
        output.writeChars("ABCD");
        output.close();
    }
}
```

A) 2字节
B) 4字节
C) 8字节
D) 12字节
E) 16字节

章节：17.4 二进制I/O类

> **答案：C)** 8 字节
> **解析：** `writeChars` 每个字符占 2 字节，总共 4 个字符，写入 `4 × 2 = 8` 字节。

132. 以下哪个陈述是正确的？
A) 对象中的方法会被序列化。
B) 静态变量不会被序列化。
C) 瞬态变量不会被序列化。
D) 一个对象必须是`Serializable`的实例才能被序列化。

章节：17.6 对象I/O

> **答案：**D) 一个对象必须是 `Serializable` 的实例才能被序列化。

133. 以下哪个是创建新的`RandomAccessFile`流的合法模式？
A) `'r'`
B) `"rwx"`
C) `"rw"`
D) `"w"`

章节：17.7 随机访问文件

> **答案：C)** `"rw"`
> **解析：** `"rw"` 模式允许读写操作。

134. 分析以下递归方法：

```java
public static long factorial(int n) {
    return n * factorial(n - 1); 
}
```

A) 调用`factorial(2)`返回2。
B) 调用`factorial(0)`返回0。
C) 调用`factorial(3)`返回6。 
D) 调用`factorial(1)`返回1。
E) 该方法会无限运行并导致`StackOverflowError`。

章节：18.2 示例：阶乘

> **答案：E)** 该方法会无限运行并导致 `StackOverflowError`。
> **解析：** 方法没有基本情况（base case），导致无限递归。

135. 在以下方法中，基本情况（base case）是什么？

```java
static int xMethod(int n) {
    if (n == 1)
        return 1;
    else
        return n + xMethod(n - 1);
}
```

A) `n`小于1
B) `n`是1
C) `n`大于1
D) 无基本情况

章节：18.4 利用递归解决问题

> **答案：B)** `n是1`
> **解析：** 基本情况出现在 `if (n == 1)`，直接返回 `1`。

136. 填写以下代码，以完成用于检查字符串是否为回文的方法。

```java
public static boolean isPalindrome(String s) {
    if (s.length() <= 1) // 基本情况
        return true;
    else if ________
        return false;
    else
        return isPalindrome(s.substring(1, s.length() - 1));   
}
```

A) `(s.charAt(1)!= s.charAt(s.length())) // 基本情况`
B) `(s.charAt(0)!= s.charAt(s.length() - 1)) // 基本情况`
C) `(s.charAt(0)!= s.charAt(s.length())) // 基本情况`
D) `(s.charAt(1)!= s.charAt(s.length() - 1)) // 基本情况`

章节：18.4 利用递归解决问题

> **答案：B)** `(s.charAt(0) != s.charAt(s.length() - 1))`
> **解析：** 检查字符串的首尾字符是否相等。

137. 填写以下代码，以完成用于对列表进行排序的方法。

```java
public static void sort(double[] list) {
    ________;
}

public static void sort(double[] list, int high) {
    if (high > 1) {
        // 查找最大数及其索引
        int indexOfMax = 0;
        double max = list[0];
        for (int i = 1; i <= high; i++) {
            if (list[i] > max) {
                max = list[i];
                indexOfMax = i;
            }
        }

        // 交换最大数与列表中最后一个数
        list[indexOfMax] = list[high];
        list[high] = max;
        
        // 对剩余列表进行排序
        sort(list, high - 1);

    }
}
```

A) `sort(list, list.length)`
B) `sort(list, list.length - 1)`
C) `sort(list)`
D) `sort(list, list.length - 2)`

章节：18.5 递归辅助方法

> **答案：B)** `sort(list, list.length - 1)`
> **解析：** `high` 是列表的最后一个索引，初始调用应传入 `list.length - 1`。

138. 对于4个圆盘，递归的`moveDisks`方法会被调用多少次？
A) 5
B) 10
C) 15
D) 20

章节：18.7 汉诺塔 

> **答案：C)** 15
> **解析：** 汉诺塔问题中，递归调用次数为 `2^n - 1`，当 `n = 4` 时为 `15` 次



























## Answers to Java Question Bank


1) C
2) A, B
3) C
4) E
5) A
6) B
7) D
8) C
9) D
10) E
11) D
12) A, B
13) C
14) B
15) B
16) A
17) D
18) A
19) D
20) B
21) A, B
22) D
23) B, C
24) C
25) C
26) A
27) D
28) B
29) B
30) C
31) C
32) C
33) C
34) D
35) C
36) A
37) D
38) D
39) C
40) A
41) D
42) A
43) D
44) B
45) C
46) B
47) C
48) C
49) B
50) D
51) A
52) C
53) B
54) D
55) D
56) C
57) B, C
58) D
59) B, C, E
60) A, B, D
61) C
62) D
63) A, D
64) A
65) B
66) B
67) B
68) A
69) D
70) C
71) B
72) C
73) D
74) A
75) A
76) D
77) C
78) D
79) B, C
80) C
81) A
82) A, C
83) C
84) B, D
85) C
86) A
87) A
88) A
89) A
90) A
91) C
92) D
93) A, C
94) D
95) A
96) A
97) A
98) B
99) B
100) B
101) E
102) C
103) B
104) B
105) D
106) C
107) D
108) A
109) B
110) D
111) A
112) C
113) A
114) A
115) C
116) B
117) E
118) C
119) A, B, C
120) C
121) E
122) C
123) C
124) C
125) A
126) A
127) C, E
128) A, D
129) E
130) D
131) C
132) D
133) C
134) E
135) B
136) B
137) B
138) C

