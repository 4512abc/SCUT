> Java速成

起手:JAVA文件中有且只能有一个public类，且此类必须与文件同名。

# 变量

## 基本类型和对象类型

用法与含义与c++一致

四类八种

整数，浮点数，字符，布尔

对应为

```java
byte,short,int,long   
float,double      
char     
boolean
```

对这些基本类型，每个都对应了一个对象类型。基本类型和对象类型之间的转换称为装箱和拆箱

```java
byte--Byte
short--Short
int--Integer
long--Long
float--Float
double--Double
char--Character
boolean--Boolean
```

## 缓冲池

对这8类对象类型，java设计了缓冲池的概念，用于减少系统开销

```java
Integer m=110;
Integer m=110;
System.out.printIn(m==n);//true
```

java为Integer分配了范围为-128~128的缓冲池，在此范围内的声明会被视为同一个变量（引用）。

```java
Integer m=new Integer(121);
Integer n=new Integer(121);
System.out.printIn(m==n);//false
```

通过如上手段可以绕过缓冲池而创建一个新的对象。

# string

String不可继承，不可修改。

## 获取引用

```java
String a=new String("s");
String b=new String("s");//a!=b!=c
String c="s";
String d="s";//c==d==e
String e=a.intern();
```

a与b以new方式创建后，其值不加入缓冲池，二者也不互为引用

c以此方式赋值后，s加入缓冲池，后续以此方式创建对象时，检测到s，则作为c的引用

intern()方法获取字符串常量池中的与a相同值的String对象的引用，若无，则创建再返回。

# I/O

需要导入包  Scanner

```java
I

import java.util.Scanner//导入（类外）
Scanner sc =new SCanner)(System.in);//创建对象（类内）
sc.nextInt();//用于接受键盘的数字录入


O
System.out.printIn("  ");//用于向屏幕输出
```

# 类型转换

```java
//与c++基本一致
byte short char 除外，他们在运算时自动转换为 int 
    
```

# 运算符

## 算数运算符

```java
= - * / % ++ -- += -= *= /= %= <<  >>
```

## 逻辑运算符

```java
^//异或
|//或
&//且
!//非
```

## 短路运算符

```java
||//当左侧为真，则不看后面的表达式
&&//当左侧为假，则不看后面的表达式
```

## 三元

# 顺序结构

```java
if()
    else if()
        else
```

# 分支结构

```java
switch()
{
        case:
    default:
}
```

# 循环结构

```java
for(int i=0;i<n;i++)
{}
//-----------------
while()
{}
//-----------------
do{}
while()
```

# 数组

```java
int []arry=new int[]{1,2,3};
int []arry={1,2,3};
int []arry=new int[10];
int [][]arry=new int{{1},{2},{3}};
int [][]arry=new int[2][3];
//int 初始化为0，double 初始化为1   字符'/u0000'
```

# 方法

```java
public  class Test 
{
    public static void main(String[] args) 
    {
        name();
        System.out.println("hello world");
    }
    public static void name()
    {
        System.out.print("hsiurfi");
    }
    public static int name(int a)
    {
        int a=10;
        return 0;
    }//重载以及返回
    
}
```

# 值传递

## 传入

在java中，方法的值传递实质上是把地址以值的方式传递到了方法的内部，因此，在方法内修改变量，相当于对变量本身做出修改。当我们使用new创建了一个新的值时，相当于只改变了方法内的变量对应的地址。

```java
public class test {  
    public static void main(String[] args)
    {
        example a=new example(1);
        sd(a);
        System.out.println(a.a);//a.a=2
    }  
    public static void sd(example c)
    {
        c.a=2;
    }
}
class example{
    public int a;
    example(int c)
    {
        a=c;
    }
}
```

但是对基础类型和具有不可变性的对象类型，值传递时会自动创建一个值的副本而非地址的副本，因此修改不会同步到本体。

```c++
public class test {  
    public static void main(String[] args)
    {
        Integer a=2;
        int b=3;
        sd(a);
        sd(b);
        System.out.println(a);//a=2
        System.out.println(b);//b=3
    }  
    public static void sd(Integer c)
    {
        c++;
    }
    public static void sd(int c)
    {
        c++;
    }
}
```

String作为不可变的对象类型，同样无法创建其引用的对象。

综上，能被引用使用的称为引用数据类型

## 传出

```java
public class test {  
    public static void main(String[] args)
    {
        example a=new example(1);
        example b=sd(a);
        b.a--;
        System.out.println(a.a);
    }  
    public static example sd(example s)
    {
        s.a--;
        return s;
    }
}
class example{
    public int a;
    example(int c)
    {
        a=c;
    }
}
```

综上，引用数据类型相当于指针，无论传入传出总代表地址。基本数据类型则为单纯的值。

# 面向对象

## 修饰符

| 修饰符    | 当前类 | 同一个包内 | 子孙类（同一包） | 子孙类（不同包） | 包外 |
| --------- | ------ | ---------- | ---------------- | ---------------- | ---- |
| public    | Y      | Y          | Y                | Y                | Y    |
| protected | Y      | Y          | Y                | Y/N              | N    |
| default   | Y      | Y          | Y                | N                | N    |
| private   | Y      | N          | N                | N                | N    |
| 默认      | Y      | Y          | Y                | N                | N    |

注：当方法，类，变量前不补充修饰符时，视为补充了默认修饰符，此时其访问范围仅限包内

## 包

在 Java 中，**包（Package）** 是一种组织和管理类、接口和子包的机制。包提供了一种将相关类和接口分组在一起的方式，帮助避免命名冲突，并控制类和接口的访问权限。包还便于项目的结构化开发，使代码更加可读、维护更加方便。

### 包的主要作用

1. **命名空间管理**：防止类名冲突。如果两个类有相同的名称，但位于不同的包中，它们可以共存。比如 `java.util.Date` 和 `java.sql.Date` 都是 `Date` 类，但它们位于不同的包中。
2. **访问控制**：通过包可以控制类、接口和方法的访问权限。使用 `public` 修饰符的类和方法可以在其他包中访问，而包级私有（默认无修饰符）的类和方法只能在同一个包中使用。
3. **组织代码**：包为大型项目提供了一种结构化和模块化的代码组织方式，使代码更易于管理和维护。

### 创建包

```java
package com.example.utils;

public class MyClass {
    public void display() {
        System.out.println("Hello from MyClass");
    }
}

```

### 导入包

```java
import com.example.utils.MyClass;

public class Main {
    public static void main(String[] args) {
        MyClass obj = new MyClass();
        obj.display();
    }
}

```

注：文件内未注明包的创建，视为创建了默认包/无名包，同一文件夹内的全部无名包视为一个包

## this

```java
class test{
    int num;
    int setNum(int num){
        this.num=num;
        reutrn num;
}
}
```

## 构造函数

```java
class test{
    int num;
    test(){};
}
}
```

## 继承

```java
//使用extends继承类
class Parent {
    // 父类的方法
    void display() {
        System.out.println("This is the parent class.");
    }
}

class Child extends Parent {
    // 子类的方法
    void show() {
        System.out.println("This is the child class.");
    }
}

public class Main {
    public static void main(String[] args) {
        Child obj = new Child();
        obj.display();  // 调用父类的方法
        obj.show();     // 调用子类的方法
    }
}
//只能继承一个类
```

### super

```java
//用于显示调用父类的构造函数
//子类的构造函数默认调用父类的无参构造
//也可以用来调用父类中重写的方法
class Parent {
    int val;
    Parent() {
        System.out.println("Parent class constructor.");
    }
    Parent(String message) {
        System.out.println(message);
    }
    public void func()
    {
         System.out.println("parent");
    }
}

class Child extends Parent {
    Child() {
        super("Calling Parent's constructor with a parameter.");
        System.out.println("Child class constructor.");
    }
    public void func()
    {
        super.func();
    }
}

public class Main {
    public static void main(String[] args) {
        Child obj = new Child();
    }
}
//对于super，可以视为父类的别名，即super.val是合法的
```

### 重写

```java
class Parent {
    void display() {
        System.out.println("Parent class method.");
    }
}

class Child extends Parent {
    @Override//使用override可以使编译器检查是否重写成功
    void display() {
        System.out.println("Child class method.");
    }
}

public class Main {
    public static void main(String[] args) {
        Child obj = new Child();
        obj.display();  // 输出: Child class method.
    }
}
//重写的方法的返回值类型，方法名，参数列表必须一致
```

### 多重继承

```java
interface A {
    void methodA();
}

interface B {
    void methodB();
}

class C implements A, B {
    public void methodA() {
        System.out.println("Method A");
    }
    public void methodB() {
        System.out.println("Method B");
    }
}

```

### final

```java
final class Parent {
}
class Child extends Parent { }//error
//final修饰的类无法被子类继承

class Parent {
    final void display() {
    }
}
//final修饰的方法无法被子类修饰
```

### 抽象类

```java
//用abstract修饰类或方法
//抽象方法只能在抽象类中，抽象类中可能包括抽象方法
//抽象类不能实例化
public abstract class Parent {
    // 父类的方法
    abstract void display() {
        System.out.println("This is the parent class.");
    }
}

class Child extends Parent {
    // 子类的方法
    void display() {
        System.out.println("This is the child class.");
    }
}
}
//只能继承一个类
```

### 接口

接口可以理解为c++的纯虚函数，但是其所有方法不允许存在默认实现（java8之前），现在，为了防止这样带来的巨大开销（指每次继承后子类都要重写接口中的方法），接口现在支持默认的方法实现了

```java
public interface Parent {
    default void display()//接口的方法默认且只能是public的,使用default来表示默认方法
    {
        System.out.println("This is the parent class.");
    }
}
```

接口的字段默认都是static和final的

前者意味着不需要声明其对象就能使用其中的数据

后者意味着这些数据不可修改

### object

Object 类是 Java 中所有类的直接或间接父类。每个 Java 类都默认继承自 Object，这意味着所有类都可以使用 Object 类中的方法。Object 提供了一些基本的、通用的方法，这些方法在任何对象中都可以使用。

#### equal(等价)

1. 对基本类型，无equal方法，==比较的是值
2. 对于第项类型，==比较两个变量是否引用自同一个对象，equal对比的是这两个变量是否等价

```java
Integer x = new Integer(1);
Integer y = new Integer(1);
Integer z = new Integer(2); 
System.out.println(x.equals(y)); // true
System.out.println(x == y);      // false
System.out.println(x == z);      // false
System.out.println(x.equals(z)); // false
```

#### hashCode（哈希码）

hashSet通过对比元素的哈希码来判断两个元素是否相等，需要时必须在类中重写此方法

```java
@Override
public int hashCode() {
    int result = 17;//方便结果不重复
    result = 31 * result + x;
    result = 31 * result + y;
    result = 31 * result + z;
    return result;//根据域得到了可能独一无二的哈希码
}
```

#### toString

默认返回“类名@哈希码”

#### clone

分为深拷贝与浅拷贝

##### 深拷贝

拷贝对象和原始对象不是引用的同一个对象

##### 浅拷贝

拷贝对象和原始对象是引用的同一个对象

一般使用拷贝构造函数而非clone

# 关键字

## final

1. 数据

对基本数据类型：表示值无法修改

对对象数据类型：表示值可以修改，但是引用关系无法修改

2. 方法

方法无法被子类重写。private 方法隐式地被指定为 final，如果在子类中定义的方法和基类中的一个 private 方法签名相同，此时子类的方法不是重写基类方法，而是在子类中定义了一个新的方法。

3. 类

表示此类无法被继承

## static

1. 用作静态类变量
2. 用作静态方法
3. 用作静态语句块

```java
//静态语句块在类实例化的时候调用以此
public class test
{
    static{
        System.out.println("test");
    }
}
```

4. 静态成员类

存在继承的情况下，初始化顺序为:

- 父类(静态变量、静态语句块)
- 子类(静态变量、静态语句块)
- 父类(实例变量、普通语句块)
- 父类(构造函数)
- 子类(实例变量、普通语句块)
- 子类(构造函数)

# 范型

# 注解

# 异常

# 反射

# SPI

