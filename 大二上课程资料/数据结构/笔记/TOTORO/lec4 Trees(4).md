# lec4 Trees(4)

> ![image-20241119170227426](C:\Totoro.trip\blog-demo\source\images\image-20241119170227426.png)Splay树已经彻底掌握了！欢迎来到还没掌握完全的B树，之后的数据结构内容都很简单，很快就可以解决。（时空回溯了？)

## B树（B-Tree）简介

B树是一种多路搜索树，常用于数据库系统中，尤其是在外部存储（如磁盘）上存储数据的场景中。B树通过保持树的高度较小来提高查询效率，因为树的高度越小，查询时所需访问的磁盘块就越少。以下是B树的定义、性质以及操作方式的详细说明：

#### 1. B树的基本定义
- **阶数（Order）**：B树的阶数 $ M $ 表示每个节点最多可以有 $ M $ 个子节点，或者说每个节点最多可以包含 $ M - 1 $ 个键。阶数也决定了每个节点中存储的数据记录的数量范围。
- **树的高度**：B树是一棵平衡的多路搜索树，其所有的叶子节点都在同一层，因此树的高度保持在一个较小的范围内，从而提高查询效率。

#### 2. B树的主要性质
B树的每个节点（包括根节点和非根节点）有一组特定的属性：

1. **根节点的子节点数**：
   - 如果根节点是叶子节点，它没有子节点。
   - 如果根节点是非叶子节点，它必须有至少 2 个子节点，并且最多有 $ M $ 个子节点。

   (**The root is either a leaf or has between 2 and M children**)
   
2. **非根节点的子节点数**：
   
   - 每个非根节点必须包含至少 $ \lceil M/2 \rceil $ 个子节点（即上限为 $ M $）。(**All nonleaf nodes (except the root) have between éM/2ù and M children.**)
   
3. **叶子节点的深度**：
   
   - 所有叶子节点必须在同一层级上，保证B树的平衡性。(**All leaves are at the same depth.**)
   
4. **叶子节点的数据记录数量**：
   
   - 每个叶子节点可以存储 $ \lceil L/2 \rceil $ 到 $ L $ 条数据记录，其中 $ L $ 是该树的最大叶子节点容量（通常为 $ M $，但可以不同）。
   
5. **键的数量**：
   - 每个非叶子节点存储的键数为 $ k_1 < k_2 < \cdots < k_{M-1} $。
   - 每个非叶子节点的键数 $ k $ 满足：$ \lceil M/2 \rceil \leq k \leq M-1 $。

6. **键的作用**：
   
   - 内部节点的键指示了子树中存储的数据的范围，作用类似于“索引”，帮助快速定位到相应的叶子节点。(这是属于**B+**树的特征)

### 图示

![image-20241119202801165](C:\Totoro.trip\blog-demo\source\images\image-20241119202801165.png)

> #### 1. 子树的键值范围
> 假设有一个内部节点，其包含 $ k_1, k_2, \dots, k_{M-1} $ 这样的键，这些键将树分割成 $ M $ 个子树，分别是 $ T_1, T_2, \dots, T_M $，其中：
> - $ T_1 $ 是第一个子树，
> - $ T_2 $ 是第二个子树，
> - 以此类推。
>
> 对于每个子树 $ T_i $ （即第 $ i $ 个子树），其存储的所有键必须满足以下条件：
>
> - 所有 $ T_i $ 中的键都必须介于其相邻的两个键之间，即：
>   $
>   k_{i-1} \leq \text{所有键} < k_i
>   $
>   其中，$ k_{i-1} $ 是子树 $ T_i $ 中键的下限，而 $ k_i $ 是其上限。
>
> #### 2. 具体规则
> - **第一个子树 $ T_1 $**：所有键值必须小于 $ k_1 $：
>   $
>   \text{所有键} < k_1
>   $
>   这意味着第一个子树中的所有键值都小于第一个键 $ k_1 $。
>
> - **最后一个子树 $ T_M $**：所有键值必须大于或等于 $ k_{M-1} $：
>   $
>   \text{所有键} \geq k_{M-1}
>   $
>   这意味着最后一个子树中的所有键值都大于或等于倒数第二个键 $ k_{M-1} $。
>
> #### 3. 子树与键的关系
> 每个子树对应的范围由它的前后两个键确定，因此：
> - **$ T_1 $** 存储的所有键值都小于第一个键 $ k_1 $；
> - **$ T_M $** 存储的所有键值都大于等于最后一个键 $ k_{M-1} $；
> - 其他子树 $ T_2, T_3, \dots, T_{M-1} $ 中的键值必须在相邻的两个键值之间，确保树的有序性。
>

## B树阶数

#### 1. **B树的阶数 $M$ 的定义和节点特性**

- **阶数 $M$**：B树的阶数 $M$ 决定了每个节点的最大子节点数量和键的存储容量。
  - **内部节点的键数量**：每个内部节点最多可以存储 $M-1$ 个键。
  - **内部节点的子节点数量**：每个内部节点的子节点数介于 $\lceil M/2 \rceil$ 到 $M$ 之间。

#### 2. **B树的深度与时间复杂度**

- **存储 $N$ 个数据项的B树的深度**：  
  深度为：$O(\log_{\lceil M/2 \rceil} N)$。  
  随着阶数 $M$ 的增大，B树的深度会变浅。

- **查找操作的时间复杂度**：
  - 在每个节点中，通过二分查找找到合适的分支，时间复杂度为 $O(\log M)$。
  - 总时间复杂度为 $O(\text{深度} \times \log M) = O(\log N)$。

#### 3. **如何选择合适的阶数 $M$**

- **内存中的小阶数**：当数据存储在内存中时，较小的阶数（如 $M=3$ 或 $M=4$）通常足够。这是因为内存的访问速度快，树的深度对性能影响较小。

- **磁盘上的大阶数**：当数据存储在磁盘上时，阶数的选择需要考虑磁盘访问次数的问题：
  - 每次访问磁盘读取数据块时，尽量加载更多的键和子节点以减少磁盘I/O次数。
  - **选择规则**：选择最大的 $M$，使得一个内部节点能够完全存储在磁盘的一个物理块中。这种选择可以最大化数据的加载效率，并尽量减少树的深度。

#### 4. **磁盘存储的典型阶数**

- 磁盘上的B树阶数 $M$ 通常在 $32$ 到 $256$ 之间。  
  这样的阶数设计可以：
  - 保证B树足够浅，减少查找过程中需要访问的磁盘块数量。
  - 平衡磁盘I/O开销和查找效率。

## 一些话

PPT上关于插入和删除的例子过于稀少：

建议到访我的另一篇博客：[B树 | Totoroの旅 (totorocatcat.top)](https://www.totorocatcat.top/2024/10/04/B树/?highlight=b树)

> 这一篇博客讲解了B树的查找，插入和删除。

这里补充一下那里没有讲过的B+树和平衡树的一些比较

## B+树

这个B+树和市面上的还不一样，按照这个来理解吧。

![image-20241119211220733](C:\Totoro.trip\blog-demo\source\images\image-20241119211220733.png)

## 平衡树的比较

#### 1. **二叉搜索树的问题**
- 二叉搜索树（Binary Search Tree, BST）需要保持**平衡性**以确保高效的存储和访问。
- **问题**：当树不平衡时，最坏情况下会退化为链表，导致查找、插入和删除的时间复杂度从 $O(\log N)$ 下降到 $O(N)$。

#### 2. **解决方案：平衡树**
为了确保树的平衡性和高效操作，提出了以下平衡树结构：

##### 2.1 **AVL树**
- **特点**：
  - AVL树是一种自平衡二叉搜索树。
  - 在插入或删除节点后，通过旋转操作确保每个节点的左右子树高度差不超过 $1$。
- **优点**：
  - 插入和删除操作后始终保持树的平衡性。
  - 提供 $O(\log N)$ 的查找、插入和删除时间复杂度。

##### 2.2 **伸展树（Splay Tree）**
- **特点**：
  - 通过**重复的查找操作**，自动将频繁访问的节点移动到靠近根部的位置。
  - 使用“伸展”操作调整树的结构。
- **优点**：
  - 对于存在热点的应用场景（某些节点被频繁访问），可以提高访问效率。
  - 不需要显式存储平衡因子，操作较为简单。

##### 2.3 **多路搜索树（例如 B树）**
- **特点**：
  - 节点可以有**多个子节点**（而非仅两个）。
  - 保证所有叶子节点处于相同深度，且树始终保持平衡。
  - 插入和删除操作通过节点分裂和合并来调整树的结构。
- **优点**：
  - 通过允许节点有多个子节点，减少树的深度（比二叉树更浅）。
  - **适合数据库系统中的索引**：能有效减少磁盘访问次数，提升性能。

#### 3. **总结**
- **二叉搜索树问题**：树的不平衡会导致性能下降。
- **解决方案**：
  - AVL树：通过严格的高度平衡条件，适合需要频繁插入和删除的场景。
  - 伸展树：通过动态调整适应访问频率，适合热点数据的场景。
  - B树：多路平衡结构，适合大规模存储（如数据库索引）的场景。

