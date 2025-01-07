# SCUT Unknown Paper A and B

##  Select the correct choice. 

### (3)

- **题目**：
An algorithm must be or do all of the following EXCEPT: (    )
(A) Partially correct  (B) Ambiguous（含糊的，不明确的）  (C) Terminate  (D) Concrete steps
算法具有以下性质：正确性（correct），具体步骤(concrete steps)，确定性(no ambiguity)，有限性(finite)，可终止性(terminable)
- **答案**：(B)
- **解释**：算法要求是明确的，不能是含糊不明确的（Ambiguous），而应该具有确定性，也就是不能有歧义。算法需要部分正确（保证在一定条件下能得到正确结果）、要有具体步骤来描述如何执行、最终要能够终止，所以必须满足 A、C、D 选项所描述的性质，不能满足的就是 B 选项描述的含糊这一情况，所以选择 B。

### (4)
- **题目**：
Which statement is **not correct** among the following four: (    )
(A) The Quick-sort is an unstable（不稳定的）sorting algorithm.
(B) The number of **empty sub-trees**（空子树） in a non-empty（非空） full binary tree 满二叉树 is one more than the number of nodes 结点 in the tree. P98 页
(C) The worst case for my algorithm is n becoming larger and larger because that is the slowest.
(D) A cluster is the smallest unit of allocation for a file, so all files occupy a multiple of the cluster size.第 8 章 P177
- **答案**：(C)
- **解释**：
    - A选项：快速排序确实是不稳定排序算法，它在排序过程中相等元素的相对顺序可能会改变，该说法正确。
    - B选项：对于非空满二叉树，其空子树的数量确实是比节点数量多 1，这是满二叉树的相关性质，该说法正确。
    - C选项：说算法最坏情况只是因为 n 越来越大就最慢这种表述不准确，算法的最坏情况通常是由其自身的数据处理逻辑、比较和移动元素等操作在特定数据分布下导致的复杂度过高的情况，而不单纯取决于 n 增大，所以该说法错误。
    - D选项：簇是文件分配的最小单位，文件占用空间通常是簇大小的整数倍，这是关于文件存储方面的正确描述。所以选择 C 选项。

### (5)
- **题目**：
Which algorithm is used to generate runs(顺串) in classic **external sorting**（外排序）? (     )
(A) Replacement selection 置换选择排序 P190    (B) Bubble sort
(C ) Insertion sort   (D) Quick-sort
- **答案**：(A)
- **解释**：在经典的外排序中，置换选择排序（Replacement selection）常用来生成顺串，它能够高效地利用内存和磁盘交互，形成初始的顺串，而冒泡排序（Bubble sort）、插入排序（Insertion sort）、快速排序（Quick-sort）主要应用于内排序场景，并不用于外排序中生成顺串这个操作，所以选择 A 选项。

### (6)
- **题目**：
Which of the following is a true statement: (    )
(A) A general tree can be transferred to a binary tree with the root having both left child and right child.**
(B) In a BST, the node can be enumerated(枚举) sorted by a **preorder traversal** （前序遍历）to the BST. 
(C) In a BST, the left child of any node is **less than**(小于) the right child（对的）, but in a heap, the left child of any node could be less than or greater than the right child.
(D) A heap（堆） must be full binary tree.
- **答案**：(C)
- **解释**：
    - A选项：一般树转化为二叉树后，根节点不一定同时有左孩子和右孩子，转化规则有其特定的对应关系，该说法错误。
    - B选项：在二叉搜索树（BST）中，中序遍历才能得到节点的有序枚举，而不是前序遍历，前序遍历得到的顺序不是排序后的顺序，该说法错误。
    - C选项：在二叉搜索树中，确实规定任意节点的左子节点小于右子节点；而在堆中（比如最小堆、最大堆等概念下），兄弟节点之间并没有严格规定左子节点和右子节点谁大谁小，该说法正确。
    - D选项：堆不一定是满二叉树，它是一种特殊的完全二叉树结构，但不一定是满二叉树，该说法错误。所以选择 C 选项。

### (7)
- **题目**：
  The golden rule of a disk-based program design is to: (    )
  (A) Improve the basic operations.   (B) Minimize the number of disk accesses.
  (C) Eliminate the recursive calls.    (D) Reduce main memory use.
- **答案**：(B)
- **解释**：在基于磁盘的程序设计中，磁盘访问速度相对较慢，所以最关键的黄金法则就是尽量减少磁盘访问次数，以此来提高程序整体的效率。而改进基本操作、消除递归调用、减少主内存使用都不是磁盘程序设计中最核心的黄金规则所强调的内容，所以选择 B 选项。 



## Select the correct choice.   

### (5)
- **题目**：
We use the parent pointer representation for general trees to solve (     ) problem?
(A) Shortest paths              (B) General tree traversal 
(C) Determining if two nodes are in the same tree (D) Exact-match query
- **答案**：(C)
- **解释**：使用父指针表示法来表示普通树，常用于判断两个节点是否在同一棵树中。比如通过向上追溯父指针，可以确定节点所在的树结构，进而判断它们是否属于同一棵树。而对于最短路径问题，通常有专门的图算法来解决（如迪杰斯特拉算法等）；普通树遍历有多种常规的遍历方式（前序、中序、后序等），并非依赖父指针表示法来专门解决；精确匹配查询也不是父指针表示法主要针对解决的问题，所以选择 C 选项。

### (4)
- **题目**：
Which statement is not correct among the following four: (    )
(A) The number of empty sub-trees in a non-empty binary tree is one less than the number of nodes in the tree.
(B) The Mergesort is a stable sorting algorithm.
(C) A general tree can be transferred to a binary tree with the root having only left child.
(D) A sector is the smallest unit of allocation for a record, so all records occupy a multiple of the sector size. 
- **答案**：(A)
- **解释**：
    - A选项：非空二叉树中，空子树的数量应该是比节点数量多 1，而不是少 1，该说法错误。
    - B选项：归并排序是稳定的排序算法，在合并过程中相等元素的相对顺序能够保持不变，该说法正确。
    - C选项：一般树可以通过特定的转换规则转化为二叉树，存在将其转化为根节点只有左孩子这种形式的转换方式，该说法正确。
    - D选项：扇区是记录分配的最小单位，文件记录占用空间通常是扇区大小的整数倍，这符合存储方面的原理，该说法正确。所以选择 A 选项。

### (7)
- **题目**：
In the following sorting algorithms, which is the best one to find the first 10 biggest elements in the 1000 unsorted elements? (     )
(A) Insert sort.               (B) Shell sort.
(C) Quicksort.               (D) Heap sort.
- **答案**：(D)
- **解释**：
    - A选项：插入排序对于少量有序数据插入时较合适，但要从众多无序元素中找前 10 个最大元素效率不高，它平均时间复杂度为 $O(n^2)$ 。
    - B选项：希尔排序是对插入排序的改进，主要是改进了插入排序中元素间隔较大时移动次数多的问题，但同样不太适合快速找出特定个数的最大元素，其时间复杂度与增量序列等因素有关。
    - C选项：快速排序主要优势在于平均性能较好，能快速对整个数据集进行排序，但如果只是想获取前 10 个最大元素，它会对所有元素都进行较多不必要的比较和交换操作，效率不是最优。
    - D选项：堆排序可以利用最大堆这种数据结构，建堆后每次取出堆顶元素（最大元素），重复 10 次就能得到前 10 个最大元素，时间复杂度相对较优，能高效地解决这类找出部分最大元素的问题，所以选择 D 选项。

### (9)
- **题目**：
Which queries supported by both of the hashing and tree indexing method? (    ) 
(A) Range queries.         (B) Queries in key order
(C) Minimum or maximum queries   (D). Exact-match queries
- **答案**：(D)
- **解释**：
    - A选项：范围查询通常树索引（如 B 树等索引结构）支持较好，便于按顺序查找一定范围内的数据，但哈希一般不太方便直接支持范围查询，它更适合精确查找。
    - B选项：按关键字顺序查询也是树索引的优势所在，能方便地按照键的顺序遍历数据，哈希表并不擅长按顺序查询。
    - C选项：求最小值或最大值，树索引结构（例如二叉搜索树等通过遍历可以方便找到最值）便于实现，哈希表很难直接用于求最值操作。
    - D选项：精确匹配查询，哈希表通过计算哈希值能快速定位到对应元素，树索引通过查找也能定位到具体匹配的元素，所以两种方法都支持精确匹配查询，选择 D 选项。 