## Cpp复习 第四章	第五章

在 C++ 编程中，控制流结构是指管理代码执行顺序的方式。主要有三种控制流结构：顺序结构、循环结构和选择结构。下面是对每种结构的详细介绍：

### 顺序结构

顺序结构是最基本的控制流结构，它按照代码编写的顺序逐行执行。所有的程序都至少包含一些顺序结构。每个语句按出现的顺序执行，直到程序结束或遇到其他控制流结构。

**示例**：

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int b = 10;
    int sum = a + b; // 按顺序执行
    cout << "Sum: " << sum << endl; // 按顺序执行
    return 0;
}
```

在这个例子中，变量 `a` 和 `b` 被依次赋值，然后计算它们的和，最后输出结果。

### 选择结构

选择结构允许程序根据条件选择不同的路径执行。主要有三种选择结构：`if` 语句、`if-else` 语句和 `switch` 语句。

1. **`if` 语句**：

   ```cpp
   if (condition) {
       // 当条件为真时执行的代码
   }
   ```

2. **`if-else` 语句**：

   ```cpp
   if (condition) {
       // 当条件为真时执行的代码
   } else {
       // 当条件为假时执行的代码
   }
   ```

3. **`switch` 语句**：

   ```cpp
   switch (expression) {
       case value1:
           // 当表达式等于 value1 时执行的代码
           break;
       case value2:
           // 当表达式等于 value2 时执行的代码
           break;
       default:
           // 当表达式不匹配任何 case 时执行的代码
   }
   ```

**示例**：

```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;

    if (number > 0) {
        cout << "The number is positive." << endl;
    } else if (number < 0) {
        cout << "The number is negative." << endl;
    } else {
        cout << "The number is zero." << endl;
    }

    switch (number) {
        case 1:
            cout << "You entered one." << endl;
            break;
        case 2:
            cout << "You entered two." << endl;
            break;
        default:
            cout << "You entered a number other than one or two." << endl;
    }

    return 0;
}
```

### 循环结构

循环结构允许程序重复执行一段代码，直到满足特定条件。主要有三种循环结构：`for` 循环、`while` 循环和 `do-while` 循环。

1. **`for` 循环**：

   ```cpp
   for (initialization; condition; increment) {
       // 循环体
   }
   ```

2. **`while` 循环**：

   ```cpp
   while (condition) {
       // 循环体
   }
   ```

3. **`do-while` 循环**：

   ```cpp
   do {
       // 循环体
   } while (condition);
   ```

**示例**：

```cpp
#include <iostream>
using namespace std;

int main() {
    // for 循环
    for (int i = 1; i <= 5; ++i) {
        cout << "For loop iteration: " << i << endl;
    }

    // while 循环
    int j = 1;
    while (j <= 5) {
        cout << "While loop iteration: " << j << endl;
        ++j;
    }

    // do-while 循环
    int k = 1;
    do {
        cout << "Do-while loop iteration: " << k << endl;
        ++k;
    } while (k <= 5);

    return 0;
}
```

### 总结

- **顺序结构**：代码按顺序逐行执行。
- **选择结构**：根据条件选择不同的路径执行（`if`、`if-else`、`switch`）。
- **循环结构**：重复执行代码块直到满足特定条件（`for`、`while`、`do-while`）。

通过组合使用这三种控制流结构，可以编写出功能丰富且灵活的 C++ 程序。

存在两种组合方式：控制语句嵌套和控制语句堆叠



在 C++ 编程中，控制语句的嵌套和堆叠是常见的技术，用于实现复杂的控制逻辑。以下是对这两种技术的详细解释及示例：

### 控制语句嵌套

控制语句嵌套是指一个控制语句（如 if、for、while 等）位于另一个控制语句的内部。这种结构允许更复杂的条件判断和循环执行。

#### 示例：

**嵌套的 if 语句**：

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int b = 10;

    if (a < b) {
        if (a > 0) {
            cout << "a is positive and less than b." << endl;
        } else {
            cout << "a is non-positive and less than b." << endl;
        }
    } else {
        cout << "a is not less than b." << endl;
    }

    return 0;
}
```

**嵌套的 for 循环**：

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 2; ++j) {
            cout << "i = " << i << ", j = " << j << endl;
        }
    }

    return 0;
}
```

### 控制语句堆叠

控制语句堆叠是指多个控制语句依次执行，没有相互嵌套。这种结构有助于实现一系列独立的条件判断或循环执行。

#### 示例：

**堆叠的 if 语句**：

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int b = 10;

    if (a < b) {
        cout << "a is less than b." << endl;
    }

    if (a > 0) {
        cout << "a is positive." << endl;
    }

    if (b > 0) {
        cout << "b is positive." << endl;
    }

    return 0;
}
```

**堆叠的 for 循环**：

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 3; ++i) {
        cout << "First loop iteration: i = " << i << endl;
    }

    for (int j = 1; j <= 2; ++j) {
        cout << "Second loop iteration: j = " << j << endl;
    }

    return 0;
}
```

### 控制语句嵌套和堆叠的综合示例

在实际应用中，经常会同时使用嵌套和堆叠的控制语句来实现复杂的逻辑。

#### 综合示例：

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 2; ++j) {
            cout << "Nested loop: i = " << i << ", j = " << j << endl;
        }
    }

    if (true) {
        cout << "First condition met." << endl;
    }

    if (true) {
        for (int k = 1; k <= 2; ++k) {
            cout << "Stacked and nested loop: k = " << k << endl;
        }
    }

    return 0;
}
```

### 总结

- **控制语句嵌套**：一个控制语句内部包含另一个控制语句，用于实现更复杂的逻辑。
- **控制语句堆叠**：多个控制语句依次执行，用于处理一系列独立的条件或循环。

通过合理地使用嵌套和堆叠的控制语句，可以编写出逻辑清晰、功能强大的程序。理解并掌握这两种技术对于编写复杂的 C++ 程序是非常重要的。



MAX与MIN存在于头文件<climits>

列表初始化器：

```cpp
int val={1}	or	int val{1}
```



在 C++ 中，循环语句、`switch` 语句以及 `break` 和 `continue` 语句是控制程序执行流的重要工具。以下是对这些语句的详细介绍及示例：

### 循环语句

循环语句用于重复执行一段代码，直到满足特定条件。C++ 中主要有三种循环语句：`for` 循环、`while` 循环和 `do-while` 循环。

1. **`for` 循环**：
   `for` 循环通常用于知道循环次数的情况。

   ```cpp
   for (initialization; condition; increment) {
       // 循环体
   }
   ```

   **示例**：

   ```cpp
   #include <iostream>
   using namespace std;
   
   int main() {
       for (int i = 0; i < 5; ++i) {
           cout << "i = " << i << endl;
       }
       return 0;
   }
   ```

2. **`while` 循环**：
   `while` 循环在执行循环体之前检查条件。

   ```cpp
   while (condition) {
       // 循环体
   }
   ```

   **示例**：

   ```cpp
   #include <iostream>
   using namespace std;
   
   int main() {
       int i = 0;
       while (i < 5) {
           cout << "i = " << i << endl;
           ++i;
       }
       return 0;
   }
   ```

3. **`do-while` 循环**：
   `do-while` 循环先执行一次循环体，然后检查条件。

   ```cpp
   do {
       // 循环体
   } while (condition);
   ```

   **示例**：

   ```cpp
   #include <iostream>
   using namespace std;
   
   int main() {
       int i = 0;
       do {
           cout << "i = " << i << endl;
           ++i;
       } while (i < 5);
       return 0;
   }
   ```

### `switch` 语句

`switch` 语句用于根据一个表达式的值来执行不同的代码块。它是多重选择结构的一个实现。

```cpp
switch (expression) {
    case constant1:
        // 当 expression 等于 constant1 时执行的代码
        break;
    case constant2:
        // 当 expression 等于 constant2 时执行的代码
        break;
    // 可以有多个 case 子句
    default:
        // 当 expression 不匹配任何 case 时执行的代码
}
```

**示例**：

```cpp
#include <iostream>
using namespace std;

int main() {
    int day = 3;

    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        default:
            cout << "Invalid day" << endl;
    }

    return 0;
}
```

### `break` 语句

`break` 语句用于立即终止所在的循环或 `switch` 语句，跳出循环或 `switch` 块。

**示例（在循环中使用）**：

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 0; i < 10; ++i) {
        if (i == 5) {
            break; // 终止循环
        }
        cout << "i = " << i << endl;
    }
    return 0;
}
```

**示例（在 `switch` 语句中使用）**：

```cpp
#include <iostream>
using namespace std;

int main() {
    int number = 2;

    switch (number) {
        case 1:
            cout << "Number is 1" << endl;
            break;
        case 2:
            cout << "Number is 2" << endl;
            break;
        default:
            cout << "Number is neither 1 nor 2" << endl;
    }

    return 0;
}
```

### `continue` 语句

`continue` 语句用于跳过当前循环迭代中的剩余代码，并立即开始下一次迭代。它只能用于循环中。

**示例**：

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            continue; // 跳过当前迭代的剩余代码
        }
        cout << "i = " << i << endl;
    }
    return 0;
}
```

### 总结

- **循环语句**：`for`、`while` 和 `do-while` 用于重复执行代码块。
- **`switch` 语句**：用于根据表达式的值选择执行不同的代码块。
- **`break` 语句**：用于终止循环或 `switch` 语句。
- **`continue` 语句**：用于跳过当前循环迭代中的剩余代码，并立即开始下一次迭代。

