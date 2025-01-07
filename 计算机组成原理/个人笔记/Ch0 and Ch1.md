# Ch0

> Computer architecture refers to those attributes of a system visible to a programmer, or put another way, those attributes that have a direct impact on the logical execution of a program.

计算机体系结构是指程序员可见的系统属性，或者换句话说，那些对程序的逻辑执行有直接影响的属性。



> Examples of architectural attributes include:
>
> The instruction set
>
> 1. The number of bits used to represent various data types.(e.g., numbers, characters)
>
> 2. I/O mechanisms
>
> 3. Techniques for addressing memory



> Computer organization refers to the operational units and their interconnections that realize the architectural specifications.

计算机组成是指实现架构规范的操作单元及其互连。



> Organizational attributes include those hardware details transparent to the programmer, such as
>
> 1. control signals
>
> 2. interfaces between the computer and peripherals
>
> 3. the memory technology used



# Ch1

## Summary

**计算机类型**：

- 嵌入式计算机
- 个人计算机
- 服务器或者企业系统
- 超级计算机



**五大功能部件**：

- 输入单元
- 输出单元
- 存储器
- 算术逻辑单元
- 控制单元



**计算机发展历史**：

- 第一代：真空管
- 第二代：晶体管
- 第三代：集成电路
- 第四代：大规模集成电路或者超大规模集成电路

### 计算机类型（Computer Types）

1. Embedded computers（嵌入式计算机）

2. Personal computers

3. Server & Enterprise systems
4. Supercomputers & Grid computers
5. Cloud Computing

### 功能单位（Functional Units）

#### 基本功能

1. 数据处理：数据是指任何数字信息，包括机器指令，数字和字符。
2. 数据存储
3. 数据移动
4. **控制**

#### 基本功能单位（Basic Functional Units of a Computer）

1. Input Unit:    Make computer accept coded information

2. Output Unit:    Send processed results to the outside world

3. Memory:    Store programs and data

   分为Primary Storage (main memory)、Cache Memory和Secondary Storage

   Primary Storage(main memory): Store programs when they are being executed.

   Cache Memory: 

   - A smaller, faster RAM unit.
   - Hold sections of a program that are currently being executed.
   - Initially, the cache is empty. As execution proceeds, instructions and the required data are copied to the cache. 最初是空的，随着程序的不断执行，指令和所需要的数据不断被复制到Cache中。

   Secondary Storage:

   - Store many programs and large amounts of data, particularly for information that is accessed infrequently. 存储大量的数据和程序，特别是那些不是经常被访问的信息。

4. Arithmetic and Logic Unit (ALU)：Execute arithmetic or logic operations. 大部分计算机操作由ALU完成。

   一般流程如下：将操作数载入到memory中，然后将题目载入到处理器中，在ALU中执行算术逻辑操作，然后将计算结果返回到memory中或者暂时保留在处理器中。

5. Control Unit:    Coordinate operations of the other units、Send control signals to other units and sense their states。

   - 协调其他单元的操作
   - 发送控制信号，并且感知确认他们的状态。

12合称为I/O Unit，45合称为Processor。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409042314495.webp)



计算机的操作：计算机通过**输入单元**以**程序和数据的形式**接收信息并将其**存储在内存**中。然后存储在内存中的信息在**程序控制**下被提取到**算术和逻辑单元中**进行处理。处理后的信息**通过输出单元**离开计算机。并且计算机的所有活动都是由**控制单元**指导的。





### 基本概念操作（Basic Operational Concepts）

**程序执行**

1. 执行的是**程序中指定的指令**。

处理器一次从内存中读取 （获取） 一条指令，并执行每条指令。程序执行包括**重复指令获取和指令执行**的过程。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409042314739.webp)



两个重要的寄存器：

PC：指向要执行的下一条指令

IR：保存当前正在执行的指令



一些常见指令的结果：

```powershell
Example: Load R2, LOC
/*
从存储器中提取指令，载入到处理器寄存器中
将存储于LOC存储单元的操作数载入到R2中
*/

Store R4, LOC
/*
将R4寄存器中的操作数复制到LOC存储单元中
*/

Add R4, R2, R3
/*
将R2寄存器和R3寄存器中的内容进行相加
将和存储到R4中
*/
```

![](https://cdn.jsdelivr.net/gh/BomLook/cartoon@main/img/202412041533374.webp)



2. 中断

中断是 I/O 设备向处理器发出的服务请求。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409042314901.webp)



### 性能（Performance）

**最重要的衡量指标：执行程序的速度。**

一般受：指令集、硬件和软件设计的影响。

- VLSI 技术：Smaller transistors switch faster

- 并行度：并行执行多个操作（Parallelism: performing a number of operations in parallel）

  包括指令级并行（流水线），多核处理器，多处理器，多计算机。



### 发展历史

看书合适。



### 练习

#### Which of the following is an example of both input and output device? 

A. Touchpad 	B. Display 	C. Printer 	D. Keyboard

**答案**：A

#### List the names of five functional units of a computer. 

Arithmetic and logic unit, 	control unit, 	memory, 	input unit, 	output unit 



#### Which technology marked the start of the first/second/third generation of electronic digital computers? 

A. integrated-circuit 	B. VLSI 	C. transistor 	D. vacuum tube

**答案**：DCA。
