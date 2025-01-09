# SCUT2010A-COAA

## 一、单选题

### A 2’s-complement overflow cannot occur when       .

A.  two positive numbers are added      

B.  two negative numbers are added

C.  a positive number is added to a negative number       

D.  a positive number is subtracted from a negative number

**答案：C**

- **解释**：当一个正数和一个负数相加时，结果的范围在可表示的数值范围内，不会发生溢出。而两个正数相加可能会超出正数的表示范围，两个负数相加可能会超出负数的表示范围，正数减负数相当于正数加正数，也可能溢出。

### What is the effect of the following instruction?       .

```assembly
move ecx, [ebp+8]
```

A.  Add 8 to the contents of `ebp` and store the sum in `ecx`.

B.  Add 8 to the contents of `ebp`, treat the sum as a memory address and store the contents at that address in `ecx`.

C.  Add 8 to the contents of the memory location whose address is stored in `ebp` and store the sum in `ecx`.

D.  Add the contents of `ebp` to the contents of memory address 8 and store the sum in `ecx`.

**答案：B**

- **解释**：该指令先将 `ebp` 的内容加上 8，把得到的和作为内存地址，然后将该地址处的内容存储到 `ecx` 中。

Answer the question 3-4 based on the following information:

### A memory system uses 24-bit physical address. It has a direct-mapped cache with 64 entries. The block size is 4 words (word size is 4 bytes). Each cache entry has a “valid bit”, a “tag field”, and space for data.

### The number of bits reserved for the tag field is      .

A.  14         B.  10         C.  6          D.  12

**答案**：A。

假设是按照字节寻址的，那么存储器容量就是$2^{24}$字节。那么$tag= 24- log_2{64}-log_2{(4 \times 4)}= 14$。

寻找的是某一个块中的某一个字中的某一个字节。

### The total number of bits in the cache is       .

A.  $2^6 * (143)$       B.  $2^6 * (33)$     C.  $2^8 * (145)$        D.  $2^{14} * (33)$ 

**答案**：一个块中的内容：$size = 4 \times 4 \times 8 = 128$。

再加上需要另外的空间来存储$tag$子段：$size_{tag} = 24$。此外还需要一位合法位。

所以一共是143位。由于是$2^6=64$个块，所以选择A。

### As part of handling interrupts, the processor must inform the device that its request has been recognized. This may be accomplished by means of a special control signal:       signal.

A.  interrupt-enable            B.  interrupt-acknowledge

C.  interrupt-request          D.  interrupt-service

**答案**：B。

### In IEEE 754 *double-precision* floating point number standard, instead of the signed exponent, E, the value actually stored in the exponent field is an unsigned integer       .

A.  E’=E+127      B.  E’=E+128      C.  E’=E+1023         D.  E’=E+1024

**答案**：按照754标准，$E'=E+2^{bit(E)-1}-1$。对应的就是$E'=E+1023$。

### The microroutines for all instructions in the instruction set of a computer are stored in a special memory called the    B   .

A.   flash memory       B.  control store        C. μPC       D.  SRAM

**答案**：B。

### In DMA transfers, the data transfer unit between main memory and I/O devices is    C   .

A.  byte        B.  word       C.  block of data        D.  bit

**答案**：C。

### A    arise from resource conflicts when the hardware cannot support all possible combinations of instructions simultaneously in overlapped execution.

A.  Structural hazards          B.  Data hazards

C.  Control hazards            D.  Branch hazards

**答案**：A。注意关键词hardware。

### In microprogram-controlled machines, the relationship between the machine instruction and the microinstruction is   C   .

A.  a machine instruction is executed by a microinstruction

B.  a microinstruciton is composed of several machine instructions

C.  a machine instruction is interpreted by a microroutine composed of microinstructions

D.  a microroutine is executed by a machine instruction

**答案**：问的是机器指令和微指令之间的关系，选择C。

在微程序控制的计算机中，机器指令是通过一系列微指令（即微程序）来执行的。每条机器指令通常对应一个或多个微指令，这些微指令控制计算机各个部件的操作。

### In memory-mapped I/O system, we use        to differentiate memory locations and I/O devices.

A.  different addresses                 B.  different address buses

C.  different instructions               D.  different control signals

**答案**：A。

在内存映射I/O系统中，内存和I/O设备共享相同的地址总线，但它们通过**不同的地址**来区分。每个内存位置和I/O设备都有唯一的地址，通过这些不同的地址，系统能够区分是访问内存还是I/O设备。

### A major advantage of direct mapping of a cache is its simplicity. The main disadvantage of this organization is that   C   .

A.  It’s more expensive than other types of cache organization.

B.  Its access time is greater than that of other cache organizations.

C.  The cache hit ratio is degraded if two or more blocks used alternatively mapped onto the same block frame in the cache.    

D.  It does not allow simultaneously access to the intended data and its tag.

**答案**：C。

### Assume that the multiplicand is 110011 and the multiplier is 101100. If multiply them using the Booth algorithm, then the Booth recoding multiplier is   C   .

A.  – 1 + 1 0 – 1 1 0               B.  – 1 – 1 0 – 1 0 0

C.  – 1 + 1 0 – 1 0 0               D.  + 1 + 1 0 – 1 0 0

**答案**：使用布斯算法堆multiplier进行计算即可，选C。

### If the 2006 version of a computer executes a program in 200s and the version of the computer made in the year 2007 executes the same program in 150s, then the speedup that the manufacturer has achieved over the two-year period is    D   .

A.  1.44       B.  1.78       C.  1.63       D.  1.33

**答案**：D

> The speedup achieved can be calculated using the formula:
>
> $$
> \text{Speedup} = \frac{\text{Old time}}{\text{New time}}
> $$
>
> Given:
> - The old time (2006 version) = 200s
> - The new time (2007 version) = 150s
>
> $$
> \text{Speedup} = \frac{200}{150} = 1.33
> $$
>
> So, the correct answer is:
>
> **D. 1.33**

### Assume that a Branch instruction uses relative addressing mode. It is two bytes in length. The first byte contains opcode, and the second contains offset (2’s-complement representation). Assume that when the processor fetches the first byte of Branch instruction, PC points to the next instruction automatically. At first (PC) = 2008H (before fetching the Brach instruction), if the program wants to jump to the address of 2001H, then the content of the second byte of this Branch instruction is    D   .

A. 07H        B. F7H        C. 09H        D. F9H

**答案**：D。

> 在相对寻址模式中，偏移量是通过计算目标地址和分支指令后续指令的地址之间的差值来获得的。
>
> 给定：
>
> - **PC = 2008H** 在取指令之前。
> - 分支目标地址是 **2001H**。
> - 分支指令的长度为 2 字节，第一字节是操作码，第二字节包含偏移量（以二进制补码表示）。
>
> ### 步骤 1：计算下一条指令的地址。
>
> 下一条指令的地址是 **PC + 1 = 2008H + 1 = 2009H**。
>
> ### 步骤 2：计算偏移量。
>
> 偏移量是目标地址和下一条指令的地址之间的差值：
>
> $$
> 偏移量=目标地址−下一条指令地址=2001H−2009H=−08H\
> $$
>
> ### 步骤 3：以二进制补码表示偏移量。
>
> **-08H** 的二进制补码表示是 **F8H**（因为 **08H** 的二进制是 **0000 1000**，其二进制补码为 **1111 1000**，即 **F8H**）。
>
> ### 步骤 4：最终答案。
>
> 因此，分支指令的第二字节（即偏移量）应该是 **F8H**。
>
> 但是，选项中并没有 **F8H**，这可能是题目或选项的一个格式问题。根据计算，**F8H** 是正确的答案，但由于没有在选项中出现，可能存在选项的错误或遗漏。

所以考虑取第二个字节时也发生了自增，指向了2010H，故选择D。

------------------

## 二、简答题

### What is the difference between a subroutine and an interrupt-service routine?

Solution:

**子程序**：它执行的是调用它的那个程序所需要的功能。所以，对于状态信息以及寄存器内容可能出现的变化，是在预期范围内的。

**中断服务程序**：它可能和接收到中断请求时正在执行的程序部分没有任何关联。因此，在开始执行中断服务程序之前，那些在该程序执行过程中可能会以不可预期的方式被改变的处理器寄存器状态信息以及寄存器内容，都必须先进行保存。而且，在被中断的程序恢复执行之前，这些保存好的信息还需要被恢复回来。



**子程序是通过程序指令调用的，用于执行调用程序所需的功能。**

**中断服务程序是由事件触发的，例如输入操作或硬件错误。它执行的功能可能与发生中断时正在执行的程序完全无关。因此，中断服务程序不能影响与该程序相关的任何数据或状态信息。**



### What are the advantages and disadvantages of hardwired and microprogrammed control?

**Solution:**

硬件：优点是速度更快

缺点是成本高，设计复杂，不够灵活

 

微程序：优点是灵活，消耗低

缺点是速度慢，在高性能计算机中可能成为一个问题



### Explain the drawback of the ripple carry full adder when you need to design 64-bit CPU core. And give a solution for the drawback. (Just give a name of the circuit. You don’t need to draw a circuit of solution).

**Solution:**

1. **在64位CPU核心设计中，行波进位全加器的缺点**

  - **传播延迟**：

   - 行波进位全加器用于构建多位加法器（如64位加法器）时存在严重的传播延迟问题。在这种加法器中，一级的进位输出是下一级的进位输入，进位信号要从最低有效位（LSB）“逐位传递”到最高有效位（MSB）。

   - 对于n位行波进位加法器，最坏情况下的传播延迟与n成正比。在64位行波进位加法器中，这个延迟会很大，会限制加法器的运算速度，进而影响CPU核心的整体速度。例如，若每个全加器级的传播延迟是$t_{pd}$，在64位行波进位加法器中，总的进位传播延迟可能高达$64\times t_{pd}$。

2. **解决方案**

- 可以使用**超前进位加法器（Carry - Lookahead Adder，CLA）**来解决这个问题。超前进位加法器通过更并行、更具前瞻性的方式生成进位信号，减少了进位传播延迟。它不是等待进位逐位传递，而是根据输入位同时计算所有级的进位输入信号，这大大减少了总体传播延迟，能实现更快的加法运算，这对64位CPU核心的高效运行很关键。





### A system has 48-bit virtual addresses and 36-bit physical addresses. If the system uses 4096-byte pages, how many virtual and physical pages can the address space support? 

**Solution:**

**The following steps will help us calculate the number of virtual and physical pages supported by the address space:**

**1. 计算虚拟页面数量**

我们已知页面大小为4096字节，等同于$2^{12}$字节。虚拟地址空间为48位。

虚拟页面数量$N_{v}$可通过将整个虚拟地址空间除以页面大小来计算。

虚拟地址空间中不同地址的总数是$2^{48}$个。由于每个页面有$2^{12}$字节，所以虚拟页面数量$N_{v}$可由以下公式得出：

$$
N_{v}=\frac{2^{48}}{2^{12}} = 2^{48 - 12}=2^{36}
$$
**2. 计算物理页面数量**

物理地址空间为36位。物理地址空间中不同地址的总数是$2^{36}$个。

因为每个页面的大小为$2^{12}$字节，所以物理页面数量$N_{p}$由以下公式给出：

$$
N_{p}=\frac{2^{36}}{2^{12}}= 2^{36 - 12} = 2^{24}
$$


因此，虚拟地址空间能够支持$2^{36}$个虚拟页面，而物理地址空间能够支持$2^{24}$个物理页面。



## 三、综合题

### What are the **largest positive** and the **smallest positive** numbers representable in this format?   compute A + B, Note: Using rounding as the truncation method in the answers. **Write the computation process!**

**A and B**

$A= 1 \ 01111 \ 101010$，$B=0 \ 10001 \ 011011$

Solution:

后续补充。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412240945325.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412271000877.webp)

### A logic circuit is needed to implement the priority network shown like figure 2. The network handles three interrupt request lines. When a request is received on line INTRi, the network generates an acknowledgement on line INTAi. If more than one request is received, only the highest-priority request is acknowledged, where the ordering of priority is: priority of INTR1 > priority of INTR2 > priority of INTR3.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412240924479.webp)

### (1) Give a truth table for each of the outputs INTA1, INTA2, and INTA3.

### (2) Give logic expressions of INTA1, INTA2, INTA3 and a logic circuit for implementing this priority network.



Solution:

 

(1)

| INTR1 | INTR2 | INTR3 | INTA1 | INTA2 | INTA3 |
| ----- | ----- | ----- | ----- | ----- | ----- |
| 0     | 0     | 0     | 0     | 0     | 0     |
| 0     | 0     | 1     | 0     | 0     | 1     |
| 0     | 1     | 0     | 0     | 1     | 0     |
| 0     | 1     | 1     | 0     | 1     | 0     |
| 1     | 0     | 0     | 1     | 0     | 0     |
| 1     | 0     | 1     | 1     | 0     | 0     |
| 1     | 1     | 0     | 1     | 0     | 0     |
| 1     | 1     | 1     | 1     | 0     | 0     |

 

(2)
$$
INTA1=INTR1 \\
INTA2=INTR2 \cdot \overline{INTR1} \\
INTA3 = INTR3 \cdot \overline{INTR1} \ \overline{INTR2}
$$

### Assume that a computer’s word-length is 16-bit, the capacity of main memory is 64K words. If it employs single-word-length one-address instructions and contains 64 instructions. Design an instruction format with addressing modes of direct, indirect, index, and relative.

Solution: 

**计算指令操作码的位数**

   - 已知计算机包含64条指令，因为$2^{n}\geqslant64$，所以操作码至少需要6位（$n = 6$时，$2^{6}=64$）来表示这64种不同的指令。
   - 另外存在4种寻址方式，所以需要 2 位来区分四种寻址方式。
   - 所以剩下 16 - 6 - 2 = 8 位。

**分析各种寻址方式下地址码的表示**

   - **直接寻址**：地址码部分直接给出操作数在主存中的地址。由于主存容量是$64K$个字，$64K = 2^{16}$，所以需要16位来表示主存中的任意一个地址。只能使用 8 位表示一个存储单元地址。
   - **间接寻址**：地址码部分给出的是指向操作数地址的指针地址。在这种情况下，这8位地址码先指向主存中的一个单元，该单元的内容才是真正的操作数地址。
   - **变址寻址**：假设使用一个变址寄存器（其内容为$X$），有效地址$EA = A+(X)$，其中$A$是指令中的地址码部分。这8位地址码与变址寄存器内容相加得到操作数的实际地址。
   - **相对寻址**：相对寻址是相对于程序计数器（PC）的寻址方式。有效地址$EA=(PC)+A$，指令中的地址码$A$（8位）与程序计数器当前值相加得到操作数的实际地址。

**设计指令格式**

   - 指令格式可以设计为16位，最高 2 位表示寻址方式，高6位为操作码（用于区分64种指令），低8位为地址码。
     - 00 表示直接寻址
     - 01 表示间接寻址
     - 10 表示 index 
     - 11 表示relative
   - 例如，操作码000000 - 111111分别代表不同的指令。对于每种指令，其地址码部分根据不同的寻址方式进行解释：
     - **直接寻址**：将这8位地址码直接作为主存地址来访问操作数。
     - **间接寻址**：先将这8位地址码所指的主存单元内容作为操作数的实际地址，再访问操作数。
     - **变址寻址**：结合变址寄存器内容与这8位地址码得到操作数实际地址后进行访问。
     - **相对寻址**：将这8位地址码与程序计数器当前值相加得到操作数实际地址后进行访问。
