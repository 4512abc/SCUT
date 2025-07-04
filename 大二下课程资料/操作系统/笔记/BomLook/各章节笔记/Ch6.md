# Ch6

## 死锁的定义与资源
### 资源的定义
- **资源**：**任何在某一时刻只能被一个进程使用的对象，必须经过请求、使用和释放的过程**。资源类型包括CPU周期、内存空间、I/O设备、数据库中的记录等。
- **资源实例**：每种资源类型 $ R_i $ 有 $ W_i $ 个实例。
- **可抢占资源**：可以**被强制从一个进程手中夺走，不会导致进程失败**（例如CPU、内存）。
- **不可抢占资源**：**如果被强制夺走会导致进程失败**（例如CD刻录机）。

### 进程对资源的使用
- 进程使用资源的步骤：
  1. 请求资源。
  2. 使用资源。
  3. 释放资源。
- ==如果请求被拒绝，进程必须等待，可能会被阻塞或返回错误代码==。

### 死锁的产生

- 进程需要以合理的顺序访问资源
- 死锁的典型场景：==两个进程分别持有对方请求的资源，导致双方都无法继续执行==。
- 死锁的定义：**一组进程中的每个进程都在等待一个事件，而该事件只能由该组中的其他进程引起**。通常这个事件是资源的释放。
  - 此时没有一个进程可以：运行，释放资源，被唤醒。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271422552.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271423431.webp)

## 死锁的条件
死锁的产生需要同时满足以下四个条件：
1. **互斥条件**：每个资源**只能分配给一个进程，或者处于可用状态**。
2. **占用和等待条件**：进程在**持有资源的同时，可以请求额外的资源**。
3. **不可抢占条件**：已经分配给进程的资源**不能被强制夺走，必须由持有它的进程显式释放**。
4. **循环等待条件**：必须**存在一个由两个或更多进程组成的循环链**，==每个进程都在等待下一个进程持有的资源==。

## 死锁的建模
### 1. 资源分配图（Resource-Allocation Graph）
- **定义**：由一组顶点 $ V $ 和一组边 $ E $ 组成。
  
  - $ V $ 分为两类：
    - $ P = \{P_1, P_2, \ldots, P_n\} $：系统中的所有进程。
    - $ R = \{R_1, R_2, \ldots, R_m\} $：系统中的所有资源类型。
  - 边的类型：
    - 请求边（request edge）：从进程 $ P_i $ 到资源 $ R_j $ 的有向边。
    - 分配边（assignment edge）：从资源 $ R_j $ 到进程 $ P_i $ 的有向边。
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271430627.webp)
- **死锁的表示**：如果资源分配图中存在环，则可能存在死锁。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271429454.webp)

### 2. 资源分配图的示例

- **如果 图 无环，则无死锁**。
- 如果包含环：
  - **如果每种资源类型只有一个实例，则死锁**。
  - 如果每个资源类型**有多个实例，则可能会发生死锁**。
- 通过资源分配图可以清晰地展示进程和资源之间的关系，以及死锁的产生过程。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271431803.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271431349.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271432559.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271433980.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271433298.webp)







## 处理死锁的方法

### 1. 忽略问题（The Ostrich Algorithm）
- **方法**：==假装死锁不存在==。
- **适用场景**：**如果死锁很少发生，且预防死锁的成本很高，这种方法是合理的。**
- **例子**：**Unix和Windows采用这种方法，是一种在便利性和正确性之间的权衡**。

### 2. 死锁检测与恢复
- **检测**：允许系统进入死锁状态，定期运行死锁检测算法。

- **恢复**：检测到死锁后，运行恢复算法。

- **检测算法**：
  - 对于每种资源只有一个实例的情况，==可以通过检测资源分配图中的环来判断是否存在死锁==。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271440369.webp)
  
    **算法一**：定期在图中搜索环
  
    - 使用一个数据结构 $L$（一个节点列表）。
    - 对检查过的圆弧进行标记，表示已经检查过，防止重复检查。
    - 对于图中的每个节点 $N$，以 $N$ 作为起始节点，执行以下 5 个步骤。
      1. 将 $L$ 初始化为空列表，并将所有圆弧指定为 unmarked。
      2. 将当前节点添加到 $L$ 的末尾，并检查该节点现在是否在 $L$ 中出现两次。如果是这样，则图形包含一个循环（以 L 列出），并且算法终止。
      3. 从给定的节点中，查看是否有任何未标记的传出弧。如果是这样，请转到步骤 4；如果没有，请执行步骤 5。
      4. 随机选择一个未标记的传出圆弧并标记它，然后按照它转到新的当前节点并转到步骤 2。
      5. 现在已经走到了死胡同。删除它并返回到上一个节点，使其成为当前节点，然后转到步骤 3。如果此节点是初始节点，则图形不包含任何循环，并且算法将终止。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271457686.webp)
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271457099.webp)
  
    
  
  - 对于每种资源有多个实例的情况，需要使用更复杂的算法来检测死锁。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271459344.webp)
  
    **算法二**：
  
    - 基于比较向量（$A < B \text{ if and only if } A_i < B_i \forall  \ 1 \leq i \leq m$）
  
    - 每个进程最初都是未标记的
  
      1. 查找 $R$ 的第 $i$ 行小于或等于 $A$ 的未标记进程 $P_i$。（可以满足 $P_i$ 的请求）
      2. 如果找到这样的进程，请将 $C$ 的第 $i$ 行添加到 $A$ 中，标记该进程并返回步骤 1。（ 当 $P_i$ 完成时，其资源将变为可用）。
      3. 如果不存在此类进程，则算法将终止。未标记的进程（如果有）处于死锁状态。
  
      ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271508907.webp)

### 3. 死锁避免（Deadlock Avoidance）
- **目标**：==动态检查资源分配状态，确保系统永远不会进入死锁状态==。

- **方法**：要求进程**在运行前声明其对每种资源的最大需求**。

  - **动态避免（谨慎分配资源）**
  - **否定四个必要条件之一**

- **安全状态**：如果**存在一种进程执行顺序，使得所有进程的资源请求都能被满足，则系统处于安全状态**。当**进程请求可用资源**时，系统必须确定立即分配是否使系统处于安全状态。

  - 如果系统处于安全状态，则没有死锁。
  - **如果系统处于不安全状态，则可能出现死锁**。
  - 确保系统**永远不会进入不安全状态。**

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271521681.webp)

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271521182.webp)

  

- **银行家算法（Banker's Algorithm）**：

  - 每个进程**在运行前声明其对每种资源的最大需求**。
  - 系统在分配资源时，检查是否会导致系统进入不安全状态。
  - **如果分配后系统仍处于安全状态，则分配资源；否则拒绝分配**。 

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271524843.webp)

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271525902.webp)

  检查状态是否安全：

  1. 在 $R$ 中**寻找小于 $A$ 的新行，如果不存在这样的行，则系统最终将死锁，不安全**。
  2. 如果存在此类行，则该过程可能会完成。将该进程（行）标记为 terminate，并将其所有资源添加到 $A$。
  3. 重复步骤 1 和 2，直到所有行都标记为安全状态，（或未标记，则不安全）。

- **从死锁中恢复**：

  - 通过**抢占进行恢复：**从其他进程中获取资源（取决于资源的性质）
  - 通过**回滚进行恢复**：定期对进程进行 checkpoint 操作，保存进程状态，如果发现进程已死锁，则重新启动进程。
  - 通过**杀死进程进行恢复**：
    - 杀死死锁循环中的一个进程，然后其他进程获取其资源。
    - kill 进程，可以从头开始重新运行，没有不良影响
    - 打破僵局的最粗暴但最简单的方法 


### 4. 死锁预防（Deadlock Prevention）
- **目标**：==通过限制请求的方式，防止死锁的发生==。

- **方法**：
  
  - **互斥条件**：==通过资源共享（例如打印机的后台打印）来避免互斥==。
  
    - 某些设备（如打印机）可以假脱机  Some devices (such as printer) can be **spooled**
  
      1. 只有 printer daemon 进程 使用 printer 资源
      2. printer daemon 进程不请求其他资源，从而消除了打印机的死锁
  
      假脱机空间有限，因此此决定仍可能出现死锁，如：两个进程各占可用空间的一半，并且无法继续，因此磁盘上存在死锁
  
    - **原则**：**避免在非绝对必要的情况下分配资源，实际声明资源的进程尽可能少**
  
    - **问题**：并非所有设备都可以假脱机
  
  - **保持和等待条件**：要求进程在开始运行前**请求所有资源**。进程**永远不必等待它需要的东西**
  
    - **问题**：
      1. 在运行开始时**可能不知道所需的资源**
      2. 还会**占用其他进程可能正在使用的资源**
    - **变化**：进程请求资源必须放弃它当前持有的所有资源，然后立即请求所有需要的资源
  
  - **不可抢占条件**：通过**强制抢占资源来解决**，但实际中很难实现。
  
    - 强制抢占可以违反此条件
    - **资源虚拟化**：
      1. 将打印机输出假脱机到磁盘
      2. 仅允许 printer daemo 进程访问真实打印机。
    - **问题**：并非所有资源都可以虚拟化
  
  - **循环等待条件**：通过**全局资源排序或限制进程请求资源的顺序来避免循环等待**。
  
    - 方法1：**一次请求一个资源，请求下一个资源时释放当前资源。**
    - 方法2：资源按照全局排序，请求必须按升序进行。
    - 方法3：方法2变体，没有进程请求低于其已持有的资源。
    - **问题**：找到合适的编号来满足每个人可能很困难，增加了程序员了解编号的负担。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271606793.webp)
  
- **防止死锁方法总结**：

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271607672.webp)

## 死锁的其他问题
### 1. 两阶段锁定（Two-Phase Locking）
- **第一阶段**：进程依次尝试**锁定所有需要的记录，如果发现需要的记录已被锁定，则重新开始**。
- **第二阶段**：如果第一阶段成功，则**执行更新并释放**锁。
- **特点**：类似于一次性请求所有资源。
- 算法在程序员可以安排的地方工作，程序可以停止、重新启动。

### 2. 通信死锁（Communication Deadlocks）
- **定义**：一组进程，每个进程**都在等待另一个进程引起的事件**。
- **例子**：进程A向进程B**发送请求消息并阻塞等待回复，如果请求消息丢失，B会阻塞等待请求**。
- **解决方案**：设置**超时机制**。

### 3. 活锁（Livelock）
- **定义**：进程运行**但没有取得进展，例如忙等待（busy waiting）可能导致活锁**。

- **例子**：

  - 两个进程分别持有对方需要的资源，但都不释放，导致双方都无法继续。
  - **轮询（忙等待）**，用于进入关键区域或访问资源，可能会导致活锁

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505271553794.webp)

### 4. 饥饿（Starvation）
- **定义**：资源分配算法**可能导致某些进程无限期地推迟执行，即使它们没有被阻塞**。
- 非常适合系统中的多个短期作业。
- **例子**：总是优先分配给短作业，可能导致长作业无限期等待。
- **解决方案**：采用先来先服务（FCFS）策略。

## 总结
- **死锁处理的成本**：**死锁检测或避免通常是昂贵的**，需要权衡死锁的成本与检测或避免的成本。
- **死锁避免和恢复的缺点**：可能导致某些进程**无限期地推迟执行**。
- **主流操作系统的做法**：Unix和Windows通常采用忽略问题的方法（The Ostrich Algorithm）。

