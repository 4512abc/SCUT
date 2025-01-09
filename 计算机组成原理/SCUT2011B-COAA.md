# SCUT2011B-COAA

## 一、选择题

For each question in this section, choose 1 answer. Choose the best answer.

### Interrupt system is implemented by    C   .

A.  only hardware                 B.  only software       

C.  both hardware and software      D.  none of the above    

**答案**：C。

### In a    D    bus, all devices derive timing information from a common clock line.

A.  system     B.  asynchronous       C.  internal     D.  synchronous

**答案**：D。

在**同步总线**中，所有设备都从一个共同的时钟线获取时序信息，这意味着所有操作都是基于这个共享的时钟信号来协调的。

### In carry-lookahead adder, the expression    C   is called the generate function $G_i$ for stage i.

A.  $x_i+y_i$       B.  $x_i\oplus y_i$      C.  $x_iy_i$     D.  $x_i\oplus y_i\oplus c_i$

**答案**：C。

### A    has/have internal fragmentation problem.

虚拟地址中页的设计具有内部碎片化的问题

A.  Paging                B.  Segmentation with paging

B.   Segmentation           D. Segmentation and segmentation with paging

**答案**：A。

### Assume that the capacity of a kind of SRAM chip is 32K×32, so the sum of address lines and data lines of this chip is   A  . 

A.  47            B.  64            C.  46            D.  74

### The time to complete a read or write operation on a disk can be divided into two parts: the seek time and the    D   .

A. transfer time  B. access time   C. sector time   D. rotational delay time

**答案**：D。

### In DMA transfers, the data transfer unit between memory and I/O devices is    C  .

A. byte     B. word    C. block of data     D. bit

**答案**：C。

### Microprogram sequencing can be implemented by    C  .

A. PC      B. control store      C. μPC   D. SRAM

**答案**：C。

微程序序列控制通常由**μPC**（微程序计数器）实现。μPC负责跟踪当前执行的微指令的地址，从而控制微程序的执行过程。

### The 32-bit value 0x30a79847 is stored to the location 0x1000. If the system is little endian, the value of the byte    A    is stored in address 0x1002.

A. 0xa7    B. 0x47    C. 0x98    D. 0x30

 **答案**：A。注意小端法。

### Which of the following is not the constituent of the I/O device’s interface circuit?  A

A. instruction register B. data register  C. status register D. address decoder

 **答案**：A。

 正确答案是 **A. instruction register**。

I/O设备的接口电路通常由**数据寄存器**、**状态寄存器**和**地址解码器**等组成。这些组件用于处理数据的传输、状态的监控和地址的识别。**指令寄存器**通常不属于I/O设备接口电路的组成部分，它主要用于存储CPU指令。

### Which one of the following is not used to prevent data hazards?   D   

A.  Bypassing   B.  Forwarding     C.  Stall       D.  Freeze or Flush

 **答案**：D。

 

### Addressing memory by giving a register (explicit or implicit) plus a constant offset as effective address is called    C   .

A.  direct addressing           B.  register addressing

C.  indexed addressing         D.  immediate addressing

 **答案**：C。

 

### In **IEEE 754** floating point number standard, instead of the signed exponent, E, the value actually stored in the exponent field is an unsigned integer    B   .

A.   E’=E+255  B.  E’=E+127      C.   E’=E+256     D.  E’=E+128

**答案**：B。

 

 

### In a computer with a microprogrammable control unit the period of the clock is determined by      **.**

A.  the delay of the control memory.

B.  the delay of the main memory.

C.  the delay of the ALU.

D.  the sum of two of the above delays.

 **答案**：D。

给的答案是D。但是A也有可能？

>  在微程序控制单元中，时钟周期的长度通常由多个因素决定，包括控制存储器的延迟、主存储器的延迟和算术逻辑单元（ALU）的延迟。这些延迟共同影响时钟周期的周期。因此，时钟周期的时长通常是这些延迟的总和。
>
> 在微程序控制单元中，时钟周期的长度主要由**控制存储器的延迟**决定。控制存储器存储微指令并控制指令的提取与执行，这个过程的延迟通常是确定时钟周期的关键因素。其他因素，如主存储器或ALU的延迟，通常不会直接影响微程序控制单元的时钟周期。

### In memory-mapped I/O system, we use   A     to differentiate memory locations and I/O devices.

因为同样是memory和IO system mapped，所以memory和IO system使用同种格式的地址（同一总线）

A. different addresses               B. different address buses

C. different instructions             D. different control signals

**答案**：A。

## 二、简答题 

### In a carry-lookahead adder, each bit-slice of the adder must use inputs $a_i$, $b_i$ and $c_i$ to produce generate function $g_i$, propagate function $p_i$, and sum output $s_i$. A proposal has been made to replace the standard definition of the propagate function: $p_i=a_i+b_i$ with a version that uses the exclusive-or function: $p_i = a_i \oplus b_i$. The carry function is now implemented in the carry-lookahead unit as before: $c_{i+1}=g_i+p_ic_i$.

### (1)Will the modified propagate function work properly in the calculation of carry signals by the carry lookahead unit? Why or why not?

### (2)What advantage would there be in using the exclusive-or version of the propagate signal? 

**Solution:**

 ### (1) **修改后的传播函数是否能正常工作？**

是的，修改后的传播函数 $ p_i = a_i \oplus b_i $ 仍然能正常工作。

- 唯一的区别是，当 $ a_i $ 和 $ b_i $ 都为 1 时，传播函数 $ p_i $ 将为 0，而不是 1。然而，在这种情况下，进位 $ c_{i+1} $ 仍然会因为生成函数 $ g_i $ 为 1 而被设置为 1。因此，即使 $ p_i $ 为 0，进位计算也不会受到影响，因为生成函数 $ g_i $ 会提供正确的进位信号。

- 综上所述，修改后的传播函数并不会影响进位计算，依然能正常工作。

### (2) **使用异或版本的传播信号有什么优势？**

使用 $ p_i = a_i \oplus b_i $ 作为传播信号的一个主要优势是，它还可以用来帮助计算每一位的和（sum）。具体来说，加法器中每一位的和公式是：
$$
s_i = a_i \oplus b_i \oplus c_i
$$

- 因为 $ p_i = a_i \oplus b_i $，在计算每一位的和时，我们可以直接使用 $ p_i $，而不需要再进行额外的异或运算。这减少了计算量。

- 对于较大的加法器（比如 32 位加法器），这种方法可以显著节省计算资源，因为它减少了计算和的步骤。

因此，使用异或版本的传播信号 $ p_i = a_i \oplus b_i $ 不仅能正确计算进位，还能优化每一位和的计算，特别是在多位加法器中，提高了计算效率，减少了硬件资源的使用。

 



 

 

 

 

 

 

### For a write operation in a cache memory system, what is the difference between write back and write through? 

**Solution:**

 **写直达（Write-through）**：缓存位置和主存位置同时更新。这样可以确保缓存和主存始终保持一致。但是所有的写操作都需要访问主存，这会导致系统速度变慢。

**写回（Write-back）**：仅更新缓存位置，并通过脏位（dirty bit）标记该位置已被修改。当包含被标记的字的块从缓存中移除时，才更新主存中的该字位置。相比写直达，写回更快，因为不会花费时间访问主存，且写入块内多个字只需要一次主存写操作。但主存的部分数据可能变得无效，并且缓存中需要额外的位来表示哪个块已经被修改。



## 三、综合题

### Using sequential multiplication algorithm, perform the operations A×B on the 4-bit unsigned numbers A= 1011 and B= 1101. Write the computation processes in a computer machine.

**Solution:**

**顺序乘法：**

- C表示进位，A表示寄存器，Q表示乘数，M表示被乘数。

- 每轮开始时，先看Q最低位，如果是1，A = A + M，否则不执行任何操作

  然后进行右移操作。

- 反复执行$n$轮，这里的$n$对应的是Q的位数。

**布斯算法**：

- 最低位是$Q_{-1}$，Q表示乘数，A表示寄存器，M表示被乘数。
- 每轮开始时，看最低两位$Q_0,Q_{-1}$：
  - 如果是00或者11，不执行任何操作
  - 如果是01，A = A + M， 如果是10， A = A - M。
  - 然后执行右移操作。
- 反复执行$n$轮，这里的$n$对应的是Q的位数。

  

 ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412241957751.webp)

 

 



### Consider the two-dimensional array A:

```cpp
int A[][] = new int[100][100];
```

### Where `A[0][0]` is at location 200, in a paged memory system with pages of size 200. A small process is in page 0 (locations 0 to 199) for manipulating the matrix; thus, every instruction fetch will be from page 0.

### Suppose that the elements of the array are stored in row order in the virtual memory. For three page frames, how many page faults are generated by the following array-initialization loops, using LRU replacement, and assuming page frame 1 has the process in it, and the other two are initially empty?

```CPP
(1)   for (int j = 0; j < 100; j++)           (2) for (int i = 0; i < 100; i++)
		for (int i = 0; i < 100; i++)              	for (int j = 0; j < 100; j++)
			A[i][j] = 0;                          		A[i][j] = 0;
```

**Solution:**

1. 5000
2. 50

**解释**：

注意数组中的元素是按照行顺序存储在虚拟内容中的，也就是

```CPP
A[0][0]
A[0][1]
A[0][2]
.......
```

总共三个页，一个存储程序，两个用于存储数据。

对应第一道：

```cpp
A[0][0]
A[1][0]
A[2][0]
.......
```

由于`A[i][0]`与`A[i + 1][0]`存储位置相差的是100，所以在将`A[0][0]`和`A[1][0]`载入page frame中后再载入数据时，就发生了page faults。

以此类推，一共是$100 \times (100 \div 2)=5000$。因为考虑到最初的page frame都是空的。



对应第二道：

```cpp
A[0][0]
A[0][1]
A[0][2]
.......
```

由于`A[i][j]`与`A[i][j + 1]`是相邻的，所以一个Page一共可以填充进200个数据。后续再次填充时就发生了Page faults。

以此类推，一共是$100 \times (100 \div 200)=50$





### Assume that a computer’s instruction length is 8-bit. Suppose the designers need 3 instructions with two 3-bit operands, 2 instructions with one 4-bit operand and 4 instructions with one 3-bit operand. How should we design the instruction format? 

**Solution:**

对于三条指令的二地址操作数（一个操作数子段为3位）。

可以设计为：最高2位表示操作码，低6位对于操作数。

对于两条指令的一地址操作数（4位）：可以设计为最高2位设置为1，`5-4`位表示操作码，最低四位表示操作数。

对于四条指令的一地址操作数（3位）：可以设计为最高3位设置位1，`5-3`位表示操作码，最低三位表示操作数。

```cpp
//3 instructions with two 3-bit operands
00 aaa bbb
01 aaa bbb
10 aaa bbb
    
//2 instructions with one 4-bit operand
11 00 aaaa    
11 01 aaaa

// 4 instructions with one 3-bit operand
11 100 aaa
11 101 aaa
11 110 aaa
11 111 aaa
```

 

 

 

 

 

 

 

 

 

 

 

 

 

 