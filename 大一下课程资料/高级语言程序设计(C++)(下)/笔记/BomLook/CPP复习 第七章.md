# CPP复习 第七章

> This chapter introduces the topic of data structures—*collections* of related data items.
>
> We discuss arrays which are *fixed-size* collections consisting of data items of the *same* type, and vectors which are collections (also of data items of the *same* type) that can grow and shrink *dynamically* at execution time. 
>
> Both array and vector are C++ standard library class templates. 
>
> After discussing how arrays are declared, created and initialized, we present examples that demonstrate several common array manipulations.
>
> 本章介绍数据结构的主题——相关数据项的集合。
> 我们讨论的数组是由相同类型的数据项组成的固定大小的集合，而向量是可以在执行时动态增长和收缩的集合(也包含相同类型的数据项)。
> 数组和向量都是c++标准库类模板。
> 在讨论了如何声明、创建和初始化数组之后，我们将提供一些示例来演示几种常见的数组操作。



> An array is a *contiguous* group of memory locations that all have the same type.
>
> To refer to a particular location or element in the array, specify the name of the array and the position number of the particular element.
>
> Figure 7.1 shows an integer array called c.
>
> **int c[12]** declares 12 elements.
>
> The position number is more formally called a subscript or index (this number specifies the number of elements from the beginning of the array).
>
> The first element in every array has subscript 0 (zero) and is sometimes called the zeroth element.
>
> The highest subscript in array c is 11, which is 1 less than the number of elements in the array (12).
>
> A subscript must be an integer or integer expression (using any integral type).
>
> 数组是一组具有相同类型的连续内存位置。
> 要引用数组中的特定位置或元素，请指定数组的名称和特定元素的位置号。
> 图7.1显示了一个名为c的整数数组。
> Int c[12]声明了12个元素。
> 位置号更正式地称为下标或索引(这个数字指定从数组开始的元素数量)。
> 每个数组中的第一个元素下标为0(0)，有时称为第零元素。
> 数组c中最大的下标是11，比数组中的元素数(12)少1。
> 下标必须是整数或整数表达式(使用任何整数类型)。



> 在C++中，数组（array）是一种非常重要且常用的数据结构。下面是关于C++数组的一些详细介绍和示例。
>
> ### C++中的数组
>
> #### 声明和初始化
>
> 1. **声明数组**:
>
> ```cpp
> int arr[5];  // 声明一个包含5个整数的数组，未初始化
> ```
>
> 2. **初始化数组**:
>
> ```cpp
> int arr[5] = {1, 2, 3, 4, 5};  // 声明并初始化一个包含5个整数的数组
> ```
>
> 3. **部分初始化**:
>
> ```cpp
> int arr[5] = {1, 2};  // 只有前两个元素被初始化为1和2，其余元素默认为0
> ```
>
> 4. **自动推断大小**:
>
> ```cpp
> int arr[] = {1, 2, 3, 4, 5};  // 编译器会根据初始化列表自动推断数组大小
> ```
>
> #### 访问和修改数组元素
>
> 数组元素可以通过索引进行访问和修改，索引从0开始。
>
> ```cpp
> #include <iostream>
> 
> int main() {
>     int arr[5] = {1, 2, 3, 4, 5};
> 
>     // 访问元素
>     std::cout << "Element at index 0: " << arr[0] << std::endl;
> 
>     // 修改元素
>     arr[0] = 10;
>     std::cout << "Modified element at index 0: " << arr[0] << std::endl;
> 
>     return 0;
> }
> ```
>
> #### 遍历数组
>
> 可以使用循环遍历数组中的元素。
>
> ```cpp
> #include <iostream>
> 
> int main() {
>     int arr[5] = {1, 2, 3, 4, 5};
> 
>     // 使用for循环遍历数组
>     for (int i = 0; i < 5; i++) {
>         std::cout << arr[i] << " ";
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> #### 多维数组
>
> C++也支持多维数组（例如二维数组），用于表示矩阵或表格。
>
> ```cpp
> #include <iostream>
> 
> int main() {
>     // 声明并初始化一个3x3的二维数组
>     int matrix[3][3] = {
>         {1, 2, 3},
>         {4, 5, 6},
>         {7, 8, 9}
>     };
> 
>     // 访问二维数组的元素
>     std::cout << "Element at [0][0]: " << matrix[0][0] << std::endl;
> 
>     // 遍历二维数组
>     for (int i = 0; i < 3; i++) {
>         for (int j = 0; j < 3; j++) {
>             std::cout << matrix[i][j] << " ";
>         }
>         std::cout << std::endl;
>     }
> 
>     return 0;
> }
> ```
>
> #### 动态数组
>
> C++中的数组大小固定，但可以使用指针和动态内存分配（`new`和`delete`）创建动态数组。
>
> ```cpp
> #include <iostream>
> 
> int main() {
>     int size;
>     std::cout << "Enter the size of the array: ";
>     std::cin >> size;
> 
>     // 动态分配数组
>     int* arr = new int[size];
> 
>     // 初始化数组元素
>     for (int i = 0; i < size; i++) {
>         arr[i] = i + 1;
>     }
> 
>     // 打印数组元素
>     for (int i = 0; i < size; i++) {
>         std::cout << arr[i] << " ";
>     }
>     std::cout << std::endl;
> 
>     // 释放动态分配的内存
>     delete[] arr;
> 
>     return 0;
> }
> ```
>
> ### 标准库中的数组
>
> C++标准库还提供了一些更高级的数组数据结构，如`std::array`和`std::vector`，推荐使用这些标准库提供的容器而不是原始数组。
>
> #### `std::array`
>
> `std::array`是一个封装的固定大小的数组，定义在`<array>`头文件中。
>
> 声明：array<类型，大小> array对象名
>
> ```cpp
> #include <iostream>
> #include <array>
> 
> int main() {
>     std::array<int, 5> arr = {1, 2, 3, 4, 5};
> 
>     // 访问元素
>     std::cout << "Element at index 0: " << arr[0] << std::endl;
> 
>     // 遍历数组
>     for (int i = 0; i < arr.size(); i++) {
>         std::cout << arr[i] << " ";
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> #### `std::vector`
>
> `std::vector`是一个动态数组，定义在`<vector>`头文件中。
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> int main() {
>     std::vector<int> vec = {1, 2, 3, 4, 5};
> 
>     // 访问元素
>     std::cout << "Element at index 0: " << vec[0] << std::endl;
> 
>     // 添加元素
>     vec.push_back(6);
> 
>     // 遍历数组
>     for (int i = 0; i < vec.size(); i++) {
>         std::cout << vec[i] << " ";
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> 总之，C++中数组的使用既有基本的内置数组，也有标准库提供的更高级的数组容器，选择适合的数组类型有助于编写更高效和可维护的代码。



size_t是一种无符号的整型类型，包含在<cstddef>中，它被其他各种头文件包括

常量在被声明时，注意需要被初始化：

```cpp
const int x;
x=7;	//这是一个编译错误
```



> `array` 是 C++ 标准库中的一个模板类，封装了固定大小的数组。它提供了更方便和安全的接口来操作数组，并且与传统的 C 风格数组相比，具有更好的类型安全和功能。`std::array` 定义在 `<array>` 头文件中。`array`不提供边界检查
>
> ### `std::array` 的特点
>
> 1. **固定大小**: `std::array` 的大小在编译时确定，不可改变。
> 2. **类型安全**: `std::array` 使用模板，确保数组中所有元素类型相同。
> 3. **标准接口**: 提供了一组标准化的接口，类似于 STL 容器，如 `begin()`, `end()`, `size()`, `at()` 等。
> 4. **性能**: `std::array` 的性能与 C 风格数组相当，但提供了更多的功能。
>
> ### 声明和初始化
>
> 使用 `std::array` 需要包含头文件 `<array>`，并指定元素类型和数组大小。
>
> ```cpp
> #include <array>
> #include <iostream>
> 
> int main() {
>     // 声明一个包含5个整数的数组，并初始化
>     std::array<int, 5> arr = {1, 2, 3, 4, 5};	//列表初始化器进行初始化
> 
>     /*
>     也可以这样初始化，注意可以在读代码时更加清晰，理解用途
>     const int size=5;
>     std::array<int,size> arr={1,2,3,4,5}
>     */
> 
> 
>     // 输出数组元素
>     for (int i = 0; i < arr.size(); ++i) {
>         std::cout << arr[i] << " ";
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> ### 访问和修改元素
>
> 可以使用索引、`at()` 方法、迭代器等方式访问和修改数组元素。
>
> ```cpp
> #include <array>
> #include <iostream>
> 
> int main() {
>     std::array<int, 5> arr = {1, 2, 3, 4, 5};
> 
>     // 使用索引访问元素
>     std::cout << "Element at index 0: " << arr[0] << std::endl;
> 
>     // 使用 at() 方法访问元素，at() 会进行边界检查
>     std::cout << "Element at index 1: " << arr.at(1) << std::endl;
> 
>     // 修改元素
>     arr[0] = 10;
>     std::cout << "Modified element at index 0: " << arr[0] << std::endl;
> 
>     return 0;
> }
> ```
>
> ### 遍历数组
>
> 可以使用范围 `for` 循环或标准迭代器遍历数组。
>
> ```cpp
> #include <array>
> #include <iostream>
> 
> int main() {
>     std::array<int, 5> arr = {1, 2, 3, 4, 5};
> 
>     // 使用范围 for 循环遍历数组
>     for (const auto& element : arr) {
>         std::cout << element << " ";
>     }
>     std::cout << std::endl;
> 
>     // 使用迭代器遍历数组
>     for (auto it = arr.begin(); it != arr.end(); ++it) {
>         std::cout << *it << " ";
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> ### 常用方法
>
> - `size()`: 返回数组的大小。
> - `at(index)`: 访问指定索引的元素，带边界检查。
> - `front()`: 返回第一个元素。
> - `back()`: 返回最后一个元素。
> - `begin()`: 返回指向数组起始位置的迭代器。
> - `end()`: 返回指向数组末尾的迭代器。
> - `data()`: 返回指向数组数据的指针。
>
> ```cpp
> #include <array>
> #include <iostream>
> 
> int main() {
>     std::array<int, 5> arr = {1, 2, 3, 4, 5};
> 
>     std::cout << "Size of array: " << arr.size() << std::endl;
>     std::cout << "First element: " << arr.front() << std::endl;
>     std::cout << "Last element: " << arr.back() << std::endl;
> 
>     // 获取原始数组指针
>     int* ptr = arr.data();
>     std::cout << "First element using data(): " << *ptr << std::endl;
> 
>     return 0;
> }
> ```
>
> ### 与传统数组的区别
>
> - **类型安全**: `std::array` 是一个模板类，确保所有元素类型相同。
> - **边界检查**: `std::array` 的 `at()` 方法提供了边界检查，防止越界访问。
> - **标准接口**: `std::array` 提供了 STL 容器的标准接口，使其与其他标准容器更一致。
> - **固定大小**: `std::array` 的大小在编译时确定，不支持动态调整。
>
> ### 结论
>
> `std::array` 提供了一种更现代和安全的方式来使用固定大小的数组。它结合了 STL 容器的接口优势和 C 风格数组的性能，是 C++ 编程中处理固定大小数组的推荐选择。





> `default_random_engine` 是 C++11 标准库中定义的一个随机数生成器（RNG），位于 `<random>` 头文件中。它是标准库提供的多种随机数生成器之一，使用起来非常方便，适合于大多数一般用途的随机数生成需求。
>
> ### 主要特性
>
> 1. **易用性**: `default_random_engine` 是一种通用的随机数生成器，提供了良好的默认行为，适合大多数应用。
> 2. **可移植性**: 使用标准库提供的随机数生成器可以确保代码在不同平台上的一致性和可移植性。
> 3. **配置性**: 可以与其他随机数分布（如均匀分布、正态分布等）结合使用，生成不同类型的随机数。
>
> ### 使用方法
>
> 1. **包含头文件**: 需要包含 `<random>` 头文件。
> 2. **创建随机数生成器**: 使用 `default_random_engine` 创建一个随机数生成器对象。
> 3. **创建分布对象**: 使用不同的分布类型（如 `uniform_int_distribution` 或 `uniform_real_distribution`）来生成不同类型的随机数。
> 4. **生成随机数**: 使用生成器和分布对象生成随机数。
>
> ### 示例代码
>
> 以下是如何使用 `default_random_engine` 生成随机整数和浮点数的示例。
>
> ```cpp
> #include <iostream>
> #include <random>
> 
> int main() {
>     // 创建随机数生成器
>     std::default_random_engine generator;
> 
>     // 创建均匀分布对象，用于生成范围在1到100之间的整数
>     std::uniform_int_distribution<int> distribution_int(1, 100);
> 
>     // 生成并打印随机整数
>     int random_int = distribution_int(generator);
>     std::cout << "Random integer: " << random_int << std::endl;
> 
>     // 创建均匀分布对象，用于生成范围在0.0到1.0之间的浮点数
>     std::uniform_real_distribution<double> distribution_real(0.0, 1.0);
> 
>     // 生成并打印随机浮点数
>     double random_double = distribution_real(generator);
>     std::cout << "Random double: " << random_double << std::endl;
> 
>     return 0;
> }
> ```
>
> ### 常见用途
>
> 1. **随机抽样**: 从一个数据集合中随机抽取元素。
> 2. **模拟和建模**: 在蒙特卡罗模拟等应用中生成随机样本。
> 3. **游戏开发**: 生成游戏中的随机事件或随机地图。
> 4. **测试和验证**: 生成随机测试数据，进行软件测试和验证。
>
> ### 其他随机数生成器
>
> 虽然 `default_random_engine` 适合大多数一般用途，但 C++ 标准库还提供了其他几种随机数生成器，用于不同的需求：
>
> 1. **`std::mt19937`**: 梅森旋转算法，提供了高质量的随机数，适合高性能需求。
> 2. **`std::ranlux24_base`** 和 **`std::ranlux48_base`**: 提供更高质量随机数，但速度较慢。
> 3. **`std::minstd_rand0`** 和 **`std::minstd_rand`**: 线性同余生成器，适合快速生成随机数，但质量相对较低。
>
> 选择哪种随机数生成器取决于具体的应用需求，`default_random_engine` 提供了一个很好的默认选择，可以满足大多数普通需求。



> A program initializes static local arrays when their declarations are first encountered.
>
> If a static array is not initialized explicitly by you, each element of that array is initialized to *zero* by the compiler when the array is created.
>
> 程序在第一次遇到静态局部数组声明时初始化它们。
> 如果静态数组没有由您显式初始化，则该数组的每个元素在创建数组时由编译器初始化为零。

可以将static用于局部array的声明，这样就不会每次函数调用时被初始化，函数结束时被销毁，可以提高性能。

否则就会自动创建，自动销毁，每次的修改没有改变。



> 在 C++11 中，`auto` 关键字和范围 `for` 循环（range-based for loop）为遍历数组提供了更加简洁和直观的方法。通过 `auto`，编译器可以自动推导变量的类型，这使得代码更加简洁，特别是在处理复杂类型时。此外，使用引用（reference）可以避免不必要的拷贝，提高性能。
>
> ### 基本用法
>
> #### 范围 `for` 循环
>
> 范围 `for` 循环可以简化数组和其他容器的遍历过程。
>
> **语法**:
>
> ```cpp
> for (auto element : container) {
>  // 处理 element
> }
> ```
>
> #### 使用 `auto` 和 引用
>
> 为了避免拷贝，通常可以使用引用遍历数组元素。
>
> **语法**:
>
> ```cpp
> for (auto& element : container) {
>  // 处理 element，通过引用修改原始数组中的值
> }
> ```
>
> ### 示例代码
>
> 以下是使用 `auto` 和范围 `for` 循环遍历数组的示例代码：
>
> ```cpp
> #include <iostream>
> #include <array>
> 
> int main() {
>  // 使用 std::array 声明并初始化一个包含5个整数的数组
>  std::array<int, 5> arr = {1, 2, 3, 4, 5};
> 
>  // 使用范围 for 循环和 auto 关键字遍历数组元素
>  for (auto element : arr) {
>      std::cout << element << " ";  // 输出每个元素的值
>  }
>  std::cout << std::endl;
> 
>  // 使用范围 for 循环和 auto& 关键字遍历数组元素，通过引用修改元素
>  for (auto& element : arr) {
>      element *= 2;  // 将每个元素的值乘以2
>  }
> 
>  // 再次遍历并输出修改后的数组
>  for (auto element : arr) {
>      std::cout << element << " ";  // 输出每个元素的值
>  }
>  std::cout << std::endl;
> 
>  return 0;
> }
> ```
>
> ### 输出结果
>
> ```
> 1 2 3 4 5 
> 2 4 6 8 10 
> ```
>
> ### 解释
>
> 1. **首次遍历**: 使用 `auto` 自动推导元素类型，输出每个元素的值。
> 2. **通过引用修改元素**: 使用 `auto&` 遍历数组，直接修改原数组中的元素。
> 3. **再次遍历**: 验证数组元素已被修改。
>
> ### 优点
>
> - **简洁**: 避免了显式声明变量类型，使代码更简洁。
> - **安全**: 使用引用可以避免不必要的拷贝，提高性能，特别是对于复杂对象。
> - **直观**: 范围 `for` 循环提供了更直观的遍历方式。
>
> ### 注意事项
>
> - 如果只需要读取数组元素而不修改，可以使用 `const auto&` 遍历，确保元素不被修改。
>
>   ```cpp
>   for (const auto& element : arr) {
>       std::cout << element << " ";  // 输出每个元素的值
>   }
>   ```
>
> - `auto` 和 `auto&` 的使用需要在编译器支持 C++11 或更高版本时才能使用。
>
> 通过结合 `auto` 和范围 `for` 循环，C++11 提供了一种简洁、高效的方式来遍历数组和其他容器，使代码更具可读性和可维护性。



> **Using an Element’s Subscript**
>
> The range-based for statement can be used in place of the counter-controlled for statement whenever code looping through an array does not require access to the element’s subscript. 
>
> However, if a program must use subscripts for some reason other than simply to loop through an array (e.g., to print a subscript number next to each array element value, as in the examples early in this chapter), you should use the counter-controlled for statement.
>
> 使用元素的下标
> 只要循环遍历数组的代码不需要访问元素的下标，就可以使用基于范围的for语句来代替反控制的for语句。
> 然而，如果程序不是为了循环数组而必须使用下标(例如，在本章前面的例子中，为了在每个数组元素值旁边打印一个下标数字)，则应该使用计数器控制的for语句。



> 在 C++ 标准库中，`sort` 和 `binary_search` 是两个常用的算法，定义在 `<algorithm>` 头文件中。`sort` 用于对容器中的元素进行排序，而 `binary_search` 用于在已排序的容器中进行二分查找。下面是这两个算法的详细介绍和示例。
>
> ### `sort` 算法
>
> `sort` 算法用于对范围内的元素进行排序。它的时间复杂度平均为 \(O(n \log n)\)，其中 \(n\) 是元素的数量。
>
> #### 基本用法
>
> ```cpp
> #include <algorithm>
> #include <vector>
> #include <iostream>
> 
> int main() {
>  std::vector<int> vec = {5, 2, 9, 1, 5, 6};
> 
>  // 使用默认的升序排序
>  std::sort(vec.begin(), vec.end());
> 
>  // 输出排序后的结果
>  for (const auto& elem : vec) {
>      std::cout << elem << " ";
>  }
>  std::cout << std::endl;
> 
>  return 0;
> }
> ```
>
> ### 自定义比较函数
>
> 可以传递一个自定义的比较函数来实现不同的排序规则，例如降序排序。
>
> ```cpp
> #include <algorithm>
> #include <vector>
> #include <iostream>
> 
> bool compare(int a, int b) {
>  return a > b;  // 实现降序排序
> }
> 
> int main() {
>  std::vector<int> vec = {5, 2, 9, 1, 5, 6};
> 
>  // 使用自定义的比较函数进行降序排序
>  std::sort(vec.begin(), vec.end(), compare);
> 
>  // 输出排序后的结果
>  for (const auto& elem : vec) {
>      std::cout << elem << " ";
>  }
>  std::cout << std::endl;
> 
>  return 0;
> }
> ```
>
> ### `binary_search` 算法
>
> `binary_search` 算法用于在已排序的范围内查找特定的值。它的时间复杂度为 \(O(\log n)\)，其中 \(n\) 是元素的数量。
>
> #### 基本用法
>
> ```cpp
> #include <algorithm>
> #include <vector>
> #include <iostream>
> 
> int main() {
>  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
> 
>  int value = 5;
> 
>  // 在已排序的范围内进行二分查找
>  bool found = std::binary_search(vec.begin(), vec.end(), value);
> 
>  if (found) {
>      std::cout << "Found " << value << " in the vector." << std::endl;
>  } else {
>      std::cout << "Did not find " << value << " in the vector." << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> ### 自定义比较函数
>
> `binary_search` 也可以使用自定义的比较函数。
>
> ```cpp
> #include <algorithm>
> #include <vector>
> #include <iostream>
> 
> bool compare(int a, int b) {
>  return a > b;  // 用于降序排序的比较函数
> }
> 
> int main() {
>  std::vector<int> vec = {9, 8, 7, 6, 5, 4, 3, 2, 1};
> 
>  int value = 5;
> 
>  // 在降序排序的范围内进行二分查找
>  bool found = std::binary_search(vec.begin(), vec.end(), value, compare);
> 
>  if (found) {
>      std::cout << "Found " << value << " in the vector." << std::endl;
>  } else {
>      std::cout << "Did not find " << value << " in the vector." << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> ### 注意事项
>
> 1. **`sort` 算法**：在使用 `sort` 前，确保包含 `<algorithm>` 头文件，并且传递的是有效的迭代器范围。`sort` 默认使用 `<` 运算符进行比较。
> 2. **`binary_search` 算法**：在使用 `binary_search` 前，确保包含 `<algorithm>` 头文件，并且数据已经排序。否则，结果是未定义的。`binary_search` 默认使用 `<` 运算符进行比较。
> 3. **效率**：`sort` 的时间复杂度为 \(O(n \log n)\)，`binary_search` 的时间复杂度为 \(O(\log n)\)。对于较大的数据集，使用 `binary_search` 前务必先排序。
>
> 通过结合使用 `sort` 和 `binary_search`，可以高效地对数据进行排序和搜索，适用于许多需要快速查询的大数据处理场景。



> 在 C++ 中，逗号运算符 (`,` operator) 是一个序列点，允许在一个语句中执行多个表达式，并保证从左到右的求值顺序。逗号运算符返回最后一个表达式的值。虽然它在代码中不常见，但在某些情况下非常有用。
>
> ### 基本用法
>
> 逗号运算符将多个表达式串联起来，所有表达式会依次求值，但只返回最后一个表达式的结果。
>
> #### 示例
>
> ```cpp
> #include <iostream>
> 
> int main() {
>  int a = 1, b = 2, c;
> 
>  c = (a = a + 1, b = b + 2, a + b);  // 使用逗号运算符
> 
>  std::cout << "a: " << a << std::endl;  // 输出 a: 2
>  std::cout << "b: " << b << std::endl;  // 输出 b: 4
>  std::cout << "c: " << c << std::endl;  // 输出 c: 6
> 
>  return 0;
> }
> ```
>
> 在上述示例中，`c` 的值是由逗号运算符中最后一个表达式 `a + b` 的结果决定的，而 `a` 和 `b` 的值在之前的表达式中被修改。
>
> ### 在循环中的使用
>
> 逗号运算符在 `for` 循环中很有用，尤其是在需要初始化或更新多个变量的情况下。
>
> #### 示例
>
> ```cpp
> #include <iostream>
> 
> int main() {
>  for (int i = 0, j = 10; i < j; i++, j--) {
>      std::cout << "i: " << i << ", j: " << j << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> 在这个示例中，`for` 循环的初始化部分和更新部分都使用了逗号运算符，使得我们可以同时操作 `i` 和 `j` 两个变量。
>
> ### 注意事项
>
> 1. **优先级**: 逗号运算符的优先级较低，因此在复杂表达式中使用时需要注意括号，以确保正确的求值顺序。
> 2. **副作用**: 逗号运算符会依次求值其操作数，所有副作用都会按顺序发生。
> 3. **代码可读性**: 虽然逗号运算符在某些情况下很有用，但过度使用可能会降低代码的可读性。因此，应谨慎使用，并确保代码的清晰性。
>
> ### 总结
>
> 逗号运算符在 C++ 中可以用来在一个语句中执行多个表达式，并按从左到右的顺序求值，返回最后一个表达式的结果。它在需要同时处理多个表达式或变量的初始化和更新时特别有用。尽管如此，由于它的低优先级和潜在的可读性问题，应该谨慎使用。



```cpp
a[x,y]返回的是a[y]
```

根据逗号运算符的规则，`x,y`最后得到的数值是`y`



> 在 C++ 中，多维数组是一种常见的数据结构，用于表示具有多个维度的数据。常见的多维数组包括二维数组（矩阵）和三维数组（立方体），它们可以扩展到更多维度。多维数组在数值计算、图像处理和科学计算等领域中广泛使用。
>
> ### 多维数组的声明和初始化
>
> #### 二维数组
>
> 二维数组是最常见的多维数组，可以看作是一个数组的数组。
>
> ```cpp
> #include <iostream>
> 
> int main() {
>  // 声明一个 3x4 的二维数组
>  int arr[3][4] = {
>      {1, 2, 3, 4},
>      {5, 6, 7, 8},
>      {9, 10, 11, 12}
>  };
> 
>  // 访问和输出二维数组中的元素
>  for (int i = 0; i < 3; ++i) {
>      for (int j = 0; j < 4; ++j) {
>          std::cout << arr[i][j] << " ";
>      }
>      std::cout << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> #### 三维数组
>
> 三维数组是包含二维数组的数组，类似于立方体。
>
> ```cpp
> #include <iostream>
> 
> int main() {
>  // 声明一个 2x3x4 的三维数组
>  int arr[2][3][4] = {
>      {
>          {1, 2, 3, 4},
>          {5, 6, 7, 8},
>          {9, 10, 11, 12}
>      },
>      {
>          {13, 14, 15, 16},
>          {17, 18, 19, 20},
>          {21, 22, 23, 24}
>      }
>  };
> 
>  // 访问和输出三维数组中的元素
>  for (int i = 0; i < 2; ++i) {
>      for (int j = 0; j < 3; ++j) {
>          for (int k = 0; k < 4; ++k) {
>              std::cout << arr[i][j][k] << " ";
>          }
>          std::cout << std::endl;
>      }
>      std::cout << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> ### 使用 `std::array` 创建多维数组
>
> C++11 引入了 `std::array`，可以用来创建更安全和灵活的多维数组。
>
> ```cpp
> #include <iostream>
> #include <array>
> 
> int main() {
>  // 使用 std::array 声明一个 3x4 的二维数组
>  // 这里的第一个参数是std::array<int,4> 表示arr的元素类型是array
>  std::array<std::array<int, 4>, 3> arr = {{
>      {1, 2, 3, 4},
>      {5, 6, 7, 8},
>      {9, 10, 11, 12}
>  }};
> 
>  // 访问和输出二维数组中的元素
>  for (const auto& row : arr) {
>      for (const auto& elem : row) {
>          std::cout << elem << " ";
>      }
>      std::cout << std::endl;
>  }
> 
>  return 0;
> }
> ```
>
> ### 动态分配多维数组
>
> 对于需要在运行时确定大小的多维数组，可以使用动态内存分配。
>
> #### 动态分配二维数组
>
> ```cpp
> #include <iostream>
> 
> int main() {
>  int rows = 3;
>  int cols = 4;
> 
>  // 动态分配二维数组
>  int** arr = new int*[rows];
>  for (int i = 0; i < rows; ++i) {
>      arr[i] = new int[cols];
>  }
> 
>  // 初始化数组
>  int value = 1;
>  for (int i = 0; i < rows; ++i) {
>      for (int j = 0; j < cols; ++j) {
>          arr[i][j] = value++;
>      }
>  }
> 
>  // 访问和输出二维数组中的元素
>  for (int i = 0; i < rows; ++i) {
>      for (int j = 0; j < cols; ++j) {
>          std::cout << arr[i][j] << " ";
>      }
>      std::cout << std::endl;
>  }
> 
>  // 释放动态分配的内存
>  for (int i = 0; i < rows; ++i) {
>      delete[] arr[i];
>  }
>  delete[] arr;
> 
>  return 0;
> }
> ```
>
> ### 总结
>
> 多维数组在 C++ 中提供了表示和操作多维数据的强大工具。根据需求，可以选择使用静态数组、`std::array` 或动态数组。静态数组适合大小固定的情况，`std::array` 提供了更安全和灵活的接口，而动态数组则适合需要在运行时确定大小的情况。通过合理选择和使用多维数组，可以有效地处理复杂的数据结构和计算任务。





> `std::vector` 是 C++ 标准模板库（STL）中的一个动态数组容器，定义在 `<vector>` 头文件中。它提供了一个灵活、动态调整大小的数组，可以存储任意类型的元素。`std::vector` 是常用的容器之一，因其高效的随机访问和动态调整大小能力而广受欢迎。
>
> ### 特性
>
> 1. **动态大小**: `std::vector` 可以根据需要动态地增长或缩小大小。
> 2. **随机访问**: 提供常数时间复杂度的随机访问（通过索引）。
> 3. **自动管理内存**: 自动管理其存储的内存，避免手动内存管理带来的复杂性和错误。
> 4. **支持迭代器**: 支持 STL 迭代器，可以与算法库无缝集成。
> 5. **自动扩展**: 当向 `std::vector` 中添加元素超过其容量时，它会自动扩展容量。
>
> ### 基本用法
>
> #### 引入头文件
>
> ```cpp
> #include <vector>
> ```
>
> #### 声明和初始化
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> int main() {
>     // 声明一个空的 vector
>     std::vector<int> vec;
> 
>     // 使用初始化列表初始化 vector
>     std::vector<int> vec2 = {1, 2, 3, 4, 5};
> 
>     // 使用特定大小和初始值初始化 vector
>     std::vector<int> vec3(5, 10);  // 包含 5 个元素，每个元素的值为 10
> 
>     // 使用范围初始化 vector
>     std::vector<int> vec4(vec2.begin(), vec2.end());
> 
>     return 0;
> }
> ```
>
> #### 添加和删除元素
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> int main() {
>     std::vector<int> vec;
> 
>     // 添加元素
>     vec.push_back(1);
>     vec.push_back(2);
>     vec.push_back(3);
> 
>     // 访问元素
>     std::cout << "First element: " << vec[0] << std::endl;
>     std::cout << "Second element: " << vec.at(1) << std::endl;  // 使用 at() 方法进行边界检查
> 
>     // 删除元素
>     vec.pop_back();
> 
>     std::cout << "Vector size after pop_back: " << vec.size() << std::endl;
> 
>     return 0;
> }
> ```
>
> #### 遍历元素
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> int main() {
>     std::vector<int> vec = {1, 2, 3, 4, 5};
> 
>     // 使用范围 for 循环遍历
>     for (const auto& elem : vec) {
>         std::cout << elem << " ";
>     }
>     std::cout << std::endl;
> 
>     // 使用迭代器遍历
>     for (auto it = vec.begin(); it != vec.end(); ++it) {
>         std::cout << *it << " ";
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> #### 其他常用操作
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> int main() {
>     std::vector<int> vec = {1, 2, 3, 4, 5};
> 
>     // 获取大小和容量
>     std::cout << "Size: " << vec.size() << std::endl;
>     std::cout << "Capacity: " << vec.capacity() << std::endl;
> 
>     // 检查是否为空
>     if (!vec.empty()) {
>         std::cout << "Vector is not empty" << std::endl;
>     }
> 
>     // 清空 vector
>     vec.clear();
>     std::cout << "Size after clear: " << vec.size() << std::endl;
> 
>     // 重新分配空间
>     vec.reserve(10);
>     std::cout << "Capacity after reserve: " << vec.capacity() << std::endl;
> 
>     // 插入元素
>     vec.insert(vec.begin(), 0);  // 在开头插入 0
>     vec.insert(vec.end(), 6);    // 在结尾插入 6
> 
>     // 删除特定位置的元素
>     vec.erase(vec.begin());  // 删除第一个元素
> 
>     // 输出结果
>     for (const auto& elem : vec) {
>         std::cout << elem << " ";
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> ### 总结
>
> `std::vector` 是 C++ 中功能强大的动态数组容器，提供了灵活的大小调整、高效的随机访问和自动内存管理。它适用于需要频繁插入、删除和随机访问元素的场景。通过掌握 `std::vector` 的使用，可以大大提高 C++ 程序的开发效率和代码的可维护性。





> 迭代器是 C++ 标准模板库（STL）中用于遍历容器元素的对象。迭代器提供了一种统一的方式来访问容器中的元素，无论容器的类型是什么，都可以使用相同的语法来进行遍历。迭代器的设计使得容器和算法可以解耦，提高了代码的灵活性和可复用性。
>
> ### 基本用法
>
> #### 迭代器类型
>
> 不同类型的容器有不同类型的迭代器，但它们通常具有相似的接口和用法。以下是常见的迭代器类型：
>
> - **begin()**: 返回指向容器第一个元素的迭代器。
> - **end()**: 返回指向容器末尾的迭代器（不包含末尾元素的下一个位置）。
>
> #### 示例
>
> ```cpp
> #include <iostream>
> #include <vector>
> 
> int main() {
>     std::vector<int> vec = {1, 2, 3, 4, 5};
> 
>     // 使用迭代器遍历 vector
>     for (auto it = vec.begin(); it != vec.end(); ++it) {
>         std::cout << *it << " ";  // 输出当前迭代器指向的元素
>     }
>     std::cout << std::endl;
> 
>     return 0;
> }
> ```
>
> ### 迭代器操作
>
> #### 解引用
>
> 使用 `*` 运算符可以获取迭代器指向的元素的值。
>
> ```cpp
> auto it = vec.begin();
> std::cout << *it << std::endl;  // 输出第一个元素的值
> ```
>
> #### 自增
>
> 使用 `++` 运算符可以将迭代器移动到容器中的下一个元素。
>
> ```cpp
> auto it = vec.begin();
> ++it;  // 将迭代器移动到第二个元素
> ```
>
> #### 比较
>
> 可以使用 `==` 或 `!=` 运算符来比较两个迭代器是否相等。
>
> ```cpp
> auto it1 = vec.begin();
> auto it2 = vec.end();
> if (it1 == it2) {
>     std::cout << "Iterators are equal" << std::endl;
> } else {
>     std::cout << "Iterators are not equal" << std::endl;
> }
> ```
>
> #### 其他操作
>
> 迭代器还支持许多其他操作，如算术运算、指针算术运算等，使得在容器中进行元素访问更加灵活。
>
> ### 迭代器失效
>
> 在对容器进行修改时，可能会导致迭代器失效。迭代器失效意味着它们不再指向有效的元素或位置。通常情况下，插入和删除操作会导致迭代器失效。
>
> ### 迭代器的类型
>
> 不同容器类型（如 `vector`、`list`、`map` 等）的迭代器具有不同的特性和行为。例如，`vector` 和 `deque` 支持随机访问迭代器，而 `list` 支持双向迭代器。了解容器的迭代器类型对正确使用迭代器非常重要。
>
> ### 总结
>
> 迭代器是 C++ 中一种强大的工具，用于遍历容器中的元素。它提供了一种统一的接口，使得容器和算法可以解耦，并且提供了一种灵活的方式来访问容器中的元素。通过掌握迭代器的基本用法和特性，可以编写更加灵活和高效的代码。