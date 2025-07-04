# 第二章：进程和线程
## 2.1 进程
### 2.1.1 顺序执行与并发执行
- **顺序执行**：
  
  - 在单道程序系统中，**一个程序独占处理器，直到执行结束**。
  - 特点：**程序结构顺序执行（可能包含循环或分支）、独占资源、结果可重现**。
  
- **并发执行**：
  
  顺序执行的特点全部消失
  
  - **多个程序同时运行，共享系统资源**。
  - 问题：资源竞争、通信与协作。
  - 解决方案：引入进程概念。

### 2.1.2 进程模型
- **多道程序**：
  - 多个程序**同时加载到内存中，共享CPU和资源**。
  - 问题：如何管理这些程序的运行？
  - 解决方案：将运行中的程序抽象为“进程”。
- **进程定义**：
  - 进程是**正在执行的程序**。
  - 进程是程序在**某个数据集合上的一次活动**。
  - 类比：生日蛋糕食谱（程序）与实际烘焙过程（进程）。
  - 进程的类型多样，可以参考如下图：
  - ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505202015776.webp)

### ==2.1.3 进程与程序的区别==
- **程序**：
  - 静态概念，是指令的集合。
  - 永久存在。
- **进程**：
  - 动态概念，描述并发性。
  - 包含程序、数据和进程控制块（PCB）。
  - 临时存在。
  - 一个程序可以对应多个进程，一个进程也可以调用多个程序。
  - 进程可以创建其他进程。

### 2.1.4 进程创建
- **触发事件**：
  - **系统初始化（如重启）**。
    - Foreground process：用于与用户进行交互
    - Background process：用于处理后台
  - **执行进程创建系统调用（如UNIX中的`fork()`）**。
  - **用户请求创建新进程（如命令行或点击图标）**。
  - **批处理作业启动**。
  
- **UNIX中的进程创建**：
  
  - 使用 `fork()` 系统调用创建新进程。
  
  - 初始时，父进程和子进程**共享相同的内存映像、环境字符串和打开的文件**。
  
    > Initially, the parent and the child have the same memory image, the same environment strings, and the same open files.
  
  - 使用 `execve()` 系统调用加载新程序。
  
  - 父进程和子进程**拥有独立的地址空间**。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505202147789.webp)
  
- **Windows中的进程创建**：
  
  - 使用`CreateProcess`函数，同时完成进程创建和程序加载。
  
- 列举正在运行的进程：

  - UNIX：使用 `ps` 命令
  - Windows：使用 任务管理器


### 2.1.5 进程终止
- **终止条件**：
  - 正常退出（如UNIX中的`exit`或Windows中的`ExitProcess`）。（自愿退出）
  - 错误退出（如编译错误）。（自愿退出）
  - 致命错误（如除以零、非法指令、访问不存在的内存）。（非自愿退出）
  - 被其他进程终止（如UNIX中的`kill`或Windows中的`TerminateProcess`）。（非自愿退出）

### 2.1.6 进程层次结构
- **父进程与子进程**：
  - 父进程创建子进程，子进程可以创建自己的子进程。
  - 形成层次结构（如UNIX中的“进程组”）。
  - Windows中没有进程层次结构的概念，所有进程地位平等。

### 2.1.7 进程状态
- **基本状态**：
  - **运行**：正在使用CPU。
  
  - **就绪**：可运行（在就绪队列中）。
  
  - **阻塞**：等待外部事件（如按键输入）。
  
    进程之间的转移关系如下：
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261045454.webp)
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261047791.webp)
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261048456.webp)
  
- **其他状态**：
  - **新建**：进程正在被创建。
  - **退出**：进程正在被终止。
  
- **状态转换**：
  - 运行 → 就绪：**时间片用完**。
  - 运行 → 阻塞：**等待I/O操作**。
  - 就绪 → 运行：**调度器分配CPU**。
  - 阻塞 → 就绪：**I/O操作完成**。

### 2.1.8 进程的实现
- **进程内容**：
  - **用户程序**。（对应的是用户的私人地址空间）
  - **用户数据**。（对应的是用户的私人地址空间）
  - **栈**（用于过程调用和参数传递）。
  - 进程控制块（PCB）：包含了**进程 ID、进程的状态信息、进程的控制信息**
  
- **PCB的作用**：
  
  - **记录进程的属性**。
  
  - 不同操作系统PCB结构不同（**如Linux的`task_struct`，包含106个字段**）。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261052757.webp)
  
- **进程上下文**：
  - 静态描述整个执行过程。
  - 包括**用户上下文、寄存器上下文和系统上下文**。
  
- **上下文切换**：
  - **从一个进程切换到另一个进程**。
  - 由调度器完成。
  - 包括**保存旧进程的PCB状态、加载新进程的PCB状态、刷新内存缓存和更改内存映射**。
  - 开销较大（1-1000微秒），可能成为瓶颈。

### 2.1.9 进程表
- **进程表的作用**：
  - 操作系统维护进程表，每个条目是一个PCB。
  - 进程表的大小决定了系统的并发程度。
  
- **组织形式**：
  - 链表。
  
  - 索引表。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261056568.webp)

## 2.2 线程
### 2.2.1 线程的概念
- **目标**：
  - **使多个程序更好地并发执行，同时减少系统开销。**
  - 将进程的两个基本属性分开处理。
- **线程定义**：
  
  - **进程内的一个顺序执行流。**
  - 线程**将执行的概念与进程的抽象分开**。
  
  - > 对于作为调度和分派的基本单位，不同时作为拥有资源的单位， 以做到“轻装上阵”； 对于拥有资源的基本单位，又不对之进行频繁的切换
    >
    > ---
    >
    > ### 1. **线程作为调度/分派的基本单位（轻装上阵）**
    >    - **特点**：**线程是CPU调度的最小单位**，但**不单独拥有资源**（如内存、文件等），而是**共享所属进程的资源**。
    >    - **优势**：
    >      - 线程切换时**只需保存/恢复少量寄存器状态**（如程序计数器、栈指针），无需切换内存空间、文件句柄等资源，因此**切换开销远低于进程切换**。
    >      - 同一进程内的多线程可以快速切换，实现并发执行（例如：一个线程阻塞时，CPU可立即切换到同进程的其他线程）。
    >
    > ---
    >
    > ### 2. **进程作为拥有资源的基本单位（减少资源切换）**
    >    - **特点**：进程是资源分配的基本单位，拥有独立的内存空间、文件描述符等。
    >    - **优势**：
    >      - 由于资源切换（如内存映射、权限检查）开销大，操作系统**尽量避免频繁切换进程**。
    >      - 线程的引入使得**无需切换进程也能实现并发**（多个线程共享同一进程的资源）。
    >
    > ---
    >
    > ### 3. **实际场景中的效果**
    >    - **同一进程的多线程切换**：  
    >      确实可以通过线程切换（而非进程切换）实现快速任务调度，例如：
    >      - Web服务器**用多线程处理请求，线程切换开销低，能高效服务大量并发用户**。
    >      - GUI程序用单独线程处理界面响应，避免主线程阻塞。
    >    - **跨进程的切换**：  
    >      若需切换进程（如从浏览器切换到游戏），则开销较大，因为涉及资源切换。
    >
    > ---
    >
    > ### 4. **补充：与进程切换的对比**
    > | **操作**     | **线程切换**       | **进程切换**             |
    > | ------------ | ------------------ | ------------------------ |
    > | **资源切换** | 无（共享进程资源） | 需要（切换内存、文件等） |
    > | **开销**     | 低（仅CPU上下文）  | 高（CPU上下文+资源切换） |
    > | **速度**     | 快                 | 慢                       |
    >
  
- **线程与进程的关系**：
  - **线程是CPU利用的基本单位。**
  - **进程是资源分配的基本单位。**
- **线程控制块（TCB）**：
  - 线程的标识。
  - 记录**线程属性和调度信息**（如Linux的`thread_struct`，包含24个字段）。
- **多线程**：
  - 一个进程可以有多个线程。
  - 多线程可以同时执行多个任务。
  
- 更具体地说：原进程 PCB 分成了两部分

  - 描述**进程资源和空间的部分**
  - 描述**执行现场、状态及调度的部分**。
  - 将第二部分内容**作为线程控制块TCB的内容**，且一个进程内允许多个线程存在。

  此外新进程描述为：

  - 一个独立的进程空间，**可装入进程映像**
  - 一个独立的进程**相关联的执行文件**
  - 进程**所用的系统资源**
  - **一个或多个线程。**（进程在创建时一般同时创建好第一个线程，其他线程按需要由用户程序请求创建）

- 线程拥有其运行所必需的一些数据结构： **TCB，程序计数器，寄存器集合，堆栈，它与该进程的其他线程共享该进程所拥有的全部资源。**

  - **堆栈和寄存器用来存储线程内的局部变量**
  - 线程控制块 TCB 用来说明线程**存在的标识、记录线程属性和调度信息**


### 2.2.2 ==线程与进程的区别==
- **资源分配**：
  - 进程是**资源分配的基本单位**，拥有独立的虚拟地址空间。
  - 线程**不拥有资源，共享进程的资源**。
- **地址空间**：
  - 不同进程有不同的虚拟地址空间。
  - 同一进程中的线程共享同一地址空间。
- **切换开销**：
  - 进程切换涉及**资源指针保存和地址空间转换，开销较大**。
  - 线程切换**不涉及资源指针保存和地址空间变化，开销较小**。
- **调度**：
  - 进程调度由操作系统内核完成。
  - 线程调度可以由内核完成，也可以由用户程序完成。
- **创建**：
  - 进程可以**动态创建进程**。被进程创建的线程**也可以创建其它线程**。

- **生命周期**：
  - 进程和线程都有创建、执行和消亡的生命周期。

### 2.2.3 线程的优势
- **创建和销毁速度快**。
- **切换速度快**。
- **通信简单**：**线程共享进程的内存和文件资源**。
- **利用多处理器架构**：在多CPU系统中，多线程可以提高性能。

### 2.2.4 线程模型
- **单线程进程**：
  - 每个进程只有一个线程。
- **多线程进程**：
  - 一个进程可以有多个线程。
  - **线程共享进程的资源，但每个线程有自己的栈**。
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261110000.webp)
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261111279.webp)
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261111573.webp)
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261115239.webp)



### 2.2.5 线程的使用场景

- **提高响应性**：多个活动**可以同时进行，提高程序的运行速度**。

- **资源共享**：线程**共享进程的内存和资源**。

- **经济性**：**线程创建和销毁简单**。

- **多处理器架构的利用**：**在多CPU系统中，多线程可以提高性能**。

- **示例**：
  
  - 文字处理软件：一个线程与用户交互，一个线程格式化文档，一个线程定期保存文件。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261118480.webp)
  
  - Web服务器：一个线程分发请求，多个工作线程处理请求。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261118241.webp)

### 2.2.6 线程的实现
- **用户级线程（ULT）**：
  - 完全**在用户空间实现，内核不知道线程的存在**。
  - 线程管理由用户级线程库完成。
  - 线程切换**不需要内核权限，创建和管理速度快**。
  - 问题：如果**内核是单线程的，任何用户级线程执行阻塞系统调用时，整个进程都会阻塞**。
  - 示例：POSIX Pthreads、Mach C-threads、Solaris UI-threads。
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261120317.webp)
  
- **内核级线程（KLT）**：
  
  - 内核支持**线程的创建、调度和管理**。
  
  - 内核**维护进程和线程的上下文**。
  
  - 线程切换**需要内核支持**。
  
  - 线程是**调度的基本单位**。
  
  - 优点：支持多处理器架构。
  
  - 缺点：**开销较大**。
  
  - 示例：Windows 95/98/NT/2000/XP。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261120859.webp)
  
- **混合实现**：
  - 将用户级线程映射到内核级线程。
  
  - 示例：Sun Solaris。
  
    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261121827.webp)

### 2.2.7 弹出式线程
- **定义**：
  - 当消息到达时，动态创建新线程。
- **应用场景**：
  - 处理突发的请求或事件。
  
  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202505261123739.webp)

