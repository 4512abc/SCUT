# Ch8

## 内存系统基本概念

### Internal Memory and External Memory（内部存储器和外部存储器）

典型的计算机系统配备有层次结构的存储器子系统。

**Internal Memory (Primary Storage)**：系统内部，可由处理器直接访问。

一般常见的例子有：主存、高速缓存、处理器寄存器（Main Memory, Cache, Processor Registers）

**External Memory (Secondary Storage）**：系统外部，可由处理器通过 I/O 模块访问。



### Memory Locations and Addresses（内存位置和地址 ）

**主存组织**

- 存储器由数百万个存储单元组成，每个存储单元可以存储一位值为 0 或 1 的信息。

- 我们可以想象主存储器被组织为位矩阵。 存储器的组织方式使得可以在单个基本存储器操作中存储或检索一组固定大小的位。
- 字：每组固定大小的位称为一个字。
- 字长：每个字中的位数称为字长。它的范围通常为 16 到 64 位。
- 计算机的内存可以形象地表示为字的集合。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409271110048.webp)



**地址和地址空间**

- 地址是标识内存字的数字。

- 对于某个合适的 k 值，通常使用 $0$ 到 $2^k-1$ 之间的数字作为存储器中连续位置的地址。

- $2^k$个地址构成了计算机的地址空间，内存最多可以有$2^k$个可寻址位置。 

- 例子：

  24 位地址生成 $2^{24}$ 或 16M 个位置的地址空间。

  32 位地址创建 $2^{32}$ 或 4G 位置的地址空间。



**字节寻址存储器**

- 将不同的地址分配给存储器中的各个位位置是不切实际的。
- 最实际的分配是让连续地址引用存储器中的连续字节位置。



### Byte Ordering（字节顺序）

分为大端法和小端法。

**大端法（从左到右）**

- 在此分配中，较低字节地址用于字的较高有效字节（最左边的字节）。

​	![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409271116459.webp)

**小端法（从右到左）**

- 在此分配中，较低字节地址用于字的较低有效字节（最右边的字节）。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409271120225.webp)



> **从0x1000-0x1001是一个字节**。
>
> 假设我们有一个 4 字节的整数值 `0x12345678`，在不同的字节序中存储方式如下：
>
> ### 大端法 (Big-endian)：
>
> 内存中的布局如下：
>
> | 地址   | 内容 |
> | ------ | ---- |
> | 0x1000 | 0x12 |
> | 0x1001 | 0x34 |
> | 0x1002 | 0x56 |
> | 0x1003 | 0x78 |
>
> 大端法将高位字节 `0x12` 存储在最低地址 `0x1000`，接着依次存储低位字节。
>
> ### 小端法 (Little-endian)：
>
> 内存中的布局如下：
>
> | 地址   | 内容 |
> | ------ | ---- |
> | 0x1000 | 0x78 |
> | 0x1001 | 0x56 |
> | 0x1002 | 0x34 |
> | 0x1003 | 0x12 |
>
> 小端法将低位字节 `0x78` 存储在最低地址 `0x1000`，接着依次存储高位字节。



### Main Memory Operations（主内存操作）

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409271123803.webp)

> 这张图展示了**处理器与内存之间的连接**，通常称为**处理器-内存接口**。这是计算机系统中处理器与主存之间数据交换的基本模型。
>
> ### 主要组成部分和含义：
>
> 1. **k-bit地址线（Address lines）**：
>    - 地址线用于处理器访问内存中的不同存储单元。图中表示为 `k-bit address`，表示处理器通过 `k` 位地址总线来**选择内存中的一个位置**。总共有 \( $2^k$ \) 个可寻址位置，也就是内存的地址空间。
>    - 例如，如果 `k=32`，那么内存可以寻址的范围为 \( $2^{32}$ \) 个不同的存储单元。
>
> 2. **n-bit数据线（Data lines）**：
>    - 数据线用于传输处理器和内存之间的实际数据。图中表示为 `n-bit data`，表示一次可以传输 `n` 位的数据。这个 `n` 位数据也被称为**字长（Word length）**，表示每次从内存中读或写的数据位数。
>    - 常见的字长为 8 位、16 位、32 位或 64 位。
>
> 3. **控制线（Control lines）**：
>    - 控制线用于**处理器发出对内存的控制信号，如读取（Read）或写入（Write）操作**。控制线包括 **R/W（读/写）** 信号以及其他控制信号，用来指定处理器是要从内存读取数据还是将数据写入内存。
>
> 4. **内存（Memory）**：
>    - 图中内存模块标示了 `Up to `$2^k$` addressable locations`，表示内存有最多 \( $2^k$ \) 个地址可供访问。每个位置的字长为 `n-bit`。
>    - 这个模块表示处理器可以通过地址总线选择特定的存储位置，并通过数据总线传递数据。
>
> ### 图的整体工作原理：
> - **地址选择**：处理器通过 `k-bit` 地址总线选择内存中的一个存储单元。
> - **数据传输**：处理器与内存之间通过 `n-bit` 数据总线交换数据，可能是读取或写入。
> - **控制信号**：控制线决定处理器的操作是读取内存数据还是向内存写入数据。
>
> 这个模型展示了处理器与内存如何通过**地址总线**、**数据总线**和**控制总线**相互连接与通信。



![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409271125134.webp)

> 这张图展示了**处理器与内存接口（Processor-Memory Interface）**的工作机制，它进一步细化了处理器内部的关键组件，以及这些组件如何通过接口与内存进行交互。我们可以通过几个关键部件来理解这个图：
>
> ### 主要组成部分：
>
> 1. **Memory（内存）**：
>    - 内存与处理器通过多个数据总线和控制线相连。处理器可以通过这些总线从内存中读取数据或向内存写入数据。
>
> 2. **MAR（Memory Address Register，内存地址寄存器）**：
>    - **MAR** 用于存储将要访问的内存地址。当处理器需要访问内存时，会先将要访问的地址存储到 **MAR** 中，之后通过地址总线发送给内存，以确定具体的存储单元。
>
> 3. **MDR（Memory Data Register，内存数据寄存器）**：
>    - **MDR** 是用来存储从内存中读取的或者即将写入内存的数据。当处理器从内存读取数据时，数据会先存储到 **MDR**，然后供处理器使用。反之，写数据时，处理器会先把数据存储到 **MDR**，再通过数据总线传送到内存。
>
> 4. **PC（Program Counter，程序计数器）**：
>    - **PC** 保存着下一条将要执行的指令的地址。在每执行完一条指令后，程序计数器会自动更新为下一条指令的地址。
>
> 5. **IR（Instruction Register，指令寄存器）**：
>    - **IR** 存储当前正在执行的指令。当处理器从内存中取出一条指令时，会先存放在 **IR** 中，然后由控制单元进行解码和执行。
>
> 6. **General Purpose Registers（通用寄存器）**：
>    - 通用寄存器用于存储处理过程中临时的数据或操作数，如图中的 `R0`, `R1`, `R2` 等。这些寄存器使得处理器可以快速访问需要频繁操作的数据，而不用每次都访问内存。
>
> 7. **Control（控制单元）**：
>    - 控制单元**负责协调和管理处理器内各组件之间的操作**。它通过解码指令来控制数据流向、内存访问、以及执行指令的步骤。
>
> 8. **ALU（Arithmetic Logic Unit，算术逻辑单元）**：
>    - **ALU** 是处理器中执行算术运算和逻辑运算的核心组件。它从寄存器中获取操作数，并执行如加法、减法、逻辑与、或等操作。
>
> ### 工作过程：
> 1. **取指阶段**：
>    - 程序计数器 **PC** 保存下一条要执行指令的地址，地址被送入 **MAR**，并通过地址总线发送到内存。
>    - 内存根据该地址返回指令，并将其存入 **MDR**。
>    - 从 **MDR** 中读取指令并存入 **IR**，控制单元会对 **IR** 中的指令进行解码。
>
> 2. **执行阶段**：
>    - 解码后的指令会指示 **ALU** 从通用寄存器中获取操作数，并执行相应的运算。
>    - 运算结果可能存储在通用寄存器中，或通过 **MDR** 写回内存。
>
> ### 总结：
> 这幅图展示了处理器与内存之间的数据流动过程，以及处理器内部各个关键组件的相互作用。处理器通过 **MAR** 和 **MDR** 与内存进行地址和数据的传递，通过 **PC** 和 **IR** 控制指令的获取和执行，通过 **ALU** 完成实际的算术与逻辑运算，所有这些操作由控制单元进行协调和管理。



**Read (Load) Operation（读（加载）操作）**

- 将特定内存位置的内容副本传输到处理器。
- 处理器：将所需内存位置的地址加载到 MAR 寄存器中，并将 R/W 线设置为 1。 
- 内存：将寻址位置中的数据放置到数据线上，**并通过置位 MFC 信号来确认此操作**。 
- 处理器：收到 MFC 信号后，处理器将数据线上的数据加载到 MDR 寄存器中。



**Write (Store) Operation（写（存储）操作）**

- 将信息项从处理器传输到特定位置，销毁该位置以前的内容。
- 处理器：将特定位置的地址加载到MAR中，并将数据加载到MDR寄存器中。它还将 R/W 线设置为 0。 
- 内存：**当数据写入后，它用 MFC 信号响应处理器**。



### Characteristics of Memory Systems（内存系统的特点）

- 物理类型

  - 半导体：主内存
  - 磁性表面：磁带和磁盘
  - 光学材料：CD、CD-R、CD-RW、DVD、蓝光

- 容量

  对于主存来说，通常用字大小和字数来描述容量。

  **字大小**

  -  Number of bits in natural unit of organization	

    自然组织单位的位数

  - The common word size is 8-bits, 16 bits, 32 bits and 64 bits.

    常见的字长有8位、16位、32位和64位。

  **字数**

  - 指定特定存储设备中可用的字数。

- 传输单位

  指的是**一次从内存中读取或写入内存的位数。**

  分为两种情况：内存和外部存储器。

  内存：

  - 通常等于进出内存模块的数据线数量。
  - 它通常等于字长的数量，但也可能不是。

  外部存储器：

  - 数据通常以比字大得多的单位传输，这些单位称为块。

- 访问方法

  顺序存取：

  - 内存被组织成数据单元，称为记录。如果当前记录为1，则为了读取记录N，需要读取记录1到N-1。
  - 访问任意记录的时间变化很大。示例：磁带

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412062035319.webp)

  随机存取：

  - **可以随机选择任何存储位置并直接寻址和访问。**
  - 访问给定位置的时间与该位置的地址无关并且是恒定的。示例：半导体 RAM 存储器

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412062036257.webp)

  直接访问：

  - 各个块或记录具有基于物理位置的唯一地址。
  - 访问是通过**直接访问到达大致附近加上顺序搜索、计数或等待到达最终位置**来完成的。
  - 访问时间是可变的。示例：磁盘

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412062036357.webp)

- 性能
  
  内存访问时间：
  
  - 呈现**地址和获取有效数据（内存或其他存储）之间的时间**
  - 对于随机存取内存：**执行读或写操作所需的时间**。
  - 对于非随机存取存储器：将读写机制定位到**所需位置所需的时间**。
  
  内存周期时间：
  
  - 仅适用于随机存取存储器（Random Access Memory，RAM）。它用于衡量这种存储器的一个特性。
  - 从一次内存访问开始，到下一次内存访问开始之间的时间间隔。这其中包含了访问时间，以及在能够开始下一次访问之前所需的额外时间。
  - 内存周期时间等于内存访问时间加上恢复时间（Memory Cycle Time = Memory Access Time + Recovery Time）。
  - 访问时间和内存周期时间都是用于衡量内存单元速度的指标，它们从不同角度反映了内存的性能。访问时间侧重于一次访问的耗时，而内存周期时间考虑了两次访问之间的整体间隔。
  
  传输速率：定义为数据传入或传出内存单元的速率。
  
- 物理特性
  挥发性/非挥发性：
  
  - 易挥发的：当电源关闭时，信息会自然衰减或丢失。 
  - 非易失性：信息一旦记录，就不会变质，直到被故意更改为止。不需要电力来保留信息。
  - 示例：磁性表面存储器是非易失性的。半导体存储器可以是易失性的或非易失性的。
  
  可擦除/不可擦除：
  
  - 可擦除：存储器的内容是可以改变的。 
  - 不可擦除：除非破坏存储单元，否则无法更改存储器的内容。
  
  
  

​	   

## Semiconductor Static RAM（半导体静态RAM）

### RAM Technology（内存技术）

静电技术：在静态 RAM 中，二进制值使用传统的触发器逻辑门配置来存储。

动态技术：动态 RAM 由将数据存储为电容器电荷的单元组成。电容器中是否存在电荷被解释为二进制 1 或 0。



### SRAM Cell（静态RAM单元）

**SRAM单元的实现**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291102946.webp)

维持状态：字线处于第电平。

假设改该单元处于**state 1**（也就是高电平）,那么`X`是位于**state 1**，`Y`是位于**state 0**

**注意**：竖线指的是位线，横线指的是字线。

字线像是开关，位线负责运输数据，进行读取或者写入。



**操作**

分为**读操作和写操作**。

- 读操作

  - 字线处于高电平状态。

  - 读取“1”时，将$b$线置于高电平，$b^{'}$置于低电平。

  - 读取”0“时，将$b$线置于低电平，$b^{'}$置于高电平。

  - **注意**：感测/写入电路位于末尾，位线监视 $b$ 和 $b'$ 的状态并相应地设置输出。

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291107674.webp)

- 写操作

  - 字线位于高电平状态。

  - 写入“1”：在位线 $b$ 上放置高电平信号，在位线 $b'$ 上放置低电平信号。

  - 写入“0”：在位线 $b$ 上放置低电平信号，在位线 $b'$ 上放置高电平信号。

  - **注意**：位线上所需的信号由感测/写入电路生成。

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291108217.webp)



**使用CMOS门电路实现SRAM**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291108761.webp)

- 较旧的 CMOS SRAM 中的电源电压为 5V，新的低电压版本中的电源电压为 3.3V。
- 如果电源中断然后恢复，锁存器将进入稳定状态，但不一定与中断前单元的状态相同。
- CMOS SRAM 的功耗非常低。
- 优点：速度快。
- 缺点：密度低，成本高。



### Organization of SRAM Chips（SRAM芯片的组织）

#### 128位单元的组织实现（16 * 8）

- 内部组织：

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291126883.webp)
  
  - 字线：一行的所有单元都连接到字线。它由地址译码器驱动。
  - 位线：每列中的单元通过两条位线连接到感测/写入电路。
  - 读出/写入电路：
    - 读：负责读取存储在单元中的信息，（单元格是由字线选择的），并且将信息传输到输出数据线上。
    - 写：负责接收信息，并且将信息存储在**被选中的字**的单元格中。
  
- 外部组织：

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291422333.webp)

  - 地址线（输入）：`A0-A3`。

  - 数据线（输入/输出）：`B0-B7`。

  - 控制线（输入）：

    - R/W（读/写）：用于指定需要的操作。
    - CS（芯片选择）：在多芯片存储器系统中选择给定的芯片。

  - 电源线

  - 地线

  - 总连接数：`4 + 8 + 2 + 1 + 1 = 16`

    

    

    

    

#### 1024位单元的组织实现（1K * 1）

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291429176.webp)

- 外部组织：
  - 地址线（输入）：`A0-A9`。
  - 数据线（输入/输出）：`B0`。
  - 控制线（输入）：`R/W、CS`
  - 电源线
  - 地线
  - 总连接数：`10 + 1 + 2 + 1 + 1 = 15`。 

  

## Semiconductor Dynamic RAM（半导体动态随机存储器）

### Dynamic RAM (DRAM) Cell（动态随机存储器单元）

**DRAM单元的实现**：信息是以电荷的形式存储在电容器`C`上的。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291437911.webp)

**操作**：分为读操作和写操作。

- 读操作：字线处于**state 1**，也就是高电平状态。

  读取 “1”：如果存储在电容器上的电荷**高于阈值，那么感测放大器将会驱使位线**

  **到满电压状态，用于表示1**。该电压将电容器再充电到对应于 “1” 的满电荷状态。

  读取 “0”：如果电容器上存储的电荷**低于阈值，则读出放大器将位线拉低值低电平状态，这将确保电容器中没有电荷**。对于的表示 “0” 状态。

- 写操作：字线处于**state 1**，也就是高电平状态。
  **写入 “1”：位线被施加高电压**
  **写入 “0”：位线被施加低电压**
  
- 维护状态：将字线置于**state 0**，也就是低电平状态。

- 缺点：更长的访问时间，并且容易泄露电荷，需要刷新状态。



### Organization of DRAM Chips（DRAM芯片的组织）

#### 256M位单元（32M × 8）的组织

这里是实现为16K * 16K 的阵列，所以一共16行，一行的一组是8位，所以是2048列。

对应的，$2^{14}=16K$选择一行，$2^{11}=2048$选择一列。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291452403.webp)



- 需要14位地址来选定一个行。
- 需要另外的11位来指定运行行中的8位组。总计需要25位地址。
- 为了减少外部连接需要的引脚，行和列地址再14个引脚上进行了多路复用。
- 行地址选通（又称为$\overline{RAS}$）
- 列地址选通（又称为$\overline{CAS}$）



### Synchronous DRAM （同步DRAM）

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291512803.webp)

- SDRAM的操作直接与时钟信号同步，上图是其结构。

- 突发操作：

  - SDRAM有记作不同的操作模式，可以通过将控制信息写入模式寄存器来选择。

  - 突发操作使用块传输能力。

  - 模式寄存器保存一个`12`位的值，SDRAM查看该值以确定应突发多少列以及应以何种顺序突发这些列。

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291515831.webp)

- 延迟和带宽：

  - 延迟和带宽是指示存储器系统的性能的两个参数。
  - 延迟：延迟是指将一个字的数据传输到内存或从内存传输一个字所需的时间。**注：在块传输中，延迟用于表示传输第一个数据字之前的时间。**
  - 带宽：一秒钟内可以传输的比特或字节数称为带宽。
    - 单位：比特每秒或字节每秒。
    - 存储器单元的带宽取决于**访问存储数据的速度和可以并行访问的位数。**
    - 有效带宽还取决于**连接内存和处理器的链路的传输能力。**
    - 有效带宽=总线速度×总线宽度

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291516810.webp)

- Double-Data-Rate SDRAM (DDR SDRAM)（双倍数据速率SDRAM）

  - 它以与SDRAM相同的方式访问单元阵列，但在时钟的两个边沿传输数据。
  - 这些设备的延迟与标准SDRAM相同，并且对于长突发传输，其带宽基本上加倍。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291522143.webp)

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291523721.webp)

  

## Structure of Larger Memories（大规模存储器的结构）

### Static Memory System（静态存储系统）

**位扩展法**：

- 芯片的每个存储单元的位数小于存储器字长时，需要进行位扩展。

- 例：用1M×1位存储芯片组成1M×8位（1MB）的存储器

  - 共需8片1M×1位的芯片，每片存储同一位权的一位数据(片的`I/O`端接$D_i$)
  - 访问芯片需要20位地址码：$A_{19}-A_0$。
  - 读写控制信号：$R/\overline{W}$。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291542831.webp)

  

**字扩展法**：

- 芯片每个存储单元的容量相当于存储器字长，但容量(字数)不够，需要进行字扩展。

- 示例：用256K×8位芯片组成1M×8的存储器

  - 共需1M/256K=4片256K×8位芯片。
  - 1MB容量需20位片内地址码($A_{19}-A_0$) ，而256KB芯片需18位片内地址码($A_{17}-A_0$)。
  - 使用高二位地址$A_{19}A_{18}$经2:4译码器选择芯片读/写
  - 每片8条`I/O`线分别接$D_7-D_0$。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291552137.webp)



**字位同时扩展法**

- 单片芯片的字数和位数均小于主存的容量要求，需进行字、位的扩展。
- 例：用`512K×8`位的存储器芯片组成`2M×32`位的存储器
  - 共需要$\frac{2 \times 1024}{512} \times \frac{32}{8}=4 \times 4=16$片`512K × 8`位的芯片，组成`4×4`的阵列。
  - `2M×32`容量需21位片内地址码($A_{20}-A_0$) ，而512KB芯片需19位片内地址码($A_{18}-A_0$)。
  - 使用高二位地址$A_{20}A_{19}$经2:4译码器选择一行芯片读/写
  - 每片8条`I/O`线分别接$D_7-D_0$。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291559940.webp)



**结论：假设存储单元的容量为M×N位，若采用l×k位芯片构成，则总共需要的芯片数量为(M/l)×(N/k)。**

  

### Dynamic Memory System（动态内存系统）

- 大型动态内存系统的组织方式本质上与上述静态内存系统相同。

- 包装：内存模块

  内存模块：在接入到计算机主板插座上的小型板上组装内存芯片。

  （原话：Assembly memory chips on a small board that plugs into a socket on the computer’s motherboard）

  - SIMM（单列直插内存模块）
  - DIMM（双列直插内存模块）

- SIMM：SIMM 是一种基本的 DRAM 封装类型，适合大多数旧系统。

  - SIMM 可以是单面的（仅一侧有 RAM 芯片）或双面的（两侧都有 RAM 芯片）。
  - 30针SIMM：1-16MB； 8 位；加 1 位用于奇偶校验；单面。
  - 72针SIMM：1MB、4MB、16MB（单面）； 2MB、8MB、32MB（双面）； 32 位，加上 4 位用于奇偶校验/ECC。
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291606333.webp)
  
- DIMM：DIMM是目前内存封装的最标准形式。

  - DIMM 能够一次传送 64 个数据位。 
  - 最常见的 DIMM 类型如下：
    - 72针、144针、200针DIMM：用于SO-DIMM（小型DIMM）。
    - 168 针 DIMM，用于 FPM（快速页模式）DRAM、EDO（扩展数据输出）DRAM 和 SDRAM。
    - 184针DIMM，用于DDR SDRAM。
    - 240 针 DIMM，用于 DDR2 和 DDR3 SDRAM。
    - 284针DIMM，用于DDR4 SDRAM。
    - 288针DIMM，用于DDR5 SDRAM。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291610359.webp)



- 实际样例：

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291611124.webp)

  快速计算内存空间大小方法：

  以系统程序区为例子：$(3FFF)_H-(0000)_H+1=(4000)_H$。
  
  转化为二级制$0100\ 0000\ 0000\ 0000$，可以得到是$16K=16 \times 2^{10}$。
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291611650.webp)
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202409291611465.webp)



## 

## 练习

### The memory is organized so that a group of n bits can be stored or retrieved in a single, basic operation. n is called the . 

A. word 	B. word length 	C. address 	D. cell



**答案：B**。



### The 32-bit value 0x30A79847 is stored to the location 0x1000. If the system is little endian, the value of the byte  is stored in address 0x1002. 

A. 0x30 	B. 0xA7 	C. 0x98 	D. 0x47 



**答案：B**。

Because the higher byte addresses are used for the more significant bytes (the rightmost bytes) of the word, so 0x30 is stored in 0x1003, 0xA7 is stored in 0x1002, and so on.

| 0x1000 | 0x1001 | 0x1002 | 0x1003 |
| ------ | ------ | ------ | ------ |
| 0X47   | 0X98   | 0XA7   | 0X30   |



### In a main memory, its word size is 16, the number of word is 8K, what is the capacity of this main memory?

A. 16K×16 	B. 16K×8 	C. 8K×16 	D. 8K×8

**答案：C。**



### For random access memory, the time it takes to perform a read or write operation is called . 

A. memory cycle time 	C. memory recovery time 	B. memory hit time 	D. memory access time



**答案：D**。



### Memory in which any location can be reached in a short and fixed amount of time after specifying its address is called . 

A. direct access memory 

C. associative access memory 

B. sequential access memory 

D. random access memory



**答案：D。**



### If you turn off the power to the computer, items stored on  device will be lost. 

A. RAM 	B. disk 	C. DVD 	D. CD-ROM



**答案：A**



### True or False? For internal memory, data are often transferred in much larger units than a word, and these are referred to as blocks.



**答案：False**。

实际上是外部设备中，数据以大于一个字的方式进行传输，通常被称为块。



### True or False? Memory access time is longer than memory cycle time.

**答案：False。**

存储器周期时间是从当前访问存储器到下一次访问存储器所花费的时间，而存储器访问时间是从提供存储器地址到获取数据所花费的时间。两者之间的关系：Memory Cycle Time = Memory Access Time + Recovery Time



### What is memory access time? What is memory cycle time? Explain the relationship between them. 

**答案：**Memory access time is time between presenting the address and  getting the valid data. Memory cycle time is time from a memory access to the next memory access. Their relationship is Memory Cycle Time = Memory Access Time + Recovery Time. 



### Assume that the capacity of a kind of SRAM chip is 8K×16, so the address lines and data lines of this chip are  respectively. 

A. 8,16 	B. 13,16 	C. 13,4 	D. 8,4



**答案：B**。



### Assume that the capacity of a kind of SRAM chip is 32K×32, so the sum of address lines and data lines of this chip is . 

A. 47 	B. 64 	C. 46 	D. 74



**答案：A**。



### What are the advantage and disadvantage of SRAM? 

- Advantage: Fast 

- Disadvantage: Low density, High cost



### Comparing to SRAM, the main advantage of DRAM is . 

A. high speed 

B. non-volatile stored data 

C. high density 

D. easily controlled



**答案：**

**C. high density**

**SRAM 与 DRAM 的区别：**

1. **SRAM（静态随机存取存储器）：**
   - 不需要刷新，速度较快，但每个存储单元由多个晶体管组成，因此密度较低，成本较高。
2. **DRAM（动态随机存取存储器）：**
   - 需要定期刷新，但存储单元由一个晶体管和一个电容组成，结构简单，能够在相同面积内容纳更多存储单元，因此密度更高，成本更低。

**选项分析：**

- **A. 高速度（High speed）：**
   SRAM 的速度比 DRAM 快，因此该选项错误。
- **B. 非易失性存储数据（Non-volatile stored data）：**
   DRAM 和 SRAM 都是**易失性存储器**，断电后数据都会丢失，因此该选项错误。
- **C. 高密度（High density）：**
   DRAM 的存储密度更高（因为其存储单元结构简单），这是 DRAM 的主要优点，正确答案。
- **D. 易于控制（Easily controlled）：**
   SRAM 的控制相对更简单，而 DRAM 需要复杂的刷新电路，因此该选项错误。



### What are advantages and disadvantages of DRAM?

优点：高密度，成本低

缺点：电容漏电，访问时间慢，需要刷新。





### 某一动态RAM芯片，容量为64K×1，除电源线、接地线和刷新线外，该芯片的最少引脚数目应为多少？

$64K=2^{16}$，由于地址线引脚只引出一半，因此地址线引脚数为8（16均分，取大的）。数据线引脚数为1 (有的芯片数据输入线与数据输出线是分开的，则数据线引脚数就为2)。它有R/W信号，而**没有CS信号**。它有行地址选通信号RAS和列地址选通信号CAS。综上所述，除电源线、接地线和刷新线外，该芯片的最少引脚数目应为12。



### Consider a 16M×128 memory built by using 512K×16 memory chips. How many rows of memory chips are needed? 

A. 8 

B. 16 

C. 32 

D. 64

**答案：C**。16M/512K=32 



### Consider a 64M×16 memory built by using 512K×8 memory chips. How many memory chips are needed? 

A. 32 

B. 64 

C. 128 

D. 256

**答案：D。**(64M * 16)/(512K * 8)=256 



### Consider a memory can be accessed with 20-bit address. Its word length is 64-bit and it is word-addressable. Assume that we use 256K×8bit SRAM chip to constitute this memory.



#### How many bytes can this memory store?   

$2^{20} \times 64 / 8 B = 1M \times 8 B = 8MB$。

#### How many SRAM chips do we need? 

$8MB / (256 K \times 8 /8B)= (8MB / 256KB)=32$片。

#### How many address pins do we need for chip select? Why?

因为每片芯片内部有18位地址(对应于256K个存储单元)，所以，20位的地址中，低18位地址直接接芯片的18位地址端，高2位地址通过2:4译码器作芯片选择。

#### Draw a figure to show how this memory can be implemented using 256K×8bit SRAM chip. 



### Assume that there are two types of static memory chips: 128K×8 bit (total 4 chips) and 512K×4 bit (total 2 chips). Please use these memory chips to implement a 512K×16 bit memory. Draw the figure of the memory organization.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412070100802.webp)
