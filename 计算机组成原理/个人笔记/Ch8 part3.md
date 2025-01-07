# Ch8 part3

### Secondary Storage

**机械结构**

**存储介质**

- **磁盘构成与安装方式**：存储介质是由一个或多个磁盘（双面/单面）安装在一个共同的主轴上组成的。磁盘是一种圆形的盘片，由金属或者涂有可磁化材料的塑料制成。这些磁盘被放置在一个旋转驱动器中，并且以均匀的速度旋转。

**读/写头**

- **固定头**：这种方式下，每个磁道都有一个读写头，这些读写头安装在固定的刚性臂上。
- **移动头**：每个盘面有一个读写头，读写头安装在一个可移动的臂上。
- **读写头的组成部分**：每个读写头都包含一个磁轭和一个磁化线圈。并且读写头与正在旋转的磁盘表面必须保持非常小的距离。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071643390.webp)

**存储原理**

- **写入原理**：通过向磁化线圈施加适当极性的电流脉冲，数字信息就可以被存储在磁盘的磁性薄膜上。
- **读取原理**：当磁盘的磁性薄膜相对于磁轭移动时，在读写头附近的磁场发生变化，这个变化会在线圈中感应出电压，从而实现信息的读取。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071643104.webp)

**温彻斯特硬盘**

- **温彻斯特技术起源**：温彻斯特硬盘采用的温彻斯特技术是由IBM在1968年开发的。
- **温彻斯特硬盘的特点**：磁盘和读写头被放置在一个密封的、带有空气过滤装置的外壳中。这种设计使得读写头可以更靠近磁化的磁道表面工作。
- **温彻斯特硬盘的优势**：这样的数据存储密度往往更高，而且对于给定的物理尺寸，它相比于非密封的存储设备容量更大。



**数据组织**

**磁道和扇区**

- **磁道和扇区的划分**：磁盘的每个盘面被划分成同心的磁道，每个磁道又被划分成扇区。每个磁道包含相同数量的扇区，但在一些大型磁盘中，外磁道会有更多扇区。通常每个盘面有500 - 2000个磁道，每个磁道有10 - 100个扇区，每个扇区大小一般是512字节。磁盘地址通过（盘面号、磁道号、扇区号）来表示。
- **扇区间隙（Inter - sector Gap）的作用**：用于轻松区分两个连续的扇区。
- **扇区首部（Sector Header，也叫Preamble）的作用**：包含用于在选定磁道上找到所需扇区的标识（寻址）信息。
- **ECC（Error - correcting Code）位的作用**：用于检测和纠正写入或读取512字节数据时可能出现的错误。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071705766.webp)

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071705180.webp)

**数据组织 - 柱面（Cylinder）**

- 磁盘组中在给定半径位置上的所有盘面的磁道集合形成一个逻辑柱面。访问一个柱面上所有磁道的数据时，不需要移动读写头，这使得数据访问在一定程度上更高效。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071705470.webp)

**数据组织 - 磁盘格式化**

- **格式化的操作和目的**：格式化操作是将磁盘划分成磁道和扇区。在这个过程中，可能会发现一些有缺陷的扇区甚至是整个磁道。
- **格式化信息的占比**：格式化信息（扇区首部、ECC位和扇区间隙）大约占磁盘可存储总信息的15%。

**磁盘上数据的访问 - 磁盘访问时间**

- **访问时间的组成**：磁盘访问时间等于寻道时间加上旋转时间。
- **寻道时间（Seek Time）**：是将读写头移动到正确磁道所需的时间，其平均值在5ms - 8ms之间。
- **旋转时间（Rotational Time，也叫Latency Time）**：是指读写头定位到正确磁道后，直到被寻址扇区的起始位置经过读写头所经过的时间，其平均值是磁盘旋转半圈所需的时间。

**磁盘上数据的访问 - 传输速率和传输时间**

- **传输速率**：是指读写头定位到数据后数据传输的比率。
- **传输时间**：是传输数据所花费的时间，它与传输的数据量和传输速率有关。传输时间的长短会直接影响磁盘数据读取或写入的效率。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071705920.webp)



### Virtual Memory and Paging

**两个需要解决的问题**

- **内存不足的问题**：如果主存储器（DRAM）不足以执行一个程序怎么办？是否可以使用磁盘来解决？如果可以，又该如何使用？
- **多程序运行的问题**：如果想要同时运行几个程序（进程），该怎么把它们加载到内存中？

**覆盖技术（Overlaying）**

- **覆盖技术的操作方式**：程序员需要把程序划分成几个段，然后利用局部性原理，在程序执行期间选择一些段保存在内存中。
- **覆盖技术的缺点**：这种手动划分的方式很繁琐。而且在考虑多道程序设计时，很难确定覆盖集。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071735945.webp)



![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071735239.webp)



**虚拟内存（Virtual Memory）**

- **虚拟内存的本质**：它不是一个物理设备，而是一个抽象概念。
- **虚拟内存的技术含义**：这是一种利用磁盘来扩展物理内存表观大小的技术（一种抽象手段），使其超过实际的物理大小。
- **虚拟内存的目标**：让每个进程都认为自己拥有一个很大的内存。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071736990.webp)

**虚拟内存作为缓存工具**

- 虚拟内存是存储在磁盘上的由N个连续字节组成的数组，这个磁盘上数组的内容会被缓存在物理内存中。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071737270.webp)

**相关术语**

- **物理内存（Physical Memory）**：指计算机中实际可用的内存。
- **逻辑或虚拟内存（Logical or Virtual Memory）**：是操作系统让程序认为自己拥有的内存。
- **物理地址（Physical Address）**：是物理内存中的真实位置，用于标识实际的存储单元。
- **逻辑或虚拟地址（Logical or Virtual Address）**：是程序使用的常规寻址方式，操作系统必须将其转换为物理地址。

**虚拟内存的典型组织**

- **MMU（内存管理单元）的作用**：硬件通过操作系统管理的查找表（页表）将虚拟地址转换为物理地址。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071736114.webp)





**虚拟内存的优点**

- **提供大地址空间**：通过虚拟地址到物理地址的映射实现。
- **简化重定位过程**：同一个程序可以在物理内存的任何位置运行。
- **减少程序启动时间**：程序启动前不需要所有的代码和数据都在物理内存中。
- **减轻程序员的覆盖负担**：虚拟内存自动管理由主存和二级存储所代表的两级存储层次结构。



**虚拟内存的实现**

虚拟内存的实现主要有三种方法，分别是分页（Paging）、分段（Segmentation）以及分段与分页结合（Segmentation with paging）这几种方式。

**分页（Paging）相关内容**

- **虚拟内存与主内存的组织形式**：
    - **页面（Page）**：是由连续字组成的一个数据块，是在主内存和磁盘之间移动信息的基本单元。其长度通常在2K到16K字节之间，页面大小既不能太小也不能太大。
    - **页框（Page Frame）**：是主内存中可以容纳一个页面的区域。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071753950.webp)

- **地址结构**：
    - **虚拟地址**：分为两个字段，高序位的是虚拟页号，低序位的是偏移量，偏移量用于指定页面内某个特定字节（或字）的位置。
    - **物理地址**：同样分为两个字段，包含高序位的物理页号以及低序位的偏移量。
- **页表（Page Table）**：
    - **基本概念**：页表是由页表项（PTEs）组成的数组，它的作用是将虚拟页面映射到物理页面。通过把虚拟页号作为索引在页表中查找对应的项，来确定虚拟页面对应的物理页面。页表保存在主内存中，并且有页表基址寄存器指向它在内存中的位置。
    - **页表项（Page Table Entry）内容**：包含页框号（即物理页号或者指向二级存储的指针）、有效位（也叫存在位，用于指示页面是否实际已加载到主内存中）、修改位（表明页面在驻留主内存期间是否被修改过）、使用位（参考位，用于指示页面近期是否被使用过）以及访问控制位（规定读、写、执行等操作权限）。

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071754819.webp)

- **页面命中（Page Hit）与页面故障（Page Fault）**：
    - **页面命中**：指对虚拟内存中某个字的访问，而该字所在的页面已经在物理主内存中。
    - **页面故障（类似“缓存未命中”）**：是由于访问的虚拟内存中的某个字所在页面不在物理主内存中而引发的情况。
- **主内存中页表的缺点及解决办法（TLB）**：
    - **缺点**：程序每次进行内存访问时，耗时至少会翻倍，因为首先要访问内存获取物理地址，然后再进行一次访问获取数据。
    - **解决办法（TLB，即转换检测缓冲器）**：它是集成在内存管理单元（MMU）中的一个小缓存，包含了页表的一小部分内容。
- **TLB地址转换相关情况**：
    - **TLB命中**：如果发生TLB命中，就可以省去一次内存访问操作。
    - **TLB未命中**：由于TLB中的条目数量远少于主内存中的页面数量，所以TLB未命中情况会比真正的页面故障更为频繁，并且TLB未命中会导致额外的内存访问操作。同时，TLB要和页表保持一致性，当操作系统更改页表内容时，必须同时使TLB中对应的条目失效。、

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412071755750.webp)

- **页面替换与写入策略**：
    - **页面替换算法**：常见的有LRU（需要使用位来辅助判断，替换最近最少使用的页面）、FIFO（先进先出原则进行替换）等，一般由软件（操作系统）来实现。
    - **写入策略**：采用回写（Write back）策略比较合适，而直写（Write through）策略并不适用于虚拟内存。
- **分页的缺点 - 内部碎片问题**：
    - 最后一个页面往往很难被填满，如果页面大小是n字节，那么由于内部碎片，程序最后一个页面平均浪费的空间将会是n/2字节。
- **页面大小相关探讨**：
    - **选择较大页面大小的优势**：页表的大小与页面大小成反比，增大页面尺寸能够节省内存空间；而且向二级存储（可能通过网络）传输较大页面比传输小页面效率更高。
    - **选择较大页面大小的劣势**：当虚拟内存中的连续区域大小不是页面大小的整数倍时，较大的页面尺寸会导致更多的存储浪费（即内部碎片问题）。 



## 练习

### The data of all tracks of a ______ can be accessed without moving the readwrite head. 

A. surface 	B. platter 	C. sector	D. cylinder

**答案：D。**

访问同一柱面上的所有磁道都不需要移动磁头



### According to the specifications of a particular hard disk, a seek takes 3ms between adjacent tracks. If the disk has 100 cylinders, how long will it take for the head to move from the innermost cylinder to the outermost cylinder? 

A. 3ms 	B. 30ms 	C. 300ms 	D. 3000ms



**答案：C。**



### A hard disk with 5 double-sided platters has 2048 tracks/platter, how many movable heads does it have? 

A. 5 	B. 10 	C. 2048 * 5 	D. 2048 * 10	

每个盘面有一个磁头，5个双面的盘片有10个盘面，所以有10个磁头

**答案：B。**

### When we read a block of data from a disk into memory, the seek time refers to __. 

A. the time required to move the read-write head to the proper track 

B. the time required to position the read-write head and transfer the data block 

C. the time required to rotate the correct sector under the head 

D. none of the above



**答案：A。**



### The amount of time required to read a block of data from a disk into memory is composed of seek time, rotational latency, and transfer time. Rotational latency refers to ___. 

A. the time it takes for the platter to make a full rotation 

B. the time it takes for the read-write head to move into position over the appropriate track 

C. the time it takes for the platter to rotate the correct sector under the head 

D. none of the above



**答案：C。**

> ### 答案：**C. the time it takes for the platter to rotate the correct sector under the head**
>
> #### **解析：**
>
> 磁盘访问的总时间由以下三部分组成：
>
> 1. **寻道时间（Seek Time）：**
>    - 将读写头移动到正确的磁道所需的时间。对应选项 **B**。
> 2. **旋转延迟（Rotational Latency）：**
>    - 指磁盘旋转使正确的扇区移到读写头下所需的时间。
>    - 旋转延迟取决于磁盘的旋转速度（例如 7200 RPM）。
>    - 对应选项 **C**。
> 3. **数据传输时间（Transfer Time）：**
>    - 数据从磁盘读取到内存的实际传输时间。
>
> #### **错误选项解释：**
>
> - **A. the time it takes for the platter to make a full rotation：**
>    这是 **磁盘旋转时间** 的定义，而非旋转延迟。
> - **B. the time it takes for the read-write head to move into position over the appropriate track：**
>    这是 **寻道时间** 的定义。
> - **D. none of the above：**
>    错误，选项 **C** 是正确的。
>
> ### **结论：**
>
> 旋转延迟是指盘片旋转将正确的扇区移动到读写头下所需的时间，因此答案是 **C. the time it takes for the platter to rotate the correct sector under the head**。



### A hard disk with 5 platters has 2048 tracks/platter, 1024 sectors/track (fixed number of sectors per track), and 512 byte sectors. What is its total capacity? 

A. 5G 	B. 10G 	C. 15G 	D. 20G



**答案：A。**

2048 * 5 * 1024 * 512B=5GB



### Which one of the following about benefits of virtual memory is NOT true? 

A. provide large address space 

B. relieve programmers from burden of overlays 

C. resolve internal fragmentation 

D. simplify relocation



**答案：C。**

> ### 答案：**C. 解决内部碎片问题**
>
> ### 解释：
>
> 1. **A. 提供大地址空间**
>    - **正确**：虚拟内存通过抽象化内存空间，使程序可以访问比物理内存更大的地址空间。
> 2. **B. 减轻程序员的覆盖负担**
>    - **正确**：在虚拟内存出现之前，程序员需要手动将程序分割成多个部分（覆盖）以适应物理内存。虚拟内存通过自动管理内存的方式，减轻了程序员的负担。
> 3. **C. 解决内部碎片**
>    - **错误**：虚拟内存主要通过**分页**机制解决**外部碎片**问题，而并不能解决**内部碎片**。内部碎片是指当分配的内存块比实际需求大时，未使用的部分内存空间。在分页机制中，若页面没有完全使用，也会产生一些内部碎片。
> 4. **D. 简化重定位**
>    - **正确**：虚拟内存通过允许进程使用相同的虚拟地址空间，不管它们在物理内存中的实际位置如何，从而简化了程序的重定位过程。硬件和操作系统负责虚拟地址到物理地址的映射。
>
> ------
>
> ### 最终答案：**C**



### In a paging system, which of the following is NOT true? 

A. When a TLB miss occurs, the operating system must copy the requested page from the disk into the main memory 

B. Transferring larger pages to or from secondary storage is more efficient than transferring smaller pages C. Paging has a problem called internal fragmentation 

D. “Write though” is not suitable for this system



**答案：A。**

> ### 答案：**A. 当发生 TLB 未命中时，操作系统必须将请求的页面从磁盘复制到主内存中**
>
> ### 解释：
>
> 1. **A. 当发生 TLB 未命中时，操作系统必须将请求的页面从磁盘复制到主内存中**
>    - **错误**：**TLB 未命中**发生在请求的虚拟页面没有在**TLB（翻译后备缓冲区）中找到时。这个时候操作系统需要查找页表来确定页面在物理内存的位置，但并不涉及从磁盘加载页面，除非发生了页面缺失**（page fault），也就是请求的页面不在主内存中，才会从磁盘将页面加载到内存。因此，TLB 未命中并不意味着立即从磁盘复制页面。
> 2. **B. 将更大的页面从二级存储转移到主存中比传输较小的页面更有效**
>    - **正确**：将较大的页面传输到主存中比传输较小的页面效率更高，因为较大的页面减少了多次磁盘I/O操作的开销，这样可以提高性能。
> 3. **C. 分页有一个叫做内部碎片的问题**
>    - **正确**：分页确实存在**内部碎片**的问题。当最后一页没有完全使用时，会浪费一些空间。例如，如果页面大小为 4 KB，但只使用了其中的 2 KB，那么剩下的 2 KB就成了内部碎片。
> 4. **D. “直写”策略不适用于此系统**
>    - **正确**：**直写（Write-through）\**缓存策略会在缓存中写入数据的同时，将数据写入主存。在分页系统中，这可能会导致不必要的开销，因为每次写操作都必须更新主存，并可能涉及到更新页表。更适合的策略是\**写回（Write-back）**，它只在页面被替换时才将数据写回内存。
>
> ------
>
> ### 最终答案：**A**



### A processor uses 46-bit virtual addresses with 2MB pages. Which bits in the virtual address correspond to the “offset” field? 

A. The most significant 34 bits 

B. The least significant 12 bits 

C. The most significant 25 bits 

D. The least significant 21 bits



**答案：D。**

> ### 答案：**D. 最低有效的 21 位**
>
> ### 解释：
>
> 在分页系统中，虚拟地址被分为两部分：**页号** 和 **页内偏移**。
>
> - **页内偏移** 用于确定地址在页内的位置，大小由页面的大小决定。
> - **页号** 用于标识虚拟地址空间中的哪一页。
>
> 给定条件：
>
> - 虚拟地址大小：46 位
> - 页面大小：2MB（即 2212^{21} 字节）
>
> 因为页面大小是 2MB，我们需要 21 位来表示在页面内的偏移量，因为 221=2MB2^{21} = 2MB。
>
> 因此，虚拟地址中的 **最低有效的 21 位** 对应于 **页内偏移**，它们表示在 2MB 页面中的具体位置。
>
> ### 最终答案：**D**





### A page fault is _____. 

A. an attempt by the computer to run instructions stored on the hard disk 

B. the process the computer uses to start itself 

C. an error the computer makes when a device driver is missing 

D. an out of memory error

**答案：D。**

> ### 答案：**D. 内存不足错误**
>
> ### 解释：
>
> **页面错误（page fault）**发生在程序尝试访问当前不在物理内存中的页面时。通常情况下，这种情况发生在使用虚拟内存系统的计算机上，操作系统需要将所需的页面从磁盘（如硬盘）加载到物理内存中。
>
> - **A. 计算机尝试运行存储在硬盘上的指令**
>   - **错误**：页面错误发生在计算机访问不在内存中的数据时，而不是尝试运行硬盘上的指令。
> - **B. 计算机启动自身的过程**
>   - **错误**：这指的是计算机的**启动过程**，而不是页面错误。
> - **C. 计算机缺少设备驱动程序时的错误**
>   - **错误**：这与缺少设备驱动程序相关，和页面错误无关。
> - **D. 内存不足错误**
>   - **正确**：页面错误通常表示程序尝试访问不在物理内存中的页面，这需要从二级存储中加载，并且在内存不足时，可能会发生页面错误。
>
> ### 最终答案：**D**



### About TLB, which of the following is true? 

A. It’s a small cache which consists of a small portion of the page table 

B. When a TLB miss occurs, the operating system must copy the requested page from the disk into the main memory 

C. TLB misses can only be handled in hardware 

D. Its content is accessed based on the address

**答案：A**。

> ### 答案：**A. 它是一个小型缓存，包含了页表的一小部分**
>
> ### 解释：
>
> 1. **A. 它是一个小型缓存，包含了页表的一小部分**
>    - **正确**：**TLB（翻译后备缓冲区）**是一个小型、高速缓存，存储了页表中的一部分条目。它的作用是通过缓存最常用的页表条目来加速虚拟地址到物理地址的转换。
> 2. **B. 当发生 TLB 未命中时，操作系统必须将请求的页面从磁盘复制到主内存中**
>    - **错误**：**TLB 未命中**意味着请求的虚拟地址对应的页表条目不在 TLB 中。这时，硬件会通过访问主内存中的页表来找到对应的物理地址。如果该页面不在内存中，才会发生**页面缺失（page fault）**，此时操作系统才需要从磁盘加载页面到内存。TLB 未命中本身并不涉及磁盘操作。
> 3. **C. TLB 未命中只能在硬件中处理**
>    - **错误**：**TLB 未命中**既可以由硬件处理，也可以由软件处理。硬件会访问主内存中的页表并更新 TLB，而在某些情况下，操作系统也会介入处理未命中的情况（如发生页面缺失时）。
> 4. **D. 它的内容是根据地址访问的**
>    - **正确**，但不完全准确：TLB 的内容确实是根据虚拟地址访问的，但问题中主要强调的是 TLB 的功能和结构，A 选项更清楚地描述了 TLB 的作用。
>
> ### 最终答案：**A**



### Suppose the paging hardware with TLB has a 90 percent hit ratio. Page numbers found in the TLB have a total access time of 100 ns. Those which are not found there have a total access time of 200 ns. What is the average access time? 

A. 100ns 	B. 110ns 	C. 190ns 	D. 200ns

**答案：B。**

> ### Answer: **B. 110ns**
>
> ### Explanation:
>
> To calculate the **average access time** with the given hit ratio, we can use the following formula:
>
> $$
> \text{Average Access Time} = (\text{Hit Ratio} \times \text{Hit Access Time}) + (\text{Miss Ratio} \times \text{Miss Access Time})
> $$
> 
>
> Where:
> - **Hit Ratio** = 90% = 0.90
> - **Miss Ratio** = 1 - Hit Ratio = 10% = 0.10
> - **Hit Access Time** = 100 ns
> - **Miss Access Time** = 200 ns
>
> Substitute the values into the formula:
>
> $$
> \text{Average Access Time} = (0.90 \times 100) + (0.10 \times 200)
> $$
>
> $$
> \text{Average Access Time} = 90 + 20 = 110 \text{ ns}
> $$
>
> 
>
> ### Final Answer: **B. 110ns**





### True or False? A Translation Lookaside Buffer (TLB) acts as a cache for the page table. 

> **正确**。
>
> **翻译后备缓冲区（TLB）** 确实是 **页表** 的缓存。它存储了最近的虚拟地址到物理地址的转换条目，使得在地址转换时可以快速访问，而无需每次都遍历整个页表。这提高了使用虚拟内存系统的效率。

### What are advantages and disadvantages of choosing smaller page size in a paging system?

**Advantages:** 

- A small page size will result in less wasted storage when a contiguous region of virtual memory is not equal in size to a multiple of the page size. 

**Disadvantages:** 

- (1) The size of the page table is inversely proportional to the page size. Memory can therefore be wasted by making the pages smaller.
- (2) Transferring smaller pages to or from secondary storage, possibly over a network, is less efficient than transferring larger pages.

> **优点：**
>
> - 较小的页面大小可以减少存储浪费，当一个连续的虚拟内存区域的大小不是页面大小的整数倍时，浪费的空间会较少。
>
> **缺点：**
>
> - (1) 页表的大小与页面大小成反比。因此，若将页面大小设得过小，可能会浪费更多内存。
> - (2) 从次级存储（可能通过网络）传输较小的页面比传输较大的页面效率低。



 

### Under what circumstances do page faults occur? Describe the actions taken by the operating system when a page fault occurs. 

A page fault occurs when an access to a page that has not been brought into main memory takes place. The operating system verifies the memory access, aborting the program if it is invalid. If it is valid, a free frame is located and I/O is requested to read the needed page into the free frame. Upon completion of I/O, the process table and page table are updated and the instruction is restarted.

> **页面错误**发生在访问尚未加载到主内存中的页面时。操作系统会验证该内存访问，如果无效，则终止程序；如果有效，操作系统会找到一个空闲的内存框架，并发出 I/O 请求，将所需页面读取到该空闲框架中。I/O 完成后，操作系统会更新进程表和页表，并重新启动该指令。