# Lec7 Sorting(2)

> 接下来登场的是$O(nlogn)$的算法。😎

## 堆排序

---

### 1. **堆排序的核心概念**

1. **堆的定义：**
   - **最大堆（Max-Heap）：** 每个节点的值都大于或等于其子节点的值。
   - **数组表示：**
     - 根节点：$ A[1] $。
     - 左子节点：$ A[2i] $，右子节点：$ A[2i+1] $。
     - 堆的大小由当前节点数 $ N $ 决定。

2. **堆排序流程：**
   - **构建最大堆：** 将原始数组调整为一个满足堆性质的最大堆。
   - **重复执行删除最大值（DeleteMax）：**
     - 每次删除堆顶元素（最大值）。
     - 将堆顶元素放到数组尾部，堆大小减一。
     - 调整剩余堆为最大堆。

---

### 2. **堆排序的实现步骤**

1. **构建最大堆：**  
   - 从最后一个非叶子节点开始，向上调整每个子堆使其满足最大堆性质。
   - 调整操作的时间复杂度为 $ O(\log N) $，整体建堆时间复杂度为 $ O(N) $。

2. **删除最大值并排序：**
   - 每次将堆顶元素与堆尾元素交换，并从堆中移除堆尾（当前最大值）。
   - 调整剩余堆为最大堆。
   - 重复 $ N $ 次，最终数组按升序排列。

3. **注意事项：**
   - 堆排序是原地排序，不需要额外的存储空间。
   - 堆排序**不稳定**，因为堆调整可能改变相同值元素的相对顺序。

---

### 3. **堆排序的代码实现**

```cpp
#include <iostream>
#include <vector>
using namespace std;

// 下沉操作，调整以索引i为根的子堆为最大堆
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;          // 初始化最大值索引为根节点
    int left = 2 * i + 1;     // 左子节点
    int right = 2 * i + 2;    // 右子节点

    // 比较左右子节点与根节点
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点，交换并递归调整
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序主函数
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 逐步移除堆顶元素
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);    // 将最大值放到数组末尾
        heapify(arr, i, 0);      // 调整剩余堆为最大堆
    }
}

int main() {
    vector<int> arr = {3, 5, 10, 8, 7, 2, 8, 1, 20, 6};
    heapSort(arr);
    for (auto num : arr) cout << num << " ";
    return 0;
}
```

---

### 4. **堆排序的复杂度分析**

| **阶段**           | **时间复杂度**    | **说明**                                           |
| ------------------ | ----------------- | -------------------------------------------------- |
| 构建最大堆         | $ O(N) $        | 每个节点调整 $ O(\log N) $，总节点数 $ N/2 $。 |
| 删除最大值并调整堆 | $ O(N \log N) $ | 删除 $ N $ 次，每次调整堆 $ O(\log N) $。      |
| **总复杂度**       | $ O(N \log N) $ | 构建堆 + 删除最大值两部分相加。                    |

---

### 5. **堆排序性质总结**

- **空间复杂度：** $ O(1) $，原地排序。
- **稳定性：** 不稳定，因堆调整会改变相同值元素的相对顺序。
- **最优、最坏和平均时间复杂度：** $ O(N \log N) $。

---

### 6. **堆排序的优缺点**

**优点：**
- 时间复杂度稳定为 $ O(N \log N) $，对数据分布不敏感。
- 不需要额外存储空间，适合内存有限的场景。

**缺点：**

- 不稳定。
- 常数时间开销较大，实际效率不如快速排序。

---

### 7. **示例操作演示**

**初始数组：**  
$ 3, 5, 10, 8, 7, 2, 8, 1, 20, 6 $

1. **构建最大堆：**  
   $ 20, 8, 10, 6, 7, 2, 8, 1, 5, 3 $

2. **删除最大值并排序：**
   - 移动最大值 $ 20 $ 到数组末尾，调整剩余堆：  
     $ 10, 8, 8, 6, 7, 2, 3, 1, 5, 20 $
   - 重复直到堆为空。

**最终排序结果：**  
$ 1, 2, 3, 5, 6, 7, 8, 8, 10, 20 $

---

### 8. **适用场景**

- 数据量大，内存空间有限。
- 对排序稳定性没有严格要求。

### 图示

![image-20241120111724357](C:\Totoro.trip\blog-demo\source\images\image-20241120111724357.png)

![image-20241120111733632](C:\Totoro.trip\blog-demo\source\images\image-20241120111733632.png)

![image-20241120111739322](C:\Totoro.trip\blog-demo\source\images\image-20241120111739322.png)

## **分治法 (Divide and Conquer)**  

### 核心思想：  
- **分解**：将问题分解为较小的部分。  
- **处理**：独立解决这些部分。  
- **合并**：将这些部分的解决方案合并为整体问题的解。  

### 常用例子：  
1. **归并排序（MergeSort）**  
   - 将数组分成两半，对左右两部分分别递归排序，然后合并两部分。  
   - 合并过程中需要使用辅助数组。  

2. **快速排序（QuickSort）**  
   - 将数组按某个基准值分成“较小”和“较大”两部分，然后分别递归排序。  

## **归并排序（MergeSort）**  

### **步骤：**  
1. **分解**：将数组分为左右两部分。  
2. **处理**：对左右部分分别递归排序。  
3. **合并**：将两个有序的部分合并为一个整体。  

![image-20241120111801819](C:\Totoro.trip\blog-demo\source\images\image-20241120111801819.png)

#### **合并算法伪代码**  
```pseudo
Merge(A[], T[] : integer array, left, right : integer) {
  mid := (right + left) / 2
  i := left, j := mid + 1, target := left
  while i <= mid and j <= right do
    if A[i] < A[j] then
      T[target] := A[i], i := i + 1
    else
      T[target] := A[j], j := j + 1
    target := target + 1
  end while
  // 将剩余的元素复制到目标数组
  while i <= mid do
    T[target] := A[i], i := i + 1, target := target + 1
  while j <= right do
    T[target] := A[j], j := j + 1, target := target + 1
  // 将临时数组 T[] 复制回 A[]
  for k := left to right do
    A[k] := T[k]
}
```

---

### **递归实现伪代码**  
```pseudo
Mergesort(A[], T[], left, right : integer) {
  if left < right then
    mid := (left + right) / 2
    Mergesort(A, T, left, mid)      // 递归排序左半部分
    Mergesort(A, T, mid + 1, right) // 递归排序右半部分
    Merge(A, T, left, right)       // 合并两部分
}
```

### **主函数驱动伪代码**
```pseudo
MainMergesort(A[], n : integer) {
  T[0..n-1] : integer array
  Mergesort(A, T, 0, n-1)
}
```

---

### **时间复杂度分析**  
- 每次递归将数组分为两部分，总共有 $\log N$ 层。  
- 每一层需要线性时间 $O(N)$ 来合并两个部分。  
- 总时间复杂度为：  
  $
  T(N) = 2T(N/2) + O(N) \implies T(N) = O(N \log N)
  $

### **推导**  
1. 递归关系：  
   $
   T(N) = 2T(N/2) + bN
   $
2. 除以 $N$：  
   $
   T(N)/N = T(N/2)/(N/2) + b
   $
3. 递归展开并累加：  
   $
   T(N) = aN + bN \log N
   $

---

### **特点总结**  
1. **时间复杂度**：$O(N \log N)$。  
2. **空间复杂度**：需要辅助数组，空间复杂度为 $O(N)$。  
3. **稳定性**：是稳定排序，保持相同值的相对顺序。  
4. **适用场景**：适合排序大型数据集，尤其在需要稳定性的场合。  

## 归并排序的实现

### 1. 归并排序的伪代码：

#### 合并算法（Merge）
合并两个有序子数组的核心方法是`Merge`函数，它将两个有序部分合并到一个临时数组中。

```cpp
template <typename Comparable>
void merge(vector<Comparable> &a, vector<Comparable> &tmpArray, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    
    // 主循环：合并两个有序数组
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos]) 
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else 
            tmpArray[tmpPos++] = std::move(a[rightPos++]);
    }

    // 复制剩余部分
    while (leftPos <= leftEnd) 
        tmpArray[tmpPos++] = std::move(a[leftPos++]);
    while (rightPos <= rightEnd) 
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    // 将合并后的数据复制回原数组
    for (int i = 0; i < numElements; i++, rightEnd--) 
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}
```

- **解释**：
    - `a` 是待排序的数组，`tmpArray` 是临时数组用来存储合并后的结果。
    - `leftPos` 和 `rightPos` 分别是左右子数组的起始索引。
    - `leftEnd` 是左子数组的结束索引，`rightEnd` 是右子数组的结束索引。
    - 合并时，通过比较左子数组和右子数组的元素，选择较小的元素放入临时数组中，直到一个子数组被完全处理。
    - 最后，将临时数组中的数据复制回原数组。

### 递归归并排序（Mergesort）

```cpp
template <typename Comparable>
void mergesort(vector<Comparable> &a, vector<Comparable> &tmpArray, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        
        // 递归排序左右子数组
        mergesort(a, tmpArray, left, mid);
        mergesort(a, tmpArray, mid + 1, right);
        
        // 合并已排序的子数组
        merge(a, tmpArray, left, mid + 1, right);
    }
}
```

- **解释**：
    - `mergesort` 是归并排序的递归实现，首先递归地分割数组，直到子数组大小为1，然后调用 `merge` 函数将两个有序的子数组合并。
    - `left` 和 `right` 是当前处理子数组的起始和结束索引，`mid` 是中点，用于分割数组。

### 主程序（Driver）

```cpp
template <typename Comparable>
void MainMergesort(vector<Comparable> &a) {
    vector<Comparable> tmpArray(a.size());
    mergesort(a, tmpArray, 0, a.size() - 1);
}
```

- **解释**：
    - `MainMergesort` 是外部接口，用于初始化临时数组并调用 `mergesort`。

### 2. 另一种实现方式（插入排序优化）

对于较小的子数组，插入排序比归并排序更有效。以下代码使用插入排序对小数组进行优化。

```cpp
template <typename E, typename Comp>
void mergesort(E A[], E temp[], int left, int right) {
    if ((right - left) <= THRESHOLD) { // 小数组使用插入排序
        insertionsort<E, Comp>(&A[left], right - left + 1);
        return;
    }
    int mid = (left + right) / 2;
    
    // 递归排序左右子数组
    mergesort<E, Comp>(A, temp, left, mid);
    mergesort<E, Comp>(A, temp, mid + 1, right);

    // 合并已排序的子数组
    for (int i = mid; i >= left; i--) temp[i] = A[i];
    for (int j = 1; j <= right - mid; j++) temp[right - j + 1] = A[j + mid];  // 反向顺序
    for (int i = left, j = right, k = left; k <= right; k++) {
        if (Comp::prior(temp[i], temp[j])) A[k] = temp[i++];
        else A[k] = temp[j--];
    }
}
```

- **解释**：
    - 使用插入排序替代归并排序处理较小的数组（通过 `THRESHOLD` 参数来控制）。
    - 将左右子数组复制到 `temp` 中，并反向复制右子数组部分。
    - 最后，将合并后的数组返回到原数组 `A`。

## 快速排序（Quicksort）算法

快速排序是一种使用分治策略的排序算法，它与归并排序不同，因为它不需要额外的O(N)空间。快速排序通过将数组分为左右两部分，并递归地对这两部分进行排序，最后将它们合并。

### 快速排序的步骤
1. **选择基准元素（pivot）**：
   - 快速排序通过选择一个元素作为“基准”，然后将数组分为两部分：
     - 左子数组的元素都比基准小。
     - 右子数组的元素都比基准大。
   
2. **递归排序**：
   - 对左子数组和右子数组递归地进行排序。
   - 快速排序的效率依赖于基准选择的好坏。理想情况下，基准能够将数组均匀地分成两个子数组，确保每次分治时子数组的大小接近相等。

3. **连接左右子数组**：
   - 快速排序通过递归返回，在排序过程中不需要额外的空间，只在分治过程中通过交换元素的位置来实现。

### 快速排序的过程
1. **初始步骤**：如果数组的元素个数为0或1，则数组已经排序。
2. **选择基准值**：从数组中选择一个元素作为基准元素（pivot）。
3. **划分操作**：将数组分为两个子数组：S1包含所有小于等于基准的元素，S2包含所有大于等于基准的元素。
4. **递归排序**：
   - 对S1和S2分别进行快速排序。
   - 返回递归排序后的结果。

![image-20241120111844219](C:\Totoro.trip\blog-demo\source\images\image-20241120111844219.png)

### 选择基准（Pivot）
选择基准时的目标是：使得左子数组和右子数组的大小接近，如果基准选择不合适，可能导致性能下降。

**常见的基准选择策略**：
1. **选择第一个元素**：对于已经排序或逆序排序的数组效果较差。
2. **选择随机位置的元素**：使用随机数生成器选择基准元素，但可能会有额外的性能开销。
3. **选择中间位置的元素**：选择 `(left + right) / 2` 位置的元素作为基准。
4. **三数中值法（Median-of-Three）**：选择左端、右端和中间元素中的中位数作为基准。

### 划分策略
划分的目的是将数组分成两部分，左边的元素都比基准小，右边的元素都比基准大。常见的划分方法是“双指针法”：

- 使用两个指针i和j，指针i从左边开始，指针j从右边开始。
- **步骤**：
  - 移动指针i，直到找到一个大于基准的元素。
  - 移动指针j，直到找到一个小于基准的元素。
  - 交换这两个元素。
  - 重复上述操作直到i和j交叉。
  - 最后，将基准元素交换到合适的位置。

### 快速排序的实现代码
```cpp
template <typename E, typename Comp>
void quickSort(E A[], int i, int j) {
    if (j <= i) return;  // 数组为空或只有一个元素时返回

    int pivotIndex = findPivot(A, i, j);  // 获取基准元素
    swap(A, pivotIndex, j);  // 将基准元素放到末尾

    // k 是右子数组的起始位置
    int k = partition<E, Comp>(A, i, j - 1, A[j]);
    swap(A, k, j);  // 将基准元素放回其正确的位置

    // 递归对左右子数组进行排序
    quickSort<E, Comp>(A, i, k - 1);
    quickSort<E, Comp>(A, k + 1, j);
}

template <typename E, typename Comp>
int partition(E A[], int l, int r, E& pivot) {
    do {
        // 移动指针直到它们相遇
        while (Comp::prior(A[++l], pivot));
        while ((l < r) && Comp::prior(A[--r], pivot));
        // 交换不符合条件的元素
        swap(A, l, r);
    } while (l < r);  // 当指针相遇时停止
    swap(A, l, r);  // 最后一交换
    return l;  // 返回右子数组的起始位置
}
```

### Example

![image-20241120111918999](C:\Totoro.trip\blog-demo\source\images\image-20241120111918999.png)

![image-20241120111929474](C:\Totoro.trip\blog-demo\source\images\image-20241120111929474.png)

### 快速排序（Quicksort）算法分析

#### 最佳情况（Best Case）
- 在最佳情况下，快速排序总是能够选择最优的基准，并将数组分成几乎相等的两个子数组。
- 递归分割后的时间复杂度是：
  $
  T(N) = 2T(N/2) + O(N)
  $
- 这是与归并排序相同的递归关系，因此在最佳情况下，时间复杂度为 $ T(N) = O(N \log N) $。

#### 最坏情况（Worst Case）
- 在最坏情况下，每次基准都选择得非常差，导致其中一个子数组为空（例如，基准总是选择数组的最大值或最小值）。
- 递归分割后的时间复杂度是：
  $
  T(N) = T(N-1) + O(N)
  $
  $
  T(N) = T(N-2) + O(N-1) + O(N)
  $
  $
  T(N) = T(1) + O(1 + 2 + \dots + (N-1) + N)
  $
  $
  T(N) = O(1) + O(N^2)
  $
- 因此，在最坏情况下，快速排序的时间复杂度为 $ T(N) = O(N^2) $。

#### 平均情况（Average Case）
幸运的是，快速排序的平均时间复杂度为 $ O(N \log N) $，这也是大多数实际应用中的时间复杂度。

### 快速排序的属性

1. **不稳定排序**：
   - 快速排序是一个不稳定的排序算法。由于在排序过程中会发生元素交换，因此可能会改变相等元素之间的相对顺序。

2. **不适合小数组**：
   - 对于小规模数组，快速排序的性能较差。通常可以使用插入排序来处理小数组，以提升效率。

3. **原地排序**：
   - 快速排序是一种“原地排序”算法，它不需要额外的存储空间来存放临时数组。
   - 然而，由于递归调用的存在，它需要 $ O(\log N) $ 的辅助空间来保存递归栈。

4. **平均情况性能**：
   - 快速排序在平均情况下具有 $ O(N \log N) $ 的时间复杂度。尽管最坏情况下时间复杂度为 $ O(N^2) $，但在大多数随机数据上，它表现得非常高效。

5. **“快速排序是最佳的内存排序算法”**：
   - 快速排序的空间占用非常小，具有良好的内存局部性。由于其递归的特性，快速排序在内存层次结构（如CPU缓存）中也表现出色。

6. **比较次数少**：
   - 快速排序平均来说使用的比较次数很少，相较于其他排序算法，快速排序能够更少的进行元素比较，从而提升排序效率。

7. **小内存占用**：
   - 快速排序的“足迹”较小，使用较少的内存空间，因此适合在内存受限的环境中使用。

### 结论
- **快速排序**是一种高效的排序算法，通常具有 $ O(N \log N) $ 的平均时间复杂度。
- **最坏情况**时间复杂度为 $ O(N^2) $，但是通过优化基准选择（例如随机选择或三数中值法），可以有效避免最坏情况的发生。
- 快速排序因其优秀的内存表现和较低的比较次数，在大多数实际应用中是最常用的排序算法之一。