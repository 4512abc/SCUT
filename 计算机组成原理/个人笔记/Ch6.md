# Ch6

## Summary

- 流水线并没有改善指令的延迟，每条指令仍然需要相同的时间才能完成。
- 流水线减少了每条指令的平均执行时间。
- 流水线实际上提高了整体吞吐量。



## outline

- Basic Concept of Pipelining（流水线基础概念）
- Pipelining Organization（流水线组织）
- Pipelining Issues
- Data Dependencies（数据依赖）
- Memory Delays
- Branch Delays
- Resource Limitations（资源限制）



### Basic Concept

上一章讲述了处理器的实现原理，这一章重点是提高处理器的性能，**重点是让程序的执行更快**。

为了实现这个目标：有以下两个方法：

- 使用更快，更先进的芯片技术实现处理器和存储器。

- 对硬件组件进行重新安排，使得在同一个时间点，可以有多条指令被同时执行。通过这种方法，执行任何一个操作所需要的时间没有改变，但是每秒执行的操作数会增加，从而提高性能。

  > In the this way, the number of operations performed per second is increased even though the elapsed time needed to perform any one operation is not changed.



这一章重点介绍第二种方法，以及一种具体实现技术：流水线。

流水线的核心在于：**能够重叠多条指令，使得他们同时进行**。

本质上：在执行完当前指令前，开始执行另外一条新指令。



可以借助汽车生产流水线来理解：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051605322.webp)



由此可以类比处理器：

- 指令获取：Instruction Fetch
- 指令译码和读取寄存器：Instruction Decode and Register Read
- 执行操作或者计算地址：Execution operation or calculate address
- 存储器访问：Memory access
- 将结果写回到寄存器中：Write result into register。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051618620.webp)

上面是没有使用流水线的情况（对应的时间周期图）。

下面是使用流水线的情况：

- 每条指令的一个阶段占据一个时间周期。
- 在每一个时间周期内，处理器可以接收一条新指令。
- 指令被逐条传递，分阶段处理。
- 多条指令在一些时间段被同时执行。

![image-20241205161828651](./../../source/images/Ch6/image-20241205161828651.png)

一些专业术语：

- **Pipe Stage / Pipe Segment**：A step in the pipeline to complete the instruction
- **Pipeline Depth**：Number of stages in a pipeline.
- **Latency**：How long does it take to execute a single instruction in a pipeline. 
- **Throughput**：The number of instructions completed per second.



### Pipelining Organization

- 使用PC来获取指令

- 每一个时间周期都有一条新指令进入到流水线中

- 随着指令在不同阶段间的流动，该指令特有的相关信息也被随其记载携带。**这些信息一般是存储在阶段间缓冲区中，**包括上一章提到的RA, RB, RZ, RY, RM, IR, PC-Temp以及其他辅助寄存器。**此外还负责保持控制信号的设置**。

- 简单介绍各种缓冲区中的内容：

  - B1：提取新指令

  - B2：

    - 提取两个操作数，源/目标寄存器
    - 立即值
    - 返回地址递增后自增的PC
    - **控制信号设置值**

  - B3：

    - 写入到存储器中的数据
    - 目标存储器的地址
    - **递增后PC值，可能作为子程序调用的返回地址**

  - B4：

    - ALU计算结果
    - 子程序调用返回指令后自增的PC值
    - 存储器中读取到的结果

    

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051647576.webp)



### Pipeline Issues

在实际的流水线操作中会存在一些问题，如：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051658701.webp)

考虑一种情况：$I_j$的目标寄存器是$I_{j + 1}$的源寄存器。因为$I_j$中目标寄存器的内容在第五个阶段才被写入，而$I_{j+1}$需要在第3个阶段就读取源寄存器中的内容，所以$I_{j+1}$不得不暂停，直到$I_j$完成再继续，也就是在第六个周期，$I_{j+1}$才可以进行Decode操作。当然后续的一系列指令也需要延迟。新的指令不能进行流水线，总的执行时间也会增加。

将会引起流水线暂停的情况成为冲突(hazard)，主要三种：

- 数据冲突：因为数据的依赖性。

  > 指令的源操作数或目标操作数在管道中预期的时间不可用的任何条件。所以一些操作不得不推迟，管道停止。

- 指令（控制）冲突

  > 指令可用性的延迟导致管道停止。

- 结构冲突：

  > 两个指令同时需要使用给定硬件资源的情况

接下来依次介绍几个例子。



### Data Dependency

```assembly
Add R2, R3, #100
Substract R9, R2, #30
```

Add中的R2是Sub中的源寄存器，这两者存在数据依赖性（因为需要将R2中的数据从Add转移到Sub）。

如果不使用流水线技术，R2在Sub中能够被访问，因为Add指令已经执行完毕。

如果使用流水线，有多种解决方法：

**停止流水线：**

- 由于在Sub指令进行解码时，旧值还在R2中，所以对Sub指令进行暂停。

- 暂停时长为三个周期：因为新值是在第五个时间周期写入的，所以解码完成最快也得在第六个周期。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051902990.webp)

- 具体细节：

  - 控制回路需要在cycle 3判断数据之间是否具有依赖性。（也就是遇到才确定依赖性）
  - 阶段间缓冲区携带指令源和目标的寄存器标识符。
  - 在cycle 3，会在译码时，**比较Compute Stage 的目标和 Destination Stage的源**。（简单来说就是判断是不是发生了冲突）
  - 如果R2匹配，继续解码Sub，Add正常进行。



**操作数转发**：

- 可以解决数据之间的依赖性，并且不用停止流水线。

- 在前面的指令序列中，R2中的新值实际上在cycle 3结束时就可以使用，所以在cycle 4时可以将新值转移到目标位置。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051917142.webp)

- 具体细节：

  - > Introduce multiplexers before ALU inputs to use contents of register RZ as forwarded value
    >
    > 在 ALU 输入前引入多路复用器，使用寄存器 RZ 的内容作为转发值

  - 控制回路此时是在阶段四进行识别，不像上面的是在cycle 3。此时Sub是Compute Stage

  - 对应的，阶段间缓冲仍然携带寄存器标识符。

  - 并且在cycle 4，会比较Add的目标（在Memory Stage）和 Sub的源（在Compute Stage）。

  - 多路复用的控制是基于两者之间的比较。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051929038.webp)

- 扩展：实际上RY中的内容也可以用于转发，例子如下：

  ```assembly
  Add			R2, R3, #100
  Or  		R4, R5, R6
  Substract 	R9, R2, #30
  ```

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051935345.webp)



![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051936878.webp)

**注意：转移只能从第一条指令的C（也就是[RZ]转移到MuxA）到第二条指令的C，或者第一条指令的M（也就是[RY]到InA）到第三条指令的C。**确切的讲：就是前者的C或者M和后者的C在时间周期上是相邻的。



**软件处理数据依赖性**：使用编译器

- 编译器可以产生和分析指令，由于寄存器中的数据依赖性是明显的，所以编译器可以通过在**存在数据依赖性的指令间显式插入多条NOP指令。**
- 这样可以确定寄存器中的新值是可以被访问的，但是这会导致总执行时间的增加。
- 为了解决这个问题，编译器可以尝试优化，通过将指令移入到NOP槽中来减少代码长度（需要考虑数据之间的依赖性，并且可能需要对指令进行重新排序）

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052016705.webp)

### Memory Delay

存储器延迟可能导致流水线暂停。

一般情况下，如果数据和指令在缓存中可以之间访问获取，那么只需要一个时间周期，否则，需要花费多个时间周期进行访问存储器。在流水线中，一条指令的存储器延迟将会导致后续指令的延迟。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052019113.webp)

即使缓存命中，由于数据之间的依赖性，也可能需要暂停一个时间周期，这样才能读取到需要的数据并进行计算。

可以在其中插入有用的指令进行优化，可以参考上面的**拓展操作数转发**，如果找不到就会引入一个周期的停顿，或者是一条显式的NOP指令。

为什么是cycle 4，联系硬件组成，**转发主要是从[RZ]或[RY]进行，对应的分别是阶段3和阶段4**。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052027938.webp)



### Resource Limitations

可能两条指令需要在同一个时间周期访问一样的资源，可能一条指令暂停，一条进行。可以通过额外的硬件组成解决这个问题。

一个典型的例子是：Fetch和Memory阶段都和cache有关。

- 一般情况下，Fetch总是在每一个时间周期内访问缓存。
- 当Load/Store指令在Memory阶段需要访问缓存时，会导致一个时间周期的暂停。
- 解决方法：将缓存分开为**数据和指令**，这样就可以同时进行Fetch和Memory阶段。



### Branch Delays

**理想流水线**：在当前指令进行译码时，获取一条新指令。

Branch 指令会改变指令的执行顺序，需要确认：是否分支，分支到哪里。



**无条件分支**：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052107272.webp)

考虑以上情况，在第五章中，我们知道在cycle 3 计算得到转移指令的递增，并且更新PC。所以在cycle 4 我们才能够Fetch $I_k$，但是$I_{j+1},I_{j+2}$已经被Fetch，不得不丢弃，由此产生了两个周期的转移代价。

**为了减少转移代价**，需要目标地址被更早的计算得到，可能在解码Decode阶段进行解码，然后更新PC，而不是在PC阶段。所以这样只有一个周期的转移代价，一条指令被丢弃。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052114103.webp)



**条件分支**：

```assembly
Branch_if_[R5]=[R6] LOOP
```

这里除了需要计算转移地址，还需要进行条件判断，还是在Decode阶段计算转移地址，再引入一个比较器在Decode阶段进行比较（条件判断）。



**转移延迟槽：**

上面的方法还是有一个周期的转移代价，**可以采用一种减少转移代价的技术**。

如果条件成立，指令被丢弃，否则继续执行。我们将位于转移指令后的单元成为转移延迟槽，我们可以在这里插入一条新指令（称为转移指令，只需要满足数据依赖性的限制即可，否则只能插入NOP，无法消除代价）。

这条新指令是一直要执行的，所以我们可以从分支前面找，并将其转移到槽中，这样就彻底消除了转移代价。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052148851.webp)

可以发现，这样彻底消除了转移延迟的周期代价。



## 练习

### What is the first stage in a typical five-stage CPU pipeline? 

A. Fetch 	B. Decode 	C. Compute 	D. Write



**答案**：A。



### When multiple-instructions are overlapped during execution of program, then function performed is called . 

A. Multitasking 

C. Hardwired control 

B. Multiprogramming 

D. Pipelining

**答案**：D。



### Ture or False? Pipelining increases processor performance by decreasing the execution time of an instruction.

**答案：**False。

实际上，流水线没有缩短每一条指令的执行时间，但是缩短了每条指令的平均执行时间。并且提高了整体吞吐量。



### A(n) _ is a situation in which the pipeline is stalled because the data to be operated on are delayed for some reason. 

### or _____ is any condition in which either the source or the destination operands of an instruction are not available at the time expected in the pipeline. 

A. control hazard 	B. data hazard 	C. structural hazard 	D. instruction hazard

**答案：**B。



### About the data dependency in a pipeline, which is not true in the following? 

A. Operand forwarding can handle all data dependencies without the penalty of stalling the pipeline. 

B. Compiler can detect data dependencies and deal with them by analyzing instructions. 

C. Compiler puts explicit NOP instructions between instructions having a dependency. 

D. Even with a cache hit and operand forwarding, the data dependency between “Load R2, (R3)” and “Subtract R9, R2, #30” will also cause onecycle stall.

**答案**：A。



### Consider the following sequence of instructions being processed on the pipelined 5-stage RISC processor: 

```assembly
Load R1, 4(R2)
Sub R4, R1, R5
And R6, R1, R7
Or R8, R3, R4 
```

#### (1) Identify all the data dependencies in the above instruction sequence. For each dependency, indicate the two instructions and the register that causes the dependency.（识别上述指令序列中的所有数据依赖项。对于每个依赖项，指示两个指令和导致依赖项的寄存器。）



**答案**：

- Sub指令依赖于Load指令中的R1

- And指令依赖于Load指令中的R1
- Or指令依赖于Sub指令中的R4





#### (2) Assume that the pipeline does not use operand forwarding. Also assume that the only sources of pipeline stalls are the data hazards. Draw a diagram that represents instruction flow through the pipeline during each clock cycle.（假设流水线不使用操作数转发。还要假设导致流水线失效的唯一原因是数据丢弃。绘制一个表示在每个时钟周期内通过流水线的指令流的图表。）



**答案**：

这里注意Sub停止，导致了后续一系列指令停止。注意一点，**在同一个时间周期下，不同指令执行的阶段是不同的，必须前一条指令执行完毕后，后续的指令才可以继续执行**。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052234992.webp)

#### (3) Assume that the pipeline uses operand forwarding. The pipeline hardware is similar to figure 2 above, but add separate forwarding paths from the outputs of stage-3 and stage-4 to the input of stage-3. Draw a diagram that represents the flow of instructions through the pipeline during each clock cycle. Indicate operand forwarding by arrows.（假设流水线使用操作数转发。流水线硬件类似于上面的图2，但是从阶段3和阶段4的输出向阶段3的输入添加单独的转发路径。绘制一个表示每个时钟周期内通过流水线的指令流的图表。用箭头表示操作数转发。）



解释一下：Load指令的M通过RY转载到Sub的C中，由于是在M阶段得到数据，所以Sub指令在D需要暂停一个时间周期。后续And指令执行，重点在于D需要延迟一个时间周期，因为如果还是正常一个时间周期的话，那么And指令的D在5，C在6，而Load的M在4，不是相邻的，无法进行转移，所以只能等到Load的W完成后，继续Decode获取寄存器中的内容。后续也是以此类推。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412052239197.webp)