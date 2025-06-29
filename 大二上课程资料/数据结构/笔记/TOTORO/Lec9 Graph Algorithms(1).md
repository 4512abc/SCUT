# Lec9 Graph Algorithms(1)

> 图论的世界，探索!!!😎

## **图（Graphs）概念与基本定义**

图是由 **节点（顶点）** 和 **边（弧）** 组成的数据结构。它用于表示对象之间的关系或连接。

![image-20241120181858945](C:\Totoro.trip\blog-demo\source\images\image-20241120181858945.png)

### **图的组成：**

1. **节点（顶点，Vertices）：**
   - 图中的每个元素称为节点（或顶点），用来表示数据中的一个对象。
   - 节点可以是 **有标签的** 或 **无标签的**，有标签时节点通常会有一个唯一的标识符。

2. **边（弧，Edges）：**
   - 边表示连接两个节点的关系。
   - 边可以是 **有向的（Directed）** 或 **无向的（Undirected）**，有向边有方向性（从一个节点指向另一个节点），无向边则没有方向。
   - 边也可以是 **有标签的** 或 **无标签的**，有标签的边可能表示一些额外的信息，如权重等。

### **图的动机与背景：**

考虑我们之前学过的数据结构，图可以被看作是这些数据结构的广义形式。

- **链表（Linked List）：**  
  每个节点都有 1 条入边和 1 条出边。链表可以看作是一个线性结构。
  
- **二叉树/堆（Binary Trees/Heaps）：**  
  每个节点有 1 条入边和 2 条出边。二叉树是特殊的树形结构，而堆是一种满足特定条件的二叉树。

- **B树（B-trees）：**  
  每个节点有 1 条入边和多个出边。B树是自平衡的多路查找树，用于数据库和文件系统中。

这些数据结构都是图的特例，图的广泛性使得它可以表示许多复杂的关系和结构。

### **图的正式定义：**

一个图 $ G $ 由 **顶点集 $ V $** 和 **边集 $ E $** 组成，其中：
- **顶点集 $ V $** 是图中所有节点的集合。
- **边集 $ E $** 是图中所有边的集合，边连接图中的节点。

图的边的数量 $ |E| $ 范围从 0 到 $ |V|^2 - |V| $，即最多可以有 $ |V|^2 - |V| $ 条边（在无向图中，每条边会计数两次，因此实际情况通常为 $ |V|^2/2 $ 条边）。

### **图的例子：**

考虑一个有向图 $ G = (V, E) $，其中：
- 顶点集 $ V = \{A, B, C, D, E, F\} $
- 边集 $ E = \{(A,B), (A,D), (B,C), (C,D), (C,E), (D,E)\} $

这个图的含义是：
- 从节点 A 到节点 B 有一条有向边。
- 从节点 A 到节点 D 有一条有向边。
- 从节点 B 到节点 C 有一条有向边，依此类推。

这个例子中的图是 **有向图**，因为所有的边都有明确的方向，从一个节点指向另一个节点。

![image-20241120181916924](C:\Totoro.trip\blog-demo\source\images\image-20241120181916924.png)

## **有向图与无向图（Directed vs Undirected Graphs）**

#### **有向图（Directed Graph）**
- **定义：** 如果边的顺序（即顶点的排列顺序）重要，那么该图是有向图（也称为**有向图**，简称 **digraph**）。
- **性质：** 在有向图中，边 $ (v_1, v_2) $ 和 $ (v_2, v_1) $ 是不同的，即 $ (v_1, v_2) \neq (v_2, v_1) $。
- **邻接关系：**
  
  - 顶点 $ u $ 和顶点 $ v $ 在有向图 $ G $ 中是邻接的，如果边 $ (u, v) $ 存在。
  - 在有向图中，边 $ (u, v) $ 具有 **起始顶点** $ u $ 和 **终止顶点** $ v $。
  
  **度（Degree）：**
  - **入度（In-degree）：** 顶点 $ v $ 的入度是以 $ v $ 为终点的边的数量。
  - **出度（Out-degree）：** 顶点 $ u $ 的出度是以 $ u $ 为起点的边的数量。

### **无向图（Undirected Graph）**
- **定义：** 如果边的顺序不重要，则该图为无向图。在无向图中，边 $ (v_1, v_2) $ 与 $ (v_2, v_1) $ 是相同的。
  - 即 $ (v_1, v_2) = (v_2, v_1) $。
  
- **邻接关系：**
  - 在无向图 $ G $ 中，两个顶点 $ u $ 和 $ v $ 是邻接的，当且仅当边 $ \{u, v\} $ 存在（无向边不区分顺序）。
  
  **度（Degree）：**
  - **度（Degree）：** 顶点 $ v $ 的度是与该顶点相连的边的数量。
  - 自环（self-loop）算两次，因为它既连接到顶点 $ v $ 的起点，又连接到终点。
  - 度记作 $ \text{deg}(v) $。

### **Handshaking 定理（Handshaking Lemma）**
- **定理：** 对于一个无向图 $ G = (V, E) $，如果该图有 $ |E| = e $ 条边，那么：
  $
  \sum_{v \in V} \text{deg}(v) = 2e
  $
- **解释：**
  - 这意味着图中所有顶点的度数之和等于图中所有边数的两倍。
  - 每条边会同时贡献 +1 给其连接的两个顶点，因此每条边的两个端点的度都会增加 1。
  - 因此，图中的边数 $ e $ 等于顶点度数之和的二分之一。
  - 由于每条边至少连接两个顶点，所以度数和的总和必须是偶数。

### **标记图（Labeled Graph）**

- **定义：** 每条边都可以关联一个权重（成本）。这种图被称为 **加权图**（Weighted Graph）。
  - 在加权图中，每条边都有一个附加的数值，通常表示边的**成本**、**距离**或**时间**等。

![image-20241120183342505](C:\Totoro.trip\blog-demo\source\images\image-20241120183342505.png)

### **路径与循环（Paths and Cycles）**

- **路径（Path）：**
  - 给定一个图 $ G = (V, E) $，路径是一个顶点序列 $ v_1, v_2, \dots, v_k $，满足：
    - 对于每个 $ 1 \leq i < k $，边 $ (v_i, v_{i+1}) $ 存在于图 $ G $ 中，即边 $ (v_i, v_{i+1}) \in E $。
  - **路径长度（Path Length）：** 路径的长度等于路径中边的数量。
  - **路径权重（Path Weight）：** 路径的权重是路径中每条边的权重之和，即每条边的权重总和。
  - **简单路径（Simple Path）：** 如果路径上的所有顶点都不同，则该路径是**简单路径**。

- **循环（Cycle）：**
  - **循环** 是一个特殊的路径，满足：
    - $ k > 1 $ 且 $ v_1 = v_k $（即路径的起始顶点与结束顶点相同）。
  - 如果图中存在循环，则称图包含**环**。

- **无环图（Acyclic Graph）：**
  - 如果图没有循环，则称该图为 **无环图（Acyclic Graph）**。

- **有向无环图（DAG）：**
  - 如果一个有向图没有任何循环，则称它为 **有向无环图（Directed Acyclic Graph, DAG）**。
  - DAG在计算机科学中有许多应用，例如任务调度、数据流图等。

## **图的表示（Graph Representations）**

在分析图的**空间**和**时间**时，我们考虑以下两个因素：
- 顶点的数量 $ |V| $
- 边的数量 $ |E| $

图的表示方法主要有两种：
1. **邻接矩阵表示法（Adjacency Matrix）**
2. **邻接表表示法（Adjacency List）**

### **邻接矩阵（Adjacency Matrix）**

- **定义：** 邻接矩阵 $ M(v, w) $ 是一个 $ |V| \times |V| $ 的二维矩阵，其中：
  - 如果边 $ (v, w) $ 存在于图 $ G $ 中，则 $ M(v, w) = 1 $，否则 $ M(v, w) = 0 $。
  - 对于无向图，邻接矩阵是对称的，即 $ M(v, w) = M(w, v) $。
- **空间复杂度：** 邻接矩阵的空间复杂度为 $ O(|V|^2) $，即矩阵的大小是顶点数的平方。

### **邻接表（Adjacency List）**

- **定义：** 对于图中的每个顶点 $ v $，邻接表 $ L(v) $ 是一个包含所有与 $ v $ 相连的顶点 $ w $ 的列表，表示为 $ (v, w) \in E $。
  - 即每个顶点存储一条与其相关联的边的列表。
- **空间复杂度：** 邻接表的空间复杂度为 $ O(|V| + 2|E|) $，其中 $ |V| $ 是顶点数，$ |E| $ 是边数。

### **空间需求：无向图与有向图的比较**

- **无向图：** 邻接矩阵是对称的，因此它所需的空间是 $ O(|V|^2) $。
- **有向图：** 对于有向图，邻接矩阵不对称，因此它仍然是 $ O(|V|^2) $。
- **邻接表：** 对于无向图，邻接表的大小大约是有向图的两倍，因为每条无向边会被记录两次（一次从 $ v $ 到 $ w $，一次从 $ w $ 到 $ v $）。

### **邻接矩阵与邻接表的空间需求比较**

- **邻接矩阵：** $ O(|V|^2) $

![image-20241120183402473](C:\Totoro.trip\blog-demo\source\images\image-20241120183402473.png)

- **邻接表：** $ O(|V| + |E|) $

![image-20241120183428037](C:\Totoro.trip\blog-demo\source\images\image-20241120183428037.png)

**邻接表是否更节省空间？**

- 这取决于图中的边的数量。
- 邻接矩阵不需要额外的指针空间。
- 当图变得更加稠密（即 $ |E| = \Theta(|V|^2) $）时，邻接矩阵相对更加高效。
- 对于稀疏图来说，使用邻接表表示更加高效。

### **示例：**

假设：
- 每个顶点索引需要 2 字节
- 每个指针需要 4 字节
- 每条边的权重需要 2 字节

- **邻接矩阵的空间需求：** $ 2|V|^2 = 50 $ 字节
- **邻接表的空间需求：**
  
  - $ 4|V| + 6|E| = 44 $ 字节（对于较少的边）
  - $ 4|V| + 6 \times 2|E| = 80 $ 字节（对于较多的边）
  
  ![image-20241120183142920](C:\Totoro.trip\blog-demo\source\images\image-20241120183142920.png)
  
  ![image-20241120183152109](C:\Totoro.trip\blog-demo\source\images\image-20241120183152109.png)

### **总结：**
- 对于**稠密图**，邻接矩阵可能更高效，因为其空间需求为 $ O(|V|^2) $。
- 对于**稀疏图**，邻接表通常更高效，因为其空间需求为 $ O(|V| + |E|) $，并且避免了无用的空间浪费。

## 图的抽象类实现

在图的实现中，我们通常定义一个通用的图抽象类，提供一些基本的操作。以下是一个图的抽象类实现：

```cpp
class Graph {
public:
    // 初始化图，接受一个参数 n，表示图有 n 个顶点
    virtual void Init(int n) = 0; 
    
    // 返回图中顶点的数量
    virtual int n() = 0; 
    
    // 返回图中边的数量
    virtual int e() = 0;

    // 返回顶点 v 的第一个邻居
    virtual int first(int v) = 0;

    // 返回顶点 v 和 w 的下一个邻居
    virtual int next(int v, int w) = 0;
    
    // 设置或返回边 (v1, v2) 的权重
    virtual void setEdge(int v1, int v2, int wgt) = 0;
    virtual int weight(int v1, int v2) = 0;
    
    // 删除边 (v1, v2)
    virtual void delEdge(int v1, int v2) = 0;

    // 判断边 (v1, v2) 是否在图中
    virtual bool isEdge(int v1, int v2) = 0;

    // 获取或设置顶点 v 的标记值
    virtual int getMark(int v) = 0;
    virtual void setMark(int v, int val) = 0;
};
```

### **功能解释**

1. **初始化与查询**
   - `Init(int n)`：初始化图，设定图中有 $n$ 个顶点。
   - `n()`：返回图中顶点的数量。
   - `e()`：返回图中边的数量。

2. **邻接操作**
   - `first(int v)`：返回顶点 $v$ 的第一个邻居（即与 $v$ 相邻的第一个顶点）。
   - `next(int v, int w)`：返回与顶点 $v$ 相邻且大于顶点 $w$ 的下一个邻居。

3. **边操作**
   - `setEdge(int v1, int v2, int wgt)`：设置边 $(v1, v2)$ 的权重为 $wgt$。
   - `weight(int v1, int v2)`：返回边 $(v1, v2)$ 的权重。
   - `delEdge(int v1, int v2)`：删除边 $(v1, v2)$。
   - `isEdge(int v1, int v2)`：判断边 $(v1, v2)$ 是否存在于图中。

4. **标记操作**
   - `getMark(int v)`：获取顶点 $v$ 的标记值。
   - `setMark(int v, int val)`：设置顶点 $v$ 的标记值为 $val$。

### **邻接矩阵的实现**

在邻接矩阵的实现中，`first()` 和 `next()` 函数的具体实现如下：

- **`first()`**：返回顶点 $i$ 的第一个邻接顶点。该函数会从矩阵的第 $i$ 行开始，扫描这一行直到找到一条边。
  
- **`next()`**：返回顶点 $i$ 的邻接顶点 $j$ 后的下一个邻接顶点。该函数从位置 $j+1$ 开始扫描第 $i$ 行，直到找到下一个边。

### **使用 `first()` 和 `next()` 遍历邻居**

通过 `first()` 和 `next()` 函数，可以遍历一个顶点的所有邻居。例如，假设有一个图 $G$，我们想遍历顶点 $v$ 的所有邻居，可以使用如下代码：

```cpp
for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
    // 处理邻居 w
}
```

该循环会遍历从顶点 $v$ 开始的所有邻居，直到没有更多的邻居为止。

### **图的实现：邻接矩阵和邻接表**

在图的实现中，我们通常使用两种基本的数据结构来存储图的边：**邻接矩阵**和**邻接表**。下面我们将详细介绍如何通过这两种方法实现图的基本操作，包括顶点的访问、边的添加、删除、查找等。

### **邻接矩阵实现**

邻接矩阵是一种用二维数组表示图的边的数据结构。在邻接矩阵中，矩阵的元素 $matrix[i][j]$ 存储了从顶点 $i$ 到顶点 $j$ 的边的权重。如果没有边，则该元素通常为 0。

#### **Graphm 类（邻接矩阵实现）**

```cpp
class Graphm: public Graph {
private:
  int numVertex, numEdge;  // 顶点数和边数
  int **matrix;            // 邻接矩阵指针
  int *mark;               // 标记数组指针

public:
  void Init(int n) {   // 初始化图
    int i;
    numVertex = n; 
    numEdge = 0;

    mark = new int[n];  // 初始化标记数组
    for (i = 0; i < numVertex; i++) 
      mark[i] = UNVISITED;

    matrix = (int**) new int*[numVertex];  // 创建邻接矩阵
    for (i = 0; i < numVertex; i++)
      matrix[i] = new int[numVertex];

    for (i = 0; i < numVertex; i++)   // 初始化权重为0
      for (int j = 0; j < numVertex; j++)
        matrix[i][j] = 0;
  }

  // 返回图中顶点的数量
  int n() { return numVertex; }

  // 返回图中边的数量
  int e() { return numEdge; }

  // 返回顶点 v 的第一个邻居
  int first(int v) {
    for (int i = 0; i < numVertex; i++) 
      if (matrix[v][i] != 0) return i;
    return numVertex; // 没有邻居
  }

  // 返回顶点 v 在顶点 w 之后的下一个邻居
  int next(int v, int w) {
    for (int i = w + 1; i < numVertex; i++) 
      if (matrix[v][i] != 0) return i;
    return numVertex;  // 没有下一个邻居
  }

  // 设置边(v1, v2)的权重
  void setEdge(int v1, int v2, int wt) {
    Assert(wt > 0, "非法权重值");
    if (matrix[v1][v2] == 0) numEdge++;
    matrix[v1][v2] = wt;
  }

  // 删除边(v1, v2)
  void delEdge(int v1, int v2) {
    if (matrix[v1][v2] != 0) numEdge--;
    matrix[v1][v2] = 0;
  }

  // 判断边(v1, v2)是否存在
  bool isEdge(int i, int j) {
    return matrix[i][j] != 0;
  }
};
```

#### **邻接矩阵的操作说明**

- **初始化图**：通过 `Init(int n)` 初始化图，创建邻接矩阵并设置所有边的权重为 0。
- **返回顶点数与边数**：通过 `n()` 和 `e()` 返回图中的顶点数和边数。
- **查找邻居**：`first(v)` 返回顶点 $v$ 的第一个邻居，`next(v, w)` 返回顶点 $v$ 在顶点 $w$ 后的下一个邻居。
- **设置和删除边**：通过 `setEdge(v1, v2, wt)` 设置边的权重，通过 `delEdge(v1, v2)` 删除边。
- **检查边是否存在**：通过 `isEdge(v1, v2)` 判断边是否存在。

### **邻接表实现**

邻接表是另一种存储图的方法，每个顶点有一个链表存储与之相邻的顶点及其边的权重。

#### **Edge 类（邻接表边类）**

```cpp
class Edge {
private:
  int vert;  // 边指向的顶点
  int wt;    // 边的权重

public:
  Edge() { vert = -1; wt = -1; }
  Edge(int v, int w) { vert = v; wt = w; }

  int vertex() { return vert; }
  int weight() { return wt; }
};
```

#### **Graphl 类（邻接表实现）**

```cpp
class Graphl: public Graph {
private:
  List<Edge>** vertex;  // 顶点链表头指针
  int numVertex, numEdge;
  int *mark;

public:
  void Init(int n) {
    int i;
    numVertex = n;  
    numEdge = 0;

    mark = new int[n];
    for (i = 0; i < numVertex; i++) 
      mark[i] = UNVISITED;

    // 创建并初始化邻接表
    vertex = (List<Edge>**) new List<Edge>*[numVertex];
    for (i = 0; i < numVertex; i++)
      vertex[i] = new Llist<Edge>();
  }

  // 返回顶点 v 的第一个邻居
  int first(int v) {
    if (vertex[v]->length() == 0)  // 如果没有邻居
      return numVertex;
    vertex[v]->moveToStart();
    Edge it = vertex[v]->getValue();
    return it.vertex();
  }

  // 返回顶点 v 在顶点 w 之后的下一个邻居
  int next(int v, int w) {
    Edge it;
    if (isEdge(v, w)) {
      if ((vertex[v]->currPos() + 1) < vertex[v]->length()) {
        vertex[v]->next();
        it = vertex[v]->getValue();
        return it.vertex();
      }
    }
    return n();  // 没有邻居
  }

  // 判断顶点 v 和 v2 之间是否有边
  bool isEdge(int v1, int v2) {
    for (vertex[v1]->moveToStart(); vertex[v1]->currPos() < vertex[v1]->length(); vertex[v1]->next()) {
      Edge it = vertex[v1]->getValue();
      if (it.vertex() == v2)
        return true;
    }
    return false;
  }
};
```

#### **邻接表的操作说明**

- **初始化图**：通过 `Init(int n)` 初始化图，创建邻接表。
- **返回顶点数与边数**：通过 `n()` 和 `e()` 返回图中的顶点数和边数。
- **查找邻居**：`first(v)` 返回顶点 $v$ 的第一个邻居，`next(v, w)` 返回顶点 $v$ 在顶点 $w$ 后的下一个邻居。
- **检查边是否存在**：通过 `isEdge(v1, v2)` 判断边是否存在。









