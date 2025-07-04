# Lec7 Sorting

## 排序：计算机科学中的核心问题

### 排序问题的定义

给定一组记录 $ r_1, r_2, \dots, r_n $ 和它们对应的关键值 $ k_1, k_2, \dots, k_n $，通过排序操作，将这些记录按照以下规则排列：

$
k_{s_1} \leq k_{s_2} \leq \dots \leq k_{s_n}
$

#### 注意事项：
1. **关键值是否允许重复**：
   - 可根据应用需求决定是否允许重复关键值。
2. **输出结果**：
   - 排列后的记录满足从小到大的排序顺序（也可以根据需求改为降序）。

---

### 排序分类

#### 1. **比较排序（Comparison-Based Sorting）**

这种排序算法基于比较操作来决定元素之间的顺序。它要求：

1. **输入**：
   - 一个存储在数组 $ A $ 中的记录集合。
   - 每条记录至少包含一个关键字段。
   - 一个**比较函数**，用于确定关键值之间的相对顺序。

2. **输出**：
   - 排序后的数组 $ A $，满足以下条件：
     - 对任意 $ i < j $，如果 $ A[i] $ 的关键值小于 $ A[j] $ 的关键值，则 $ A[i] $ 出现在 $ A[j] $ 前面。

---

#### 2. **内部排序（Internal Sorting）**

- 适用于数据量较小，能够完全存储在内存中的情况。
- 常见算法：
  - 冒泡排序（Bubble Sort）
  - 插入排序（Insertion Sort）
  - 归并排序（Merge Sort）
  - 快速排序（Quick Sort）
  - 堆排序（Heap Sort）

---

#### 3. **外部排序（External Sorting）**

- 当数据量太大以至于不能完全加载到内存时，采用外部排序。
- 通常依赖磁盘存储和分块操作，典型算法是**外部归并排序**。

---

## 排序算法的空间与时间复杂度以及稳定性分析

---

### 空间复杂度（Space Complexity）

1. **排序算法需要多少额外空间？**
   - 排序算法所需的额外空间决定了算法的实现效率和适用场景。

2. **是否需要复制数据？**
   - **需要复制数据**：使用额外的 $ O(n) $ 空间（例如，归并排序需要辅助数组）。
   - **原地排序（In-place Sorting）**：
     - 不需要复制数据。
     - 额外空间复杂度为 $ O(1) $。
     - 例如，快速排序（Quick Sort）、堆排序（Heap Sort）。

3. **临时空间使用：**
   - 某些算法介于两者之间，例如快速排序需要递归栈空间，平均为 $ O(\log n) $。

---

### 时间复杂度（Time Complexity）

1. **算法的运行速度有多快？**
   - 一个排序算法的性能取决于它需要比较和移动元素的次数。

2. **最少需要的比较次数：**
   - 在最理想情况下，每个元素至少需要检查一次，时间复杂度下限为 $ \Omega(n) $。

3. **最坏情况下的比较次数：**
   - 每个元素可能需要与所有其他元素进行比较，时间复杂度为 $ O(n^2) $（例如冒泡排序、选择排序在未优化时的最坏表现）。

4. **关键问题：**
   - 排序算法能多接近 $ O(n) $？
   - 线性时间排序的实现通常需要利用非比较排序算法，例如计数排序（Counting Sort）、基数排序（Radix Sort）。
   
   ![image-20241120095712571](C:\Totoro.trip\blog-demo\source\images\image-20241120095712571.png)

---

### 稳定性（Stability）

1. **什么是排序算法的稳定性？**
   - **稳定排序算法**：不会改变相同关键值记录的相对顺序。
   - 例如，在按姓名排序的电话簿中，如果再次按县排序，仍希望同一县的记录保持原姓名排序。

2. **为什么重要？**
   - 对于数据库等场景，稳定性非常重要，特别是当需要多次排序时。

3. **案例分析：**

   **输入记录：**  
   $ r_1(7), r_2(5), r_3(8), r_4(3), r_5(7) $

   **输出 1（稳定排序）：**  
   $ r_4(3), r_2(5), r_1(7), r_5(7), r_3(8) $  
   - 重复关键值 $ 7 $ 的记录顺序未被改变：$ r_1 $ 在 $ r_5 $ 前。

   **输出 2（不稳定排序）：**  
   $ r_4(3), r_2(5), r_5(7), r_1(7), r_3(8) $  
   - 重复关键值 $ 7 $ 的记录顺序被打乱：$ r_5 $ 在 $ r_1 $ 前。

| **性质**       | **分析**                                                     |
| -------------- | ------------------------------------------------------------ |
| **空间复杂度** | - $ O(n) $：需要额外存储（如归并排序）。 - $ O(1) $：原地排序（如快速排序、堆排序）。 - $ O(\log n) $：临时空间（如快速排序递归栈）。 |
| **时间复杂度** | - 最优：$ \Omega(n) $。- 最差：$ O(n^2) $（比较排序）。 - 非比较排序可实现 $ O(n) $（如计数排序）。 |
| **稳定性**     | - 稳定：保持重复关键值的记录相对顺序（如归并排序）。 - 不稳定：可能改变相对顺序（如快速排序、堆排序）。 |

**选择排序算法时，需综合考虑时间、空间和稳定性三个方面的权衡。**

## 冒泡排序（Bubble Sort）算法分析

---

### 冒泡排序算法简介

**核心思想：**  
通过两两比较相邻元素，将较大的元素“冒泡”到数组的正确位置。每次遍历后，未排序部分的最大元素会移动到它的最终位置。

**算法特点：**  
1. **逐步冒泡：**  
   - 第 $ i $ 次迭代中，将当前未排序部分的第 $ i $ 小元素冒泡到第 $ i $ 个位置。
   - 重复 $ n-1 $ 次，最终排序完成。

2. **实现方式：**  
   - 从数组末尾开始，每次比较 $ A[j] $ 和 $ A[j-1] $，如果 $ A[j] < A[j-1] $，则交换两者。
   - 每次循环结束后，未排序部分的最大元素就会被“冒泡”到正确位置。

---

### 算法实现

**模板代码：**

```cpp
template <typename E, typename Comp>
void bubsort(E A[], int n) {
  for (int i = 0; i < n - 1; i++)                // 总共进行 n-1 次冒泡操作
    for (int j = n - 1; j > i; j--)             // 从数组末尾向前冒泡
      if (Comp::prior(A[j], A[j - 1]))          // 比较相邻两个元素
        swap(A, j, j - 1);                      // 交换元素
}
```

---

### 算法复杂度分析

1. **比较次数：**
   - 第 $ i $ 次冒泡需要比较 $ n - i $ 次。
   - 总比较次数为：
     $
     \sum_{i=1}^{n-1} (n - i) = \frac{n(n - 1)}{2} = O(n^2)
     $
   - **无论是最好、平均还是最坏情况，比较次数都接近 $ O(n^2) $。**

2. **交换次数：**
   - **最好情况（已排序）：** 不发生任何交换，交换次数为 0。
   - **最坏和平均情况：** 平均情况下，交换次数大约为总比较次数的一半，仍为 $ O(n^2) $。

3. **时间复杂度：**
   - 最好情况：$ O(n) $（已排序时，可通过优化减少不必要的比较）。
   - 平均和最坏情况：$ O(n^2) $。

---

### 优化建议

1. **提前终止判断：**  
   如果某次遍历中没有发生交换，则说明数组已经有序，可以提前结束算法。

2. **时间复杂度优化：**
   - **已排序数组：** $ O(n) $。
   - **未排序数组：** 仍为 $ O(n^2) $。



## 选择排序（Selection Sort）算法分析

---

### 选择排序算法简介

**核心思想：**  
每次从未排序部分中选择最小（或最大）的元素，将其放到已排序部分的末尾。  
**具体步骤：**
1. 第 $ i $ 轮遍历中，从未排序部分中找到最小值，将其放置在位置 $ i $。
2. 重复 $ n-1 $ 次，最终完成排序。

**特点：**  
- **交换次数少：** 每轮只需一次交换操作。
- **与冒泡排序的区别：**  
  冒泡排序需要多次交换，而选择排序通过减少交换次数提高效率。

---

### 算法实现

**模板代码：**

```cpp
template <typename E, typename Comp>
void selsort(E A[], int n) {
  for (int i = 0; i < n - 1; i++) {    // 第 i 轮选择
    int lowindex = i;                 // 记录最小值的索引
    for (int j = n - 1; j > i; j--)   // 从后往前查找最小值
      if (Comp::lt(A[j], A[lowindex]))
        lowindex = j;                 // 更新最小值的索引
    swap(A, i, lowindex);             // 交换当前元素与最小值
  }
}
```

---

### 算法复杂度分析

1. **比较次数：**
   - 第 $ i $ 轮需要比较 $ n - i - 1 $ 次。
   - 总比较次数为：
     $
     \sum_{i=0}^{n-2} (n - i - 1) = \frac{n(n - 1)}{2} = O(n^2)
     $
   - **在最佳、平均、最坏情况下，比较次数均为 $ \Theta(n^2) $。**

2. **交换次数：**
   - 每轮选择完成后只需一次交换操作。
   - **最好情况（已排序）：** 交换次数为 0。
   - **最坏和平均情况：** 交换次数为 $ n-1 $ 次，复杂度为 $ \Theta(n) $。

3. **时间复杂度：**
   - 最好、平均、最坏情况均为 $ O(n^2) $。

---

### 选择排序过程示例

**输入数组：**  
$ 5, 3, 8, 6, 2 $

**排序步骤：**

| 迭代轮次 | 查找最小值索引 | 交换操作   | 数组状态          |
| -------- | -------------- | ---------- | ----------------- |
| 第 1 轮  | 最小值索引 4   | 交换 5 ↔ 2 | $ 2, 3, 8, 6, 5 $ |
| 第 2 轮  | 最小值索引 1   | 无需交换   | $ 2, 3, 8, 6, 5 $ |
| 第 3 轮  | 最小值索引 4   | 交换 8 ↔ 5 | $ 2, 3, 5, 6, 8 $ |
| 第 4 轮  | 最小值索引 3   | 无需交换   | $ 2, 3, 5, 6, 8 $ |

![image-20241120103520878](C:\Totoro.trip\blog-demo\source\images\image-20241120103520878.png)

### 选择排序的性质

| **性质**       | **分析**                                                     |
| -------------- | ------------------------------------------------------------ |
| **时间复杂度** | 最好情况：$ O(n^2) $<br>平均情况：$ O(n^2) $<br>最坏情况：$ O(n^2) $。 |
| **空间复杂度** | $ O(1) $（原地排序）。                                     |
| **稳定性**     | **不稳定**（交换可能改变相同元素的相对顺序）。               |
| **交换次数**   | 最好情况：0 次<br>最坏和平均情况：$ n-1 $ 次。             |
| **适用场景**   | 小规模数据排序，或当交换操作代价较大时。                     |

---

### 选择排序的优缺点

**优点：**
1. 简单易实现。
2. 与冒泡排序相比，交换次数更少。

**缺点：**
1. 不稳定，可能打乱相同元素的相对顺序。
2. 时间复杂度为 $ O(n^2) $，在处理大规模数据时效率较低。

---





## 插入排序（Insertion Sort）算法分析

---

### 插入排序算法简介

**核心思想：**  
每次将一个新元素插入到已排序序列中，使得序列依然保持有序。  
假设前 $ k $ 个元素已经排好序，在第 $ k+1 $ 步中，将第 $ k+1 $ 个元素插入到合适的位置。

---

### 算法步骤

1. 从数组的第二个元素开始，将其视为待插入的元素。
2. 遍历已排序部分，将待插入元素向前移动，直到找到合适位置。
3. 重复该过程，直到所有元素都插入完成。

---

### 示例

**输入：**  
$ 4, 7, 12, 5, 19, 16 $

**排序过程：**

1. 初始已排序部分：$ 4, 7, 12 $  
   待插入元素：5  
   插入后：$ 4, 5, 7, 12, 19, 16 $

2. 已排序部分：$ 4, 5, 7, 12, 19 $  
   待插入元素：16  
   插入后：$ 4, 5, 7, 12, 16, 19 $

---

### 算法实现

**模板代码：**

```cpp
template <typename E, typename Comp>
void insertionSort(E A[], int n) {
  for (int i = 1; i < n; i++) {         // 从第二个元素开始插入
    for (int j = i; (j > 0) && Comp::prior(A[j], A[j - 1]); j--) {
      swap(A, j, j - 1);               // 向前移动元素，直至找到插入位置
    }
  }
}
```

---

### 时间复杂度分析

1. **最坏情况：**  
   - 输入数据完全逆序。
   - 第 $ i $ 次插入操作需要 $ i $ 次比较。
   - 总比较次数为：
     $
     \sum_{i=2}^n i = \frac{n(n - 1)}{2} \approx O(n^2)
     $
   - 每次比较几乎都伴随一次交换操作，交换次数为 $ O(n^2) $。

2. **最好情况：**  
   - 输入数据已经有序。
   - 每次比较直接退出，无需交换。
   - 比较次数为 $ n-1 $，时间复杂度为 $ O(n) $。

3. **平均情况：**  
   - 假设每次插入时，约有一半的元素需要比较和移动。
   - 比较次数和交换次数均为 $ \Theta(n^2/4) $，时间复杂度为 $ O(n^2) $。

4. **空间复杂度：**  
   - 插入排序是**原地排序算法**，额外空间复杂度为 $ O(1) $。

---

### 插入排序性质

| **性质**       | **分析**                                                     |
| -------------- | ------------------------------------------------------------ |
| **时间复杂度** | 最好情况：$ O(n) $<br>平均情况：$ O(n^2) $<br>最坏情况：$ O(n^2) $。 |
| **空间复杂度** | $ O(1) $（原地排序）。                                     |
| **稳定性**     | **稳定**，不会改变相同元素的相对顺序。                       |
| **适用场景**   | **适用于几乎有序的数据**，或者数据量较小的场景。             |

---

### 插入排序过程示例

| 迭代次数 | 插入元素 | 已排序部分          | 数组状态                |
| -------- | -------- | ------------------- | ----------------------- |
| 第 1 次  | 7        | $ 4 $               | $ 4, 7, 12, 5, 19, 16 $ |
| 第 2 次  | 12       | $ 4, 7 $            | $ 4, 7, 12, 5, 19, 16 $ |
| 第 3 次  | 5        | $ 4, 7, 12 $        | $ 4, 5, 7, 12, 19, 16 $ |
| 第 4 次  | 19       | $ 4, 5, 7, 12 $     | $ 4, 5, 7, 12, 19, 16 $ |
| 第 5 次  | 16       | $ 4, 5, 7, 12, 19 $ | $ 4, 5, 7, 12, 16, 19 $ |

![image-20241120103538855](C:\Totoro.trip\blog-demo\source\images\image-20241120103538855.png)

---

### 优缺点

**优点：**
1. 简单易实现。
2. 稳定性强。
3. 在几乎有序数据中表现优异，接近 $ O(n) $。

**缺点：**
1. 时间复杂度较高，处理大规模数据效率较低。
2. 逆序数据的最坏情况性能差。

---



## 冒泡排序、选择排序、插入排序的比较

---

### 比较总结表格

| **算法**     | **最优时间复杂度** | **平均时间复杂度** | **最坏时间复杂度** | **交换次数（最优）** | **交换次数（平均）** | **交换次数（最坏）** | **是否稳定** | **是否原地排序** |
| ------------ | ------------------ | ------------------ | ------------------ | -------------------- | -------------------- | -------------------- | ------------ | ---------------- |
| **冒泡排序** | $ O(n^2) $       | $ O(n^2) $       | $ O(n^2) $       | 0                    | $ O(n^2) $         | $ O(n^2) $         | 是           | 是               |
| **选择排序** | $ O(n^2) $       | $ O(n^2) $       | $ O(n^2) $       | $ O(n) $           | $ O(n) $           | $ O(n) $           | 否           | 是               |
| **插入排序** | $ O(n) $         | $ O(n^2) $       | $ O(n^2) $       | 0                    | $ O(n^2) $         | $ O(n^2) $         | 是           | 是               |

---

### 时间复杂度比较

- **冒泡排序：**  
  每次冒泡需要比较 $ n-i $ 次，循环 $ n-1 $ 次，最优情况下输入已排序，仅比较，无交换。  
  **时间复杂度：**  
  - 最优情况：$ O(n^2) $  
  - 平均和最坏情况：$ O(n^2) $。

- **选择排序：**  
  每次选择最小元素需扫描整个未排序部分，共 $ n-1 $ 次，比较次数固定为 $ n^2/2 $。  
  **时间复杂度：**  
  - 最优、平均、最坏情况均为 $ O(n^2) $。

- **插入排序：**  
  每次将一个新元素插入到已排序部分，最优情况仅需比较。  
  **时间复杂度：**  
  - 最优情况：$ O(n) $。  
  - 平均和最坏情况：$ O(n^2) $。

---

### 交换次数比较

- **冒泡排序：**  
  最优情况（已排序）：0 次交换；  
  最坏情况：约 $ O(n^2) $ 次交换。

- **选择排序：**  
  每次只需 1 次交换，总交换次数固定为 $ n-1 $。

- **插入排序：**  
  最优情况（已排序）：0 次交换；  
  最坏情况：约 $ O(n^2) $ 次交换。

---

### 稳定性比较

1. **冒泡排序：** 稳定，每次交换仅发生在相邻元素之间，且相等元素不会改变顺序。
2. **选择排序：** 不稳定。例如：$ 3, 9, 3, 2, 5 $，在选择过程中会破坏相同元素的相对顺序。
3. **插入排序：** 稳定，元素插入过程中不会破坏相等元素的顺序。

---

### 算法性质分析

1. **共同点：**
   - 三种算法均为**原地排序算法**，空间复杂度为 $ O(1) $。
   - 都是基于**比较**和**交换**的排序方法。
   - 平均情况下，时间复杂度均为 $ O(n^2) $。

2. **局限性：**
   - 三种算法都只对相邻元素进行比较和交换，适用于小规模数据，但对大规模数据性能较差。
   - **冒泡排序**和**插入排序**在输入接近有序时表现较好。

3. **交换次数与反序对：**  
   - 反序对定义为 $ i < j $ 且 $ A[i] > A[j] $。  
   - 平均情况下，一个数组的反序对数为 $ \frac{n(n-1)}{4} $。  
   - 排序时需要消除所有反序对，导致 $ O(n^2) $ 时间复杂度。

---

### 适用场景

| **算法**     | **适用场景**                                                 |
| ------------ | ------------------------------------------------------------ |
| **冒泡排序** | 数据量较小或输入数据近乎有序时；学习排序算法原理的入门选择。 |
| **选择排序** | 数据量较小、对稳定性要求不高时；交换次数少的场景。           |
| **插入排序** | 输入数据接近有序时表现最佳；适用于小型数据集或实时排序场景。 |

---



## Shell排序

---

### 1. **算法简介**

Shell排序（**缩小增量排序**）是一种基于插入排序改进的排序算法，核心思想是通过比较和交换**非相邻元素**，逐步将序列调整为“**基本有序**”，最终利用插入排序完成排序工作。  
Shell排序的特点：
- **增量序列（Increment Sequence）：** 定义步长 $ h_1, h_2, \ldots, h_t $，逐渐减小。
- 每一轮按照当前步长 $ h_k $，将数组分成若干个子序列，分别进行插入排序。
- **关键性质：** 如果一个序列是 $ h_k $-有序（$ h_k $-sorted），那么它保持 $ h_{k-1} $-有序的特性。
- **时间复杂度：** 优于 $ O(n^2) $，取决于步长序列的选择。

---

### 2. **算法流程**

1. **初始步长选择：** 通常选择 $ h = \lfloor n/2 \rfloor $，逐步缩小 $ h $ 为 $ h = \lfloor h/2 \rfloor $。
2. **子序列划分：** 根据当前步长 $ h_k $，将数组分为多个间隔为 $ h_k $ 的子序列。
3. **对子序列排序：** 每个子序列使用插入排序。
4. **步长递减：** 重复上述过程，直到步长减小到 1。

---

### 3. **核心代码（C++实现）**

**版本 1：标准 Shell排序**

```cpp
template <typename Comparable>
void shellsort(std::vector<Comparable>& a) {
    for (int gap = a.size() / 2; gap > 0; gap /= 2) { // 步长逐渐缩小
        for (int i = gap; i < a.size(); ++i) {       // 遍历当前步长子序列
            Comparable tmp = std::move(a[i]);
            int j = i;
            for (; j >= gap && tmp < a[j - gap]; j -= gap) { // 插入排序
                a[j] = std::move(a[j - gap]);
            }
            a[j] = std::move(tmp);
        }
    }
}
```

**版本 2：带插入排序函数的 Shell排序**

```cpp
// 插入排序（支持指定步长）
template <typename E, typename Comp>
void inssort2(E A[], int n, int incr) {
    for (int i = incr; i < n; i += incr) {
        for (int j = i; j >= incr && Comp::prior(A[j], A[j - incr]); j -= incr) {
            std::swap(A[j], A[j - incr]);
        }
    }
}

// Shell排序
template <typename E, typename Comp>
void shellsort(E A[], int n) {
    for (int i = n / 2; i > 2; i /= 2) {   // 减小步长
        for (int j = 0; j < i; j++) {      // 遍历每个子序列
            inssort2<E, Comp>(&A[j], n - j, i);
        }
    }
    inssort2<E, Comp>(A, n, 1);            // 最后一轮插入排序
}
```

---

### 4. **增量序列的选择**

增量序列的选择直接影响 Shell排序的性能：  
- **Shell's 增量：** $ h_k = \lfloor n/2^k \rfloor $。最常用，但性能不是最佳。
- **Hibbard 增量：** $ h_k = 2^k - 1 $。改善性能，但最坏情况仍为 $ O(n^2) $。
- **Sedgewick 增量：** 一组混合序列，如 $ 1, 5, 19, 41, 109, \ldots $，可达到 $ O(n^{4/3}) $。
- **Knuth 增量：** $ h_k = 3^k - 1 $。常用的高效序列，性能较好。

---

### 5. **时间复杂度分析**

| **步长序列**   | **最坏时间复杂度** | **说明**                                           |
| -------------- | ------------------ | -------------------------------------------------- |
| Shell's 增量   | $ O(n^2) $       | 使用 $ h_k = \lfloor n/2^k \rfloor $，性能较差。 |
| Hibbard 增量   | $ O(n^{3/2}) $   | 改善了比较次数，但依赖增量序列的性质。             |
| Knuth 增量     | $ O(n^{5/3}) $   | 实现较为复杂，性能更优。                           |
| Sedgewick 增量 | $ O(n^{4/3}) $   | 理论上性能较好，适合大规模数据。                   |

---

### 6. **算法特点**

- **优点：**
  - 简单易实现。
  - 空间复杂度低，为 $ O(1) $。
  - 对大规模数据性能优于直接插入排序。

- **缺点：**
  - 性能受增量序列影响较大。
  - 稳定性较差（非相邻元素交换会破坏顺序）。

---

### 7. **适用场景**

- 数据量较大但不希望使用复杂排序（如快速排序、归并排序）时。
- 需要原地排序，且对稳定性要求不高的场景。  
例如：中型数据集的排序、对性能要求适中的程序设计。

### 举例

![image-20241120103634131](C:\Totoro.trip\blog-demo\source\images\image-20241120103634131.png)













