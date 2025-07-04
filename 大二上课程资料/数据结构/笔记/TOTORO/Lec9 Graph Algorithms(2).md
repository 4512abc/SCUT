# Lec9 Graph Algorithms(2)

> 图论的世界，探索!!!😎

## **图的遍历及三种常见策略概述**

> 可以看成引言。

### **1. 图遍历的概念**
图的遍历是指按照某种特定顺序访问图中的所有顶点，并遵循以下原则：
- **基于图的拓扑结构**：遍历过程中只能沿着图的边访问顶点。
- **起始点与连通性**：
  - 遍历通常从一个起始顶点开始。
  - 若图不连通，则需从未访问过的顶点继续遍历。
- **防止死循环**：若图中存在环路，算法需要确保不进入死循环。
  - 每个顶点维护一个“标记位”（mark bit），标记该顶点是否已访问。
- **目标**：在保证不重复访问的前提下，尽量遍历图中所有顶点。

---

### **2. 图遍历的基本框架**
**代码示例：遍历一个图**
```cpp
void graphTraverse(Graph* G) {
    int v;
    // 初始化所有顶点为未访问状态
    for (v = 0; v < G->n(); v++) {
        G->setMark(v, UNVISITED);
    }

    // 从未访问过的顶点开始遍历
    for (v = 0; v < G->n(); v++) {
        if (G->getMark(v) == UNVISITED) {
            doTraverse(G, v); // 调用具体的遍历方法
        }
    }
}
```

- **核心逻辑**：
  - 初始化所有顶点为未访问状态。
  - 对每个顶点 $ v $，若未访问过，则调用具体的遍历算法（如 DFS 或 BFS）。

---

### **3. 三种典型的图遍历策略**

#### **(1) 深度优先搜索（DFS）**
- **特点**：尽可能深入访问顶点，直到无法前进时再回溯。
- **过程**：
  1. 从当前顶点开始，标记为已访问。
  2. 递归访问所有未访问的邻接顶点。
  3. 回溯到上一个顶点，继续访问其他未访问的邻接顶点。
---

##### **(2) 广度优先搜索（BFS）**
- **特点**：按照层次逐层访问，从当前顶点的所有邻接顶点开始，再逐步扩展到更远的顶点。
- **过程**：
  1. 使用队列存储待访问的顶点。
  2. 从起始顶点入队，标记为已访问。
  3. 逐个出队，访问其邻接顶点，并将未访问的邻接顶点入队。

---

##### **(3) 拓扑排序**
- **特点**：对有向无环图（DAG）进行排序，使得每条有向边 $ (u, v) $ 满足 $ u $ 在 $ v $ 之前。
- **过程**：
  1. 计算图中所有顶点的入度。
  2. 将入度为 0 的顶点加入队列。
  3. 不断出队，访问顶点，同时减少其邻接顶点的入度。
  4. 若邻接顶点入度变为 0，则加入队列。

---

#### **4. 比较总结**
| **算法**     | **特点**                             | **时间复杂度** | **空间复杂度** | **适用场景**           |
| ------------ | ------------------------------------ | -------------- | -------------- | ---------------------- |
| **DFS**      | 深度优先，适合路径搜索               | $ O(V + E) $ | $ O(V) $     | 连通性检测，环检测     |
| **BFS**      | 广度优先，适合层次遍历和最短路径计算 | $ O(V + E) $ | $ O(V) $     | 最短路径，层次结构     |
| **拓扑排序** | 有向无环图排序，确保依赖关系满足     | $ O(V + E) $ | $ O(V) $     | 任务调度，依赖关系解析 |

- $ V $：顶点数量
- $ E $：边数量

## **图搜索及相关性质**

### **1. 图的性质**
在图中，搜索可以帮助我们发现以下图的性质：
- **生成树（Spanning Trees）**：
  - 从连通图的所有顶点构造的无环子图。
  - 保持连通性，且边数最少（$n-1$ 条边）。
- **连通分量（Connected Components）**：
  - 一个连通分量是图中顶点的一个子集，其中每对顶点都可以通过路径互相到达。
- **双边结构（Bipartite Structure）**：
  - 图的顶点可以分成两个集合 $ U $ 和 $ V $，每条边都连接 $ U $ 和 $ V $ 中的顶点。
  - 图不含奇数环时为双边图。
- **双连通分量（Biconnected Components）**：
  - 去掉任意一个顶点后，仍然保持连通的图的最大子图。

---

### **2. 图搜索的实际应用**
- **网络图的构造**：
  - 例如，Google 搜索的网页图用来分析网页间的超链接关系。
- **垃圾回收（Garbage Collection）**：
  - 在 Java 运行时系统中，基于图搜索的算法检测哪些对象可以被访问，释放不可达的内存碎片。
- **交替路径（Alternating Paths）**：
  - 图匹配问题中，用交替路径优化匹配算法。

## **深度优先搜索（DFS）算法**

#### **1. 深度优先搜索的核心思想**
- DFS 是一种递归的标记算法。
- 起始时，每个顶点都未被标记。
- 递归遍历从一个顶点出发，尽可能沿着一条路径深入，直到无法继续，再回溯探索其他路径。

---

#### **2. 伪代码**
**递归形式的 DFS：**
```text
DFS(i: 顶点)
   标记 i 为已访问
   对于 i 的每个相邻顶点 j：
       如果 j 未被标记，则递归调用 DFS(j)
```

- **说明**：
  - DFS 会标记从起点顶点 $ i $ 可达的所有顶点。
  - 通过递归方式处理未访问的相邻顶点，直至没有新的顶点可访问。

---

#### **3. 实现代码**
以下是带前置与后置处理动作的深度优先搜索实现：
```cpp
void DFS(Graph* G, int v) {
    PreVisit(G, v);            // 前置动作，例如记录当前顶点
    G->setMark(v, VISITED);    // 标记顶点 v

    for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
        if (G->getMark(w) == UNVISITED) {
            DFS(G, w);         // 递归访问未访问的邻接顶点
        }
    }

    PostVisit(G, v);           // 后置动作，例如记录离开顶点
}
```

---

#### **4. 深度优先搜索的应用**

##### **(1) 生成树（Spanning Tree）**
- **定义**：
  - 给定图 $ G(V, E) $，生成树 $ G'(V', E') $ 满足以下条件：
    - $ V' = V $：生成树包含图的所有顶点。
    - $ E' \subseteq E $：生成树的边是图的边的子集。
    - $ G' $ 是连通图，并且不含环。
- **特点**：
  - DFS 的过程中，访问的边可以形成一个生成树。
  - 如果从某顶点 $ u $ 到 $ v $ 存在路径，则生成树保证 $ u $ 和 $ v $ 连通。

![image-20241120152712564](C:\Totoro.trip\blog-demo\source\images\image-20241120152712564.png)

![image-20241120152727303](C:\Totoro.trip\blog-demo\source\images\image-20241120152727303.png)

![image-20241120152742603](C:\Totoro.trip\blog-demo\source\images\image-20241120152742603.png)

![image-20241120152756432](C:\Totoro.trip\blog-demo\source\images\image-20241120152756432.png)

![image-20241120152826444](C:\Totoro.trip\blog-demo\source\images\image-20241120152826444.png)

![image-20241120152834334](C:\Totoro.trip\blog-demo\source\images\image-20241120152834334.png)

![image-20241120152842944](C:\Totoro.trip\blog-demo\source\images\image-20241120152842944.png)

![image-20241120152853769](C:\Totoro.trip\blog-demo\source\images\image-20241120152853769.png)

![image-20241120152911100](C:\Totoro.trip\blog-demo\source\images\image-20241120152911100.png)

![image-20241120152924814](C:\Totoro.trip\blog-demo\source\images\image-20241120152924814.png)

### **深度优先搜索（DFS）的另一用途：连通分量（Connected Components）**

#### **1. 连通分量的定义**
- **连通分量**是无向图中的一个极大连通子图。
  - 如果在某个子图中，任意两个顶点之间都存在路径，则称该子图为连通的。
  - 图中的所有顶点可以划分为多个连通分量，每个顶点只能属于一个连通分量。

---

#### **2. 问题目标**
利用深度优先搜索（DFS），找到无向图中的所有连通分量，并为每个顶点标记其所属分量。

---

#### **3. 算法核心步骤**
1. **初始化：**
   - 创建一个数组 $ M[] $，记录每个顶点的标记（初始为 0，表示未标记）。
   - 初始化标签 $ label = 1 $。

2. **遍历顶点：**
   - 对于每个顶点 $ i $：
     - 如果 $ M[i] = 0 $（即未标记），调用 DFS 标记该连通分量的所有顶点。
     - 增加标签 $ label $ 的值，用于下一次标记新的连通分量。

3. **DFS 递归标记：**
   - 标记当前顶点 $ i $ 的分量 $ M[i] = label $。
   - 遍历顶点 $ i $ 的所有邻居顶点 $ v $：
     - 如果 $ M[v] = 0 $（未标记），递归调用 DFS 对其进行标记。

---

#### **4. 伪代码**
**主函数：**
```cpp
Main {
    for i = 1 to n do 
        M[i] = 0;            // 初始化所有顶点的标记为 0

    label = 1;               // 初始化标签值
    for i = 1 to n do {
        if M[i] == 0 then    // 如果顶点 i 未标记
            DFS(G, M, i, label);  // 以 i 为起点标记连通分量
            label = label + 1;    // 增加标签值
    }
}
```

**深度优先搜索函数：**
```cpp
DFS(G[]: 节点指针数组, M[]: 整数数组, i: 当前顶点, label: 当前标签) {
    M[i] = label;               // 标记顶点 i 所属分量
    v = G[i];                   // 获取顶点 i 的第一个邻接点

    while v != null do {        // 遍历所有邻接点
        if M[v.index] == 0 then // 如果邻接点未标记
            DFS(G, M, v.index, label); // 递归标记
        v = v.next;             // 下一个邻接点
    }
}
```

---

#### **5. 算法复杂度**
1. **时间复杂度**：
   - 每条边和每个顶点最多被访问一次。
   - 总复杂度为 $ O(n + m) $，其中 $ n $ 是顶点数，$ m $ 是边数。

2. **空间复杂度**：
   - 邻接表存储的图需要 $ O(n + m) $ 空间。
   - 标记数组 $ M[] $ 需要 $ O(n) $ 空间。

---

#### **6. 连通分量的输出**
- 运行结束后，标记数组 $ M[] $ 中的值表示每个顶点所属的连通分量。例如：
  - $ M[1] = 1 $ 表示顶点 1 属于第 1 个连通分量。
  - $ M[5] = 2 $ 表示顶点 5 属于第 2 个连通分量。

---

#### **7. 示例**
**输入图：**
- 顶点：$ \{1, 2, 3, 4, 5, 6\} $
- 边：$ \{(1, 2), (2, 3), (4, 5)\} $

**执行过程：**
1. 初始化 $ M[] = [0, 0, 0, 0, 0, 0] $，标签 $ label = 1 $。
2. 遍历顶点：
   - 从顶点 1 开始，标记 $ \{1, 2, 3\} $ 为第 1 个连通分量。
   - 继续遍历未标记的顶点，发现顶点 4，标记 $ \{4, 5\} $ 为第 2 个连通分量。
   - 顶点 6 独立，标记为第 3 个连通分量。

**输出结果：**
- $ M[] = [1, 1, 1, 2, 2, 3] $。

---

## **广度优先搜索（BFS）**

---

### **1. BFS 的定义**
广度优先搜索（BFS）是一种图遍历算法，按照从起始顶点开始的层次顺序（即距离）逐层访问图中的顶点。  
- 使用 **队列** 作为辅助数据结构。  
- 按照 **先进先出（FIFO）** 原则处理每个顶点及其邻接点。  

---

### **2. BFS 的主要特点**
- **按层遍历**：BFS 会优先访问起点的所有直接邻居，然后再访问这些邻居的邻居，以此类推。  
- **标记已访问顶点**：防止重复访问顶点或进入死循环（在有环图中）。  
- **用于连通性检测**：通过 BFS 可以判断图是否连通，以及找到连通分量。  

---

### **3. 算法核心步骤**
1. **初始化：**
   - 创建一个队列 $ Q $ 并清空。
   - 将起点 $ start $ 入队，并标记为已访问。

2. **循环处理队列：**
   - 当队列不为空时，重复以下步骤：
     1. 弹出队首顶点 $ i $。
     2. 遍历顶点 $ i $ 的所有邻接点 $ j $：
        - 如果 $ j $ 未被访问，则将其标记为已访问，并入队。

![image-20241120155953656](C:\Totoro.trip\blog-demo\source\images\image-20241120155953656.png)

![image-20241120160004755](C:\Totoro.trip\blog-demo\source\images\image-20241120160004755.png)

---

### **4. BFS 的伪代码**
```cpp
Initialize Q to be empty;
Enqueue(Q, 1) and mark 1;
while Q is not empty do {
    i := Dequeue(Q);
    for each j adjacent to i do {
        if j is not marked then {
            Enqueue(Q, j) and mark j;
        }
    }
}
```

---

### **5. BFS 的代码实现**

**主函数：**
```cpp
void BFS(Graph* G, int start, Queue<int>* Q) {
    int v, w;
    Q->enqueue(start);        // 初始化队列，将起点加入队列
    G->setMark(start, VISITED); // 标记起点为已访问

    while (Q->length() != 0) { // 当队列非空时，继续处理
        v = Q->dequeue();       // 取出队首元素
        PreVisit(G, v);         // 执行必要的操作（例如打印顶点）

        for (w = G->first(v); w < G->n(); w = G->next(v, w)) { 
            if (G->getMark(w) == UNVISITED) { 
                G->setMark(w, VISITED);  // 标记邻接点
                Q->enqueue(w);           // 将邻接点加入队列
            }
        }
    }
}
```

**辅助函数：**
- **`PreVisit`**：用于处理顶点 $ v $，如记录其值或打印信息。
- **`G->first(v)` 和 `G->next(v, w)`**：分别用于获取顶点 $ v $ 的第一个邻接点和下一个邻接点。
- **`G->setMark(v, VISITED)`**：将顶点 $ v $ 标记为已访问。

---

### **6. BFS 的复杂度分析**
1. **时间复杂度**：  
   - 遍历所有顶点 $ n $ 和所有边 $ m $。  
   - 总复杂度为 $ O(n + m) $。  

2. **空间复杂度**：  
   - 队列存储需要 $ O(n) $ 空间。
   - 标记数组也需要 $ O(n) $ 空间。

## **深度优先搜索（DFS）与广度优先搜索（BFS）的对比**

| **对比维度**          | **DFS**                                  | **BFS**                              |
| --------------------- | ---------------------------------------- | ------------------------------------ |
| **核心数据结构**      | 栈或递归                                 | 队列                                 |
| **遍历顺序**          | 沿路径深度优先，直至无法深入时回溯       | 按距离（层次）逐层扩展               |
| **实现难度**          | 递归实现简单                             | 需显式管理队列                       |
| **内存需求**          | 最坏情况时递归栈深度为 $ O(n) $        | 队列最大空间为 $ O(n) $            |
| **最短路径查找**      | 无法直接找最短路径                       | 无权图中找到起点到其他点的最短路径   |
| **适合稠密图/稀疏图** | 稠密图（较少回溯）                       | 稀疏图（顶点扩展少，队列开销低）     |
| **典型应用**          | 拓扑排序、检测环路、生成树、连通性检测等 | 最短路径查找、连通性检测、层次分析等 |

---

## **拓扑排序（Topological Sort）**

---

### **1. 什么是拓扑排序？**

拓扑排序是一种 **将任务或顶点按依赖关系排列** 的方法，通常用于有向无环图（DAG）。  
- **应用场景**：  
  - 课程安排：某些课程需要先修课程的支持。  
  - 任务调度：某些任务需要在完成其他任务后才能执行。  
- **目标**：  
  找到一种线性顺序，使得每个任务的依赖关系都被满足。  

---

### **2. 问题描述**

给定一个 **有向图** $ G = (V, E) $：  
- 顶点集合 $ V $：表示任务或事件。  
- 边集合 $ E $：表示依赖关系（例如，边 $ (v, w) $ 表示 $ v $ 必须在 $ w $ 之前完成）。  

要求：  
- 找出一种顶点的线性排序，使得对于任意一条边 $ (v, w) $，在排序中 $ v $ 排在 $ w $ 之前。  

**注意**：  

- **只有有向无环图（DAG）可以进行拓扑排序**。  

![image-20241120155857251](C:\Totoro.trip\blog-demo\source\images\image-20241120155857251.png)

- 如果图中有环（循环依赖），则无法完成拓扑排序。

---

### **3. 拓扑排序算法**

**算法步骤**：

1. **初始化入度**：
   - 计算每个顶点的“入度”（in-degree），即有多少边指向该顶点。  
   - 入度为 0 的顶点没有依赖关系，可以立即执行。

2. **选择入度为 0 的顶点**：
   - 从图中找到一个入度为 0 的顶点。如果没有这样的顶点，说明图中存在环，排序失败。

3. **删除顶点**：
   - 删除选定的入度为 0 的顶点及其所有出边，并将该顶点加入输出结果。

4. **重复步骤 2 和 3**：
   - 继续寻找入度为 0 的顶点并删除，直到图为空。

5. **输出排序结果**：
   - 若成功删除所有顶点，输出排序；否则说明图中有环，无法完成排序。



---

### **4. 伪代码实现**

**核心伪代码：**
```plaintext
输入：DAG 图 G = (V, E)
输出：拓扑排序结果或检测循环
1. 初始化入度数组 D[]，遍历所有边计算入度
2. 将所有入度为 0 的顶点加入队列 Q
3. 初始化结果集为空
4. 当队列 Q 不为空时：
   - 从队列中取出顶点 v，加入结果集
   - 遍历 v 的所有邻接顶点：
       - 减少邻接顶点的入度
       - 如果邻接顶点的入度变为 0，将其加入队列 Q
5. 如果排序结果集大小小于顶点数，说明图中存在环路

```

### C++代码实现

```cpp
void topsort(Graph* G, Queue<int>* Q) {
    int InDegree[G->n()];  // 入度数组
    int v, w;

    // Step 1: 初始化入度数组
    for (v = 0; v < G->n(); v++) InDegree[v] = 0;

    // Step 2: 计算每个顶点的入度
    for (v = 0; v < G->n(); v++) 
        for (w = G->first(v); w < G->n(); w = G->next(v, w))
            InDegree[w]++;  // 邻接点的入度加 1

    // Step 3: 将入度为 0 的顶点加入队列
    for (v = 0; v < G->n(); v++) 
        if (InDegree[v] == 0) 
            Q->enqueue(v);

    // Step 4: 处理队列中的顶点
    while (Q->length() != 0) {
        v = Q->dequeue();  // 从队列中取出顶点
        printout(v);       // 输出该顶点

        for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
            InDegree[w]--; // 邻接点入度减 1
            if (InDegree[w] == 0) // 如果入度为 0，加入队列
                Q->enqueue(w);
        }
    }

    // Step 5: 检测是否存在环路
    for (v = 0; v < G->n(); v++) {
        if (InDegree[v] > 0) {
            cout << "图中存在环路，无法完成拓扑排序。\n";
            return;
        }
    }
}

```

### **拓扑排序时间复杂度分析**

---

#### **1. 初始化入度数组：**  
**时间复杂度：**  
- 初始化入度数组（`In-Degree`）需要遍历所有顶点和边来计算每个顶点的入度。
- 对于每个边 $ (u, v) $，都会使顶点 $ v $ 的入度加1，处理完所有边后就完成了入度的计算。

**时间复杂度：**  
- **O(|V| + |E|)**  
  - **O(|V|)**：初始化顶点的入度为0。
  - **O(|E|)**：遍历所有边，更新入度信息。

---

#### **2. 初始化队列（Queue）：**  
**时间复杂度：**  
- 需要遍历所有顶点，将入度为0的顶点放入队列中。  
- 每次检查一个顶点的入度，并决定是否将其加入队列。

**时间复杂度：**  
- **O(|V|)**

---

#### **3. 出队并输出顶点：**  
**时间复杂度：**  

- 对每个顶点，从队列中出队一次并输出。由于每个顶点只会出队一次，因此时间复杂度为 $ O(|V|) $。

**时间复杂度：**  
- **O(|V|)**

---

#### **4. 更新相邻顶点的入度并入队：**  
**时间复杂度：**  
- 每个顶点 $ v $ 会检查它的所有邻接顶点 $ w $，并将这些邻接顶点的入度减少1。
- 如果某个邻接顶点的入度减少到0，就将该顶点加入队列。

**时间复杂度：**  
- 对于每条边 $ (u, v) $，顶点 $ v $ 的入度减少1，最多需要处理 $ O(|E|) $ 次。

**总体时间复杂度：**  

- **O(|E|)**

---

#### **5. 综合时间复杂度**

- **总时间复杂度 = O(|V| + |E|)**  
  - **O(|V|)** 来初始化队列和出队操作。
  - **O(|E|)** 来更新邻接顶点的入度并执行入队操作。

由于顶点和边的处理是线性级别的，因此拓扑排序的总时间复杂度为 **O(|V| + |E|)**，是线性时间复杂度。

### **基于深度优先策略的拓扑排序算法**

---

#### **算法步骤：**

1. **初始化标记：**
   - 初始化图中所有顶点的标记为 **UNVISITED**，即尚未访问。
   - 这一步确保在进行深度优先遍历时，我们能够正确判断哪些顶点尚未被访问过。

2. **遍历所有顶点：**
   - 遍历图中的每个顶点。如果顶点没有被访问过（标记为 **UNVISITED**），就调用深度优先搜索的辅助函数 `tophelp` 来进行遍历。

3. **深度优先遍历 `tophelp`：**
   - 对于每个顶点 **v**，标记其为 **VISITED**，表示已经访问过。
   - 然后递归遍历其所有未访问的邻接顶点（通过 `G->next(v, w)` 获取相邻的顶点）。
   - 当递归回到顶点 **v** 时，即完成了其所有邻接点的访问，打印该顶点。这是拓扑排序的关键操作。

4. **输出结果：**
   - 在递归回溯时输出顶点，打印顺序就是拓扑排序的反向顺序。因为拓扑排序要求每个顶点的输出要在其所有依赖（前驱）顶点之后。

#### **代码实现：**

```cpp
void topsort(Graph* G) { 
    int i;
    // 初始化所有顶点的标记为 UNVISITED
    for (i = 0; i < G->n(); i++) 
        G->setMark(i, UNVISITED);

    // 遍历所有顶点，调用深度优先搜索
    for (i = 0; i < G->n(); i++) 
        if (G->getMark(i) == UNVISITED)
            tophelp(G, i);  // 调用辅助函数进行深度优先遍历
}

void tophelp(Graph* G, int v) { 
    // 访问顶点 v
    G->setMark(v, VISITED);

    // 遍历 v 的所有邻接顶点
    for (int w = G->first(v); w < G->n(); w = G->next(v, w)) 
        if (G->getMark(w) == UNVISITED)
            tophelp(G, w);  // 递归访问

    // 在递归回溯时输出顶点 v
    printout(v);  // 输出顶点 v
}
```

#### **算法解释：**

1. **初始化阶段：**
   - 使用 `G->setMark(i, UNVISITED)` 初始化所有顶点的状态为 **UNVISITED**，确保深度优先搜索可以正常进行。
   
2. **深度优先遍历：**
   - 对每个未访问过的顶点调用 `tophelp` 函数，开始深度优先遍历。
   - 在每次递归中，标记当前顶点为 **VISITED**，然后遍历其所有邻接点。
   
3. **输出拓扑排序：**
   - 在递归的回溯阶段（即所有邻接顶点已经被访问过），我们打印当前顶点 **v**，这是拓扑排序中的一部分。
   - 由于是递归回溯，输出的顺序是拓扑排序的反向顺序。

#### **时间复杂度分析：**

- **时间复杂度：**  
  由于每个顶点和每条边仅被访问一次，时间复杂度是 **O(|V| + |E|)**，其中 **V** 是顶点数，**E** 是边数。
  
- **空间复杂度：**  
  需要存储每个顶点的访问标记，空间复杂度为 **O(|V|)**。

##  **图的遍历对比**

### **深度优先搜索（DFS）**

- **适用图类型**：适用于有向图和无向图。
- **实现方式**：可以使用 **栈** 或 **递归** 来实现深度优先搜索。
- **过程**：DFS 从图的一个起始节点开始，尽可能深入图的每个分支，直到遇到无法继续深入的节点，然后回溯到上一个节点，继续探索未访问的节点。此过程重复直到所有可达的节点都被访问。
- **特点**：使用栈或递归，符合后进先出（LIFO）原则。

### **广度优先搜索（BFS）**

- **适用图类型**：适用于有向图和无向图。
- **实现方式**：可以使用 **队列** 来实现广度优先搜索。
- **过程**：BFS 从图的一个起始节点开始，首先访问该节点的所有邻接节点，然后再访问这些邻接节点的邻接节点，依此类推，直到所有可达的节点都被访问。
- **特点**：使用队列，符合先进先出（FIFO）原则。

### **拓扑排序（Topological Sort）**

- **适用图类型**：仅适用于有向无环图（DAG）。
- **实现方式**：拓扑排序可以通过 **深度优先搜索（DFS）** 或 **基于队列的方法** 来实现。
  - 使用 **DFS**：通过递归访问每个节点并在回溯时输出节点，即可得到反向的拓扑排序。
  - 使用 **队列方法**：通过计算每个节点的入度，初始时将入度为 0 的节点加入队列，逐步输出节点并更新其邻接节点的入度，直到图为空。
- **过程**：拓扑排序是对有向无环图的节点进行排序，使得对于每条边 (u, v)，节点 u 必须排在节点 v 之前。











