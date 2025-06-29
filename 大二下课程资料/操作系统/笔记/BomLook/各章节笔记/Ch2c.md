# Ch2c

## 进程与线程概述
### 进程（Processes）
- 进程是操作系统**进行资源分配和调度的基本单位**。
- 每个进程有**其独立的内存空间、程序计数器、寄存器集合**等。

### 线程（Threads）
- 线程是进程内的一个执行单元，是**CPU调度的最小单位**。
- 一个进程可以包含多个线程，线程共享进程的资源。

### 进程间通信（Inter-process Communication, IPC）
- 进程间通信是多个进程之间交换数据或信息的方式。
- 常见的IPC方式包括管道（Pipes）、消息队列（Message Queues）、共享内存（Shared Memory）等。

### 经典IPC问题（Classical IPC Problems）
- 生产者-消费者问题（Producer-Consumer Problem）：生产者生成数据，消费者消费数据，需要同步机制避免数据丢失或覆盖。
- 读者-写者问题（Readers-Writers Problem）：多个读者可以同时读取资源，但写者需要独占资源。
- 哲学家就餐问题（Dining Philosophers Problem）：多个哲学家围坐一圈，需要同时拿起左右两根筷子才能就餐，避免死锁。

## 调度（Scheduling）
### 调度的定义
- **调度**：决定哪个进程/线程应该占用资源（如CPU）来运行。

- **解决问题**：

  - 在何时（调度机会）将 CPU 分配给进程？
  - 何种（调度算法）的分配原则是什么？
  - 如何（上下文切换）进行 CPU 分配？调度进程？

- 调度的目标是**优化资源利用率、提高系统性能和响应速度**。

- **进程行为**：通常由 CPU burst 和 I / O burst 组成。

  - A period of time when a process needs the CPU is called a CPU burst
  - A period of time when a process needs I/O is called a CPU burst.

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505272349251.webp)

  - burst 的持续时间和频率因进程而异：

    - CPU 密集型进程：长时间 CPU burst，不需要频繁的 I / O 等待（例如：数值计算任务，图像处理）
    - I/O 密集型进程：短时间的 CPU burst，频繁的 I / O 等待（例如，一个处理磁盘数据的任务，比如统计文件中的行数，很可能是 I/O 受限的）
    - **随着 CPU 变快，进程往往会变得更加 I/O 受限**。

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505272353054.webp)

### 调度的时机
- 新进程创建时。（需要）
- 运行中的进程退出时。（有空闲）
- 运行中的进程被阻塞时。（临时有空闲）
- I/O中断发生时。（有其他任务）
- 时钟中断发生时（如每10毫秒一次）。（轮流）

### 抢占式与非抢占式调度
- **非抢占式调度（Non-preemptive Scheduling）**：运行中的进程会一直占用CPU，直到它自愿释放CPU。
- **抢占式调度（Preemptive Scheduling）**：运行中的进程可以被中断，强制释放CPU。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505272358892.webp)

### 调度算法的分类
- **批处理系统（Batch Systems）**：
  - **非抢占式算法。**
  - 例如：先来先服务（FCFS）、最短作业优先（SJF）。
  - 抢占式算法（每个进程具有较长时间段）
- **交互式系统（Interactive Systems）**：
  - **需要抢占式调度。**
  - 例如：时间片轮转（Round-Robin）、优先级调度（Priority Scheduling）、多队列与多级反馈队列（Multi-Queue & Multi-level Feedback）。
- **实时系统（Real-Time Systems）**：
  - **有时不需要抢占式调度。**
  - 例如：保证调度（Guaranteed Scheduling）、彩票调度（Lottery Scheduling）、公平共享调度（Fair Sharing Scheduling）。

## 调度算法

**一个优秀调度算法的特性**

- **公平、存在优先级、高效**、支持高负债、鲁棒性强（适应不同的环境）、Encourage good behavior（？）



**性能衡量标准**

不同系统的侧重点不同，一般来说，对于所有系统，需要考虑：公平性、效率、政策执行三方面。

- 公平性：没有进程遭受饥饿
- 效率：尽可能让资源保持忙碌
- 政策执行：确保已声明的政策得到执行



各个系统的侧重点如下：

- 批处理系统：
  - **吞吐量：单位时间内完成的进程数量**
  - **周转时间（又称为 elapse time ）：从开始进入到执行特定进程所需的时间**
  - 等待时间：进程在就绪队列中等待的时间
  - 处理器利用率：CPU 繁忙时的时间百分比
- 交互式系统：
  - 响应时间：从**首次提交请求**到**产生第一个响应**所经过的时间量。
  - 比例性 Proportionality：需要满足用户期望
- 实时系统：
  - **按时完成任务，避免数据丢失**
  - 可预测性：无论系统负载如何，时间/成本始终相同

### 批处理系统调度算法
#### 先来先服务（First-Come First-Served, FCFS）
- **原理**：按照进程到达的顺序分配CPU。

- **实现**：使用FIFO队列。

- **优点**：简单。

- **缺点**：

  - 可能**导致长作业阻塞短作业（“护航效应”），平均等待时间可能较长**。
  - **无法并行利用资源：可能一个进程时 CPU 密集型，而其他进程是 I / O 密集型**

- **性能指标**：平均等待时间

- **给定参数**：执行时间、到达时间和顺序

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280029936.webp)

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280029401.webp)

- **护航效应**

  - 考虑系统中存在 $n-1$ 个 I/O 密集型任务和 1 个 CPU 密集型任务。
  - I/O 密集型任务迅速通过就绪队列，并挂起等待 I/O。CPU 密集型任务到达队列头部并执行直到完成。
  - I/O 密集型任务重新加入就绪队列，等待 CPU 密集型任务完成。
  - **I/O 设备空闲，直到 CPU 密集型任务完成。**
  - **当 CPU 密集型任务完成时，其他进程再次争相等待 I/O**。而 CPU 变得空闲

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280033940.webp)

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280033974.webp)



#### 最短作业优先（Shortest Job First, SJF）

- **原理**：优先调度预计运行时间最短的进程。
- **需求**：需要提前知道经过的时间。
- **类型**：
  - 非抢占式（Non-preemptive）。
  - 抢占式（Preemptive），也称为最短剩余时间优先（Shortest Remaining Time First, SRTF）。
- **优点**：在所有作业**同时到达时**，**可以实现最小的平均等待时间**。
- **缺点**：可能导致**饥饿现象**（**长作业永远无法运行**）。
  - 例子：进程 A 的运行时间为 1 小时，在时间 0 到达，从时间 0 开始，每隔 1 分钟，一个运行时间为 2 分钟的短进程就会到达，这样的结果是 A 永远无法运行。




**非抢占式 SJF**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280035055.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280035274.webp)

**但如果不是所有作业同时可用，不一定是最优的。**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280038250.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280038795.webp)



**抢占式 SJF**

- 也被称为最短剩余时间优先：安排需要最短剩余时间完成的任务
- **要求**：需要提前知道经过的时间

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280056990.webp)

### 交互式系统调度算法

- 通常具有**抢占性**
  - **时间被分割成时间片（时间间隔）**
  - 调度决策在**每个时间片的开始时做出**
- 性能衡量标准：
  - **最短响应时间**
  - **最佳比例（？）**

#### 时间片轮转（Round-Robin, RR）
- **原理**：将时间切分成固定长度的“时间片”（Quantum），每个进程轮流运行一个时间片。
- **优点**：**简单，响应时间短，适合交互式系统。**
- **缺点**：**时间片过大时，类似于FCFS；时间片过小时，上下文切换开销大。**
  - 启发式方法：70-80% of jobs block within time-slice
  - 典型时间片：10~100ms

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280101307.webp)

==注意 P2 和 P3 是 0 时刻到达的，所以需要注意计算之前的时间==

#### 优先级调度（Priority Scheduling）
- **原理**：每个进程**分配一个优先级，优先级高的进程优先调度**。
- **实现**：在每个优先级内使用FCFS。**优先选择高优先级任务而非低优先级任务**（高优先级任务更关键）。
- **优点**：可以**满足不同进程的重要性和紧急性**。
- **缺点**：**可能导致低优先级进程饥饿。**
- **方法**：实现方法有两种
  - **静态（适用于具有良好且常规的应用行为的系统）**
  - **动态（适用于其他情况）**

- **优先级**可以基于：用户成本，用户重要性，进程类型，资源需求，老化，过去某个时间段内的 CPU 时间百分比

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505280110179.webp)

#### 多队列调度（Multi-Queue Scheduling）

是**优先级调度和轮转调度的结合**，适用于可以将进程根据属性（如进程类型、CPU 时间、IO 访问、内存大小等）分类成组的场景。

- **原理**：将**就绪队列分成多个队列，将进程分类到不同的队列中，每个队列有自己的调度算法**。

- **实现**：例如，交互式进程使用时间片轮转，后台进程使用FCFS。

- **优点**：可以根据进程类型优化调度策略。

- **缺点**：**固定优先级可能导致饥饿**。

- **示例**：系统进程（最高优先级），交互式进程（轮转调度），后台进程（FCFS），学生进程

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505281005009.webp)

  

#### 多级反馈队列调度（Multi-level Feedback Queue Scheduling）
- **原理**：进程**在不同优先级的队列之间移动**，**每个队列有自己的时间片**。
- **实现**：新进程**从高优先级队列开始，每次完成一个CPU burst 后，移动到低优先级队列**。
  - 每个队列中，其中的工作具有相似的 CPU 使用率
  - 在给定队列中的任务，按照指定的时间片执行

- **优点**：可以**动态调整进程的优先级，避免饥饿。**
- **理由**：**一旦一个 I/O 进程完成一个 I/O 请求，它应该具有更高的 CPU 优先级，反之，如果任务未完成，则降级**。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505281016580.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505281016936.webp)



**例题**

**Show your schedule with timeline and calculate the average turnaround time when use multi-level feedback queue as below. (Please take arrival time into account.) Note that the priority of the top 2 queues is based on arrival times.**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505281018068.webp)



![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505281022148.webp)

### 其他调度算法

#### 保证调度（Guaranteed Scheduling）
- **原理**：为每个进程**分配固定的CPU时间份额，确保每个进程都能获得公平的CPU时间**。（按照进程分配）
- **实现**：计算每个进程实际消耗的CPU时间与应得的CPU时间的比率，**选择比率最低的进程运行**。

#### 彩票调度（Lottery Scheduling）
- **原理**：为进程分配“彩票”，**调度时随机选择一个彩票，持有该彩票的进程获得CPU。给高优先级进程分配更多彩票（近似优先级），或给短任务分配更多彩票（近似最短作业优先）**
- **优点**：**简单，响应速度快，能够支持进程间协作，可以支持优先级和比例要求。**

#### 公平共享调度（Fair Sharing Scheduling）
- **原理**：从用户角度出发，确保每个用户**获得公平的CPU时间份额**。（按照用户分配）
- **实现**：例如，一个用户有多个进程，这些进程共享该用户的CPU份额。
- **例子**：
  - Alice 有 4 个进程：A1、A2、A3、A4，Bob 有 1 个进程：B1
  - 然后 A1、A2、A3、A4 只能获得 50%的 CPU，而 B1 独占 50%
  - 可能的调度序列：A1，B1，A2，B1，A3，B1，A4，B1……


## 实时系统调度
- **实时系统**：调度器对用户做出关于截止时间和CPU利用率的真实承诺。

- **可调度的实时系统**：给定多个周期性事件，每个事件在周期内发生并需要一定时间，调度器需要确保系统负载可以被处理。

  具体如下：给定 $m$ 个周期性时间，事件 $i$ 在周期 $P_i$ 完成，且需要 $C_i$ 秒，当且仅当：
  $$
  \sum_{i=1}^{m} \frac{C_i}{P_i} \leq 1
  $$
  系统负载可以解决需求。

## 线程调度
### 用户级线程调度（User-level Thread Scheduling）
- **特点**：线程调度由**运行时系统完成，内核不感知线程的存在**。

- **限制**：**线程切换依赖于进程切换，无法实现真正的抢占式调度**。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505281340742.webp)

### 内核级线程调度（Kernel-level Thread Scheduling）
- **特点**：内核直接管理线程，**可以实现抢占式调度**。

- **优点**：线程**切换效率高，可以实现更细粒度的调度**。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505281340626.webp)

## 总结
- 调度是操作系统中的一个重要功能，用于决定哪个进程或线程占用CPU。
- 不同的调度算法适用于不同的系统类型（批处理、交互式、实时系统）。
- 调度算法需要平衡公平性、响应时间和资源利用率。

---

## 总结
- **进程与线程**：进程是**资源分配的基本单位**，线程是**CPU调度的最小单位**。
- **调度**：决定哪个进程或线程占用CPU，调度算法需要根据系统类型和需求选择。
- **调度算法**：包括FCFS、SJF、RR、优先级调度、多队列调度、多级反馈队列调度等。
- **实时系统调度**：需要**满足严格的截止时间和CPU利用率要求**。
- **线程调度**：用户级线程调度和内核级线程调度各有优缺点。