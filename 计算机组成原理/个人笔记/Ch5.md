# Ch5

## Summary

- 硬件组成
- 取指令和执行指令的行动
- 控制信号
- 产生控制信号的方法：
  - 硬件控制
  - 微程序
    - 微指令（控制字）
    - 微程序
    - 控制存储



### 基础概念

处理器：指令集处理器或者中央处理器（CPU），负责从存储器中读取指令。

- 一次读取一条指令
- 对其进行解码
- 执行所需要的操作



分为两个阶段：取阶段和执行阶段

- 取：将获取PC指向的存储地址中的内容，载入到IR中，然后PC自增：`PC <- PC + 4`。每条指令是四个字节。
- 执行：根据IR中的指令执行所需要的操作。
- 注意如果指令占据多个字，可能取指令阶段需要重复多次。



指令执行的具体操作：

- 读取给定的存储地址中的内容，并且载入到处理器寄存器中。
- 从寄存器中读取数据。
- 执行算术逻辑运算，并将计算结果存储到寄存器中。
- 将寄存器中的数据存储到指定的存储器地址。



硬件组成：

- PC：提供指令的地址
- IR：指令被提取存放在IR中
- 指令地址产生器更新PC（Instruction address generator updates PC）
- 控制回路负责解码指令，并且产生控制信号从而完成需要的任务。



数据处理器系统结果：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050113879.webp)

一个操作可以被划分为多步执行

寄存器A中的内容被处理，存放到寄存器B中，在这其中由组合逻辑电路进行处理，其中又可以划分为多个逻辑回路，每一个逻辑回路进行一个分步处理。

这样的好处是一个周期执行一个阶段的任务，可以实现高性能，一个比较常见的例子就是流水线。



### 指令执行

所有的指令都执行相同的步数，每一步在一个硬件阶段执行，处理器使用五个阶段来解决。

```assembly
Example: Load R5, X(R7)
```

1. 获取指令，并且PC自增。
2. 对指令进行解码，读取存储在寄存器R7中的内容
3. 进行算术逻辑运算，获得有效地址：X + [R7]
4. 从存储器中读取操作数
5. 将操作数载入到寄存器R5中



```assembly
Add R3, R4, R5
```

只需要四步即可实现，不许要第四步对存储器的访问，还是使用一样多的阶段，第四阶段不执行任何操作即可。

1. 获取指令，并且PC自增
2. 对指令进行解码，从寄存器R4和R5中读取数据
3. 计算[R4]+[R5]的和
4. 没有任何操作
5. 将结果载入到寄存器R3中



```assembly
Store R6, X(R8)
```

因为不需要将计算结果存储到目的寄存器中，所以还是只需要四步，最后一步不执行任何操作。

1. 获取指令，并且PC自增
2. 对指令进行解码，从R8中读取数据
3. 计算有效地址X+[R8]
4. 将R6中的内容存储到存储单元X+[R8]中。
5. 没有任何操作。

总结为以下五步：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050132631.webp)



### 硬件组成

**Register file：两个端口，负责读取两个寄存器中的数据。**

对应的，有两个输入地址端口，两个数据输出端口，用于读取两个寄存器中的数据（与IR中的源寄存器子段相关）。

另外还有一个输入地址端口和一个输入数据端口，从而将数据写入到指定的寄存器中。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050137153.webp)

具体实现如下：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050138083.webp)

两个Register file存储的数据是一模一样的。



**ALU**：负责执行算术运算和逻辑运算。可能源操作数和目标地址都在register file中，或者一个操作数是在指令中立即获得的。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050142234.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050143369.webp)





由此对应的硬件层可以分为两部分：

- 第一部分：获取指令，进行解码，产生控制信号，为后续合适的操作做好准备。
- 第二部分：执行指令，读取指令中指明的数据操作数，进行所需要的计算，存储结果。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050153448.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050154858.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050156427.webp)

输入地址AB联系到IR中的对应字段，源寄存器被读取，并且数据存储到RA和RB中。

指令的结果存储到目标寄存器中，目标寄存器有输入地址C确定。

ALU执行计算，结果存放到RZ中，MuxB选择是立即值还是RB中的数据，另外RB中的数据会被写到存储器中（从RB->RM，联系到存储器地址）。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050209989.webp)

RZ负责存储器地址，RM负责数据，用于写入存储器。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050206615.webp)



MuxMA负责选择地址：当获取指令时，选择PC，当读取或者写入数据时选择RZ。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050210678.webp)

处理器控制部分：指令被读取存放到IR中，控制回路负责对其译码，产生控制信号驱动其他单元。立即值被扩展到32位进行操作。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050212785.webp)

指令地址发生器部分：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050217102.webp)

### 取指令和执行步骤

1. - 从PC中读取存储器的地址，根据地址找到对应的存储器，将其中的指令载入到IR中，PC自增，指向下一条指令。
   - 对指令进行译码，读取寄存器R4和R5中的内容，分别载入到RA和RB中。
   - 执行计算，计算结果[RA]+[RB]载入到RZ中
   - 将[RZ]载入到RY中
   - 将[RY]写回到R3中。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050230915.webp)

2. - 从PC中读取存储器地址，将指定存储器中的指令载入到IR中，PC自增指向下一条指令
   - 对指令进行译码，读取[R7]，载入到RA中，X由MuxB选择（Immediate value）产生。
   - 执行计算，计算结果[RA]+X载入到RZ中。
   - 读取RZ，得到目标存储器的地址，读取对应的存储器，将存储器中的内容载入到RY中。
   - 将RY中的内容写入到寄存器R5中。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050231959.webp)

3. - 读取PC中的内容，得到目标存储器的地址，读取对应的存储器，将其中的指令载入到IR中，PC自增指向下一条指令。
   - 对指令进行译码，读取寄存器R8中的内容，载入到寄存器RA中，X是MuxB产生的立即值。读取寄存器R6中的内容，并且载入到寄存器RB中。
   - 计算[RA]+X，并将计算结果载入到RZ中，**RB中的内容载入到RM中**
   - 读取RZ中的内容，得到目标存储器的地址，将[RM]写入到目标存储器中。
   - 不执行操作。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050231050.webp)

4. - 读取PC中的内容，得到目标存储器的地址，读取对应的寄存器，得到指令，载入到IR中，PC自增指向下一条指令。
   - 对指令进行解码
   - MuxINC选择将IR中转移偏移量加入到PC中。
   - 空
   - 空

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050232096.webp)

5. - 读取PC中的内容，得到目标存储器的地址，读取存储器，将存储器中的指令载入到IR中，PC自增。
   - 读取R5和R6中的内容，分别载入到RA和RB中。
   - 比较RA和RB中的内容，如果[RA]=[RB]，那么PC加上立即值。
   - 空
   - 空

   可以发现，相比于无条件跳转，只是在第二步多读取了寄存器，在第三步进行计算判断（多使用一个简单的比较器，可以不用消耗多余的时间）。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050232605.webp)

6. - 读取PC中的内容，得到目标存储器的地址，读取对应的存储单元得到指令，PC自增指向下一条指令。
   - 对指令进行译码，读取R9中的内容，载入到RA中。
   - 将PC中的内容载入到RC-Temp中，再将RA中的内容载入到PC中。
   - 将RC-Temp中的内容载入到RY中。
   - 将RY中的内容写回到LINK-register中。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412050233667.webp)

在执行指令的过程中，实际上大部分指令和数据都是可以在缓存中读取到的（减少了访问时间，只需要一个时间周期），但是某些数据不存在于缓存中，这时候就需要进行存储器的访问，可能需要多个时间周期。



处理器-存储器接口会产生一个MFC信号(Memory Function Completed)，负责宣称读操作或者写操作是否执行完毕。当需要的数据在缓存中时，**MFC信号会在发出存储器请求的时钟周期结束前就发出。**否则，就推迟发送MFC信号，直到操作完成。



因为可能需要多个时间周期完成，所以使用了Wait for MFC命令来推迟，直到接收到MFC后再执行下一步操作。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051234924.webp)

### 控制信号

处理器硬件组件操作是由控制信号控制的。

- ALU执行什么样的操作
- 多路复用器决定使用哪一个输入端
- 确定什么时候数据写入到PC中，IR中，register file中，memory中

一般需要很多内部阶段的寄存器。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051239675.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051244227.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051245978.webp)

> Cache memory described earlier as faster and smaller storage that is an adjunct to the larger and slower main memory.前面描述的缓存内存是指速度越来越快、体积越来越小的存储器，它是较大、体积越来越小的主存的附件。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051249930.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051258135.webp)

### 硬件控制

需要考虑步数计数器，IR，ALU结果以及外部输入（MFC，中断需求）。

- 步骤计数器跟踪执行进度，前面描述的五个步骤中的每个步骤都有一个时钟周期。
- 指令解码器解释 IR 中的 OP 码和寻址模式信息，并将相应的 INSi 输出设置为1。
- 在每个时钟周期中，步进计数器的一个输出 T1到 T5被设置为1，以指示正在执行五个步骤中的哪一个。
- 控制信号发生器是一个组合电路，根据其所有输入产生必要的控制信号。

简单说：输出信号是一个函数$C$，变量为$T_i, INS_i, E_k, F_i$，$C=f(T_i,INS_i, E_k,F_i)$。



**数字通路控制信号**：

检查每条指令的每一个执行步骤中发送的所有动作，来决定各种控制信号需要的设置。

有些控制信号随输入的变化而变化，而有些一直不变，我们可以将其设置为恒定值。



很多例子看课本上的内容。



### 微程序控制

Microprogramming is a software-based approach to the generation of control signals.

微程序设计是一种基于软件的控制信号生成方法。

The values of the control signals for each clock period are stored in a microinstruction (control word)

每个时钟周期的控制信号的值存储在微指令(控制字)中

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051335018.webp)

处理器指令是通过放置在控制存储器中的一系列微指令(微程序或微程序)来实现的。

从IR指令的解码，控制电路执行相应的微指令序列。

$\mu PC$ 维护当前微指令的位置。

微程序设计提供了在 CISC 处理器中实现更复杂指令所需的灵活性。然而，在高性能处理器中，读取和执行微指令会导致不必要的长时间延迟。



## 练习

### In hardwired control unit, the required control signals are determined by the following information except 

A. contents of the control step counter 

B. contents of the condition code flags 

C. contents of the instruction register 

D. contents of the program counter



**答案**：D。



### In microprogram-controlled machines, the control signals required by a machine instruction are generated by a 

A. control store 

B. control word 

C. microroutine 

D. microinstruciton



**答案**：D



### The microprograms for all instructions in the instruction set of a computer are stored in a special memory called the 

A. memory controller 

B. main memory 

C. cache 

D. control store



**答案**：D



### In microprogram-controlled machines, the relationship between the machine instruction and the microinstruction is . 

A. a machine instruction is executed by a microinstruction 

B. a microinstruciton is composed of several machine instructions 

C. a machine instruction is executed by a microprogram, which is composed of several microinstructions 

D. None of the above



**答案**：C。



### What are the advantage(s) and disadvantage(s) of hardwired and microprogramed control? 

硬件控制：

- 优点：更快
- 缺点：硬件设计复杂，成本高，不够灵活。

The main advantage of hardwired control is fast operation. 

**The disadvantages include: higher cost, inflexibility when changes or additions are to be made, and longer time required to design and implement such units.** 



微程序：

- 优点：更加灵活，消耗低。
- 缺点：速度慢，在高性能计算机中可能成为一个问题。

Microprogrammed control is characterized by low cost and high flexibility. Lower speed of operation becomes a problem in high-performance computers.



### A 5-stage RISC processor is used to execute the following instruction:` Load R4, 100(R2) `，The processor datapath with all control signals is shown in the following figure:

### (1)  Write sequence of actions needed for executing this instruction at stage-3, stage-4 and stage-5. 

**答案**：

```powershell
Step					Action
3						RZ <- [RA] + 100
4						memory address <- [RZ], Read Memory, RY <- memory data
5						[R4] <- RY
```



### (2) Write the values of control signals B_select in stage-3, Y_select in stage-4 and RF_write in stage-5.

```
B_select = 1
Y_select = 01
RF_write = 1
```



![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412051456820.webp)

