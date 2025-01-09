# SCUT2010B-COAA

## 一、单项选择题

### A memory system uses 24-bit physical address. It has a direct-mapped cache with 64 entries. The block size is 4 words (word size is 4 bytes). Each cache entry has a “valid bit”, a “tag field”, and space for data.

### The number of bits reserved for the tag field is___.

A.   14         B.  10         C.  6          D.  12

**答案**：A。

### The total number of bits in the cache is___.

A.   $2^6 * (143)$       B.  $2^6 * (33)$     C.  $2^8 * (145)$        D.  $2^{14} * (33)$ 

**答案**：A。

### Which one of the following about one-address instruction is true? ___

A.   One-address instruction has only one operand

B.   One-address instruction may have one operand or two operands

C.   One-address instruction has two operands, and the other operand is provided implicitly

D.   One-address instruction may have three operands, and the other two operands are provided implicitly

**答案**：不确定。



### CPU responses the interrupt request___. 

A.   after it completes its fetch cycle

B.   after it completes its execution cycle

C.   when the interrupt source issues the interrupt request 

D.   when the bus is not busy

**答案**：B。

CPU通常会在完成当前指令的执行周期后响应中断请求。这是因为在处理中断之前，CPU需要先完成当前指令的执行，以保证指令的原子性。响应中断的过程通常包括保存当前的程序状态，然后跳转到中断处理程序进行处理。

### The advantage of carry-lookahead adder is___. 

A.   Optimize the structure of the adder

B.   Save hardware parts

C.   Accelerate the generation of the carries

D.   Augment the structure of the adder

**答案**：C。

### In microprogram-controlled machines, the relationship between the machine instruction and the microinstruction is____. 

A.   a machine instruction is executed by a microinstruction

B.    a microinstruciton is composed of several machine instructions

C.    a machine instruction is interpreted by a microroutine composed of microinstructions

D.    a microroutine is executed by a machine instruction

**答案**：C。

### Once the DMA controller obtains access to the system bus, it transfers one byte of data and then returns the control of system to the processor. This DMA transfer mode is___C__. 

A.   Burst Mode                   C.  Cycle Stealing Mode

B.    Block Mode                  D.  Transparent Mode

**答案**：C。

与周期窃取模式的特征相同。

### Assume that the capacity of a kind of SRAM chip is 16K×32, so the sum of address lines and data lines of this chip is_A_. 

A.   48            B.  46            C.  36            D.  32

**答案**：A。

$log_2 16K+32=48$。

### Assume that the multiplicand is 110011 and the multiplier is 101110. If multiply them using the Booth algorithm, then the Booth recoding multiplier is_C_. 

A.   – 1 – 1 0 0 – 1 0               C.  – 1 + 1 0 0 – 1 0 

B.    + 1 – 1 0 0 + 1 0             D.   1 + 1 0 0 – 1 0

**答案**：C。按照布斯算法进行计算即可。

### The microroutines for all instructions in the instruction set of a computer are stored in the  C  .

A.   memory controller              C.  control store        

B.    main memory                 D.  cache

**答案**：C。

### ___ is the process by which the next device to become the bus master is selected and bus mastership is transferred to it. 

A.   Bus protocol                   C.  Bus timing

B.    Bus arbitration                 D.  Bus transceiver

**答案**：B。总线仲裁是指选择下一个将成为总线主控设备的过程，并将总线控制权转交给它。总线仲裁机制确保多个设备能够公平地共享总线资源，避免冲突并控制总线的访问权。

### ___ has/have external fragmentation problem.

A.   Paging                C. Segmentation with paging

B.    Segmentation           D. Segmentation and segmentation with paging

**答案**：B。

分段（Segmentation）存在外部碎片问题，因为每个段可能有不同的大小，当系统分配内存时，可能会出现空闲内存区域无法完全适应某个段的情况，从而导致外部碎片。

而**分页**和**分页结合分段**则通过固定大小的页面来管理内存，通常没有外部碎片问题，尽管它们可能会产生内部碎片。

### The range and accuracy of floating-point numbers depend on __ respectively. 

A.   The size of exponent and the representation of mantissa

B.    The size of exponent and the size of mantissa

C.    The size of mantissa and the representation of exponent

D.   The size of mantissa and the size of exponent

**答案**：A。

### In a synchronous bus, controlling of data transfer on the bus is based on __A__. 

A.   a common clock signal only

B.    a handshake signal only

C.    both clock signal and handshake signal

D.   either clock signal or handshake signal

> 在同步总线（synchronous bus）中，数据传输是由一个公共时钟信号（common clock signal）来控制的。设备在时钟信号的边沿（上升沿或下降沿）进行同步操作，比如在时钟信号的某个边沿进行数据的发送和接收。
>
> 而异步总线（asynchronous bus）主要是依靠握手信号（handshake signal）来控制数据传输，因为没有公共时钟来同步设备，设备之间需要通过请求、响应等握手信号来协调数据传输的开始和结束。
>
> 同步总线是严格按照时钟信号来进行数据传输控制的，不依靠握手信号来进行基本的数据传输控制。
>

### Which one of the following is not used to prevent data hazards? __D__

A.   Bypassing

B.    Forwarding

C.    Stall

D.   Freeze or Flush

正确答案是：

**D. Freeze or Flush**

**Freeze** 或 **Flush** 主要用于控制和处理中断、异常、或者不必要的指令的清除，而不是直接用于防止数据冒险（Data Hazards）。

数据冒险是指在流水线执行过程中，由于指令之间存在数据依赖关系，可能导致错误或延迟。为防止数据冒险，常用的技术包括：

- **A. Bypassing** 和 **B. Forwarding**：这两者用于将数据从流水线的一个阶段直接传递到另一个阶段，以避免等待数据的传递。
- **C. Stall**：通过插入气泡（stall cycles）来暂停流水线，直到数据可用，以避免数据冒险。

因此，**Freeze** 或 **Flush** 主要涉及控制流水线状态，而不是直接解决数据冒险问题。



## 二、选择题

### What is the difference between DRAM and SRAM, in terms of characteristics such as speed, size, cost and application? 

Solution:
DRAM：速度较慢，密度高，成本低，一般用于实现高速缓存
SRAM：速度快，密度低，成本高，一般用于实现存储器

**速度**

  - SRAM快，数据访问时间通常在10纳秒以下，因为用双稳态触发器存储数据。
  - DRAM相对慢，数据访问时间一般在几十纳秒左右，因其基于电容存储，且读取写入涉及复杂过程。

**尺寸**

  - SRAM存储单元电路复杂，存储密度低，相同面积下存储数据量少。
  - DRAM存储单元结构简单，存储密度高，能在较小面积存储大量数据。

**成本**
  - SRAM高，因电路复杂、存储密度低，制造材料和工艺要求高。
  - DRAM低，存储单元结构简单、存储密度高，大规模生产价格亲民。

**应用**

  - SRAM用于对速度要求极高的地方，如CPU高速缓存、小型嵌入式系统。
  - DRAM是计算机主存主要成分，也用于GPU显存等大容量存储设备。



### In what circumstance will arithmetic overflow occur when two integers represented by 2's complement form are added? And write out the logic expression to detect overflow.

**Solution:**

当两个操作数的符号（减法转换为加法处理）与得到的结果符号不同时，会产生溢出。

可以根据这个得到表达式：
$$
overflow &= x_ny_n \overline{s_n} + \overline{x_n} \ \overline{y_n} s_n \\
overflow &= c_n \oplus c_{n-1}
$$




### Describe the process of interrupt processing. 

**Solution:**

1. **中断请求**：外部设备或内部事件通过中断请求线向CPU发送信号，请求CPU处理紧急事务。
2. **中断响应**：CPU在当前指令周期结束后检查请求，若符合条件则暂停当前程序，保存上下文后发送响应信号。
3. **中断识别**：通过查询中断向量表或中断控制器确定中断源。
4. **中断服务程序执行**：CPU跳转到对应的中断服务程序入口，执行程序处理中断事件。
5. **中断返回**：中断服务程序执行完后，CPU恢复被中断程序的上下文并继续执行。



## 三、综合题

### Using nonrestoring division algorithm, perform the operations A÷B on the 5-bit unsigned numbers A= 10101 and B= 00101. Write the computation processes in a computer machine.

**Solution:** 

手写答案，字丑见谅。

**不恢复除法的流程**：

- 一开始：M代表除数，Q代表被除数。

- 最后A表示余数，但是需要进行恢复操作：和除数相加。

- Q最后表示商。

- 每一轮开始时，先进行左移，此时最低位为空

  如果此时A大于等于0，那么执行减法，否则执行加法。

  如果计算后A>0，那么最低位设置为1，否则设置为0。

- 一共执行$n$轮，这里对应的是被除数的位数。

**恢复除法的流程**：和不恢复除法类似

- 一开始：M代表除数，Q代表被除数。

- 最后A表示余数，Q表示商。但是不用进行恢复。

- 每一轮开始时，先进行左移，此时最低位为空。

  然后执行减法，A=A-M。

  如果A大于等于0，最低位设置为1。

  否则进行恢复操作，A = A + M，最低位设置为0。

- 一共执行$n$轮，这里对应的是被除数的位数。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412242023952.webp)

### A byte-addressable computer has 16 address lines, 8 data lines, $\overline{WR}$ signal (read/write control signal) and $\overline{MREQ}$ signal (access memory control signal). Its address space includes:

### a)    system program area ranging from 0 to 8191(decimal)

### b)    user program area ranging from 8192 to 32767(decimal)

### c)    and the last 2K address space for system program working area

### There are some memory chips: 

### ROM: 8K×8

### SRAM: 16K×1, 2K×8, 4K×8, 8K×8

### (1)  Please specify how many chips to select to design the main memory of the computer.

### (2)  Draw the logic structure figure of the main memory, and the connection between the main memory and CPU.

**Solution**:

注意：系统程序区是由ROM组成的。其余的是由RAM组成。

后续复习再做。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412270959684.webp)



### Consider a computer with 4M×16 memory contains 97 instructions in its instruction set. The opcode length is fixed, and the addressing modes are direct, indirect, immediate, index, and relative. (Assume that the instruction length equals to word length) 

### (1)Draw the figure of one-address instruction format, and specify the function of each field.

### (2)Specify the max range of the direct addressing mode. (in decimal)

### (3)Specify the addressing range of one-level indirect addressing mode. (in decimal)

### (4)Specify the offset of the relative addressing mode. (in decimal)

Solution: 

### （1）绘制一地址指令格式图并说明各字段功能
- **指令格式图**：
已知计算机的存储器规格为 $4M×16$，这意味着存储容量为 $4M$（$4×2^{20}$个存储单元），字长为 $16$ 位，而指令集中包含 $97$ 条指令，操作码长度固定。
由于 $2^7 = 128\gt 97$，所以操作码（opcode）字段用 $7$ 位即可表示所有指令。另外由于5种寻址方式，所以剩余的 $16 - 7 - 3 = 6$ 位用于地址相关信息，可绘制一地址指令格式如下：

| 操作码（opcode） | 寻址方式（addressing mode） | 地址码（address） |
| :---: | :---: | ----- |
| 7 位 | 3 位 | 6 位 |

- **各字段功能说明**：
    - **操作码（opcode）字段**：其主要功能是用来唯一标识指令集中的不同指令。通过这 $7$ 位的不同二进制编码组合，可以确定具体要执行的是哪一条指令，例如是执行加法运算、数据读取还是跳转等操作。
    - **寻址方式（addressing mode）子段**：用于确定是哪一种寻址方式。
        - 000表示直接寻址方式
        - 001表示间接寻址方式
        - 010表示立即寻址方式
        - 011表示变址寻址方式
        - 100表示相关寻址方式
    - **地址码（address）字段**：它所承载的功能与寻址方式紧密相关。在不同的寻址方式下有不同的作用：
        - **直接寻址方式**：地址码字段直接给出操作数在主存储器中的实际地址，处理器依据此地址就能直接访问到对应的操作数存储单元。
        - **间接寻址方式**：地址码字段存放的是操作数地址的地址，即先通过该地址找到存放真正操作数地址的存储单元，再从该单元获取操作数地址，进而访问操作数。
        - **立即寻址方式**：地址码字段本身就作为操作数参与运算，它直接就是指令要操作的数据。
        - **索引寻址方式**：地址码字段通常与一个特定的索引寄存器内容相结合，共同确定操作数的地址，例如将索引寄存器的值与地址码字段的值进行某种运算（如相加）来得到最终的操作数地址。
        - **相对寻址方式**：地址码字段的值表示相对于当前指令地址的偏移量，结合当前指令所在地址来确定操作数或转移目标地址等。

### （2）指定直接寻址方式的最大范围（十进制）
在直接寻址方式中，地址码字段的位数决定了其可表示的地址范围。此处地址码有 $6$ 位，它所能表示的地址数量是 $2^6$ 个，对应的地址范围是从 $0$ 到 $2^6 - 1$。计算可得：

$$
2^6 - 1 = 64 - 1 = 63
$$
所以直接寻址方式下能直接访问的主存储器地址范围是 $0$ 到 $63$（十进制）。

### （3）指定一级间接寻址方式的寻址范围（十进制）
在一级间接寻址方式中，首先通过地址码字段（ $6$ 位）来获取一个存储单元的地址，该地址码可表示的范围是 $0$ 到 $2^6 - 1$，也就是能指向 $64$ 个不同的存储单元。

因为存储器字长为 $16$ 位，在这些存储单元中存放的内容被当作操作数地址（假设按字长存放地址信息），而 $16$ 位地址所能表示的最大地址空间为 $2^{16}$ 个存储单元。

所以一级间接寻址方式可寻址的范围是 $0$ 到 $2^{16} - 1$，经计算：

$$
2^{16} - 1 = 65536 - 1 = 65535
$$


即一级间接寻址方式能访问的主存储器地址范围是 $0$ 到 $65535$（十进制）。

### （4）指定相对寻址方式的偏移量（十进制）
对于相对寻址方式，地址码字段同样是 $6$ 位。由于是相对偏移量，采用有符号数表示，其范围是用补码形式来确定的，可表示的范围是从$-2^{6}$ 到 $2^{6} - 1$ 。计算如下：
$$
- 2^{6} = - 64 \\
2^{6} - 1 = 64 - 1 = 63
$$
所以相对寻址方式的偏移量范围是 $ - 64$ 到 $63$（十进制），意味着可以相对于当前指令地址向前（地址减小方向）偏移 $64$ 个存储单元或者向后（地址增大方向）偏移 $63$ 个存储单元去定位操作数或者转移目标等。 实际情况还有考虑当前指令的地址，加上偏移量后是否会超出地址空间范围。

