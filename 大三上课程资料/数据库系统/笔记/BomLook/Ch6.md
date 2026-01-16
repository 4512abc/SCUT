# Ch6

## Relational Algebra（关系代数）
> [!important]
>
> 关系代数：一个过程化的语言
>
> - 六个基本运算符
>
>   | 类型                         | 说明 |
>   | ---------------------------- | ---- |
>   | select ($\sigma$)            |      |
>   | project ($\prod$)            |      |
>   | union ($\cup$)               |      |
>   | set difference ($-$)         |      |
>   | cartesian product ($\times$) |      |
>   | rename ($\rho$)              |      |
>
> - 输入：两个关系。输出：一个关系

## Select Operation – Example（选择操作——示例）

## Select Operation（选择操作）
> [!important]
>
> $\sigma$ select 操作
>
> - 定义：$\sigma_p(r)=\{t | t \in r \text{ and } p(t)\}$，表示选择 $r$ 中满足 $p$ 谓词的所有元组 $t$
>
>   - $p$ 称为选择谓词，命题演算公式，可以由 $\and \or \urcorner$ 等连接，格式为：
>
>     ```
>     <attribute> op <attribute> or <constant>
>     ```
>
>     其中 op 表示运算符，可以是 $=,\ne,>,<,\leq,\geq$

## Project Operation – Example（投影操作——示例）
## Project Operation（投影操作）
> [!important]
>
> $\prod$ project 操作
>
> - 定义：$\prod_{A_1,A_2...A_k}(r)$，其中 $A_1,A_2$ 等是属性名称，$r$ 是关系名称
> - 结果：选择 $k$ 列数据，删除未列出的属性列，且结构中去除重复行（原因：关系是集合）

## Union Operation – Example（并集操作——示例）

## Union Operation（并集操作）
> [!important]
>
> $\cup$ union 操作
>
> - 定义：$r \cup s =\{t|t \in r \text{ or } t \in s\}$
> - 要求：
>   - $r$ 和 $s$ 的元组长度相等，即属性数量一致
>   - 属性的值域兼容

## Set difference of two relations（两个关系的差集）

## Set Difference Operation（差集操作）
> [!important]
>
> $-$ set difference 操作
>
> - 定义：$r-s=\{t|t \in r \text{ and } t \in s\}$
> - 要求：关系兼容
>   - $r$ 和 $s$ 的元组长度相等，即属性数量一致
>   - 属性的值域兼容

## Cartesian-Product Operation – Example（笛卡尔积操作——示例）

## Cartesian-Product Operation（笛卡尔积操作）
> [!important]
>
> $\times$ Cartesian-Product 操作
>
> - 定义：$r \times s = \{ t q|t \in r \text{ and } q \in s\}$
> - 要求：假定两个关系的属性集合不相交，若相交，则需要使用重命名运算符

## Composition of Operations（操作组合）
## Rename Operation（重命名操作）
> [!important]
>
> $\rho$ rename 操作
>
> - 定义：$\rho_{x(A_1,A_2...A_n)}(E)$，其中 $A_1,A_2...A_n$ 为属性名称，$E$ 为关系代数表达式，$x$ 表示新名称，返回表达式 $E$ 的结果。
> - 作用：为关系代数表达式的结果进行命名，便于引用
> - 允许一个关系有多个名称

## Example Query（查询示例）
## Example Queries（查询示例）
## Formal Definition（形式化定义）

- A basic expression in the relational algebra consists of either one of the following:（关系代数的基本表达式为以下之一）
  1. A relation in the database（数据库中的一个关系）
  2. A constant relation（常量关系）
- Let E1 and E2 be relational-algebra expressions; the following are all relational-algebra expressions:（设E1和E2为关系代数表达式，则以下均为关系代数表达式）
  1. E1 ∪ E2（并集）
  2. E1 – E2（差集）
  3. E1 × E2（笛卡尔积）
  4. σₚ(E1)，P is a predicate on attributes in E1（选择操作，P为E1属性上的谓词）
  5. Πₛ(E1)，S is a list consisting of some of the attributes in E1（投影操作，S为E1的部分属性列表）
  6. ρₓ(E1)，x is the new name for the result of E1（重命名操作，x为E1结果的新名称）

> [!important]
>
> 关系代数的基本表达式：
>
> - 数据库中的一个关系
> - 常量关系（？）
>
> 分类：设$E1$和$E2$为关系代数表达式，则以下均为关系代数表达式
>
> | 分类           | 说明                                   |
> | -------------- | -------------------------------------- |
> | $E1\cup E2$    | 并集                                   |
> | $E1-E2$        | 差集                                   |
> | $E1 \times E2$ | 笛卡尔积                               |
> | $\sigma_p(E1)$ | 选择操作，$P$ 为 $E1$ 上关于属性的谓词 |
> | $\prod_s(E1)$  | 投影操作，$S$ 为 $E1$ 的部分属性列表   |
> | $\rho_x(E1)$   | 重命名操作，$x$ 为 $E1$ 结果的新名称   |

## Additional Operations（附加操作）
> [!important]
>
> 附加操作，不增加表达能力，但是可以简化常用查询
>
> 分类：
>
> - Set intersection（交集）
> - Natural join（自然连接）
> - Assignment（赋值）
> - Outer join（外连接）
> - Division（除法）

## Set-Intersection Operation（交集操作）
- Notation: r ∩ s（符号：r ∩ s）
- Defined as: r ∩ s = {t | t ∈ r and t ∈ s}（定义：同时属于r和s的元组集合）
- Assume:（假设）
  - r, s have the same arity（r和s元组长度相同）
  - attributes of r and s are compatible（属性值域兼容）
- Note: r ∩ s = r – (r – s)（注：交集可通过差集推导）

> [!important]
>
> $\cap$ 交集操作
>
> - 定义：$r \cap s = \{t|t \in r \text{ and } t \in s\}$
> - 要求：关系兼容
>   - $r$ 和 $s$ 的元组长度相等，即属性数量一致
>   - 属性的值域兼容
> - 等价于：$r-(r-s)$

## Set-Intersection Operation – Example（交集操作——示例）
## Natural-Join Operation（自然连接操作）
> [!important]
>
> $\bowtie$ natural join 操作
>
> - 定义：设 $r$ 和 $s$ 分别为模式 $R$ 和 $S$ 上的关系，$r \bowtie s$ 是 $R \cup S$ 上的关系：
>   - Consider each pair of tuples tr from r and ts from s.
>   - If tr and ts have the same value on each of the attributes in R ∩ S, add a tuple t to the result.
>   - t has the same value as tr on r, and the same value as ts on s.
> - 满足交换律和结合律
>
> $\theta$ 连接操作
>
> - 定义：$r \bowtie_{\theta} s = \sigma_{\theta}(r \times s)$

### Natural Join Example（自然连接示例）
### Natural Join and Theta Join（自然连接与θ连接）
### Assignment Operation（赋值操作）
> [!important]
>
> $\larr$ assignment 操作
>
> - 为复杂查询提供便捷的表达
> - 原因：查询可能包含了一系列赋值语句，最终是返回结果的表达式
> - 赋值对象必须是临时关系变量

### Outer Join（外连接）
- An extension of the join operation that avoids loss of information.（连接操作的扩展，避免信息丢失）
- Computes the join and then adds tuples from one relation that do not match tuples in the other relation to the result.（先执行连接，再将未匹配的元组添加到结果）
- Uses null values:（使用空值）
  - null signifies that the value is unknown or does not exist（null表示值未知或不存在）
  - All comparisons involving null are (roughly speaking) false by definition.（所有涉及null的比较结果大致为false）
- We shall study precise meaning of comparisons with nulls later.（后续将详细介绍null比较的精确规则）

> [!important]
>
> outer join 操作
>
> - 连接操作的扩展，目的是避免信息丢失
>
> - 操作：先执行连接，再将未匹配的元组添加到结果中，未匹配的元组，部分属性值使用 null 值进行替代
>
> - 分类：
>
>   左外连接：$\ltimes$：保留左关系所有元组，右关系匹配不到填 `NULL`
>
>   右外连接：$\rtimes$：保留右关系所有元组，左关系匹配不到填 `NULL`
>
>   全外连接：$\bowtie_+$：保留左右关系所有元组，未匹配项填 `NULL`
>



### Outer Join – Example（外连接——示例）
### Outer Join – Example（外连接——示例）
### Outer Join – Example（外连接——示例）
### Null Values（空值）
### Null Values（空值）
> [!important]
>
> null
>
> - 表示位置或者不存在
> - 任何**包含 null 的算法表达式**，结果为 null
> - **聚合函数忽略 null 值**
> - **去重和分组**时，null 值视为普通值，null 值都是相等的
> - $P$ 的结果为 unknown 时，视为 false（lIn SQL “*P* **is unknown**” evaluates to true if predicate *P* evaluates to *unknown*）

### Division Operation（除法操作）
> [!important]
>
> $\div$ 
>
> - 定义：设 $r(R)$ 和 $s(S)$ 为关系，满足：
>
>   - $R=(A_1,A_2...A_m,B_1,B_2...B_n)$
>   - $S=(B_1,B_2...B_n)$
>
>   $r \div s = \{ t | t \in \prod_{R-S}(r) \and \forall u \in s(tu \in r)\}$
>
>   注意 $\forall u \in s(tu \in r)$
>
> - 性质：$q= r \div s$ 是满足 $q \times s \subseteq r$ 的最大关系
>
> - 基本运算符定义：
>
>   $r \div s = \prod_{R-S}(r)- \prod_{R-S}((\prod_{R-S}(r) \times s)-\prod_{R-S,S}(r))$
>
>   解释：
>
>   - $\prod_{R-S,S}(r)$：将 $r$ 的属性进行重排
>   - $\prod_{R-S}(r) \times s$：列举出 $r$ 和 $s$ 的所有可能组合
>   - 上述两者相减，得到一些没有的组合情况：$((\prod_{R-S}(r) \times s)-\prod_{R-S,S}(r))$。投影之后保留 $R-S$（$\prod_{R-S}$）。

## Division Operation – Example（除法操作——示例）
## Another Division Example（另一个除法示例）
## Division Operation (Cont.)（除法操作（续））
## Extended Relational-Algebra-Operations（扩展关系代数操作）
> [!important]
>
> Generalized Projection（广义投影）
>
> - 允许投影列表中使用算术函数
> - 语法：$\prod_{F_1,F_2...F_n}(E)$，其中 $F_1,F_2...F_n$ 为算术表达式，包含常量和 $E$ 的属性，$E$ 为关系代数表达式
>
> Aggregate Functions（聚合函数）
>
> - 接收一组值，返回单个结果值
> - 语法：$_{G_1,G_2...G_n}\mathcal{G}_{F_1(A_1),F_2(A_2),F_3(A_3)...F_m(A_m)}(E)$，$E$ 为关系代数表达式，$G_i$ 表示分组属性列表，可为空，$F_i$ 表示聚合函数，$A_i$ 表示属性名，结果共有 $n+m$ 个属性
> - 特点：聚合函数的属性没有名称，可以通过重命名操作指定。
>
> ![image-20251222165447013](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222165447013.png)
>
> ![image-20251222165458556](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222165458556.png)

## Generalized Projection（广义投影）
## Aggregate Functisons and Operations（聚合函数与聚合操作）
## Aggregate Operation – Example（聚合操作——示例）
## Aggregate Operation – Example（聚合操作——示例）
## Aggregate Functions (Cont.)（聚合函数（续））
## Modification of the Database（数据库修改）
> [!note]
>
> - Deletion（删除）$r \larr r-E$
> - Insertion（插入）$r \larr r \cup E$
> - Updating（更新）$r \larr \prod_{F_1...F_i...F_n}(r)$
>   - $F_i$ 既可以是属性，也可以是包含 $r$的属性的表达式
>
> 以上操作均可通过赋值运算符实现

## Modification of the Database（数据库修改）
## Multiset Relational Algebra（多集关系代数）
> [!note]
>
> 多重集关系代数
>
> - 纯关系代数：去除所有重复元组。而多重集关系代数保留重复元组，这与 SQL 的语法等价（SQL 保留重复，最初是未来效率，现在已经成为一种特征）

## SQL and Relational Algebra（SQL与关系代数）
## SQL and Relational Algebra（SQL与关系代数）
