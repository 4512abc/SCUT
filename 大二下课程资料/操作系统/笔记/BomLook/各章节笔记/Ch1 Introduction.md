# Ch1 Introduction

## 1.1 What is an operating system

计算机系统由两部分组成：

- 硬件部分

- 软件部分

  - User mode：

    - Web browser
    - Email reader
    - Music player
    - User interface program

  - Kernel mode：

    - Operating System

**不同角度解析OS**

**OS 是一台 extended machine（top-down）**

- 隐藏了诸多需要执行的混乱细节。
- 向用户提供了容易使用的虚拟机。



**OS 是一位 resource manager（bottom-up）**

- **允许多个程序同时运行。**
- **管理和保护内存，I/O设备和其他资源**。
  - 通过两种方式，包括多重（共享）资源：
    - time 时间
    - space 空间

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251416761.webp)

## 1.2 History of Operating Systems

### First generation 1945 -1955

Vacuum tubes 真空管，plug boards 插头板

- mode
  - 用户：operator and programmer
  - 语言：machine language
  - I/O：plugboard 插头板，punched cards 打孔卡
- characteristic
  - The user occupy the machine alone
  - CPU wait the user load and unload the plugboard
- conflict
  - CPU（high）------ handwork（low）CPU 速度和 handwork 速度之间的差距的矛盾
- method
  - Special operator，batch system 特殊操作员，批处理系统

### Second generation 1955 -1965

Transistors 晶体管，batch system 批处理系统

- mode

  - 用户：operator or programmer

  - 语言：assembly language，Fortran

  - I/O：card，tape（磁带）

  - OS：Monitor（execute the jobs）

  - online batch system / offline batch system（在线批处理系统 / 离线批处理系统）

    早期离线批处理系统

    - Programmers bring cards to 1401
    - 1401 reads batch of jobs onto tape
    - Operator carries input tape to 7094
    - 7094 does computing
    - Operator carries output tape to 1401
    - 1401 prints output

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251512497.webp)

- 典型的 FMS job 结构

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251514506.webp)

### Third generation 1965 - 1980

ICs and multiprogramming ICs 和 多程序

- Batch system：良好的效率，互动性差

- time-sharing system（多程序的变体）：

  - multi users share the computer, each has a online terminal 多用户共享计算机，每个用户都有一个在线终端。
  - Allocate CPU by time slice 按照时间片分配CPU。
  - quick response time 快速响应时间。

- mode

  - Partition memory into several pieces, with a different job in each partition 将内存划分为几个部分，每个分区中都有不同的工作

  -  Parallel in macroscopic 宏观并行

  - Serial in microcosmic 微观串行

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251525423.webp)

    （Multiprogramming system:  three jobs in memory）

### Fourth generation 1980 - present

Personal computers（Network operating systems and distributed operating systems）

个人计算机（网络操作系统和分布式操作系统）

- Large scale integration（LSI）大规模集成
- Operating systems for personal computers
  - CP/M (Control Program for Microcomputers)
  - DOS (Disk Operating System) ➔ MS-DOS
  - GUI (Graphical User Interface)
  - Windows ➔ Windows 95/98/Me
  - Windows NT➔ Windows 2000➔ Windows XP➔ Vista➔Win7 ➔Win8 ➔Win10➔Win11
  - UNIX:
    - X Windows
    - Linux, GNOME, KDE

### Fifth generation 1990 - present

Mobile computers 移动计算机

- Combining telephony and computing in a phone-like device since the 1970s
- The first real smartphone: Nokia N9000, mid-1990s
  - Symbian OS
  - RIM’s Blackberry OS introduced for 2002
  - Apple’s iOS released for the first iPhone in 2007
  - Google’s Android in 2008
  - Huawei’s HarmonyOS NEXT in 2024

## 1.4 The Operating System Zoo

1. Mainframe operating systems 大型机操作系统

   E.g.: OS/390, zOS

2. Server operating systems 服务器操作系统
   E.g.: Solaris, FreeBSD, Linux, Windows Server 201x

3. Multiprocessor operating systems 多处理器操作系统

4. Personal computer operating systems 个人计算机系统
   E.g.: Win 7/8/10/11, Linux, FreeBSD, Apple OS

5. Handheld operating systems 手持操作系统
   E.g.: Android, iOS

6. Embedded operating systems 嵌入式操作系统
   E.g.: QNX, VxWorks
7. Sensor node operating systems 传感器节点操作系统
   E.g.: Tiny OS
8. Real-time operating systems
   Hard real-time system: the action absolutely must occur at a certain moment, such as e-Cos.
9. Smart card operating systems
   Java Virtual Machine (JVM)

## 1.5 Operating System Concepts

### 1.5.1 Processes

- 进程是正在执行的程序。

- 为了描述和控制进程的运行，系统为**每个进程**定义了一个数据结构——**进程控制块PC**B (Process Control Block)。
  所谓系统**创建一个进程，就是由系统为某个程序设置一个PCB，用于对该进程进行控制和管理**。

  进程任务完成，由系统收回其PCB，该进程便消亡。

  系统将根据某PCB而感知相应进程的存在，故说**PCB是进程存在的唯一标志**。

- command interpreter / shell 也是进程，负责从终端读取命令。

- 一个进程可以**创建一个或者多个其他的进程（又称为子进程），这些进程又可以创建他们的子进程。据此我们可以在树结构中创建进程**。

  在UNIX系统中，存在一个父进程，其他所有的进程都是他的子进程。

  下面展示一个进程树，便于熟悉其结构：

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251553747.webp)

  进程 A 创建了两个子进程 B 和 C。

  进程 B 创建了三个子进程 D、E 和 F。

- 进程存在多种状态：running，blocked，ready
- 每个被授予使用系统的人都分配到了一个UID（用户标识符），每个进程都被分配到一个PID（进程标识符）。
- 用户可以是组的成员，每一个组都有一个GID（组标识符）。
- superuser（UNIX中的根用户）拥有特权，**可以违反许多保护规则。**
- interprocess  communication：合作和同步（synchronize）进程的 communication

### 1.5.2 Address Spaces & Files

- Address Space（地址空间）：内存分配表，从 0 到 maximum，进程可以进行读写。

- 在虚拟内存中，操作系统将==地址空间的一部分保存在主存中，部分保存在硬盘中== 。

- 文件系统==为用户提供了一个简洁、清晰的抽象模型，使得用户可以以设备无关的方式操作文件==。

  A file system provides users with a nice, clean abstract model of device-independent files.

- **目录 directory 用于将文件组织在一起。**

- 路径名 path name 可以指定文件的位置。

- 根目录是目录层次的顶层，在UNIX系统中，/是根目录。

- 每个进程都有当前的工作目录（PWD）。

### 1.5.3 Files

例子：

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251622834.webp)

- 如果文件允许访问，系统将返回一个被称为**文件描述符**的小整数，其将在后续的操作中发挥作用。

- 在UNIX系统中，`/dev`目录下存在两种特殊的文件：

  - block special files（disks）
  - character special files（printers，modems）

- 在UNIX系统中，**在UNIX系统中，挂载的文件系统用于处理可移动媒体（如U盘、光盘等）**

  > In UNIX the mounted file system is used to deal with removable media (mount).
  >
  > 这句话的意思是：在UNIX系统中，挂载的文件系统用于处理可移动媒体（如U盘、光盘等）。
  >
  > 具体解释如下：
  >
  > 1. **挂载的文件系统（mounted file system）**：在UNIX和类UNIX系统中，文件系统需要被挂载到一个目录（挂载点）上，才能被访问。挂载是将存储设备（如硬盘分区、U盘等）与目录树关联起来的过程。
  >
  > 2. **可移动媒体（removable media）**：指的是可以随时插入或移除的存储设备，如U盘、光盘、外接硬盘等。
  >
  > 3. **mount命令**：在UNIX系统中，`mount`命令用于将文件系统挂载到目录树中。对于可移动媒体，用户通常需要手动挂载设备，才能访问其中的文件。
  >
  > 总结来说，这句话的意思是：在UNIX系统中，通过挂载文件系统的方式，用户可以访问和管理可移动媒体中的内容。

  e.g.:

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251741429.webp)

  - 挂载之前：CD-ROM上的文件无法进行访问
  - 挂载之后：CD-ROM上的文件是文件层次结构中的一部分

- 管道 pipe：A pipe is a sort of pseudofile that can be used to connect two processes.

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251757024.webp)

  > 这句话的意思是：**管道（pipe）是一种特殊的伪文件，用于连接两个进程**。
  >
  > 具体解释如下：
  >
  > 1. **管道（pipe）**：  
  >    管道是UNIX和类UNIX系统（如Linux）中的一种进程间通信（IPC）机制。它==允许一个进程的输出直接作为另一个进程的输入，从而实现两个进程之间的数据传输==。
  >
  > 2. **伪文件（pseudofile）**：  
  >    管道并不是真正的文件，而是一种特殊的文件类型。它**存在于内存中，不占用磁盘空间**，但可以通过文件描述符（file descriptor）像普通文件一样进行读写操作。
  >
  > 3. **连接两个进程**：  
  >    管道的主要作用是**将两个进程连接起来**。例如，一个进程向管道写入数据，另一个进程从管道读取数据。典型的例子是在命令行中使用 `|` 符号（管道符）将一个命令的输出传递给另一个命令：
  >    
  >    ```bash
  >    command1 | command2
  >    ```
  >    这里，`command1` 的输出会通过管道传递给 `command2` 作为输入。
  >
  > ### 总结
  > 管道是一种用于进程间通信的机制，它像一个伪文件一样工作，==可以将一个进程的输出直接传递给另一个进程的输入==，从而实现两个进程之间的数据传递。

### 1.5.4 Input/Output

- 操作系统必须了解如何与多种类型的外围设备进行通信（e.g.:  键盘、鼠标、监视器、打印机······）

- 每一个操作系统**都有一个 I/O 子系统，用于管理 I/O 设备**。

  - **某些 I/O 软件是独立的设备**
  - 其他部分，例如**设备驱动，特定服务于特定的 I/O 设备**

- 设备驱动程序 Device driver

  - 黑盒子==隐藏了硬件设备的详细信息== 。

  - 主要作用：Map standard calls to device-specific operations. **将标准调用映射到设备特定的操作**

    > 这句话的意思是：**将标准调用映射到设备特定的操作**。
    >
    > 具体解释如下：
    >
    > 1. **标准调用（standard calls）**：  
    >    指的是**操作系统或应用程序中通用的、与设备无关的接口或函数调用**。例如，在UNIX系统中，标准的文件操作调用包括 `open()`、`read()`、`write()` 和 `close()` 等。**这些调用是通用的，不依赖于具体的硬件设备**。
    >
    > 2. **设备特定的操作（device-specific operations）**：  
    >    指的是针对具体硬件设备的操作。不同的硬件设备（如硬盘、键盘、打印机等）可能有不同的实现方式和操作细节。例如，读取硬盘数据和读取键盘输入的具体实现是不同的。
    >
    > 3. **映射（map）**：  
    >    这里指的是将通用的标准调用与具体的设备操作关联起来。操作系统通常会提供一个抽象层（如设备驱动程序），将标准调用转换为设备能够理解和执行的操作。
    >
    > ### 具体过程
    > - 当应用程序调用一个标准函数（如 `read()`）时，操作系统会将该调用传递给相应的设备驱动程序。
    > - 设备驱动程序根据具体的硬件特性，将标准调用转换为设备能够执行的操作。
    > - 例如，`read()` 调用在硬盘上可能是读取磁盘扇区，而在键盘上可能是读取键盘缓冲区。
    >
    > ### 总结
    > 这句话描述的是操作系统**如何通过抽象层（如设备驱动程序）将通用的标准调用（如文件操作）转换为具体硬件设备的操作**。这种映射机制使得应用程序可以以统一的方式访问不同的硬件设备，而无需关心设备的底层细节。

  - 可以与内核的其余部分分开开发，在运行时按需插入。

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251815663.webp)

### 1.5.5 Protection

- 操作系统**必须防止未经授权的资源访问**。
- 必须防止一个用户干扰另外一个用户的资源。
- e.g.:  UNIX系统中的文件受9位二进制保护代码
  - 保护码由三个字段组成：一个用于拥有者，一个用于组，一个用于其他。
  - 每一个字段都有一位用于**读，一位用于写，一位用于执行**，统称为`rwx` 位。

### 1.5.6 Shell

- UNIX 命令行解释器被称为外壳。

- 三类主要的UNIX Shells：

  - Bourne Shell（or Standard Shell）:  sh,  bash
    - 速度快
    - $ 用于命令提示
  - Korn Shell:  ksh
    - sh 的超级
  - C shell:  
    - 带有 C 语言风格的 Shell
    - % 用于命令提示

- 用户可以使用 `<` `>` 重定向标准输入和输出，**在命令后面加上“&”符号，可以将该命令作为后台任务启动**。

  ```bash
  date >file
  sort <file1 >file2
  cat file1 file2 file3 | sort >/dev/lp
  cat file1 file2 file3 | sort >/dev/lp &
  ```

> 这些命令涉及文件操作、输入/输出重定向和后台执行，以下是逐条解释：
>
> ---
>
> ### **1. `date > file`**
> - **功能**：将 `date` 命令的输出（当前系统日期和时间）**重定向**到文件 `file` 中。
> - **细节**：
>   - 若 `file` 不存在，则创建该文件；若存在，则**覆盖**原有内容。
>   - 等价于 `date 1> file`（`1` 表示标准输出）。
>
> ---
>
> ### **2. `sort < file1 > file2`**
> - **功能**：从 `file1` 读取内容，排序后写入 `file2`。
> - **细节**：
>   - `< file1`：将 `file1` 的内容作为 `sort` 命令的**输入**（替代键盘输入）。
>   - `> file2`：将排序后的结果**输出**到 `file2`（覆盖原有内容）。
>   - 若 `file1` 不存在，命令会报错。
>
> ---
>
> ### **3. `cat file1 file2 file3 | sort > /dev/lp`**
> - **功能**：合并三个文件的内容，排序后发送到打印机设备（假设 `/dev/lp` 是打印机）。
> - **细节**：
>   - `cat file1 file2 file3`：依次读取三个文件的内容并合并输出到标准输出。
>   - `| sort`：将合并后的内容通过管道传递给 `sort` 命令进行排序。
>   - `> /dev/lp`：将排序后的结果重定向到打印机设备（需设备存在且用户有权限）。
>   - **注意**：现代Linux系统通常使用 `lp` 或 `cups` 命令打印，`/dev/lp` 可能不存在。
>
> ---
>
> ### **4. `cat file1 file2 file3 | sort > /dev/lp &`**
> - **功能**：与上一条命令相同，但通过 `&` 放入**后台执行**。
> - **细节**：
>   - `&`：使命令在后台运行，终端可继续输入其他命令。
>   - 适用于耗时操作（如大量数据排序和打印），避免阻塞当前Shell。
>   - 可通过 `jobs` 命令查看后台任务状态。
>
> ---
>
> ### **关键概念总结**
> 1. **重定向**：
>    - `>`：覆盖输出到文件（或设备）。
>    - `<`：从文件读取输入。
> 2. **管道（`|`）**：将前一个命令的输出作为后一个命令的输入。
> 3. **后台执行（`&`）**：让命令在后台运行，不占用当前终端。
>
> ---
>
> ### **注意事项**
> - 若文件或设备（如 `/dev/lp`）不存在，命令会报错。
> - 现代系统中，打印通常通过 `lp` 或 `lpr` 命令实现，而非直接写入设备文件。



## 1.6 System Calls

==系统调用提供了运行程序和操作系统之间的接口== 。

- 应用程序**通过一种机制向操作系统请求服务**，这种机制通常是通过==高级应用程序编程接口（API）来访问==，而不是直接使用系统调用。

- 三个最常见的API：

  - Win32 API：用于Windows系统
  - POSIX API： 用于基于POSIX的系统
  - Java AP：用于JVM。

- POSIX：Portable Operating System Interface

- IEEE标准集：Mandatory + Optional Parts

- 目的：**应用程序的源代码在多个操作系统之间的可移植性**。

- 大多数POSIX进程包含系统调用，通常将==一个进程直接映射为一个系统调用==，但是绝对一对一的。

- 执行一个系统调用的步骤具体如下：

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251902476.webp)

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502251906500.webp)

- System Call Code

  ```bash
  #define __NR_restart_syscall 0
  #define __NR_exit 1
  #define __NR_fork 2
  #define __NR_read 3
  #define __NR_write 4
  #define __NR_open 5
  #define __NR_close 6
  #define __NR_waitpid 7
  ```

- **System Calls for Process management**

  | Call                                | Desciption                                     |
  | ----------------------------------- | ---------------------------------------------- |
  | pid=fork()                          | Create a child process identical to the parent |
  | pid=waitpid(pid, &statloc, options) | Wait for a child to terminate                  |
  | s=execve(name, argv,environp)       | Replace a process' core image                  |
  | exit(status)                        | Terminate process execution and return status  |

- **System Calls for Process**

  - **Fork 是POSIX 中唯一创建新进程的方法。**

  - **Fork 创建了原进程的复制，且通过fork创建的新进程被称为子进程。**

  - 该函数被调用一次，**但是返回两次**。

    - 0 in child
    - process ID of child in parent
    - -1 on error

  - **注意**：Both the child and parent continue executing with the instruction that follows the call to fork.

    > 这句话的意思是：**在调用 `fork()` 之后，父进程和子进程都会从 `fork()` 之后的指令开始继续执行**。
    >
    > 具体解释如下：
    >
    > 1. **`fork()` 系统调用**：  
    >    `fork()` 是 UNIX 和类 UNIX 系统（如 Linux）中的一个系统调用，用于创建一个新的进程（称为子进程）。子进程是父进程的副本，拥有与父进程相同的代码、数据和堆栈。
    >
    > 2. **`fork()` 的行为**：  
    >    - 调用 `fork()` 后，操作系统会创建一个新的子进程。
    >    - 子进程和父进程从 `fork()` 之后的指令开始继续执行。
    >    - 在父进程中，`fork()` 返回子进程的进程ID（PID）。
    >    - 在子进程中，`fork()` 返回 0。
    >    - 如果 `fork()` 失败，则返回一个负值。
    >
    > 3. **代码示例**：
    >    ```c
    >    #include <stdio.h>
    >    #include <unistd.h>
    >                   
    >    int main() {
    >        pid_t pid = fork();  // 创建子进程
    >                   
    >        if (pid == 0) {
    >            // 子进程
    >            printf("This is the child process (PID: %d)\n", getpid());
    >        } else if (pid > 0) {
    >            // 父进程
    >            printf("This is the parent process (PID: %d), child PID: %d\n", getpid(), pid);
    >        } else {
    >            // fork() 失败
    >            fprintf(stderr, "fork() failed\n");
    >            return 1;
    >        }
    >                   
    >        // 父进程和子进程都会执行以下代码
    >        printf("This message is from PID: %d\n", getpid());
    >        return 0;
    >    }
    >    ```
    >
    > 4. **执行流程**：
    >    - 调用 `fork()` 后，父进程和子进程都会从 `fork()` 之后的代码开始执行。
    >    - 通过 `if-else` 语句，可以根据 `fork()` 的返回值区分父进程和子进程。
    >    - 父进程和子进程都会执行 `printf("This message is from PID: %d\n", getpid());` 这一行代码。
    >
    > ### 输出示例
    > 假设父进程的 PID 是 1234，子进程的 PID 是 1235，输出可能如下：
    > ```
    > This is the parent process (PID: 1234), child PID: 1235
    > This message is from PID: 1234
    > This is the child process (PID: 1235)
    > This message is from PID: 1235
    > ```
    >
    > ### 总结
    > 调用 `fork()` 后，父进程和子进程都会从 `fork()` 之后的指令开始继续执行。通过 `fork()` 的返回值，可以区分父进程和子进程，并让它们执行不同的逻辑。

  - `execve` 是一个系统调用，用于在当前进程中执行一个新的程序。它会==替换当前进程的内存空间（包括代码、数据、堆栈等）为新程序的镜像==。

    execve 允许子进程执行与父进程不同的代码。

    > `execve` 是一个系统调用，用于在当前进程中执行一个新的程序。它会替换当前进程的内存空间（包括代码、数据、堆栈等）为新程序的镜像。
    >
    > 当 `execve` 在 `fork` 之后使用时，通常是为了创建一个新进程并让它执行一个不同的程序。具体步骤如下：
    >
    > 1. **fork**: 创建一个子进程，子进程是父进程的副本，拥有相同的内存空间和代码。
    > 2. **execve**: 在子进程中调用 `execve`，**用新程序替换子进程的内存空间**。子进程的代码、数据、堆栈等会被新程序的镜像取代。
    >
    > ### 示例
    > ```c
    > #include <unistd.h>
    > #include <stdio.h>
    > #include <sys/types.h>
    > #include <sys/wait.h>
    > 
    > int main() {
    >     pid_t pid = fork();  // 创建子进程
    > 
    >     if (pid == 0) {  // 子进程
    >         char *argv[] = {"/bin/ls", "-l", NULL};
    >         execve("/bin/ls", argv, NULL);  // 替换为 ls 程序
    >     } else if (pid > 0) {  // 父进程
    >         wait(NULL);  // 等待子进程结束
    >         printf("Child process finished.\n");
    >     } else {  // fork 失败
    >         perror("fork");
    >         return 1;
    >     }
    > 
    >     return 0;
    > }
    > ```
    >
    > ### 解释
    > - **fork**: 创建子进程，子进程从 `fork` 处继续执行。
    > - **execve**: 在子进程中调用 `execve`，执行 `/bin/ls -l`，子进程的内存空间被 `ls` 程序替换。
    > - **wait**: 父进程等待子进程结束。
    >
    > ### 总结
    > `execve` 在 `fork` 后用于替换子进程的内存空间，使其执行新程序。这是 Unix/Linux 系统中创建新进程并运行不同程序的常见方式。

  - `exec` 种类：

    - execl，execle，execlp
    - execv，execve，execvp

  - `waitpid` 是一个系统调用，用于**让父进程等待指定的子进程终止**。它的作用是==将父进程从 **就绪队列（ready queue）** 中移出，直到子进程结束==。

    > ### 详细解释
    > 1. **就绪队列（Ready Queue）**:
    >    - 操作系统中，就绪队列是存放所有准备好运行的进程的队列。
    >    - 当一个进程在等待某个事件（如子进程结束）时，它会被移出就绪队列，进入阻塞状态。
    >
    > 2. **waitpid 的作用**:
    >    - 父进程调用 `waitpid` 后，==会阻塞自己，直到指定的子进程终止==。
    >    - 在此期间，==父进程不会占用 CPU 资源，操作系统会将其从就绪队列中移出==。
    >
    > 3. **子进程终止**:
    >    - 当子进程终止时，操作系统会向父进程发送信号，父进程从阻塞状态恢复，重新进入就绪队列，继续执行。
    >
    > ### 函数原型
    > ```c
    > #include <sys/types.h>
    > #include <sys/wait.h>
    > 
    > pid_t waitpid(pid_t pid, int *status, int options);
    > ```
    >
    > - **pid**: 指定要等待的子进程 ID。
    >   - `pid > 0`: 等待指定的子进程。
    >   - `pid = -1`: 等待任意子进程。
    > - **status**: 用于存储子进程的退出状态。
    > - **options**: 控制 `waitpid` 的行为，例如 `WNOHANG` 表示非阻塞模式。
    >
    > ### 示例
    > ```c
    > #include <unistd.h>
    > #include <stdio.h>
    > #include <sys/types.h>
    > #include <sys/wait.h>
    > 
    > int main() {
    >     pid_t pid = fork();  // 创建子进程
    > 
    >     if (pid == 0) {  // 子进程
    >         printf("Child process is running.\n");
    >         sleep(2);  // 模拟子进程工作
    >         printf("Child process is done.\n");
    >     } else if (pid > 0) {  // 父进程
    >         printf("Parent is waiting for child to finish...\n");
    >         waitpid(pid, NULL, 0);  // 等待子进程结束
    >         printf("Parent process continues.\n");
    >     } else {  // fork 失败
    >         perror("fork");
    >         return 1;
    >     }
    > 
    >     return 0;
    > }
    > ```
    >
    > ### 输出
    > ```
    > Parent is waiting for child to finish...
    > Child process is running.
    > Child process is done.
    > Parent process continues.
    > ```
    >
    > ### 总结
    > - `waitpid` 用于让父进程等待子进程终止。
    > - 调用 `waitpid` 后，==父进程会被移出就绪队列，进入阻塞状态，直到子进程结束==。
    > - 这是**父进程和子进程之间同步的常用方法**。

  - 返回值：如果OK，返回process ID，否则返回0或-1。

  - pid 参数的解释取决于其值：

    - pid = -1 等待**任何子进程**，从这方面说，waitpid 等价于 wait。
    - pid > 0 等待**进程ID 等于 pid 的子进程**。

  - 相关的案例：

    ```c
    #define TRUE 1
    while(TRUE){									/* repeat forever*/
    	type_prompt();								/* display prompt on the screen */
    	read_command(command, parameters);			/* read input from terminal */
    	
    	if(fork()!=0){								/* fork off child process */
    		/*Parent code.*/						
    		waitpid(-1, &status, 0);				/* wait for child to exit*/
    	}
    	else{
    		/*Child code*/
    		execve(command, parameters, 0);			/* execute command */
    	}
    }
    ```

    ```c
    /* fork processes */
    main()
    {
    	int i, pid;
    	for (i=1; i<=3; i++) {
    		if ((pid = fork()) == 0) {
    			printf("In child %d. \n", i);
    		}
    	}
    }
    ```

- **System Calls for the File Management**

  **Fill management**

  | Call                               | Description                              |
  | ---------------------------------- | ---------------------------------------- |
  | fd=open(file, how, ···)            | Open a file for reading, writing or both |
  | s=close(fd)                        | Close an open file                       |
  | n= read(fd, buffer, nbytes)        | Read data from a file into a buffer      |
  | n =read(fd, buffer, nbytes)        | Write data from a buffer into a file     |
  | position=lseek(fd, offset, whence) | Move the file pointer                    |
  | s=start(name, &buf)                | Get a file's status information          |

- **System Calls For Directory Management**

  **Directionary and file system management**

  | Call                         | Description                              |
  | ---------------------------- | ---------------------------------------- |
  | s=mkdir(name, mode)          | 创建一个新目录                           |
  | s=rmdir(name)                | 删除一个空目录                           |
  | s=link(name1, name2)         | Create a new entry, name2 point to name1 |
  | s=unlink(name)               | Remove a directory entry                 |
  | s=mount(special, name, flag) | Mount a file system                      |
  | s=umount(special)            | Unmount a file system                    |

  **Linking**

  <img src="https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502252326880.webp" style="zoom:80%;" />

  **Mounting**

  <img src="https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502252328832.webp" style="zoom:80%;" />

- **System Calls For Miscellaneous Tasks**

  **Miscellaneous**

  | Call                   | Description                               |
  | ---------------------- | ----------------------------------------- |
  | s=chdir(dirname)       | Change the working directory              |
  | s=chmod(name, mode)    | Change a file's protection bits           |
  | s=kill(pid, signal)    | Send a signal to a process                |
  | seconds=time(&seconds) | Get the elapsed time since Jan.  1,  1970 |



## 1.7 Operating System Structure

### Monolithic System - "the big mess".

所有操作系统操作都放入一个文件中。操作系统是一个程序的集合，每个程序都可以调用其他任何一个。

**基本结构**：

- 一个主要程序包含了**所需要的服务程序。**

- 一组服务程序的集合**用于执行系统调用**。A set of service procedures that carry out the system calls

- 一组程序用于**帮助服务程序。**

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502252351738.webp)操

### Layered System

操作系统被组织为层的层次结构，每一个层都在其下方的层的基础上进行构建。

第一个划分层次的操作系统：THE Operating System

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502252353113.webp)

### Microkernel

尽可能多的**将功能从核移动到用户空间**。

OS 核是非常小的——功能最小

- ==原始的内存管理（地址空间）==
- ==I/O 和中断管理==
- ==Inter-Process Communication（IPC）==
- ==基本调度 Basic scheduling==

Other OS functions provided at user level by trusted servers.

- User process, trusted by kernel.
- Device drivers, file system, virtual memory...

**Layered 和 Microkernels 的对比**

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502252359264.webp)

### Client-server model

是一个 microkernel 的微小变体

- 区分两类进程：**客户端和服务端**

- ==将大部分代码移至较高的层中，使内核变得最小，并且仅负责客户与服务器之间的通信==。

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502260001149.webp)

- 客户和服务器在不同的计算机上运行，并**通过本地或广阔的网络连接。**

  ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502260002372.webp)

### Virtual Machine

- **硬件上的虚拟软件层。**
- **抽象机器的软件仿真。**
- 多个硬件实例的幻想。Illusion of multiple instances of hardware
- 支持OSS的多个实例。Supports multiple instances of Oss

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502260002323.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502260002904.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502260002621.webp)

### Exokernel

用于应用程序级资源管理的操作系统体系结构

- Exokernel: ==跟硬件打交道，主要用于完成硬件的复制工作==

- Library OS

  - 跟具体的应用打交道，不同应用的libOS根据不同应用的特点进行设计，所以**具体应用跟OS之间是紧耦合的**。

  - 应用程序跟libOS编译、链接在一起，这样，应用程序与libOS共用一个地址空间，应用程序就可以有限制的访问系统资源 （网络SOCKET、内存VMA等）


  - Exokernel与宏内核、微内核的本质区别：**传统内核是不允许应用程序直接访问系统资源的**。

    ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202502260003323.webp)
