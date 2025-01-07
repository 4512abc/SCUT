# SCUT2016 A and B

## Select the correct choice.

### (4)
- **题目**：
Which is the realization of a data type as a software component: (  A  )
(A) An abstract data type   (B) A real data type
 (C) A type        (D) A data structure
- **答案**：(A)
- **解释**：抽象数据类型（Abstract Data Type，简称 ADT）是将数据类型作为软件组件进行实现的一种方式。它通过定义一组数据以及对这些数据进行操作的接口，隐藏了数据的具体表示和内部实现细节，外部只通过规定的操作来与该数据类型交互，就如同一个软件组件一样被使用。而“真实数据类型”这种表述比较宽泛笼统；“类型”概念也很宽泛，没有体现出作为软件组件这一特性；“数据结构”侧重于数据的组织和存储方式，并非强调作为软件组件层面的数据类型实现，所以选择 A 选项。

### (6)
- **题目**：
In the hash function, collision refers to (  B   ).
(A) Two elements have the same key value.
(B) Different keys are mapped to the same position of hash table.
(C) Two records have the same requiring number.    
(D) Data elements are too much.
- **答案**：(B)
- **解释**：在哈希函数中，碰撞（collision）指的就是不同的键经过哈希函数计算后，被映射到了哈希表中的同一个位置。选项 A 说的是两个元素本身具有相同的键值，这和哈希函数中的碰撞概念不同；选项 C 中“相同要求编号”与哈希函数的碰撞概念无关；选项 D 说数据元素太多，这不是碰撞的定义，碰撞强调的是键映射到哈希表位置的情况，所以选择 B 选项。

### (8)
- **题目**：
Which statement is not correct among the following four: (  A  )
(A) The number of empty sub-trees in a non-empty binary tree is one less than the number of nodes in the tree.
(B) The Mergesort is a stable sorting algorithm.
(C) The root of a binary tree transferred from a general tree has only left child.
(D) A sector is the smallest unit of allocation for a record, so all records occupy a multiple of the sector size. 
- **答案**：(A)
- **解释**：
    - A选项：实际上，在非空二叉树中，空子树的数量是比节点数量多 1，而不是少 1，该说法错误。
    - B选项：归并排序在合并子序列的过程中，对于相等元素能够保证其相对顺序不变，是稳定的排序算法，该说法正确。
    - C选项：一般树转换为二叉树时，通常采用的转换方法会使得转换后的二叉树其根节点只有左孩子（例如左孩子表示原树节点，右孩子表示原树节点的兄弟节点这种常见转换方式），该说法正确。
    - D选项：扇区作为记录分配的最小单位，从存储原理来讲，所有记录所占用的空间确实是扇区大小的整数倍，该说法正确。所以选择 A 选项。

### (9)
- **题目**：
Tree indexing methods are meant to overcome what deficiency in hashing? (  D  )
(A) Inability to handle range queries.    (B) Inability to maximum queries
(C) Inability to handle queries in key order   (D) All of above.
- **答案**：(D)
- **解释**：哈希方法存在一些局限性，比如它很难直接处理范围查询，因为哈希表是基于键值快速定位元素，不是按照顺序存储的，不利于查找某个范围内的数据；对于求最大值或最小值这样的查询操作，哈希表也不方便直接实现，它不是以方便获取最值的结构来组织数据的；同样，按关键字顺序进行查询，哈希表也不擅长，它没有像树索引那样天然具有顺序性便于按顺序查找。而树索引方法则可以较好地处理这些情况，能够克服哈希在这些方面的不足，所以选择 D 选项。 



### 3.
1. **分析**
   - 计算具有特定节点数的不同形态二叉树数量可以使用卡特兰数（Catalan number）公式$C_n=\frac{1}{n + 1}{2n\choose n}$来计算。
   - 题目中给出了计算2、3、4、5节点不同形态二叉树数量的示例方法，我们可以按照类似思路进行计算。
2. **计算过程**
   - 2节点：2种形态
   - 3节点：
     - 设根节点为1个节点，剩下2个节点分配到左右子树。
     - 左子树0个节点，右子树2个节点有2种形态；左子树1个节点，右子树1个节点有2种形态；左子树2个节点，右子树0个节点有2种形态。
     - 总共$1 + 2+ 2 = 5$种形态。
   - 4节点：
     - 设根节点为1个节点，剩下3个节点分配到左右子树。
     - 左子树0个节点，右子树3个节点有5种形态；左子树1个节点，右子树2个节点有5种形态；左子树2个节点，右子树1个节点有2种形态；左子树3个节点，右子树0个节点有2种形态。
     - 总共$5+5 + 2+2 = 14$种形态。
   - 5节点：
     - 设根节点为1个节点，剩下4个节点分配到左右子树。
     - 左子树0个节点，右子树4个节点有14种形态；左子树1个节点，右子树3个节点有14种形态；左子树2个节点，右子树2个节点有5种形态；左子树3个节点，右子树1个节点有5种形态；左子树4个节点，右子树0个节点有4种形态。
     - 总共$14+14 + 5+5+4 = 42$种形态。
   - 6节点：
     - 设根节点为1个节点，剩下5个节点分配到左右子树。
     - 左子树0个节点，右子树5个节点有42种形态；左子树1个节点，右子树4个节点有42种形态；左子树2个节点，右子树3个节点有14种形态；左子树3个节点，右子树2个节点有14种形态；左子树4个节点，右子树1个节点有5种形态；左子树5个节点，右子树0个节点有5种形态。
     - 总共$42+42+14 + 14+5\times2+5\times2 = 132$种形态。
   - 也可以直接使用卡特兰数公式$C_6=\frac{1}{7}{12\choose 6}=\frac{12!}{7\times6!\times6!}=132$

### 8.
1. **(a) 外部排序两阶段主要任务**
   - 第一阶段：
     - 主要任务是通过置换选择算法（replacement selection）将文件分解成较大的初始顺串（runs）。
     - 置换选择算法利用内存缓冲区，尽可能生成较长的顺串，减少后续合并阶段的工作量。
   - 第二阶段：
     - 主要任务是将这些顺串合并在一起，形成一个单一的已排序文件。
     - 通常采用多路合并（multi - way merge）的方法，例如2 - way merge（二路合并）、k - way merge（k路合并）等方法来合并顺串。
2. **(b) 计算可处理的最大文件大小**
   - 已知工作内存为$512KB$，块大小为$4096$字节（$4KB$）。
   - 首先计算工作内存中的块数：$512KB\div4KB = 128$块。
   - 在置换选择阶段，预期的顺串长度为$1024KB$（这是基于置换选择算法的特性，通常顺串长度约为内存大小的两倍）。
   - 第一路合并（第一次多路合并）：
     - 由于有$128$块内存，每次可以合并$128$个顺串，每个顺串长度为$1024KB$。
     - 第一路合并后形成的顺串长度为$1024KB\times128 = 128MB$。
   - 第二路合并（第二次多路合并）：
     - 再次合并这些顺串，同样有$128$个顺串（每个顺串现在是$128MB$大小）。
     - 第二路合并后形成的文件大小为$128MB\times128 = 16GB$。

所以，使用置换选择和两路多路合并可以处理的最大文件大小为$16GB$。

## Recovery a general tree as following transferred from a binary tree.

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412021510518.webp)

这题暂时留着，不进行研究。



## Select the correct choice.   

### 1.
1. **(3)**
   - **题目**：Which statement is **not** correct among the following four: (  D  ) 
   - **选项**：
     - (A) In a BST, the left child of any node is less than the right child, but in a heap, the left child of any node could be less than or greater than the right child.
     - (B) The number of empty subtrees in a non - empty binary tree is one more than the number of nodes in the tree.
     - (C) A general tree can be transferred to a binary tree with the root having only left child.
     - (D) A heap must be a full binary tree.
   - **分析**：
     - A选项：在二叉搜索树（BST）中，确实有任意节点的左子节点小于右子节点这一特性，而在堆中（比如最小堆、最大堆），兄弟节点间并没有严格规定左子节点和右子节点谁大谁小，该说法正确。
     - B选项：非空二叉树中空子树的数量比节点数量多1，这是二叉树的基本性质，该说法正确。
     - C选项：一般树可以通过特定方法转换为根节点只有左孩子的二叉树，该说法正确。
     - D选项：堆是一种完全二叉树，但不一定是满二叉树，该说法错误。
   - **答案**：(D)
2. **(9)**
   - **题目**：The time cost of Quicksort in the worst case is (  D  ).
   - **选项**：(A) $O(n)$  (B) $O(log_2 n)$  (C) $O(n log_2 n)$  (D) $O(n^2)$
   - **分析**：快速排序（Quicksort）在最坏情况下，例如每次选择的基准元素都是最大或最小元素时，其时间复杂度为$O(n^{2})$。
   - **答案**：(D)
3. **(10)**
   - **题目**：The function of replacement selection sort is (  B   ).
   - **选项**：(A) Select the maximal element.    (B) Generate the initial sorted merge files.
   (C) Merge the sorted file.          (D) Replace some record.
   - **分析**：置换选择排序（Replacement selection sort）的主要作用是生成初始的顺串（即初始的已排序合并文件），这在外排序过程中非常重要。
   - **答案**：(B)

### 2.
1. **题目**：Arrange the following expressions by growth rate from slowest to fastest. (4 scores)
2. **表达式**：$3n^2, log_3n, n!, 10n, 2n, 20, log_2n, 8n^{2/3}$
3. **分析**：
   - 常数函数增长最慢，这里$20$是常数函数。
   - 对数函数增长较慢，$\log_{2}n$和$\log_{3}n$属于对数函数，且对数函数增长速率小于多项式函数。
   - 在多项式函数中，$n$的幂次越低增长越慢，所以$8n^{2/3}<3n^{2}$。
   - 指数函数增长很快，$2^{n}<10^{n}$。
   - 阶乘函数$n!$增长速率比指数函数还要快。
4. **排序**：
   - 从慢到快依次为：$20<\log_{2}n<\log_{3}n<8n^{2/3}<3n^{2}<2^{n}<10^{n}<n!$



## Please apply Quicksort Algorithm to sort the array in ascending order: 265, 301, 751, 129, 937, 863, 742, 694, 076, 438. Note that the pivot value is selected based on the following function, Parameters `i` and `j` define the start and end indices of the Array `A`, respectively.           

```cpp
template <typename E>
inline int findpivot(E A[], int i, int j)
{ 
	return A[i]; 
}  
```

**疑似存在问题**

### 1. Quicksort Algorithm

1. **原理**
   - 快速排序（Quicksort）是一种基于分治策略的排序算法。它的基本思想是选择一个基准元素（pivot），将数组分为两部分，使得左边部分的元素都小于等于基准元素，右边部分的元素都大于等于基准元素。然后对这两部分分别进行快速排序，直到整个数组有序。
   - 在这个例子中，基准元素选择函数`findpivot`简单地选择了子数组的第一个元素作为基准。
2. **步骤分析**
   - **Initial（初始）**：[265 301 751 129 937 863 742 694 076 438]
     - 选择第一个元素265作为基准（pivot）。
   - **1st pass（第一趟）**：[076 129] 265 [751 937 863 742 694 301 438]
     - 从数组的两端开始扫描，将小于265的元素移到左边，大于265的元素移到右边。
     - 得到左边子数组[076 129]，基准265，右边子数组[751 937 863 742 694 301 438]。
   - **2nd pass（第二趟）**：076 [129] 265 [438 301 694 742] 751 [863 937]
     - 对左边子数组[076 129]和右边子数组[751 937 863 742 694 301 438]分别进行快速排序。
     - 左边子数组以129为基准，得到076和129。
     - 右边子数组以751为基准，得到[438 301 694 742]和[863 937]。
   - **3rd pass（第三趟）**：076 129 265 [301] 438 [694 742] 751 863 [937]
     - 继续对[438 301 694 742]和[863 937]进行快速排序。
     - [438 301 694 742]以301为基准，得到301和[438 694 742]。
     - [863 937]以863为基准，得到863和937。
   - **4th pass（第四趟）**：076 129 265 301 438 694 [742] 751 863 937
     - 对[438 694 742]进行快速排序，以742为基准，得到[438 694]和742。
   - **5th pass（第五趟）**：076 129 265 301 438 694 742 751 863 937
     - 此时整个数组已经有序。

 



## Given a hash table of size 11, assume that $H_1(k)=(2k+1)mod \ 11$ and $H_2(k)=(3k \ mod \ 10) + 1$are two hash functions, where $H_1$ is used to get home position and $H_2$ is used to resolve collision for method double hashing. Please insert keys 9, 17, 63, 55, 22, 27, 88, 41 into the hash table in order.  

### 2. Hash Table Insertion

1. **原理**
   - 哈希表（Hash Table）是一种数据结构，用于快速查找、插入和删除数据。在这个问题中，使用了双哈希（Double Hashing）方法来处理冲突。
   - 双哈希使用两个哈希函数$H_1$和$H_2$。$H_1$用于计算元素的初始哈希位置（home position），如果该位置已经被占用（发生冲突），则使用$H_2$来计算下一个可能的位置。
2. **步骤分析**
   - **Inserting keys（插入键值）**
     - $H_1(9)=8$，9插入到位置8。
     - $H_1(17)=2$，17插入到位置2。
     - $H_1(63)=6$，63插入到位置6。
     - $H_1(55)=1$，55插入到位置1。
     - 当插入22时，$H_1(22)=1$（冲突，位置1已被55占用），计算$H_2(22)=7$，新位置为$(1 + 2*7)\%11 = 4$，22插入到位置4。
     - $H_1(27)=0$，27插入到位置0。
     - 当插入88时，$H_1(88)=1$（冲突，位置1已被55占用），计算$H_2(88)=5$，新位置为$(1+3*5)\%11 = 5$，88插入到位置5。
     - 当插入41时，$H_1(41)=6$（冲突，位置6已被63占用），计算$H_2(41)=4$，新位置为$(6 + 1*4)\%11 = 10$，41插入到位置10。
   - **Resulting Hash Table（最终哈希表）**
     - | 27   | 55   | 17   |      | 22   | 88   | 63   |      | 9    |      | 41   |
       | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
       | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   |



## Complete the insert, remove functions of the Link-based List class. (6 scores) 

```cpp
template <class Elem> class LList: public List<Elem> {

private:
	Link<Elem>* head;//Point to list header
 	Link<Elem>* tail;//Pointer to last Elem 
	Link<Elem>* fence;//Last element on left
 	int leftcnt; //Size of left
 	int rightcnt; //Size of right

public:
	bool LList<Elem>::insert(const Elem& item) { }
	template <class Elem> bool LList<Elem>::remove(Elem& it) { }
```



### 3. Link - based List Insert and Remove Functions

1. **Insert Function（插入函数）**
   - **原理**
     - 这个插入函数是在链表的右分区（right partition）的前端插入元素。
     - 首先创建一个新的节点，其元素为`item`，下一个节点为`fence->next`（即当前`fence`节点之后的节点）。
     - 如果`tail`等于`fence`，说明`fence`是最后一个节点，那么插入新节点后`tail`应该更新为新节点。
     - 最后增加右分区的大小`rightcnt`。
   - **代码分析**
     - `fence->next = new Link<Elem>(item, fence->next);`：创建新节点并插入。
     - `if (tail == fence) tail = fence->next;`：更新`tail`。
     - `rightcnt++;`：增加右分区大小。
2. **Remove Function（删除函数）**
   - **原理**
     - 这个删除函数是删除链表右分区（right partition）的第一个元素。
     - 首先检查`fence->next`是否为`NULL`，如果是则表示右分区为空，无法删除，返回`false`。
     - 如果右分区不为空，记录要删除节点的值到`it`，并记录要删除的节点为`ltemp`。
     - 更新`fence`的下一个节点为`ltemp->next`，即跳过要删除的节点。
     - 如果`tail`等于`ltemp`，说明要删除的是最后一个节点，那么`tail`应该更新为`fence`。
     - 最后删除`ltemp`节点，减少右分区大小`rightcnt`并返回`true`。
   - **代码分析**
     - `if (fence->next == NULL) return false;`：检查是否可删除。
     - `it = fence->next->element;`：记录要删除节点的值。
     - `Link<Elem>* ltemp = fence->next;`：记录要删除的节点。
     - `fence->next = ltemp->next;`：跳过要删除的节点。
     - `if (tail == ltemp) tail = fence;`：更新`tail`（如果需要）。
     - `delete ltemp;`：删除节点。
     - `rightcnt--;`：减少右分区大小。