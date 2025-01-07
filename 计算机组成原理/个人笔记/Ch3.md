# Ch3

## Outline

- I/O Interface I/O接口
- Program Controlled I/O 程序控制I/O
- Interrupt Concepts & Processing
- Multiple Devices Interrupt System Design Issues 
- Direct Memory Access



### I/O Interface

**访问I/O设备**：

计算机系统组件是通过互联网络进行沟通的。

每个I/O设备必须包含可寻址位置：**这些位置可以被Load/Store指令访问，以I/O寄存器方式实现**。

- These locations are accessed with Load and Store instructions.
- These locations are implemented as I/O registers.



分为两种：

- Memory-mapped I/O：I/O设备和存储器使用同样的地址空间，没有特殊的命令，就像存储器读写一样。

  ```assembly
  Load R2, DATAIN
  Store R2, DATAOUT
  //DATAIN 是输入设备寄存器的地址 DATAOUT是输出设备寄存器的地址
  ```

  优点是任何用于访问存储器的指令都可以用于I/O设备，缺点是宝贵的地址空间被使用完了。

- Separated I/O：使用分开的地址空间，并且有特殊的命令执行数据传输，如:IN OUT。

  优点是只会使用一些地址线，注意I/O地址线和存储器地址线不一定是分开的。



I/O**设备问题**：

- 不同的输入输出设备：传输大量的数据，可能以不同的速度和格式进行传输。
- 比RAM和CPU慢。

为了解决这个问题，使用了I/O接口。

- I/O接口是一个芯片，用于连接设备和互联网络，**提供传输数据的方法和交换状态和控制信息，包括了data，status，control registers（可使用Load/Store指令进行访问）**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052346304.webp)

与CPU交流的方法有三种：

- Program-controlled I/O (Polling)
- Interrupt-driven I/O
- Direct Memory Access (DMA)



### Program-controlled I/O

以下是按照要求将上述内容概述为中文并分为三部分：

**第一部分：关于I/O任务及方式概述**

使用键盘和显示器来探讨输入/输出（I/O）相关问题，要实现读取键盘字符，将其存储在内存中，然后在屏幕上显示出来这一任务，并且通过一个执行所有相关功能的程序来完成此项任务，这种方式被称作程序控制I/O。

**第二部分：确保动作时机正确及设备间同步传输的方式**

假设I/O设备能够向处理器发送“就绪”信号来确保动作的正确时机以及设备间的同步传输。对于键盘而言，该“就绪”信号意味着可以读取字符了，此时处理器就可以使用加载（Load）操作来访问数据寄存器；对于显示器来说，“就绪”信号表示可以发送字符了，处理器则使用存储（Store）操作来访问数据寄存器。在每种情况下，“就绪”信号都是状态寄存器中的一个状态标志位，由处理器进行轮询。

**第三部分：示例I/O程序相关假设情况**

对于接下来的示例I/O程序，假定寄存器有特定的地址以及位的位置。寄存器的宽度为8位且按字对齐。例如，键盘在地址为0x4004的键盘状态（KBD_STATUS）寄存器的第1位（b1）有键盘输入（KIN）状态标志。处理器会轮询键盘状态寄存器，检查键盘输入标志是0还是1，如果该标志为1，处理器就会读取键盘数据（KBD_DATA）寄存器。 

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412060004221.webp)



**Wait Loop for Polling I/O Status**

**第一部分：通过轮询键盘状态寄存器等待循环实现程序控制I/O**

以下是一段用于轮询键盘状态寄存器的等待循环代码：
```assembly
READWAIT: 
LoadByte R4, KBD_STATUS  // 将键盘状态寄存器（KBD_STATUS）的值加载到寄存器R4中
LoadByte R4, KBD_STATUS  // 再次加载，可能是确保获取到最新状态
And R4, R4, #2          // 与操作，提取相关标志位（此处可能是与代表键盘输入就绪的位进行操作）
And R4, R4, #2          // 再次进行与操作，进一步确认相关状态
Branch_if_[R4]=0   READWAIT  // 如果R4的值为0（即键盘未就绪），则跳转到READWAIT继续循环等待
LoadByte R5, KBD_DATA  // 当键盘就绪（对应标志位为1）时，读取键盘数据寄存器（KBD_DATA）中的字符到R5
```
键盘电路会将字符放入键盘数据寄存器（KBD_DATA）中，并在键盘状态寄存器（KBD_STATUS）中设置键盘输入（KIN）标志位。而且当键盘数据寄存器（KBD_DATA）中的数据被读取后，电路会自动清除键盘输入（KIN）标志位。

**第二部分：针对显示设备的类似等待循环**

以下是用于显示设备的类似等待循环代码：
```assembly
WRITEWAIT : 
LoadByte R4, DISP_STATUS  // 将显示状态寄存器（DISP_STATUS）的值加载到寄存器R4中
LoadByte R4, DISP_STATUS  // 再次加载以获取最新状态
And R4, R4, #4          // 与操作，提取与显示相关的标志位（可能代表显示就绪的位）
And R4, R4, #4          // 再次进行与操作确认状态
Branch_if_[R4]=0   WRITEWAIT  // 如果R4的值为0（即显示未就绪），则跳转到WRITEWAIT继续循环等待
StoreByte R5, DISP_DATA  // 当显示就绪（对应标志位为1）时，将寄存器R5中的字符存储到显示数据寄存器（DISP_DATA）中
```
显示电路会在前一个字符被显示后，在显示状态寄存器（DISP_STATUS）中设置显示输出（DOUT）标志位，并且当字符被传输到显示数据寄存器（DISP_DATA）时，电路会自动清除显示输出（DOUT）标志位。 



**RISC-Style Program**

**程序功能概述**

考虑使用轮询方式来读取、存储并显示一行字符的完整程序。该程序在键盘上输入回车（CR）字符时结束。并且每个从键盘输入的字符都会回显到显示器上。其中`LOC`是存储行中第一个字符的地址。

**程序执行逻辑（可进一步补充细节）**

程序会不断地轮询键盘状态寄存器，一旦检测到有字符输入（键盘就绪），就读取该字符并存储到指定内存位置（从`LOC`开始），同时将该字符输出到显示器。在这个过程中持续循环，直到接收到回车字符才停止整个程序的运行。 



![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412060016953.webp)



### InterruptConcepts &Processing

I/O中断的优点：

- 不需要CPU重复检查设备的状态
- 克服CPU的等待问题，消除等待时间
- I/O模块通过发送中断信号，CPU执行中断。



**中断的相关概念**

- **中断请求（Interrupt Request）**：这是一种由I/O设备通过总线控制线路中的某一条向处理器发送的信号，用于告知处理器自身有需要处理的情况。
- **中断应答（Interrupt Acknowledge）**：是指CPU发出的用于对中断请求做出回应、表示已确认收到中断的信号。

- **中断服务程序（Interrupt-Service Routine，也叫Interrupt Handler）**：当接收到中断请求后，为响应这个请求而执行的程序段就被称作中断服务程序。
- **中断延迟（Interrupt Latency）**：指的是从接收到中断请求的时刻起，到开始执行中断服务程序之间所存在的时间延迟。



**子程序和中断服务程序的区别**

- **子程序**：它执行的是调用它的那个程序所需要的功能。所以，对于状态信息以及寄存器内容可能出现的变化，是在预期范围内的。
- **中断服务程序**：它可能和接收到中断请求时正在执行的程序部分没有任何关联。因此，在开始执行中断服务程序之前，那些在该程序执行过程中可能会以不可预期的方式被改变的处理器寄存器状态信息以及寄存器内容，都必须先进行保存。而且，在被中断的程序恢复执行之前，这些保存好的信息还需要被恢复回来。 



**Interrupt Processing** 

**中断处理概述**

当中断发生且被接受时，当前程序的执行会被暂停。此时，必须将程序计数器（PC）以及各寄存器的内容保存到进程控制块（PCB）中，然后执行中断服务程序来处理该中断。

**中断处理的细节——处理器应答（处理中断的一部分）**

- **方法一**：处理器会发出中断应答信号，以此告知相应设备其发出的中断请求已被识别。
- **方法二**：通过执行中断服务程序中访问设备接口里的状态或数据寄存器的指令，来隐式地通知设备其中断请求已得到认可。

**保存和恢复信息**

- **需要保存和恢复的信息内容**：通常包括条件码标志以及被中断程序和中断服务程序都会用到的寄存器内容。这些信息的保存与恢复任务，既可以由处理器自动完成，也可以通过程序指令来操作。

- **信息保存和恢复的具体情况**：大多数现代处理器只保存维持程序执行完整性所必需的最少信息量（一般是程序计数器和程序状态字的内容）。而其他任何需要保存的额外信息，则必须在中断服务程序开始时通过程序指令进行保存，并在该程序结束时恢复。 

  

**中断使能与禁止的重要性**

使能和禁止中断对于所有计算机而言都是基础性的操作。因为中断可能随时发生，它会改变程序员原本设想的事件执行顺序，所以程序执行的中断情况必须被谨慎控制。有时候，有必要确保某一特定的指令序列能够不被中断地执行完毕，这是由于中断服务程序可能会改变相关指令所使用的数据。

**处理器端的中断控制**

- **通过程序状态寄存器控制**：在程序状态寄存器中设置中断使能位（IE）来实现中断控制。当IE = 1时，处理器会接受并处理来自I/O设备的中断请求；而当IE = 0时，处理器会直接忽略所有来自I/O设备的中断请求。并且，处理器在开始执行中断服务程序前会自动禁止中断（将中断使能位清零，即IE = 0）。当执行从中断返回指令时，会从栈中恢复程序状态寄存器（PS）的内容，把中断使能位重新设置为1（IE = 1）。这种方式适用于只有一条中断请求线路的简单处理器。

**I/O设备端的中断控制**

确保只有处理器当前愿意响应的那些I/O设备才能产生中断请求是很重要的。因此，在各个设备的接口电路中需要一种机制，用于控制某个设备是否被允许中断处理器，也就是需要一个中断使能（此处描述未完整，推测后续可能会继续介绍相关机制等内容）。 

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412060113447.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412060113518.webp)



### Multiple Devices Interrupt System Design Issues 

- 确认中断来源
- 多层级中断
- 同时中断



**多设备中断系统设计问题 - 中断源识别**

在多设备中断系统中，面临的一个关键问题是如何确定发出中断的模块。并且，处理器怎样获取不同设备对应的中断服务程序起始地址，也就是如何进行中断源的识别。

> How do you identify the module issuing the interrupt? How the processor obtain the starting address of the appropriate routine of different devices?—Identify Interrupt Source



**多中断请求线路情况（Case1）**

- **方式介绍**：在处理器和I/O接口之间设置多条中断线路。不过即便采用了多条线路，每条线路上也很可能会连接多个I/O接口。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061223893.webp)



**公共中断请求线路：分为向量中断（Vectored Interrupt）和非向量中断（Polling (Nonvectored Interrupt) ）**

**公共中断请求线路情况之轮询（非向量中断）（Case2）**

- **非向量中断定义**：当CPU接收到中断时，会通过硬件将程序计数器跳转到一个固定地址，这就是非向量中断。它适用于中断源较少且软件结构较为简单的小型系统。
- **实现方法**：处理器会读取各个I/O接口的状态寄存器（当某个设备发出中断请求时，会将其状态寄存器中的中断请求位，即IRQ位设置为1）。
- **键盘和显示器接口中的寄存器相关情况**：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061225730.webp)



**公共中断请求线路情况之向量中断（Case2）**

- **向量中断定义**：这是一种中断机制，设备在请求中断时，会通过向处理器发送**中断向量码**来表明自身身份。
- **中断向量相关概念**：中断向量指的是中断处理程序的内存地址；中断向量表包含了所有中断处理程序的内存地址；**中断向量码则是用于在中断向量表中进行索引的一个标识**。
- **向量中断的其他相关内容（未展开描述）**：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061227259.webp)



**多设备中断系统设计问题 - 多级中断**

当处理器正在处理一个中断时，是否应该允许另一个设备中断处理器，这涉及到多级中断的相关考量，需要确定在这种情况下中断处理的优先级与规则等策略。

> Should a device be allowed to interrupt the processor while another interrupt is being serviced? —Multi-level Interrupt



**单级中断**

无论是单个设备还是多个I/O设备产生中断，在执行中断服务程序期间，都应当禁止新的中断产生。

**多级中断（中断嵌套）**

在为某个设备执行中断服务程序的过程中，有必要允许处理器接受来自其他设备的中断请求。I/O设备按照优先级结构进行组织安排，当处理器正在处理来自低优先级设备的中断请求时，应当接受来自高优先级设备的中断请求。

**多级优先级**

- **优先级设定与控制**：给处理器分配一个优先级级别，并且该优先级级别可以在程序（通过特权指令）控制下进行更改。处理器的优先级级别等同于当前正在执行的程序的优先级。
- **中断接受规则**：处理器只接受来自优先级高于自身优先级的设备的中断请求。当开始执行某个设备的中断服务程序时，处理器的优先级会提升至该设备的优先级。
- **优先级编码方式**：处理器的优先级可以用处理器状态寄存器中的若干位进行编码表示。 

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061234475.webp)







**多设备中断系统设计问题 - 同时中断处理**

若有两个或更多中断请求同时发生，处理器应该如何应对，怎样确定处理这些同时到来的中断请求的顺序与方式，这就是同时中断处理需要解决的问题。

> How should two or more simultaneous interrupt requests be handled? —Simultaneous Interrupt



**各设备有独立中断请求与应答线路的情况（Case 1）**

- **中断处理方式**：处理器只需接受具有最高优先级的中断请求。它能够让处理器依据各设备的优先级情况，选择接受某些设备的中断请求，而不接受其他设备的中断请求。

**多个设备共享一条中断请求线路的情况（Case 2）**

- **软件轮询（Software Poll）**：处理器会轮询I/O设备的状态寄存器，各设备的优先级由轮询它们的先后顺序来决定，先被轮询到的设备优先级相对较高。
- **菊花链（Daisy Chain）**：
    - **优先级确定方式**：在菊花链这种连接方式中，在电气连接上距离处理器最近的设备具有最高优先级，沿着链路的第二个设备具有次高优先级，依此类推，设备的优先级按照其在链路上与处理器的相对电气位置依次递减。 

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061240175.webp)

- **Priority Group** :

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061241494.webp)

    



### Direct Memory Access (DMA)

**中断驱动与程序控制I/O的特点及局限**

中断驱动以及程序控制I/O这两种方式都需要CPU积极地介入干预。它们存在一定局限性，比如数据传输速率会受到限制，而且CPU会被束缚在管理I/O传输的事务上，难以抽身去处理其他任务。

**解决上述局限的办法——直接内存访问（DMA）**

直接内存访问（DMA）是一种解决方案，它主要用于外部设备和主存储器之间直接进行高速的批量数据传输。为此会配备一个DMA控制器，它能够从CPU那里接管系统的控制权，在数据传输过程中，CPU无需参与其中，从而使得CPU可以去处理其他事务，同时也提高了数据传输的效率。 



**DMA 中的程序控制 I/O**
在直接内存访问（DMA）机制下的程序控制 I/O 操作中，CPU 需要通过向 DMA 控制器（DMAC）传输相关信息来 “准备” DMA 操作，这些信息具体包括：**设备上数据所处的位置、数据在内存中的存放位置、要传输的数据块大小、传输的方向以及传输的模式**（如突发模式、周期窃取模式等）。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061424309.webp)

**DMA 控制器控制数据传输**
当外部设备准备好进行数据传输时，DMA 控制器会接管系统总线的控制权，进而负责处理数据传输相关事宜，而此时 CPU 就可以继续去执行其他工作了。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061424668.webp)

**DMA 中的 I/O 中断**
当 DMA 控制器完成数据传输任务后，它会向 CPU 发送中断信号，告知 CPU 传输已结束。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061425901.webp)



**DMA控制器的功能**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061432267.webp)



- DMA控制器的主要功能是接管内存与I/O设备之间的数据传输控制工作。在进行数据字传输时，它具体要承担以下职责：
    - **提供内存地址**：确定数据在内存中的具体位置，以便准确地进行读写操作。
    - **提供控制数据传输的总线信号**：生成用于控制数据在不同设备间传输的各类总线相关信号，保障传输顺利进行。
    - **递增内存地址以处理连续字**：针对连续传输的数据字，能自动更新内存地址，确保按顺序对相应内存位置进行操作。
    - **记录传输次数**：对已经完成的数据传输次数进行跟踪，便于知晓传输进度以及判断整个传输任务是否结束。



**DMA接口中的寄存器布局：**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061434712.webp)

**突发模式（块模式）**

- **传输过程**：一旦DMA控制器获得处理器授予的系统总线访问权限，它就会在将系统总线控制权交还给处理器之前，一次性把数据块里的所有字节数据都传输完毕。
- **应用场景**：这种模式在将程序或数据文件加载到内存中时比较有用。
- **缺点**：会使得处理器在相对较长的时间段内处于闲置状态，导致CPU的使用效率变低。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061435437.webp)

**周期窃取模式**

- **传输过程**：当DMA控制器获取到系统总线的访问权限后，它每次只传输一个字节的数据，然后就把系统总线的控制权交还给处理器。之后它会持续发出请求，每次请求传输一个字节的数据，如此循环，直至完成整个数据块的传输。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061435263.webp)

**透明模式**

- **传输特点**：DMA控制器只会在CPU执行那些不使用系统总线的操作时进行数据传输。需要注意的是，在此模式下，DMA控制器无需向处理器请求系统总线的控制权。
- **优点**：处理器可以一直不间断地执行自己的程序。
- **缺点**：用于判断处理器何时不使用系统总线的相关硬件往往比较复杂，而且成本相对较高。 



**DMA配置**：

**单总线、分离式DMA控制器**

- **传输过程**：在这种模式下，每次数据传输需要使用两次总线。先是将数据从I/O设备传输到DMA控制器，然后再从DMA控制器传输到内存。
- **对CPU的影响**：由于上述的两次总线使用过程，CPU会被暂停两次，这可能会对CPU的工作效率产生一定影响。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061442297.webp)

**单总线、集成式DMA控制器**

- **控制器特点**：这种控制器可以支持多个设备。
- **传输过程**：每次数据传输只使用一次总线，即直接从DMA控制器传输到内存。
- **对CPU的影响**：相比分离式，这种方式下CPU只需被暂停一次，在一定程度上减少了对CPU工作的干扰。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061443880.webp)

**独立I/O总线**

- **总线功能**：此总线能够支持所有启用了DMA功能的设备。
- **传输过程**：每次数据传输同样只使用一次总线，是从DMA控制器直接传输到内存。
- **对CPU的影响**：和单总线、集成式DMA控制器一样，CPU在这个过程中也只需被暂停一次，有助于提高系统的整体性能。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061444419.webp)



## 练习

### About memory-mapped I/O, which of the following is not true? 

A. The I/O devices and the memory share the same address space. 

B. Any machine instruction that can access memory can be used to transfer data to or from an I/O device. C. Valuable memory address space is used up. 

D. I/O devices deal with few address lines.



**答案**：D。



### What is the difference between memory-mapped I/O and isolated I/O?

- Memory-mapped I/O: 

  - The I/O devices and the memory share the same address space. I/O 设备和内存共享相同的地址空间。

  - No special commands for I/O. Any machine instruction that can access memory can be used to transfer data to or from an I/O device. 没有 I/O 的特殊命令，任何可以访问内存的指令都可以用来传输输入输出设备的数据。

  - Valuable memory address space is used up.宝贵的内存地址空间被用完了。
- Isolated I/O: 
  - Separate address spaces 单独的地址空间
  - Special I/O instructions to perform I/O transfers. 执行 I/O 传输的特殊 I/O 指令
  - I/O devices deal with few address lines.I/O 设备只处理很少的地址线



### In an interrupt process, the usage of saving PC is . 

A. to make CPU find the entry address of the interrupt service routine 

B. to continue from the program breakpoint when returning from interrupt 

C. to make CPU and peripherals working in parallel 

D. to enable interrupt nesting

**答案**：B。



### What is interrupt? What advantage does Interrupt-Driven I/O have over Program-Controlled I/O? 

**Solution: An interrupt is an event that causes the processor to stop its current program execution and switch to performing an interrupt service routine.** 

**Interrupt-Driven I/O allows the computer to process other tasks while waiting for I/O.**

中断是一种事件，它会使处理器停止当前程序的执行，并转而执行中断服务程序。

中断驱动输入 / 输出允许计算机在等待输入 / 输出时处理其他任务。





### In the process of determining which device is requesting an interrupt, the device identifies itself directly by sending a signal or a binary code to the processor. This approach is called _______. 

A. polling 

B. non-vectored interrupt 

C. vectored interrupt 

D. interrupt vector



**答案**：C。



### The following figure shows the interface of a keyboard. Write functions of (1) KIN (2) KIRQ (3) KIE.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412061400508.webp)

**答案**：

**第一部分：键盘状态位介绍 - KIN位**

KIN位是一个状态标志位，处理器通过读取它来判断字符代码何时已被放入键盘数据寄存器（KBD_DATA）。如果KIN = 1，就表示字符已经在KBD_DATA中；如果KIN = 0，则表示字符尚未放入。

**第二部分：键盘状态位介绍 - KIRQ位**

KIRQ位也是一个状态标志位，用于表明键盘是否正在请求中断。当KIRQ = 1时，意味着键盘发出了中断请求；当KIRQ = 0时，表示键盘没有发出中断请求。

**第三部分：键盘状态位介绍 - KIE位**

KIE位是用于控制键盘是否能够发出中断的位。如果KIE = 1，那么键盘就处于一种允许的模式，只要它准备好进行I/O传输，就可以中断处理器。



### Which method bypasses the CPU for certain types of data transfer? 

A. Software interrupts 

B. Polled I/O 

C. Interrupted-driven I/O 

D. Direct Memory Access (DMA) 



**答案：**D。



### _____ is used for high-speed block transfers directly between an external device and the main memory. 

A. Program-controlled I/O 

B. Interrupt-driven I/O

C. DMA approach 

D. Event-driven



**答案：**C。



### Once the DMA controller obtains access to the system bus, it transfers one byte of data and then returns the control of system bus to the processor. This is _______. 

A. burst mode 

B. block mode 

C. cycle stealing mode  

D. transparent mode



**答案**：C。