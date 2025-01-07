# SCUT2020AB-COAA

### Which type of memory will need refresh circuitry.

A. DRAM    B. Flash    C. ROM    D. Blu-ray

**答案**：A。

### The advantage of carry-lookahead adder is.

A. decrease cost of the adder.    B. save hardware parts.

C. augment CPU clock frequency.    D. accelerate the generation of the carries.

**答案**：D。

### In the direct addressing mode.

A. The operand is inside the instruction.

B. The address of the operand is inside the instruction.

C. The register containing the address of the operand is specified inside the instruction.

D. The location of the operand is implicit.

**答案**：B。

### In a microprogram-control computer, the microinstructions are stored in a memory called the.

A. direct memory    B. physical memory    C. virtual memory    D. control store

**答案**：D。

### Consider a four bit ALU which does four bit arithmetic. When computing 1101 + 1011, what is the status of NZCV flags.

计算结果：

```CPP
1101 + 1011 = 11000
// 保留4位 1000
```

对应的NZCV：1010。

### The pipelining technique typically improves the performance of a computer by.

A. decreasing the execution time of an instruction    B. improving CPU block frequency

C. improving the throughput    D. decreasing the cache miss rate

**答案**：C。

### The required control signals in a hardwired control unit are determined by the following information except.

A. contents of the control step counter    B. contents of the MAR (memory address register)

C. contents of the IR (instruction register)    D. contents of the condition code flags

**答案**：B。

### The processor informs the IO devices that it is ready to acknowledge interrupts by.

A. enabling the interrupt request line    B. activating the interrupt acknowledge line

C. activating the interrupt completion line    D. enabling the interrupt starting line

**答案**：B。

> 解释：
>
> 当处理器准备好响应中断并确认中断时，它会通过激活中断确认线来通知I/O设备。这条线用于通知外设处理器已经准备好处理中断请求，并开始进行相关的处理中断操作。
>
> 其他选项的解释：
>
> - **A. 启用中断请求线（enabling the interrupt request line）**：中断请求线通常是由外部设备发送信号到处理器，用于请求中断。启用这条线是外设发起中断请求时的动作，而不是处理器确认中断的动作。
> - **C. 激活中断完成线（activating the interrupt completion line）**：中断完成线通常是在处理中断操作后，告诉外设中断已经完成的信号。它与处理器确认中断的行为无关。
> - **D. 启用中断起始线（enabling the interrupt starting line）**：这个选项并不常见，也不适用于处理器确认中断的过程。
>
> 因此，**B** 是正确答案，处理器通过激活中断确认线来告诉I/O设备它已准备好处理中断。

### The starting address sent by the device in the vectored interrupt is called as.

A. interrupt vector    B. location ID    C. service location    D. service ID

**答案**：A。

### If the bytes 0x12, followed by 0x34, followed by 0x56, followed by 0x78 are interpreted as a 4-byte little endian integer, what value will they have.

**答案**：

```assembly
0x78 0x56 0x34 0x12
```



### Explain the process of DMA.

> ### Direct Memory Access (DMA) 过程解释
>
> **直接内存访问（DMA）** 是一种允许外设（如硬盘、网络接口卡、音频设备等）直接与系统内存交换数据的技术，而不需要经过CPU。这种方式提高了数据传输效率，并减轻了CPU的负担。DMA允许外设在内存中读取或写入数据，而CPU只需要在传输开始前和结束后进行少量干预。
>
> #### DMA过程步骤：
>
> 1. **初始化DMA控制器**：
>    - 在DMA传输开始前，CPU需要配置DMA控制器。控制器将包括需要传输的数据的源地址、目标地址、数据传输的大小、方向（读或写）等信息。
>    - 这通常是通过写入控制寄存器来完成的。
> 2. **启动DMA传输**：
>    - 一旦DMA控制器配置完毕，CPU会向DMA控制器发出启动传输的信号，告诉外设开始数据传输。
>    - 此时，DMA控制器会与外设（如硬盘、键盘、显示卡等）进行通信，并将传输请求提交给外设。
> 3. **外设准备数据**：
>    - 外设准备好数据（例如从磁盘读取数据，或将数据写入内存）并通知DMA控制器准备开始传输。
> 4. **数据传输**：
>    - DMA控制器将外设的数据直接传输到指定的内存地址，或者将数据从内存传输到外设。
>    - 在此过程中，CPU不参与数据的实际传输。DMA控制器控制数据流，并直接访问系统总线进行数据传输。
>    - 外设和内存之间的传输可以是单向的，也可以是双向的，具体取决于应用需求。
> 5. **传输完成**：
>    - 数据传输完成后，DMA控制器会通过中断或轮询的方式通知CPU，表示传输已完成。
>    - 在传输完成后，CPU可以读取传输结果，或者启动进一步的操作。
> 6. **释放DMA控制器**：
>    - 完成数据传输后，DMA控制器释放相关资源，CPU再次获得对内存和外设的控制权。
>
> ### DMA的优势：
>
> - **减少CPU负担**：在DMA传输期间，CPU不需要参与实际的数据传输，能够执行其他任务，提高系统效率。
> - **高效的数据传输**：DMA通常比CPU直接参与的数据传输（如使用程序中断）更快速、更高效。
> - **实时性**：在一些实时应用中，DMA可以提供及时的数据传输，满足特定的时间要求。
>
> ### DMA模式：
>
> 1. **单次传输模式（Burst Mode）**：
>    - 在该模式下，DMA控制器会一次性传输所有数据。传输完成后，控制权返回给CPU。
> 2. **单次传输模式（Cycle Stealing）**：
>    - 在该模式下，DMA控制器每次使用总线的一小段时间进行数据传输。传输过程中CPU也可以执行任务，DMA和CPU共享系统总线。
> 3. **块传输模式（Block Transfer）**：
>    - DMA控制器可以连续传输大块数据，直到所有数据传输完成。此过程中CPU的操作被暂时中断。
> 4. **双向传输模式（Demand Mode）**：
>    - DMA控制器在CPU需要时主动要求访问总线进行数据传输。当系统总线空闲时，DMA会请求占用总线进行数据传输。
>
> ### 总结：
>
> DMA通过允许外设与内存直接通信来减少CPU负担，提高数据传输效率。DMA的过程包括初始化、启动、数据传输、传输完成的通知，以及最终释放资源。通过DMA，系统可以实现更高效、快速的数据传输，特别是在需要频繁数据交换的应用中。

### Imagine a system with the following parameters. Virtual addresses 20 bits, physical addresses 18 bits, page size 1 KB. Please give the format of virtual address and physical address. Explain your answer.

**答案**：虚存地址一共有20位，物理地址一共18位，对应的页面大小为1KB，计算得到一共有$2^{20}\div 2^{10}= 2^{10}$个页面。

所以需要最低10位用于表示页面偏移量，剩下的10位用于表示虚拟页号。

因此，虚拟地址可以分为：

- **虚拟页号（10位）**
- **页内偏移（10位）**

物理地址一共有18位，一共有$2^{18}\div 2^{10}=2^8$个页面，所以最低10位用于表示页面偏移量，剩下的8位用于表示页面编号。

因此，物理地址的格式是：

- **物理页号**：18位 - 10位（偏移） = **8位**。
- **页内偏移**：**10位**。

> ### 系统参数：
>
> - **虚拟地址**是20位。
> - **物理地址**是18位。
> - **页面大小**是1 KB（即 1024 字节）。
>
> ### 1. 虚拟地址格式：
>
> - 虚拟地址
>
>   由两个部分组成：
>
>   1. **页号（Page Number）**：用来标识虚拟页。
>   2. **页内偏移（Offset within the Page）**：用来标识虚拟页内的具体字节位置。
>
> #### 计算虚拟地址的格式：
>
> - 页面大小是1 KB，即1024字节。所以，页内偏移需要 **10 位**来表示（因为 210=10242^{10} = 1024）。
> - 剩下的位数将用于表示 **虚拟页号（Page Number）**。
>
> 所以，虚拟地址的格式是：
>
> - **虚拟页号**：20位 - 10位（偏移） = **10位**。
> - **页内偏移**：**10位**。
>
> 因此，虚拟地址可以分为：
>
> - **虚拟页号（10位）**
> - **页内偏移（10位）**
>
> ### 2. 物理地址格式：
>
> - 物理地址
>
>   同样由两部分组成：
>
>   1. **物理页号（Physical Page Number）**：用来标识物理内存中的页。
>   2. **页内偏移（Offset within the Page）**：表示具体的字节位置。
>
> #### 计算物理地址的格式：
>
> - 由于页面大小仍为1 KB，**页内偏移**同样是 **10位**。
> - 物理地址总共有18位，所以剩下的位数将用于表示 **物理页号**。
>
> 因此，物理地址的格式是：
>
> - **物理页号**：18位 - 10位（偏移） = **8位**。
> - **页内偏移**：**10位**。
>
> ### 3. 虚拟地址到物理地址的转换：
>
> 在一个典型的分页系统中，虚拟地址到物理地址的转换过程如下：
>
> 1. **虚拟页号**（10位）通过页表映射到 **物理页号**（8位）。页表保存虚拟页号到物理页号的映射关系。
> 2. **页内偏移**（10位）在虚拟地址和物理地址中保持相同。
>
> #### 转换过程：
>
> - 从虚拟地址中提取 **虚拟页号** 和 **页内偏移**。
> - 查找页表，将 **虚拟页号** 转换为 **物理页号**。
> - 将转换得到的 **物理页号** 与 **页内偏移** 组合，得到物理地址。
>
> ### 4. 总结：
>
> - **虚拟地址格式**（20位）：
>   - 虚拟页号（10位） + 页内偏移（10位）
> - **物理地址格式**（18位）：
>   - 物理页号（8位） + 页内偏移（10位）
>
> #### 解释：
>
> - 虚拟地址通过页号和页内偏移组成。页号通过页表映射到物理页号，页内偏移保持不变。
> - 物理地址则由物理页号和页内偏移组成，通过页表映射得到。

### The two numbers given below are multiplied using the Booth's algorithm. Multiplicand: 0101 1010 1110 1110. Multiplier: 0111 0111 1011 1101. How many additions/subtractions are required for the multiplication of the above two numbers.

**答案**：利用布斯算法，将Multiplier进行转化

```cpp
   0111 0111 1011 1101
-> +1 0 0 -1 +1 0 0 0 -1 +1 0 0  0 -1 +1 -1
```

所以一共需要进行4次加法，4次减法。

### In a computer, can we build a memory system with one type of memory to get a large, fast and cheap memory.

 **答案**：我们可以建立一个多层级存储器系统，每一个$i$级存储设备是$i+1$设备的高速缓存，越靠近处理的存储设备速度越快，容量越小，相反的，距离越远的容量越大，速度越慢。通过这种多层级存储结构，可以实现容量高，读写速度快，成本低的特点。

> 使用**多层级存储器**（如内存层次结构）可以在一定程度上实现大容量、快速和便宜的内存系统。通过将不同类型的内存结合使用，可以在每个层级提供优化的速度、容量和成本。
>
> ### 多层级存储器系统的工作原理：
>
> 现代计算机系统通常使用多层次的存储器来平衡**速度**、**容量**和**成本**，从而实现高效的内存管理。这些层级包括：
>
> 1. **CPU寄存器**：
>    - **非常快**，但**容量小**，用于存储CPU正在处理的数据和指令。
> 2. **一级缓存（L1 Cache）**：
>    - **速度非常快**，通常由**SRAM**构成，但**容量小**。L1缓存直接与CPU紧密连接，用来缓存经常使用的数据。
> 3. **二级缓存（L2 Cache）和三级缓存（L3 Cache）**：
>    - **比L1缓存慢一些**，但仍然是**非常快的内存**，容量比L1大，通常用于缓存更多的常用数据和指令。
>    - **L2**和**L3缓存**的成本比L1更低，但仍然比主内存（DRAM）昂贵。
> 4. **主内存（RAM，通常是DRAM）**：
>    - **容量大**，但速度较慢（相对于缓存），成本低，适合存储大量数据，但访问速度受限于与CPU的总线带宽和延迟。
> 5. **硬盘或固态硬盘（SSD）**：
>    - **容量非常大**，**速度最慢**，主要用于存储数据（例如操作系统、应用程序、文件等）。
>
> ### 多层级存储器如何平衡速度、容量和成本：
>
> - **缓存（L1、L2、L3）**提供快速的数据访问，但由于成本和面积限制，它们的容量较小。
> - **主内存（DRAM）**提供大容量存储，且成本相对较低，但速度比缓存要慢。
> - **SSD和硬盘**提供超大的存储空间，成本最低，但速度非常慢。
>
> **通过这种多层次存储器架构，系统能够在需要高速度时使用更高层次的内存（如寄存器和缓存），在需要大量数据存储时使用较低层次的内存（如主内存和磁盘）**。操作系统和硬件会根据需要自动管理数据的加载和迁移，使得系统能够在不增加单一类型内存成本的情况下，优化整体性能。
>
> ### 总结：
>
> 使用**多层级存储器**（例如，缓存、主内存和外部存储）可以在一个系统中实现**大容量、快速、便宜**的内存系统。每一层存储器都根据不同的速度、容量和成本特点进行优化，最终通过缓存和内存的配合，达到整体优化的效果。

### Suppose we have a 7-bit computer that uses IEEE floating-point arithmetic where a floating point number has 1 sign bit, 3 exponent bits, and 3 fraction bits. The exponent part uses an excess-3 representation. The remaining 3-bit mantissa is normalized with an implied 1 to the left of the binary point. Rounding is employed as the truncation methal.

### (1) Write the largest positive normalized floating-point number. And write the smallest positive normalized floating-point number.

### (2) Write the result and computation process of A+B. Give the result in normalized form. A = 1.001, B= 0.010111.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412271000850.webp)

### Is it possible to design an expanding opcode to allow the following to be encoded in a 12-bit instruction. Justify your answer. Assume a register operand requires 3 bits and this instruction set does not allow memory addresses to be directly used in an instruction.

### (1) 6 instructions with 3 registers    (2) 14 instructions with 2 registers    (3) 15 instructions with 1 register    (4) 8 instructions with 0 register

**答案**：

- 需要9位用于分配三个操作数，剩下的三位用于分配操作码：

  ```cpp
  000 aaa bbb ccc
  001 aaa bbb ccc
  010 aaa bbb ccc
  011 aaa bbb ccc
  100 aaa bbb ccc
  101 aaa bbb ccc
  ```

- 需要6位用于分配2个操作数，剩下的6位用于分配操作码，最高两位置为1，剩下的4位实际对应操作码。

  ```cpp
  11 0000 aaa bbb 
  11 0001 aaa bbb
  11 0010 aaa bbb
  11 0011 aaa bbb
  11 0100 aaa bbb
  11 0101 aaa bbb
  11 0110 aaa bbb
  11 0111 aaa bbb
  11 1000 aaa bbb
  11 1001 aaa bbb
  11 1010 aaa bbb
  11 1011 aaa bbb
  11 1100 aaa bbb
  11 1101 aaa bbb
  ```

- 类推得到：

  ```cpp
  11111 0000 aaa
  11111 0001 aaa
  11111 0010 aaa
  11111 0011 aaa
  11111 0100 aaa
  11111 0101 aaa
  11111 0110 aaa
  11111 0111 aaa
  11111 1000 aaa
  11111 1001 aaa
  11111 1010 aaa
  11111 1011 aaa
  11111 1100 aaa
  11111 1101 aaa
  11111 1110 aaa
  ```

- 类推得到：

  ```cpp
  11111 1111 000
  11111 1111 001
  11111 1111 010
  11111 1111 011
  11111 1111 100
  11111 1111 101
  11111 1111 110
  11111 1111 111
  ```

  

### Part of a RISC-style processor's datapath is shown as the following figure. Instruction execution can be divided into 5-stages. Now we want to execute Mutiply R7, R8, R9 on this datapath. Before this instruction, [R7]=20, [R8]=10, [R9]=30. Write the values of registers at the end of instruction stage 2, stage 3, stage 4.  2.[RA],[RB].  3.[RZ].  4.[RY].

**答案**：

```assembly
stage2	[RA] = 10，[RB] = 30
stage3  [RZ] = 300
stage4	[RY] = 300
```

 

### The following sequence of RISC instructions are executed on a 5-stage pipeline. We can indicate the 5 stages of the pipeline using: F, D, C, M and W.  

```cpp
Add R2, R1, R3.  

Sub R4, R2, R1  

And R5, R1, R2  

Sub R6, R2, R4
```

### (1) Write all the data dependencies in the four instructions above.

**答案**：

Sub指令中的R2依赖于Add指令中的R2。

And指令中的R2依赖于Add指令中的R2。

第二道Sub指令中的R4依赖于第一道Sub指令中的R4。

第二道Sub指令中的R2依赖于Add指令中的R2。

### (2) Draw a figure to illustrate the execution of the four instructions on the pipeline. Assume that the pipeline has operand forwarding paths. Pay attention to mark the forwarding paths.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412252234384.webp)

### An integrated circuit RAM chip can hold 2048 words os 8 bits each (2k*8).

### (1) How many addresses and the data lines are there in the chips.

数据线一共是8条，地址线对应的是$2^{11}=2048$，一共是11条。

### (2) How many chips are needed to construct a 32k*16 RAM.

需要的芯片数目为$(32K \div 2K) \times (16 \div 8)= 16 \times 2=32$片。

### (3) How many addresses and the data lines are there in a 32k * 16 RAM.

数据线一共是 16 条，地质线$log_2 32K=15$条。

### (4) What size of the decoder is needed to construct 32k * 16 memory from the 2k * 8 chips. What are the inputs to the decoder and where are its outputs connected.

使用字扩展法，需要$32K \div 2K=16$个 2K * 16 的芯片进行扩展。所以需要使用3-8译码器。

根据memory的容量，得到的是 $log_2 32K = 15$位，最高三位用于3-8译码器的输入，产生的输出分别是8位，只取`0-4`即可。

### A computer system uses 16-bit memory addresses. It has a 2k-byte cache organized in a direct-mapped manner with 64 bytes per cache block. Assume that the size of each memory word is 1 byte.

### (1) Calculate the number of bits in each of the tag, block and word fields of the memory address.

**答案**：一个块是64字节，一个字是一个字节，所以Word字段：$log_2 64 = 6$位。

一共有$2K \div 64 = 32$块，所以是$log_2 32 = 5$位。

剩下的$16- 6 - 5 = 5$位用于Tag字段。

### (2) When a program is executed, the processor reads data sequentially from the following word addresses: 0080H, 0090H, 0880H, 0884H, 0080H, 0880H. Assume that the cache is initially empty. For each of the above addresses, indicate whether the cache access will result in a hit or a miss.

最初，缓存是空的，所以当访问0080H时，会将这个字所在块全部放入到缓存中，由于一个块的大小位64字节，所以放置的是location 128(10)开始的块，对应的是第二块，映射到的是第二块。

```cpp
0080H 128 
0090H 144
0880H 2176
0884H 2180
0080H 128
0880H 2176
```

由于块的大小是64字节，所以0090H访问时也发生了命中，访问0880H时没有命中，2176所在的是第34块，映射到的是$34 \% 32 = 2$块，所以映射到的是2块。

访问0884H时，所在块是34块，已在缓存中，所以命中。注意使用的直接映射法，所以原来的块2被替换了。

访问0080H时，此时在缓存中块2位置的是第34块，所以没有命中，需要将该块进行替换，后续访问0880时由于第34块已经被第2块替换，没有命中，所以需要重新载入。

总结一下：一共发生了miss 4次，命中发生了2次。



 

 



 

### ___ is not a kind of random access memory.

A. DRAM    B. SRAM    C. Floppy disk    D. Cache

**答案**：C。

### ___ is not the basic functional unit of a computer.

A. Input unit    B. Network interface card    C. Memory    D. Control unit

**答案**：B。

### ___ addressing mode only exists in CISC-style processors.

A. Indirect    B. Immediate    C. Index    D. Register indirect

**答案**：A。

### ___ is not a kind of cache mapping scheme.

A. Fully associative mapping    B. set associative mapping

C. Segmentation with paging    D. Direct mapping

**答案**：C。

### In program-controlled IO, the processor always polls _______ register in the IO interface to see if the IO device is ready.

A. status    B. data    C. control    D. none of above

**答案**：A。

### The functions of the IO interface do not include _____.

A. device communication    B. instruction decoding

C. error detection    D. control and signaling

**答案**：B。

> I/O接口的主要功能是管理处理器与I/O设备之间的通信，其功能包括：
>
> - **A. 设备通信**：实现处理器与I/O设备之间的数据交换。
> - **C. 错误检测**：在数据传输过程中检测并报告错误。
> - **D. 控制与信号**：管理控制信号，用于协调处理器与设备的操作（例如，设备是否准备就绪或忙碌的状态信号）。
>
> 然而：
>
> - **B. 指令解码**：这是**处理器（CPU）**的功能，而不是I/O接口的功能。CPU从内存中获取指令并进行解码以执行，而I/O接口则主要负责处理器与I/O设备之间的通信与控制。
>
> 因此，**指令解码**不属于I/O接口的功能。

### Which of the following statements is true for memory-mapped IO?

A. IO devices and memory use separate address spaces.

B. Input/Output operations of the devices look different from memory read/write.

C. The instructions which can access memory can not be used to access IO devices.

D. The address space for the memory is reduced.

**答案**：D。

### _____ is a kind of DMA transfer mode.

A. Direct mode    B. Burst mode    C. Indirect mode    D. Relative mode

**答案**：B。

### Which of the following statements is true in a CISC-style processor.

A. Each instruction fits in a single word.

B. It has a small set of instructions.

C. A load/store architecture is used.

D. Autoincrement addressing mode can be used.

**答案**：D。

### A microprogram is stored in _____.

A. control store    B. microinstructions    C. control word    D. micro memory

**答案**：A。

### Assuming that register R3 contains a number 200, register R5 contains a number 100, and the memory is byte-addressable, what is the effective address in each of the following cases.

### (1) -(R5)    (2) (R3)+    (3) 20(R3,R5)

**答案**：

- 96
- 200
- 320

### In a 16-bit floating-point number format, the most significant bit is the sign bit, the following 6 bits are for excess -31 exponent, and the remaining 9 bits are for normalized mantissa with an implied 1 to the left of the binary point.

### (1) What is the 16-bit floating-point representation of -36.

### (2) What is the decimal equivalent of the floating-point number 0 100010 010100000.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412271000850.webp)



### How many types of pipeline hazards. What are they. Which hazard is caused by data dependencies. And which hazard is caused by resource limitation.

 **答案**：

3。Data Hazard，Structure Hazard，Control Hazard。

Data Hazard。Structure Hazard。

### Design a 32Kx32 memory using 4Kx8 memory chips.

### (1) How many rows and columns are the memory chips organized.

一共是$32K \div 4K =8$行，$32 \div 8= 4$列。

### (2) How many bits are required for the memory chip select.

需要3位，使用3-8译码器，可以选择8行中的一行。

### (3) Draw the implementation figure of the 32Kx32 memory.



### Assume that a computer's instruction length is 15 bits, and the length of operand address is 4 bits. Design four types of instructions: three-address instructions, two-address instructions, one-address instructions, and zero-address instruction. Please describe the design of the instruction format and specify the number of each type of instructions.

**答案**：

一个操作数占据4位。

- 三地址指令：一共12位用于操作数。

  ```cpp
  000 aaaa bbbb cccc
  001 aaaa bbbb cccc
  010 aaaa bbbb cccc
  011 aaaa bbbb cccc
  100 aaaa bbbb cccc
  101 aaaa bbbb cccc
  110 aaaa bbbb cccc
  ```

  一共是7条指令。

- 二地址指令：一共8位用于操作数

  ```cpp
  111 0000 aaaa bbbb
  111 0001 aaaa bbbb
  111 0010 aaaa bbbb
  111 0011 aaaa bbbb
  111 0100 aaaa bbbb
  111 0101 aaaa bbbb
  111 0110 aaaa bbbb
  111 0111 aaaa bbbb
  111 1000 aaaa bbbb
  111 1001 aaaa bbbb
  111 1010 aaaa bbbb
  111 1011 aaaa bbbb
  111 1100 aaaa bbbb
  111 1101 aaaa bbbb
  111 1110 aaaa bbbb
  ```

- 一地址指令：一共4位用于操作数。

  ```cpp
  1111111 0000 aaaa
  1111111 0001 aaaa
  1111111 0010 aaaa
  1111111 0011 aaaa
  1111111 0100 aaaa
  1111111 0101 aaaa
  1111111 0110 aaaa
  1111111 0111 aaaa
  1111111 1000 aaaa
  1111111 1001 aaaa
  1111111 1010 aaaa
  1111111 1011 aaaa
  1111111 1100 aaaa
  1111111 1101 aaaa
  1111111 1110 aaaa
  ```

- 零地址指令：一共0位用于操作数

  ```cpp
  11111111111 0000 
  11111111111 0001
  11111111111 0010
  11111111111 0011
  11111111111 0100
  11111111111 0101
  11111111111 0110
  11111111111 0111
  11111111111 1000
  11111111111 1001
  11111111111 1010
  11111111111 1011
  11111111111 1100
  11111111111 1101
  11111111111 1110
  11111111111 1111
  ```

  





### Show $A\div B$ on the 5-bit unsigned numbers A=11010 and B=01001 using non-restoring division.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412260013252.webp)





### Consider the following instructions at given hexadecimal addresses in the memory.

```assembly
0x0010   Add   R5,R1,R2

0x0014   Subtract   R6,R5,#8

0x0018   Add   R7,R5,#12

0x001C   Subtract   R8,R1,R2
```

### Registers R1,R2 and R5 contain decimals 30, 400 and 50 respectively. The instructions are executed in a computer with a five-stage pipeline. The first instruction is fetched in clock cycle 1, and the remaining instructions are fetched in successive cycles.

### (1) Draw a diagram showing the flow of the instructions through the pipeline, assuming that the pipeline provides no forwarding paths.

### (2) Draw a diagram showing the flow of the instructions through the pipeline, assuming that the pipeline provides forwarding paths to the ALU from registers RY and RZ.

### (3) Write down the contents of registers IR, PC, RA, RB, RZ and RY in the pipeline with operand forwarding during cycles 2 to 8.   

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412260947829.webp)





### In a 2-way set associative mapped cache consisting of eight words, each cache line can hold two 32-bit words. The memory is byte-addressable. The processor reads data sequentially from the following memory addresses which are represented by hexadecimal numbers: 18, 14, 1C, 20, 2C, 48.

### Assume that the cache is initially empty. Show the contents of the cache (denoted by the memory addresses) at the end of each data read. LRU replacement algorithm is used.

**答案**：缓存中一共有2组，一组2个块，一个块两个字，一个字是四个Byte。

所以计算得到结果如下：

```cpp
18 -> 24 //第3块
14 -> 20 //第2块
1C -> 28 //第3块
20 -> 32 //第4块
2C -> 44 //第5块
48 -> 72 //第9块
```

最初缓存是空的，所以访问位置18时需要载入，载入到的是$3 \% 2 =1$组。访问14时miss，载入第2块，载入到的是$2 \% 2 =0$组。

访问位置1C时已经在内存中，命中。访问20时，块4还没有载入内存中，所以发生了miss，需要载入主存中，对应的是$4 \% 2 =0$组。此时0组剩余1个位置恰好可以载入。访问2C时，块5还没有载入到主存中，对应的是$5 \%2 =1$，此时1组还有一个位置恰好可以载入。

访问48时miss，所以需要将块9载入到主存中，对应的是$9 \% 2 =1$，此时1组已满，使用选择替换算法，将第三块移除，再将第九块载入。