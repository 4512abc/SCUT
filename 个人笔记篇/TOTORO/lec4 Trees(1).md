# lec4 Trees(1)

> ![image-20241119170227426](C:\Totoro.trip\blog-demo\source\images\image-20241119170227426.png)注意，你的弱项在哪一块。博主的话对于原理有一些淡忘，需要重新拿起原理，并加强一下代码的实现。高屋建瓴之后，进入这一章吧。

## 引入

**列表、栈与队列是线性关系**

**信息中经常存在层次关系**

现实中的信息通常并非简单的线性排列，而是层次化的。以下是一些典型的层次化关系示例：

- **文件目录或文件夹结构**
- **游戏中的移动路径**
- **组织中的层级结构**

**用树形结构表示层次关系**

树形结构是一种有效的方式，可以用来表示层次关系，同时支持快速查找。

## 术语集合

### **树的基础概念**

---

#### **1. 节点和边**
- **节点 (Nodes)**：树中的元素。
- **边 (Edges)**：连接树中节点的线段。

---

#### **2. 树中节点的关系**
- **父节点 (Parent)**：直接连接到某节点上方的节点。
- **子节点 (Children)**：直接连接到某节点下方的节点。
- **兄弟节点 (Siblings)**：同一父节点的所有子节点。
- **祖先节点 (Ancestors)**：从某节点向上追溯到根节点的所有节点。
- **后代节点 (Descendants)**：从某节点向下延伸到叶子节点的所有节点。

---

#### **3. 特殊节点**
- **根节点 (Root)**：树的起始节点，唯一且没有父节点。
- **叶子节点 (Leaves)**：没有子节点的节点。
- **子树 (Subtrees)**：由某节点及其所有后代组成的树。

---

#### **4. 路径与路径长度**
- **路径 (Path)**：从一个节点到另一个节点经过的节点序列。
- **路径长度 (Path Length)**：路径中边的数量。

---

#### **5. 树的深度和高度**
- **节点 N 的深度 (Depth)**：从根节点到节点 $ N $ 的路径长度。
- **节点 N 的高度 (Height)**：从节点 $ N $ 到某叶子节点的最长路径长度。
- **树的深度 (Depth of Tree)**：树中最深节点的深度。
- **树的高度 (Height of Tree)**：树中根节点的高度。

> 高度和深度如果只是从文字的角度上看可能还是会迷糊。
>
> 因此可以看这个图理解一下：
>
> 误区主要是`0`和`D`那里。
>
> ![image-20241119165402931](C:\Totoro.trip\blog-demo\source\images\image-20241119165402931.png)

---

#### **6. 树的定义**
- **树 (Tree)** 是一组节点，满足以下条件：
  1. 树可以是空集合。
  2. 如果不是空集合，则包含一个称为 **根节点 (Root)** 的节点，其余节点从根节点派生为若干 **子树 (Subtrees)**。
  3. 树中的任意两个节点之间最多只能有一条路径。

---

#### **7. 树的特性**
- 树中不存在从某节点 $ N $ 出发再返回 $ N $ 的非零路径。
- **树不能有环 (Cycles)**，即不能形成闭环或回路。

---

### 树的边数和节点数

#### **定理：**
一个包含 $ N $ 个节点的树，始终有 $ N - 1 $ 条边。

![image-20241119165723612](C:\Totoro.trip\blog-demo\source\images\image-20241119165723612.png)

---

#### **证明：**

使用 **数学归纳法** 来证明这个定理。

---

#### **基础情况：**
- 当 $ N = 1 $ 时，树只有一个节点，即根节点，显然没有边。
- 因此，树的边数为 0，满足 $ 1 - 1 = 0 $，这符合定理。

---

#### **归纳假设：**
- 假设对于包含 $ k $ 个节点的树，边数总是 $ k - 1 $ 条。
- 现在，我们假设树中有 $ k $ 个节点且该树符合定理，即边数为 $ k - 1 $。

---

#### **归纳步骤：**
- 现在考虑包含 $ k+1 $ 个节点的树。
- 第 $ k+1 $ 个节点必须连接到树中的其他节点。为了避免形成环，必须通过一条边连接其余部分。
- 因此，增加一个节点后，树的边数增加 1。
- 所以，包含 $ k+1 $ 个节点的树的边数为 $ (k - 1) + 1 = k $，这也符合定理 $ N - 1 $。

---

#### **结论：**
- 根据数学归纳法，已经证明对于任何包含 $ N $ 个节点的树，树的边数总是 $ N - 1 $ 条。

##  **树的实现**

---

#### **一种可能的基于指针的实现方式**

- **树节点**：每个节点包含一个值以及指向每个子节点的指针。
- **问题**：每个节点需要为多少个子节点分配指针空间？

---

#### **更灵活的基于指针的实现方式：**  
**1st Child / Next Sibling List 表示法**

- **基本思想**：
  - 每个节点有 **两个指针**：
    - 一个指向**第一个子节点**（First Child）
    - 另一个指向**下一个兄弟节点**（Next Sibling）
- 通过这种方式，可以处理具有任意数量子节点的树结构。

---

#### **如何工作：**

1. **第一个指针**：指向当前节点的第一个子节点。
2. **第二个指针**：指向当前节点的下一个兄弟节点。
   - 如果没有下一个兄弟节点，则该指针为空。
3. 通过这个结构，我们不需要为每个节点的每个子节点分配独立的指针空间，而是通过兄弟节点的链接来管理树的层次关系。

---

#### **优点：**
- 该表示法 **灵活且高效**，可以动态处理节点的子节点数量。
- 不需要预先分配大量的空间用于存储指针，而是根据需要动态链接兄弟节点。

---

#### **示意图**：

假设我们有如下树形结构：
```
        A
       / \
      B   C
     / \
    D   E
```

- **节点 A**：第一个指针指向 B（A 的第一个子节点），第二个指针指向 C（A 的下一个兄弟节点）。
- **节点 B**：第一个指针指向 D（B 的第一个子节点），第二个指针指向 E（B 的下一个兄弟节点）。
- **节点 D 和 E**：没有子节点或兄弟节点，因此它们的指针都为空。

这种方法非常适合于需要表示**任意数量子节点**的树结构，尤其是在处理多叉树时表现出色。

![image-20241119170123126](C:\Totoro.trip\blog-demo\source\images\image-20241119170123126.png)

```cpp
//Node declarations for trees
Struct TreeNode{
      Object element;
      TreeNode *firstChild;
      TreeNode *nextSibling;
};

```

## Binary Trees

### **二叉树 (Binary Trees)**

---

#### **基本定义：**
- 每个节点最多有两个子节点。
- 二叉树是计算机科学中最常见的树结构。

---

#### **给定 N 个节点，二叉树的最小深度是多少？**
- **最小深度**：意味着除最后一层外，所有层都是完全填充的。
- 在深度 $d$ 时，二叉树的节点数量 $N$ 可以在 $2^d \leq N < 2^{d+1}$ 范围内。
  - 即 $2^d \leq N \leq 2^{d+1} - 1$。
  - 最小深度 $d_{\text{min}} = \lfloor \log_2 N \rfloor$。

---

#### **推导过程：**
- 给定 $2^d \leq N < 2^{d+1}$，
- 取对数后得到：
  - $d \leq \log_2 N < d+1$
  - 从而得出： $d = \lfloor \log_2 N \rfloor$。

- **最小深度** $d_{\text{min}}$ 为 $O(\log N)$。

![image-20241119170847318](C:\Totoro.trip\blog-demo\source\images\image-20241119170847318.png)

---

#### **最大深度：**
- **退化情况**：如果树变成了链表，最大深度为 $N-1$。
- 在这种情况下，树的结构极为不平衡，所有节点只有一个子节点。

![image-20241119170906575](C:\Totoro.trip\blog-demo\source\images\image-20241119170906575.png)

---

#### **目标：**
- **理想情况**：我们希望树的深度保持在 $\log N$ 左右，这样对于一些操作（例如查找操作）能获得比链表更好的性能。

### **二叉树的遍历与定义**

---

#### **`BinNode` 类定义：**
```cpp
template <typename E> class BinNode { 
 public:
   virtual E& element() = 0;      // 返回节点的值
   virtual void setElement(const E&) = 0; // 设置节点的值
   
   virtual BinNode* left() const = 0;  // 返回节点的左子节点
   virtual void setLeft(BinNode*) = 0; // 设置左子节点

   virtual BinNode* right() const = 0; // 返回节点的右子节点
   virtual void setRight(BinNode*) = 0; // 设置右子节点
   
   virtual bool isLeaf() = 0; // 检查节点是否是叶子节点
};
```
该类定义了二叉树节点的基本操作，包括获取和设置节点值、左右子节点以及判断是否为叶子节点。

---

#### **遍历定义：**
遍历的定义通常是递归的过程。下面是三种常见的二叉树遍历方式的定义：

1. **前序遍历 (Preorder)**:
   - 顺序：节点 -> 左子树 -> 右子树
   - 递归过程：首先访问根节点，然后递归访问左子树，再递归访问右子树。
   - 例子：`+ * + A B C D`
   
2. **中序遍历 (Inorder)**:
   - 顺序：左子树 -> 节点 -> 右子树
   - 递归过程：首先递归访问左子树，然后访问根节点，最后递归访问右子树。
   - 例子：`A + B * C + D`

3. **后序遍历 (Postorder)**:
   - 顺序：左子树 -> 右子树 -> 节点
   - 递归过程：首先递归访问左子树，然后递归访问右子树，最后访问根节点。
   - 例子：`A B + C * D +`

这些遍历定义可以扩展到一般（非二叉）树中。

### 构造二叉树

可以看图推理：

![image-20241119171719273](C:\Totoro.trip\blog-demo\source\images\image-20241119171719273.png)

代码如下：根据前序遍历和中序遍历进行推理。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
unordered_map<int,int>mp;
class Solution {
public:
    TreeNode* deduceTree(vector<int>& preorder, vector<int>& inorder) {
    for(int i=0;i<inorder.size();i++)
    {
        mp[inorder[i]]=i;
    }
    return build(preorder,inorder,0,0,inorder.size()-1);
    }
    TreeNode *build(vector<int>&preorder,vector<int>&inorder,int pre_root,int in_left,int in_right)
{
    if(in_left>in_right)
    {
        return NULL;
    }
    TreeNode * root=new TreeNode(preorder[pre_root]);
    int in_root=mp[preorder[pre_root]];
    root->left=build(preorder,inorder,pre_root+1,in_left,in_root-1);
    root->right=build(preorder,inorder,pre_root+in_root-in_left+1,in_root+1,in_right);
    return root;
}
};
```

## Binary Search Trees

---

#### **二叉搜索树的性质：**
- **左子树**的所有节点值都小于节点的值。
- **右子树**的所有节点值都大于节点的值。
- 二叉搜索树通过这些性质确保了查找、插入和删除操作的高效性。

![image-20241119172429115](C:\Totoro.trip\blog-demo\source\images\image-20241119172429115.png)

---

#### **常见操作：**

1. **查找（Find）**:
   ```cpp
   bool contains( const Comparable & x, BinaryNode *t ) const {
     if( t == nullptr ) return false; // 如果节点为空，返回 false
     else if( x < t->element ) return contains( x, t->left ); // 如果 x 小于当前节点，递归查找左子树
     else if( t->element < x ) return contains( x, t->right ); // 如果 x 大于当前节点，递归查找右子树
     else return true; // 找到匹配的节点，返回 true
   }
   ```

2. **查找最小值（FindMin）**:
   查找子树中最小的节点：
   ```cpp
   BinaryNode* findMin(BinaryNode *t) const {
     if( t == nullptr ) return nullptr; // 如果子树为空，返回空
     if( t->left == nullptr ) return t; // 如果没有左子节点，则当前节点是最小的
     return findMin(t->left); // 否则递归查找左子树
   }
   ```

3. **插入（Insert）**:
   插入操作需要保持二叉搜索树的性质。每次插入时，我们首先执行查找操作。
   
   - 如果找到该元素，更新该节点的值（若不需要插入）。
   - 如果没找到元素（查找结束为 NULL），则插入新节点。
   ```cpp
   void insert( const Comparable & x, BinaryNode * & t ) {
     if( t == nullptr ) {
       t = new BinaryNode{ x, nullptr, nullptr }; // 如果树为空，创建新节点
     }
     else if( x < t->element ) {
       insert( x, t->left ); // 递归插入到左子树
     }
     else if( t->element < x ) {
       insert( x, t->right ); // 递归插入到右子树
     }
     else {
       ; // 如果是重复元素，不做任何操作
     }
   }
   ```
   
4. **删除（Delete）**:
   删除操作较为复杂，需考虑删除节点的不同情况：
   - 如果节点没有子节点，直接删除。
   
   > ![image-20241119172831405](C:\Totoro.trip\blog-demo\source\images\image-20241119172831405.png)

   - 如果节点只有一个子节点，用该子节点替代。
   
   > ![image-20241119172852884](C:\Totoro.trip\blog-demo\source\images\image-20241119172852884.png)
   
   - 如果节点有两个子节点，用右子树中最小的节点（即该节点的后继节点）替代。
   
   > ![image-20241119172939544](C:\Totoro.trip\blog-demo\source\images\image-20241119172939544.png)
   
   ```cpp
   void remove(const Comparable & x, BinaryNode * & t ) {
     if( t == nullptr ) return; // 如果树为空，返回
     if( x < t->element ) remove( x, t->left ); // 在左子树中查找
     else if( t->element < x ) remove( x, t->right ); // 在右子树中查找
     else if( t->left != nullptr && t->right != nullptr ) { 
       // 如果节点有两个子节点
       t->element = findMin(t->right)->element; // 用右子树中最小的元素替代
       remove( t->element, t->right ); // 删除右子树中的最小元素
     }
     else { 
       // 如果节点有一个或没有子节点
       BinaryNode *oldNode = t;
       t = ( t->left != nullptr ) ? t->left : t->right; // 用子节点替代
       delete oldNode; // 删除原节点
     }
   }
   ```

---

#### **二叉搜索树的性能：**
- 查找、插入、删除的时间复杂度取决于树的深度。在最坏情况下，如果树是线性的（类似链表），这些操作的时间复杂度为 O(n)。
- 在平均情况下，如果树是平衡的，操作的时间复杂度为 O(log n)。

**理想的树形结构：**

- **平衡的二叉搜索树**：高度保持在最小，时间复杂度为 O(log n)。
- **不平衡的二叉搜索树**：最坏情况下退化成链表，时间复杂度为 O(n)。

**遍历时间复杂度**：  
无论是前序遍历、中序遍历还是后序遍历，都需要遍历整个树，因此其时间复杂度为 O(n)。

---

> AVL树就单独开一个吧，期待一下。